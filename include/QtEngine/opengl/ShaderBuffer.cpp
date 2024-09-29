#include "QtEngine/opengl/ShaderBuffer.h"

namespace QtEngine
{
ShaderBuffer::ShaderBuffer()
{
  shader = new QOpenGLShaderProgram();
}
ShaderBuffer::ShaderBuffer(std::string vtxShader, std::string pxlShader)
{
  shader = new QOpenGLShaderProgram();
  QGLHelper::BindShader(shader, vtxShader, pxlShader);
}
ShaderBuffer::~ShaderBuffer()
{
  delete shader;
}

ShaderBuffer::SharedPtr ShaderBuffer::MakeShared(std::string vtxShader, std::string pxlShader)
{
  return std::make_shared<ShaderBuffer>(vtxShader, pxlShader);
}

void ShaderBuffer::UpdateUniformMat4(std::string name, QMatrix4x4& mat)
{
  this->shader->setUniformValue(name.c_str(), mat);
}

void ShaderBuffer::UpdateUniformVec3(std::string name, QVector3D& vec3)
{
  this->shader->setUniformValue(name.c_str(), vec3);
}

void ShaderBuffer::Use()
{
  shader->bind();
}

void ShaderBuffer::SetVertexShaderCode(std::string code)
{
  shader->addShaderFromSourceCode(QOpenGLShader::Vertex, code.c_str());
}

void ShaderBuffer::SetFragmentShaderCode(std::string code)
{
  shader->addShaderFromSourceCode(QOpenGLShader::Fragment, code.c_str());
}
}  // namespace QtEngine