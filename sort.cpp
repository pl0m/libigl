#include "sort.h"

#include <algorithm>
#include "reorder.h"

template <typename T>
IGL_INLINE void igl::sort(
  const Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic> & X,
  const int dim,
  const bool ascending,
  Eigen::Matrix<T,Eigen::Dynamic,Eigen::Dynamic> & Y,
  Eigen::MatrixXi & IX)
{
  // dim must be 2 or 1
  assert(dim == 1 || dim == 2);
  // Resize output
  Y.resize(X.rows(),X.cols());
  IX.resize(X.rows(),X.cols());
  // idea is to process each column (or row) as a std vector
  // get number of columns (or rows)
  int num_outer = (dim == 1 ? X.cols() : X.rows() );
  // get number of rows (or columns)
  int num_inner = (dim == 1 ? X.rows() : X.cols() );
  // loop over columns (or rows)
  for(int i = 0; i<num_outer;i++)
  {
    // Unsorted index map for this column (or row)
    std::vector<size_t> index_map(num_inner);
    std::vector<T> data(num_inner);
    for(int j = 0;j<num_inner;j++)
    {
      if(dim == 1)
      {
        data[j] = X(j,i);
      }else
      {
        data[j] = X(i,j);
      }
    }
    // sort this column (or row)
    sort<T>(
      data,
      ascending,
      data,
      index_map);
    // Copy into Y and IX
    for(int j = 0;j<num_inner;j++)
    {
      if(dim == 1)
      {
        Y(j,i) = data[j];
        IX(j,i) = index_map[j];
      }else
      {
        Y(i,j) = data[j];
        IX(i,j) = index_map[j];
      }
    }
  }
}

// Comparison struct used by sort
// http://bytes.com/topic/c/answers/132045-sort-get-index
namespace igl{
  template<class T> struct index_cmp
  {
    index_cmp(const T arr) : arr(arr) {}
    bool operator()(const size_t a, const size_t b) const
    {
      return arr[a] < arr[b];
    }
    const T arr;
  };
}

template <class T>
IGL_INLINE void igl::sort(
  const std::vector<T> & unsorted,
  const bool ascending,
  std::vector<T> & sorted,
  std::vector<size_t> & index_map)
{
  // Original unsorted index map
  index_map.resize(unsorted.size());
  for(size_t i=0;i<unsorted.size();i++)
  {
    index_map[i] = i;
  }
  // Sort the index map, using unsorted for comparison
  sort(
    index_map.begin(),
    index_map.end(),
    igl::index_cmp<const std::vector<T>& >(unsorted));

  // if not ascending then reverse
  if(!ascending)
  {
    std::reverse(index_map.begin(),index_map.end());
  }
  // make space for output without clobbering
  sorted.resize(unsorted.size());
  // reorder unsorted into sorted using index map
  igl::reorder(unsorted,index_map,sorted);
}

#ifndef IGL_HEADER_ONLY
// Explicit template specialization
#endif
