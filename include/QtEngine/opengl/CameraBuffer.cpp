#include "QtEngine/opengl/CameraBuffer.h"

namespace QtEngine
{
CameraBuffer::CameraBuffer()
{
  dPhi = 0.f;
  dDelta = 0.f;
  cameraPosition = QVector3D(-3.f, 0.f, 0.f);
  targetPosition = QVector3D(0.f, 0.f, 0.f);
  distance = targetPosition.distanceToPoint(cameraPosition);
  upVector = QVector3D(0.f, 0.f, 1.f);
  frontVector = (cameraPosition - targetPosition).normalized();
  rightVector = QVector3D::crossProduct(frontVector, upVector).normalized();
  sensitivity = 0.001f;

  viewMatrix.setToIdentity();
  persepctiveMatrix.setToIdentity();
  Update();
}

CameraBuffer::~CameraBuffer()
{
}

void CameraBuffer::SetSensitivity(float value)
{
  sensitivity = value;
}

void CameraBuffer::SetPerspective(float angleDeg, float width, float height, float nearDistance, float farDistance)
{
  persepctiveMatrix.setToIdentity();
  persepctiveMatrix.perspective(angleDeg, width / height, nearDistance, farDistance);
}

void CameraBuffer::SetDistance(float dist)
{
  distance = dist;
  QVector3D moveVec = cameraPosition - targetPosition;
  moveVec.normalize();
  cameraPosition = targetPosition + moveVec * distance;
  Update();
}
void CameraBuffer::SetPosition(QVector3D pos)
{
  cameraPosition = pos;
  distance = cameraPosition.distanceToPoint(targetPosition);
  frontVector = (cameraPosition - targetPosition).normalized();
  rightVector = QVector3D::crossProduct(frontVector, upVector).normalized();
}
void CameraBuffer::SetTargetPosition(QVector3D pos)
{
  targetPosition = pos;
  distance = cameraPosition.distanceToPoint(targetPosition);
  frontVector = (cameraPosition - targetPosition).normalized();
  rightVector = QVector3D::crossProduct(frontVector, upVector).normalized();
}

QMatrix4x4* CameraBuffer::GetViewMatrix()
{
  return &viewMatrix;
}

QVector3D* CameraBuffer::GetCameraPosition()
{
  return &cameraPosition;
}
QVector3D* CameraBuffer::GetTargetPosition()
{
  return &targetPosition;
}

QMatrix4x4* CameraBuffer::GetPerspectiveMatrix()
{
  return &persepctiveMatrix;
}

void CameraBuffer::RotateOrbitOnlyLongitude(float deltaX, float deltaY)
{
  dDelta = -(deltaX * sensitivity);
  dPhi = (deltaY * sensitivity);
  frontVector = (frontVector * cos(dDelta) - rightVector * sin(dDelta)).normalized();
  upVector = QVector3D::crossProduct(rightVector, frontVector).normalized();
  Update();
}

void CameraBuffer::RotateOrbit(float deltaX, float deltaY)
{
  dDelta = -(deltaX * sensitivity);
  dPhi = (deltaY * sensitivity);
  frontVector = (frontVector * cos(dDelta) - rightVector * sin(dDelta)).normalized();
  rightVector = QVector3D::crossProduct(frontVector, upVector).normalized();
  frontVector = (frontVector * cos(dPhi) + upVector * sin(dPhi)).normalized();
  upVector = QVector3D::crossProduct(rightVector, frontVector).normalized();
  cameraPosition = targetPosition + frontVector * distance;

  Update();
}

void CameraBuffer::Update()
{
  viewMatrix.setToIdentity();
  viewMatrix.lookAt(cameraPosition, targetPosition, upVector);
}
void CameraBuffer::Translate(float deltaX, float deltaY)
{
  auto delta = (rightVector * deltaX * distance * 0.001f + upVector * deltaY * distance * 0.001f);
  cameraPosition += delta;
  targetPosition += delta;
  Update();
}
}  // namespace QtEngine