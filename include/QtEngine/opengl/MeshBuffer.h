#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "QtEngine/Macro.h"
#include "QtEngine/opengl/QGLHelper.hpp"
#include "QtEngine/opengl/Vertex.h"
#include "QtEngine/opengl/Mesh.h"

#include <QtGui/qevent.h>
#include <QtGui/qopenglbuffer.h>
#include <QtGui/qopenglfunctions.h>
#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglvertexarrayobject.h>

#include "QGLHelper.hpp"
#include "ShaderBuffer.h"
#include "CameraBuffer.h"

namespace QtEngine
{
class MeshBuffer
{
public:
  enum class MeshType
  {
    POINT,
    LINE,
    TRIANGLE
  };

  SHARED_PTR(MeshBuffer);

  MeshBuffer();

  ~MeshBuffer();

  void SetShader(ShaderBuffer::SharedPtr shader);

  void SetMesh(Meshes meshes);

  void SetPosition(QVector3D pos);

  void SetRotationAxis(QQuaternion quat);

  // void UpdateMesh(QtEngine::Mesh mesh);
  void UpdateMesh(Meshes mesh);

  void UpdateModelMatrix(QVector3D position);

  void UpdateModelMatrix(QQuaternion quat);

  void SetMeshType(MeshType t);

  QMatrix4x4* GetModelMatrix();

  void UpdateModelMatrix(QMatrix4x4& mat);

  virtual void Initialize(ShaderBuffer::SharedPtr shader);

  void Initialize();

  virtual void Render();

  virtual void Render(QMatrix4x4& model);

public:
  MeshType m_type;
  QVector3D m_position;
  QVector4D meshPos;
  QQuaternion m_axis = QQuaternion(1, 0, 0, 0);
  QMatrix4x4 modelMatrix;
  QMatrix4x4 invModelMatrix;
  ShaderBuffer::SharedPtr mainShader;

  Meshes m_mesh;
};

}  // namespace QtEngine