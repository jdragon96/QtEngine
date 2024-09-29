#include "QtEngine/opengl/GLWidget.h"
#include <exception>

namespace QtEngine
{
GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
GLWidget::~GLWidget()
{
}

void GLWidget::SetVertexShaderPath(std::string path)
{
  vertexPath = path;
}

void GLWidget::SetPixelShaderPath(std::string path)
{
  pixelPath = path;
}

QSize GLWidget::sizeHint() const
{
  return QSize(1280, 800);
}

void GLWidget::initializeGL()
{
  QOpenGLWidget::initializeGL();
  // QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glFrontFace(GL_CCW);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  mainCamera = CameraBuffer::MakeShared();
  mainCamera->SetDistance(3.f);
  mainCamera->SetSensitivity(0.005f);
  mainCamera->SetPerspective(45.f, width(), height(), 0.1f, 100.f);
  mainShader = ShaderBuffer::MakeShared();
  mainShader->SetVertexShaderCode(R"(
    #version 460 core

    layout(location = 0) in vec3 vertexPosition;
    layout(location = 1) in vec4 vertexColor;
    layout(location = 2) in vec2 texCoord;
    layout(location = 3) in vec3 normalVector;

    out vec4 color;
    out vec3 posWorld;
    out vec3 posProj;
    out vec3 normal;
    out vec2 texturecoord;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;
    uniform mat4 invModel;

    void main() {
        color = vertexColor;
        texturecoord = texCoord;
        normal = normalize((invModel * vec4(normalVector, 1.f)).xyz);
        vec4 pos = model * vec4(vertexPosition, 1.0f);
        posWorld = pos.xyz;
        gl_Position = projection * view * pos;
        posProj = gl_Position.xyz;
    }
)");
  mainShader->SetFragmentShaderCode(R"(
    #version 460 core

    in vec4 color;
    in vec3 posWorld;
    in vec3 posProj;
    in vec3 normal;
    in vec2 texturecoord;
    out vec4 FragColor;

    uniform vec3 campos;

    void main(){
        vec3 toEye = normalize(campos - posWorld);
        FragColor = vec4(color.xyz * dot(toEye, normal), 1);
    }
)");
  init();
}
void GLWidget::resizeGL(int w, int h)
{
  QOpenGLWidget::resizeGL(w, h);
  // QOpenGLFunctions* f = QOpenGLContext::currentContext()->functions();
  mainCamera->SetPerspective(45.f, w, h, 0.1f, 100.f);
  resize();
}
void GLWidget::paintGL()
{
  QOpenGLWidget::paintGL();
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.f, 1.0f);

    float halfWidth = width() / 2.f;
    float halfHeight = height() / 2.f;

    mainShader->Use();
    mainShader->UpdateUniformMat4("view", *mainCamera->GetViewMatrix());
    mainShader->UpdateUniformMat4("projection", *mainCamera->GetPerspectiveMatrix());
    mainShader->UpdateUniformVec3("campos", *mainCamera->GetCameraPosition());
  }

  {
    rendering();
  }

  {
    mainShader->shader->release();
  }

  // UI 랜더링
}

void GLWidget::mousePressEvent(QMouseEvent* e)
{
  switch (e->button())
  {
    case Qt::MouseButton::LeftButton:
      prevPosX = e->pos().x();
      prevPosY = e->pos().y();
      mousePressStatus = Qt::MouseButton::LeftButton;
      isMousePressed = true;
      isRightMousePressed = false;
      break;
    case Qt::MouseButton::RightButton:
      prevPosX = e->pos().x();
      prevPosY = e->pos().y();
      mousePressStatus = Qt::MouseButton::RightButton;
      isMousePressed = true;
      isRightMousePressed = true;
      break;
  }
  update();
}

void GLWidget::mouseMoveEvent(QMouseEvent* e)
{
  posX = e->pos().x();
  posY = e->pos().y();
  if (isMousePressed)
  {
    switch (mousePressStatus)
    {
      case Qt::MouseButton::LeftButton:
        mainCamera->RotateOrbit(e->pos().x() - prevPosX, e->pos().y() - prevPosY);
        break;
      case Qt::MouseButton::RightButton:
        mainCamera->Translate(e->pos().x() - prevPosX, e->pos().y() - prevPosY);
        break;
    }

    prevPosX = e->pos().x();
    prevPosY = e->pos().y();
  }
  update();
}

void GLWidget::mouseReleaseEvent(QMouseEvent* e)
{
  isMousePressed = false;
  isRightMousePressed = false;
  update();
}

void GLWidget::SetRenderFunction(std::function<void()> func)
{
  rendering = func;
}

void GLWidget::SetInitializeFunction(std::function<void()> func)
{
  init = func;
}

void GLWidget::SetResizeFunction(std::function<void()> func)
{
  resize = func;
}
}  // namespace QtEngine