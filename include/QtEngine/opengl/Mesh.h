#pragma once

#include <vector>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBUffer>
#include <QtEngine/opengl/Vertex.h>

namespace QtEngine
{

class Mesh
{
public:
  Mesh();
  ~Mesh();

  std::vector<QtEngine::Vertex> vertices;
  std::vector<uint32_t> indices;

  /* GPU ∆˜¿Œ≈Õ */
  QOpenGLVertexArrayObject* vertexArrayObject;
  QOpenGLBuffer* vertexBuffer;
  QOpenGLBuffer* indexBuffer;
};

using Meshes = std::vector<Mesh>;
}  // namespace QtEngine