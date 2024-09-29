#pragma once

#include <iostream>
#include <memory>
#include <string>

#include <QEvent>
#include <QOpenGLFunctions>
#include <QtGui/qopenglshaderprogram.h>
#include <QOpenGLShaderProgram>
#include <QOpenGLWIdget>

#include "QtEngine/Macro.h"

namespace QtEngine
{
class CameraBuffer
{
public:
  SHARED_PTR(CameraBuffer);

  // Phi: Latitude(위도)
  float dPhi;
  // Delta: Longitude(경도)
  float dDelta;
  float sensitivity;
  float distance;
  QMatrix4x4 viewMatrix;
  QMatrix4x4 persepctiveMatrix;
  QVector3D cameraPosition;
  QVector3D targetPosition;

  // 카메라벡터
  QVector3D frontVector;
  QVector3D rightVector;
  QVector3D upVector;

  CameraBuffer();
  ~CameraBuffer();
  void SetSensitivity(float value);
  void SetPerspective(float angleDeg, float width, float height, float nearDistance, float farDistance);
  void SetDistance(float dist);
  void SetPosition(QVector3D pos);
  void SetTargetPosition(QVector3D pos);

  QMatrix4x4* GetViewMatrix();
  QVector3D* GetCameraPosition();
  QVector3D* GetTargetPosition();
  QMatrix4x4* GetPerspectiveMatrix();

  void RotateOrbitOnlyLongitude(float deltaX, float deltaY);
  void RotateOrbit(float deltaX, float deltaY);
  void Translate(float deltaX, float deltaY);
  void Update();
};
}  // namespace QtEngine