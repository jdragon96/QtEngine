#include <QtEngine/utility/EigenUtility.h>

using namespace QtEngine;

QMatrix4x4 EigenUtility::Eigen2Qt(Eigen::Matrix<float, 4, 4, Eigen::RowMajor> mat)
{
  return QMatrix4x4(mat.data());
}