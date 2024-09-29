#include <QtEngine/OpenGL/Mesh.h>

namespace QtEngine
{
Mesh::Mesh() : vertexArrayObject(nullptr), vertexBuffer(nullptr), indexBuffer(nullptr)
{
}
Mesh::~Mesh()
{
  if (vertexArrayObject != nullptr && vertexArrayObject->isCreated())
  {
    vertexArrayObject->destroy();
    vertexArrayObject = nullptr;
  }
  if (indexBuffer != nullptr && indexBuffer->isCreated())
  {
    indexBuffer->destroy();
    indexBuffer = nullptr;
  }
  if (vertexBuffer != nullptr && vertexBuffer->isCreated())
  {
    vertexBuffer->destroy();
    vertexBuffer = nullptr;
  }
}
}  // namespace QtEngine