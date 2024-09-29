#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <filesystem>
#include <QMatrix4x4>

#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "QtEngine/Macro.h"
#include "QtEngine/OpenGL/Mesh.h"

#include "Eigen/Dense"

namespace QtEngine
{
class EigenUtility
{
public:
  SINGLETON(EigenUtility);

  static QMatrix4x4 Eigen2Qt(Eigen::Matrix<float, 4, 4, Eigen::RowMajor> mat);
};

}  // namespace QtEngine