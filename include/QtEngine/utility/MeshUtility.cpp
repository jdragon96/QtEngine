#include <QtEngine/utility/MeshUtility.h>

using namespace QtEngine;

std::vector<QtEngine::Mesh> MeshUtility::Read(std::string path)
{
  std::vector<QtEngine::Mesh> totalObject;

  // 1. 씬 데이터 읽기
  Assimp::Importer importer;
  const aiScene* scene =
      importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

  // 2. 에러 체크
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)  // if is Not Zero
  {
    std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
    // return totalObject;
  }
  std::string directory = path.substr(0, path.find_last_of('/'));
  std::cout << "폴더 : " << directory << std::endl;

  // process ASSIMP's root node recursively
  if (scene != nullptr)
  {
    MeshUtility::instance().processNode(scene->mRootNode, scene, totalObject);
  }

  return totalObject;
}

void MeshUtility::processNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& models)
{
  // 1. 현재 노드에 위치하여있는 각각의 매쉬를 처리한다.
  for (unsigned int i = 0; i < node->mNumMeshes; i++)
  {
    // 2.
    // node 객체에는 씬 속 실제 객체의 색인값을 포함
    // 씬은 모든 데이터를 포함, 노드는 단순히 조직화된 stuff만 유지
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    Mesh model;
    processMesh(mesh, scene, model);
    models.push_back(model);
  }
  // after we've processed all of the meshes (if any) we then recursively
  // process each of the children nodes
  for (unsigned int i = 0; i < node->mNumChildren; i++)
  {
    processNode(node->mChildren[i], scene, models);
  }
}

void MeshUtility::processMesh(aiMesh* mesh, const aiScene* scene, Mesh& model)
{
  // Walk through each of the mesh's vertices
  for (unsigned int i = 0; i < mesh->mNumVertices; i++)
  {
    Vertex vertex;
    // own vector class that doesn't directly convert to
    // glm's vec3 class so we transfer the data to this
    // placeholder glm::vec3 first.
    if (mesh->HasVertexColors(0))
    {
      vertex.r = mesh->mColors[i]->r;
      vertex.g = mesh->mColors[i]->g;
      vertex.b = mesh->mColors[i]->b;
      vertex.a = mesh->mColors[i]->a;
    }
    else
    {
      vertex.r = 1.f;
      vertex.g = 1.f;
      vertex.b = 1.f;
      vertex.a = 1.f;
    }

    // positions
    if (mesh->HasPositions())
    {
      vertex.x = mesh->mVertices[i].x;
      vertex.y = mesh->mVertices[i].y;
      vertex.z = mesh->mVertices[i].z;
    }
    // normals
    if (mesh->HasNormals())
    {
      vertex.nx = mesh->mNormals[i].x;
      vertex.ny = mesh->mNormals[i].y;
      vertex.nz = mesh->mNormals[i].z;
    }
    // texture coordinates
    if (mesh->HasTextureCoords(0))  // does the mesh contain texture coordinates?
    {
      // glm::vec2 vec;
      // a vertex can contain up to 8 different texture coordinates. We thus
      // make the assumption that we won't use models where a vertex can have
      // multiple texture coordinates so we always take the first set (0).
      vertex.tx = mesh->mTextureCoords[0][i].x;
      vertex.ty = mesh->mTextureCoords[0][i].y;
      //// tangent
      // vector.x = mesh->mTangents[i].x;
      // vector.y = mesh->mTangents[i].y;
      // vector.z = mesh->mTangents[i].z;
      //// bitangent
      // vector.x = mesh->mBitangents[i].x;
      // vector.y = mesh->mBitangents[i].y;
      // vector.z = mesh->mBitangents[i].z;
    }
    else
    {
      vertex.tx = 0.f;
      vertex.ty = 0.f;
    }
    model.vertices.push_back(vertex);
  }
  // 매쉬의 정면(face)를 찾아냄
  // 대응되는 vertex 색인(순번)을 찾아냄(retrieve)
  for (unsigned int i = 0; i < mesh->mNumFaces; i++)
  {
    aiFace face = mesh->mFaces[i];
    // assimp의 face는 triangle이다.
    if (face.mNumIndices != 3)
      continue;
    for (unsigned int j = 0; j < face.mNumIndices; j++)
      model.indices.push_back(face.mIndices[j]);
  }

  // process materials
  // TODO: Material 파싱 로직 만들기
  aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
}
