#pragma once

#include <chrono>
#include <random>
#include <vector>

#include <QMatrix4x4>
#include <QMatrix>
#include <QQuaternion>
#include <QVector3D>

#include <QtEngine/opengl/Vertex.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/common.hpp>

namespace QtEngine
{
class QMathHelper
{
public:
  static QVector3D AxisX(QQuaternion& q)
  {
    return QVector3D(q.scalar() * q.scalar() + q.x() * q.x() - q.y() * q.y() - q.z() * q.z(),
                     (q.x() * q.y() + q.z() * q.scalar()) * 2, (q.z() * q.x() - q.y() * q.scalar()) * 2);
  }
  static QVector3D AxisY(QQuaternion& q)
  {
    return QVector3D((q.x() * q.y() - q.z() * q.scalar()) * 2,
                     q.scalar() * q.scalar() - q.x() * q.x() + q.y() * q.y() - q.z() * q.z(),
                     (q.y() * q.z() + q.x() * q.scalar()) * 2);
  }
  static QVector3D AxisZ(QQuaternion& q)
  {
    return QVector3D((q.z() * q.x() + q.y() * q.scalar()) * 2, (q.y() * q.z() - q.x() * q.scalar()) * 2,
                     q.scalar() * q.scalar() - q.x() * q.x() - q.y() * q.y() + q.z() * q.z());
  }

  static QQuaternion MakeQuaternion(QQuaternion& a, QQuaternion& b)
  {
    return QQuaternion(a.scalar() * b.scalar() - a.x() * b.x() - a.y() * b.y() - a.z() * b.z(),
                       a.x() * b.scalar() + a.scalar() * b.x() + a.y() * b.z() - a.z() * b.y(),
                       a.y() * b.scalar() + a.scalar() * b.y() + a.z() * b.x() - a.x() * b.z(),
                       a.z() * b.scalar() + a.scalar() * b.z() + a.x() * b.y() - a.y() * b.x());
  }

  static QMatrix4x4 PointingAxisMatrix(QVector3D pointVector, int startIndex, QVector3D initPos)
  {
    QMatrix4x4 mat;
    mat.fill(0);

    int coord1 = (startIndex + 1) % 3;
    int coord2 = (startIndex + 2) % 3;
    pointVector = pointVector.normalized();

    // 1. 위치변환
    mat.translate(initPos);
    mat(3, 3) = 1;

    // 2. Pointing Vector를 X축으로 가정한다.
    mat(startIndex, 0) = pointVector.x();
    mat(startIndex, 1) = pointVector.y();
    mat(startIndex, 2) = pointVector.z();

    // 3. point vector가 X축에 있는지 파악
    float h = hypot(pointVector.y(), pointVector.z());

    // 3.1. X축에 있는 경우
    mat(coord1, 0) = 0;
    if (h < 1e-10)
    {
      mat(coord1, 1) = 1.f;
      mat(coord1, 2) = 0.f;
    }
    else
    {
      mat(coord1, 1) = -pointVector.z() / h;
      mat(coord1, 2) = pointVector.y() / h;
    }

    // 4. Find z-axis vector
    QVector3D yVec = QVector3D(mat(coord1, 0), mat(coord1, 1), mat(coord1, 2));
    QVector3D zVec = QVector3D::crossProduct(pointVector, yVec).normalized();
    mat(coord2, 0) = zVec.x();
    mat(coord2, 1) = zVec.y();
    mat(coord2, 2) = zVec.z();

    return mat;
  }

  static QtEngine::Vertex Rodrigues(QVector3D& rotAxis, QVector3D& startPos, float angleDeg)
  {
    float rad = angleDeg / 180.f * 3.141592;
    QVector3D p = cos(rad) * startPos + QVector3D::crossProduct(rotAxis, startPos) * sin(rad) +
                  rotAxis * QVector3D::dotProduct(rotAxis, startPos) * (1 - cos(rad));
    QtEngine::Vertex vtx;
    vtx.x = p.x();
    vtx.y = p.y();
    vtx.z = p.z();
    return vtx;
  }
  static QVector3D RodrigusGLM(QVector3D& rotAxis, QVector3D& startPos, float angleDeg)
  {
    float rad = angleDeg / 180.f * 3.141592;
    return cos(rad) * startPos + QVector3D::crossProduct(rotAxis, startPos) * sin(rad) +
           rotAxis * QVector3D::dotProduct(rotAxis, startPos) * (1 - cos(rad));
  }
  static glm::vec3 QVecToGVec(QVector3D& qvec)
  {
    return glm::vec3(qvec.x(), qvec.y(), qvec.z());
  }
  static glm::vec3 toGLM(QVector3D* q)
  {
    return glm::vec3(q->x(), q->y(), q->z());
  }
  static glm::quat toGLM(QQuaternion* q)
  {
    return glm::quat(q->scalar(), q->x(), q->y(), q->z());
  }
  static glm::mat4 toGLM(QMatrix4x4* q)
  {
    glm::mat4 mat;
    for (int c = 0; c < 4; ++c)
    {
      auto column = q->column(c);
      for (int r = 0; r < 4; ++r)
      {
        mat[c][r] = column[r];
      }
    }
    return mat;
  }

  static QVector3D toQT(glm::vec3 g)
  {
    return QVector3D(g.x, g.y, g.z);
  }
  static QMatrix4x4 toQT(glm::mat4 g)
  {
    QMatrix4x4 mat;
    for (int c = 0; c < 4; ++c)
    {
      for (int r = 0; r < 4; ++r)
      {
        mat(r, c) = g[c][r];
      }
    }
    return mat;
  }
  static QQuaternion toQT(glm::quat g)
  {
    return QQuaternion(g.w, g.x, g.y, g.z);
  }
};
}  // namespace QtEngine