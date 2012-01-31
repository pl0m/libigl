#ifndef IGL_SUM_H
#define IGL_SUM_H
#include "igl_inline.h"
#define EIGEN_YES_I_KNOW_SPARSE_MODULE_IS_NOT_STABLE_YET
#include <Eigen/Sparse>

namespace igl
{
  // Note: If your looking for dense matrix matlab like sum for eigen matrics
  // just use:
  //   M.colwise().sum() or M.rowwise().sum()
  // 

  // Sum the columns or rows of a sparse matrix
  // Templates:
  //   T  should be a eigen sparse matrix primitive type like int or double
  // Inputs:
  //   X  m by n sparse matrix
  //   dim  dimension along which to sum (1 or 2)
  // Output:
  //   S  n-long sparse vector (if dim == 1) 
  //   or
  //   S  m-long sparse vector (if dim == 2)
  template <typename T>
  IGL_INLINE void sum(
    const Eigen::SparseMatrix<T>& X, 
    const int dim,
    Eigen::SparseVector<T>& S);
}

#ifdef IGL_HEADER_ONLY
#  include "sum.cpp"
#endif

#endif
