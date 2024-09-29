#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include <QEvent>
#include <QOpenGLFunctions.h>
#include <QOpenGLShaderProgram.h>
#include <QOpenGLWidget.h>

#include "QtEngine/Macro.h"
#include "QtEngine/opengl/CameraBuffer.h"
#include "QtEngine/opengl/ShaderBuffer.h"
#include "QtEngine/opengl/MeshHelper.h"

namespace QtEngine
{
class GLWidget : public QOpenGLWidget
{
public:
  SHARED_PTR(GLWidget);
  GLWidget(QWidget* parent = 0);
  virtual ~GLWidget();

  void SetVertexShaderPath(std::string path);
  void SetPixelShaderPath(std::string path);

public:
  QSize sizeHint() const;

  virtual void initializeGL() override;
  virtual void resizeGL(int w, int h) override;
  virtual void paintGL() override;
  virtual void mousePressEvent(QMouseEvent* e) override;
  virtual void mouseMoveEvent(QMouseEvent* e) override;
  virtual void mouseReleaseEvent(QMouseEvent* e) override;

protected:
  void SetRenderFunction(std::function<void()> func);
  void SetInitializeFunction(std::function<void()> func);
  void SetResizeFunction(std::function<void()> func);

  // virtual void InitializeCallback() = 0;
  // virtual void ResizeCallback() = 0;
  // virtual void RenderCallback() = 0;

protected:
  // 마우스 입력처리
  bool isMousePressed;
  bool isRightMousePressed;
  Qt::MouseButton mousePressStatus;
  float prevPosX;
  float prevPosY;
  float posX;
  float posY;

protected:
  // 메인 카메라 및 셰이더
  CameraBuffer::SharedPtr mainCamera;
  ShaderBuffer::SharedPtr mainShader;

  // 셰이더 파일 경로
  std::string vertexPath;
  std::string pixelPath;

  // 랜더링 루프
  std::function<void()> rendering = []() {};
  std::function<void()> init = []() {};
  std::function<void()> resize = []() {};
};

}  // namespace QtEngine