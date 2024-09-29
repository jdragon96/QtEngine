#pragma once

#include <limits>

#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
#include "QtEngine/opengl/MeshBuffer.h"
#include "QtEngine/opengl/Vertex.h"

namespace QtEngine
{
class Ray
{
public:
  Ray();
  ~Ray();

  QVector3D& GetDirection();
  QVector3D& GetPosition();
  QVector3D& GetTracedPos();

  void UpdateRay(QMatrix4x4& projMat, QMatrix4x4& eye, QVector3D& camPos, double cursorX, double cursorY, double width,
                 double height);
  bool Trace(MeshBuffer::SharedPtr meshBuffer, double& shorttestDistance);

private:
  bool IsTriangleIntersected(Vertex* p0, Vertex* p1, Vertex* p2, double& best_t);

  bool isTraced = false;
  QVector3D tracedPos;
  QVector3D rayDirection;
  QVector3D rayPos;
};
}  // namespace QtEngine