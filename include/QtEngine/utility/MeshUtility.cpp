#include <QtEngine/utility/MeshUtility.h>

using namespace QtEngine;

std::vector<QtEngine::Mesh> MeshUtility::Read(std::string path)
{
  std::vector<QtEngine::Mesh> totalObject;

  // 1. �� ������ �б�
  Assimp::Importer importer;
  const aiScene* scene =
      importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

  // 2. ���� üũ
  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)  // if is Not Zero
  {
    std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
    // return totalObject;
  }
  std::string directory = path.substr(0, path.find_last_of('/'));
  std::cout << "���� : " << directory << std::endl;

  // process ASSIMP's root node recursively
  if (scene != nullptr)
  {
    MeshUtility::instance().processNode(scene->mRootNode, scene, totalObject);
  }

  return totalObject;
}

void MeshUtility::processNode(aiNode* node, const aiScene* scene, std::vector<Mesh>& models)
{
  // 1. ���� ��忡 ��ġ�Ͽ��ִ� ������ �Ž��� ó���Ѵ�.
  for (unsigned int i = 0; i < node->mNumMeshes; i++)
  {
    // 2.
    // node ��ü���� �� �� ���� ��ü�� ���ΰ��� ����
    // ���� ��� �����͸� ����, ���� �ܼ��� ����ȭ�� stuff�� ����
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
  // �Ž��� ����(face)�� ã�Ƴ�
  // �����Ǵ� vertex ����(����)�� ã�Ƴ�(retrieve)
  for (unsigned int i = 0; i < mesh->mNumFaces; i++)
  {
    aiFace face = mesh->mFaces[i];
    // assimp�� face�� triangle�̴�.
    if (face.mNumIndices != 3)
      continue;
    for (unsigned int j = 0; j < face.mNumIndices; j++)
      model.indices.push_back(face.mIndices[j]);
  }

  // process materials
  // TODO: Material �Ľ� ���� �����
  aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
}
