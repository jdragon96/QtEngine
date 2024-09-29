#include "QtEngine/opengl/MeshBuffer.h"

namespace QtEngine
{
MeshBuffer::MeshBuffer() : m_type(MeshType::TRIANGLE)
{
  modelMatrix.setToIdentity();
  invModelMatrix = modelMatrix.inverted();
  invModelMatrix = invModelMatrix.transposed();
}

MeshBuffer::~MeshBuffer()
{
  for (auto& m : m_mesh)
  {
    if (m.vertexArrayObject != nullptr)
    {
      m.vertexArrayObject->destroy();
    }
    if (m.indexBuffer != nullptr)
    {
      m.indexBuffer->destroy();
    }
    if (m.vertexBuffer != nullptr)
    {
      m.vertexBuffer->destroy();
    }
  }
}

void MeshBuffer::SetMeshType(MeshType t)
{
  m_type = t;
}

void MeshBuffer::SetShader(ShaderBuffer::SharedPtr shader)
{
  mainShader = shader;
}

void MeshBuffer::SetMesh(Meshes meshes)
{
  this->m_mesh = meshes;
}

void MeshBuffer::SetPosition(QVector3D pos)
{
  m_position = pos;
  meshPos.setX(pos.x());
  meshPos.setY(pos.y());
  meshPos.setZ(pos.z());
  meshPos.setW(1);
  modelMatrix(0, 3) = pos.x();
  modelMatrix(1, 3) = pos.y();
  modelMatrix(2, 3) = pos.z();
  modelMatrix(3, 3) = 1;
}

void MeshBuffer::SetRotationAxis(QQuaternion quat)
{
  m_axis = quat;
  auto mat = m_axis.toRotationMatrix();
  for (int r = 0; r < 3; ++r)
  {
    for (int c = 0; c < 3; ++c)
    {
      modelMatrix(r, c) = mat(r, c);
    }
  }

  modelMatrix(0, 3) = m_position.x();
  modelMatrix(1, 3) = m_position.y();
  modelMatrix(2, 3) = m_position.z();
  modelMatrix(3, 3) = 1;
}

void MeshBuffer::UpdateMesh(Meshes mesh)
{
  if (mesh.size() != m_mesh.size())
    return;
  for (int i = 0; i < m_mesh.size(); ++i)
  {
    m_mesh[i].vertices = mesh[i].vertices;
    m_mesh[i].vertexBuffer->bind();
    void* buffer_data = m_mesh[i].vertexBuffer->map(QOpenGLBuffer::WriteOnly);
    memcpy(buffer_data, m_mesh[i].vertices.data(), sizeof(QtEngine::Vertex) * m_mesh[i].vertices.size());
    m_mesh[i].vertexBuffer->unmap();
    m_mesh[i].vertexBuffer->release();
  }
}

void MeshBuffer::UpdateModelMatrix(QVector3D position)
{
  modelMatrix.setToIdentity();
  modelMatrix.translate(position);
  m_position = position;
}

void MeshBuffer::UpdateModelMatrix(QQuaternion quat)
{
  // modelMatrix(0, 0) = 3.4f;
}

QMatrix4x4* MeshBuffer::GetModelMatrix()
{
  return &modelMatrix;
}

void MeshBuffer::UpdateModelMatrix(QMatrix4x4& mat)
{
  mainShader->UpdateUniformMat4("model", mat);
}

void MeshBuffer::Initialize(ShaderBuffer::SharedPtr shader)
{
}

void MeshBuffer::Initialize()
{
  for (auto& m : m_mesh)
  {
    m.vertexArrayObject = new QOpenGLVertexArrayObject();
    m.vertexArrayObject->create();
    m.vertexArrayObject->bind();

    int vtxSize = sizeof(QtEngine::Vertex);
    int xyzOffset = 0;
    int rgbOffset = sizeof(float) * 3;
    int textureOffset = sizeof(float) * 7;
    int normalOffset = sizeof(float) * 9;

    m.vertexBuffer = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    m.vertexBuffer->create();
    m.vertexBuffer->bind();
    m.vertexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    m.vertexBuffer->allocate(m.vertices.data(), sizeof(QtEngine::Vertex) * m.vertices.size());

    mainShader->shader->bind();
    mainShader->shader->enableAttributeArray(0);
    mainShader->shader->setAttributeBuffer(0, GL_FLOAT, xyzOffset, 3, vtxSize);
    mainShader->shader->enableAttributeArray(1);
    mainShader->shader->setAttributeBuffer(1, GL_FLOAT, rgbOffset, 4, vtxSize);
    mainShader->shader->enableAttributeArray(2);
    mainShader->shader->setAttributeBuffer(2, GL_FLOAT, textureOffset, 2, vtxSize);
    mainShader->shader->enableAttributeArray(3);
    mainShader->shader->setAttributeBuffer(3, GL_FLOAT, normalOffset, 3, vtxSize);

    m.indexBuffer = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
    m.indexBuffer->create();
    m.indexBuffer->bind();
    m.indexBuffer->allocate(m.indices.data(), sizeof(uint32_t) * m.indices.size());

    m.vertexArrayObject->release();
    m.vertexBuffer->release();
    m.indexBuffer->release();
  }
}

void MeshBuffer::Render()
{
  for (auto& m : m_mesh)
  {
    mainShader->Use();
    m.vertexArrayObject->bind();
    m.indexBuffer->bind();
    m.vertexBuffer->bind();
    mainShader->UpdateUniformMat4("model", modelMatrix);
    mainShader->UpdateUniformMat4("invModel", invModelMatrix);
    switch (m_type)
    {
      case MeshType::TRIANGLE:
        glDrawElements(GL_TRIANGLES, m.indices.size(), GL_UNSIGNED_INT, 0);
        break;
      case MeshType::LINE:
        glDrawElements(GL_LINES, m.indices.size(), GL_UNSIGNED_INT, 0);
        break;
    }
    m.vertexArrayObject->release();
    m.indexBuffer->release();
    m.vertexBuffer->release();
  }
}

void MeshBuffer::Render(QMatrix4x4& model)
{
  modelMatrix = model;
  invModelMatrix = model;
  invModelMatrix.translate(QVector3D(0, 0, 0));
  invModelMatrix = invModelMatrix.inverted();
  invModelMatrix = invModelMatrix.transposed();
  Render();
}
}  // namespace QtEngine