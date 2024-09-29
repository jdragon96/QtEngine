#pragma once
#include <iostream>
#include <memory>
#include <string>

#include <QtGui/qevent.h>
#include <QtGui/qopenglfunctions.h>
#include <QtGui/qopenglshaderprogram.h>
#include <QtWidgets/qopenglwidget.h>

#include "QtEngine/Macro.h"
#include "QtEngine/opengl/QGLHelper.hpp"

namespace QtEngine
{
class ShaderBuffer
{
public:
  SHARED_PTR(ShaderBuffer);

  QOpenGLShaderProgram* shader;

  ShaderBuffer();
  ShaderBuffer(std::string vtxShader, std::string pxlShader);
  ~ShaderBuffer();

  static ShaderBuffer::SharedPtr MakeShared(std::string vtxShader, std::string pxlShader);

  void SetVertexShaderCode(std::string);
  void SetFragmentShaderCode(std::string);

  void UpdateUniformMat4(std::string name, QMatrix4x4& mat);
  void UpdateUniformVec3(std::string name, QVector3D& vec3);
  void Use();
};
}  // namespace QtEngine