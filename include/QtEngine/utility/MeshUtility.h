#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "QtEngine/Macro.h"
#include "QtEngine/OpenGL/Mesh.h"

namespace QtEngine
{
class MeshUtility
{
public:
  SINGLETON(MeshUtility);

  static std::vector<QtEngine::Mesh> Read(std::string path);

private:
  void processNode(aiNode* node, const aiScene* scene, std::vector<QtEngine::Mesh>& models);
  void processMesh(aiMesh* mesh, const aiScene* scene, QtEngine::Mesh& model);
};

}  // namespace QtEngine