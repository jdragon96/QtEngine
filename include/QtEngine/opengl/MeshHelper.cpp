#include "QtEngine/OpenGL/MeshHelper.h"

#include "QtEngine/OpenGL/QMathHelper.hpp"
#include <utility>
#include <QVector4D>
#include <QVector3D>
#include <QVector2D>
#include <cmath>
#include <iostream>

using namespace QtEngine;

Mesh MeshHelper::MakeArrow(QVector3D start, QVector3D end, QVector4D color, QVector3D translate, float cylinderRadius,
                           float headRadius, float headRatio)
{
  Mesh mesh;
  int sliceNum = 4;

  //> 화살표 중심점 계산
  QVector3D centerPoint;
  centerPoint.setX((end.x() + start.x()) / 2.f);
  centerPoint.setY((end.y() + start.y()) / 2.f);
  centerPoint.setZ((end.z() + start.z()) / 2.f);

  //> 포인팅 벡터
  QVector3D pointVector = (end - start).normalized();
  float arrowLength = start.distanceToPoint(end);

  //> 좌표계 생성
  auto axisMatrix = QMathHelper::PointingAxisMatrix(pointVector, 2, start);
  axisMatrix = axisMatrix.transposed();
  std::vector<QVector2D> cc;
  const float dRad = 3.141592 * 2.f / static_cast<float>(sliceNum);
  for (unsigned int i = 0; i <= sliceNum; ++i)
  {
    QVector2D v;
    v.setX(cos(static_cast<float>(i) * dRad));
    v.setY(sin(static_cast<float>(i) * dRad));
    cc.push_back(v);
  }

  const float cylinderHeight = (1.f - headRatio) * arrowLength;
  const float headHeight = arrowLength - cylinderHeight;

  //> 원통 생성
  for (int i = 0; i < sliceNum; ++i)
  {
    QVector4D LeftBotton = axisMatrix * QVector4D(cc[i].x() * cylinderRadius, cc[i].y() * cylinderRadius, 0.f, 1.f);
    QVector4D LeftUp =
        axisMatrix * QVector4D(cc[i].x() * cylinderRadius, cc[i].y() * cylinderRadius, cylinderHeight, 1.f);
    QVector4D RightUp =
        axisMatrix * QVector4D(cc[i + 1].x() * cylinderRadius, cc[i + 1].y() * cylinderRadius, cylinderHeight, 1.f);
    QVector4D RightDown =
        axisMatrix * QVector4D(cc[i + 1].x() * cylinderRadius, cc[i + 1].y() * cylinderRadius, 0.f, 1.f);

    mesh.vertices.push_back(Vertex(LeftBotton, color));
    mesh.vertices.push_back(Vertex(LeftUp, color));
    mesh.vertices.push_back(Vertex(RightUp, color));
    mesh.vertices.push_back(Vertex(RightDown, color));
    mesh.indices.push_back(i * 4);
    mesh.indices.push_back(i * 4 + 2);
    mesh.indices.push_back(i * 4 + 1);
    mesh.indices.push_back(i * 4);
    mesh.indices.push_back(i * 4 + 3);
    mesh.indices.push_back(i * 4 + 2);
  }

  //> 원뿔 생성
  QVector4D Top = axisMatrix * QVector4D(0, 0, arrowLength, 1.f);
  mesh.vertices.push_back(Vertex(Top, color));
  uint32_t topIndex = mesh.vertices.size() - 1;
  for (int i = 0; i < sliceNum; ++i)
  {
    QVector4D LeftBottom = axisMatrix * QVector4D(cc[i].x() * headRadius, cc[i].y() * headRadius, cylinderHeight, 1.f);
    QVector4D RightBottom =
        axisMatrix * QVector4D(cc[i + 1].x() * headRadius, cc[i + 1].y() * headRadius, cylinderHeight, 1.f);

    mesh.vertices.push_back(Vertex(LeftBottom, color));
    mesh.vertices.push_back(Vertex(RightBottom, color));
    mesh.indices.push_back(topIndex + i * 2 + 2);
    mesh.indices.push_back(topIndex);
    mesh.indices.push_back(topIndex + i * 2 + 1);
  }

  //> 바닥면 생성;
  auto cylinderBottomCenter = axisMatrix * QVector4D(0, 0, 0, 1);
  mesh.vertices.push_back(Vertex(cylinderBottomCenter, color));
  uint32_t startIndex = mesh.vertices.size() - 1;
  for (int i = 0; i < sliceNum; ++i)
  {
    QVector4D Left = axisMatrix * QVector4D(cc[i].x() * cylinderRadius, cc[i].y() * cylinderRadius, 0, 1.f);
    QVector4D Right = axisMatrix * QVector4D(cc[i + 1].x() * cylinderRadius, cc[i + 1].y() * cylinderRadius, 0, 1.f);

    mesh.vertices.push_back(Vertex(Left, color));
    mesh.vertices.push_back(Vertex(Right, color));
    mesh.indices.push_back(startIndex);
    mesh.indices.push_back(startIndex + i * 2 + 2);
    mesh.indices.push_back(startIndex + i * 2 + 1);
  }
  auto HeadBottomCenter = axisMatrix * QVector4D(0, 0, cylinderHeight, 1);
  mesh.vertices.push_back(Vertex(HeadBottomCenter, color));
  startIndex = mesh.vertices.size() - 1;
  for (int i = 0; i < sliceNum; ++i)
  {
    QVector4D Left = axisMatrix * QVector4D(cc[i].x() * headRadius, cc[i].y() * headRadius, cylinderHeight, 1.f);
    QVector4D Right =
        axisMatrix * QVector4D(cc[i + 1].x() * headRadius, cc[i + 1].y() * headRadius, cylinderHeight, 1.f);

    mesh.vertices.push_back(Vertex(Left, color));
    mesh.vertices.push_back(Vertex(Right, color));
    mesh.indices.push_back(startIndex);
    mesh.indices.push_back(startIndex + i * 2 + 2);
    mesh.indices.push_back(startIndex + i * 2 + 1);
  }

  for (auto& vtx : mesh.vertices)
  {
    vtx.x += translate.x();
    vtx.y += translate.y();
    vtx.z += translate.z();
  }

  return mesh;
}

Mesh MeshHelper::MakeTorus(QVector3D axis, QVector4D color, QVector3D pos)
{
  Mesh m;

  float width = 0.08;
  float largeRadius = 1.f;
  float smallRadius = 0.98f;
  float height = 0.04f;
  float halfHeight = height / 2.f;
  //> 좌표계 생성
  auto axisMatrix = QMathHelper::PointingAxisMatrix(axis, 2, QVector3D(0, 0, 0));
  axisMatrix = axisMatrix.transposed();
  float halfWidth = width / 2.f;
  int slice = 40;

  std::vector<Vertex> outerUps;
  std::vector<Vertex> outerDowns;
  std::vector<Vertex> innerUps;
  std::vector<Vertex> innerDowns;

  for (int i = 0; i <= slice; ++i)
  {
    float rad = static_cast<float>(i) / static_cast<float>(slice) * 3.141592f * 2.f;
    QVector4D outerUpPos(cos(rad) * largeRadius, sin(rad) * largeRadius, halfHeight, 1.f);
    QVector4D outerDownPos(cos(rad) * largeRadius, sin(rad) * largeRadius, -halfHeight, 1.f);
    QVector4D innerUpPos(cos(rad) * smallRadius, sin(rad) * smallRadius, halfHeight, 1.f);
    QVector4D innerDownPos(cos(rad) * smallRadius, sin(rad) * smallRadius, -halfHeight, 1.f);
    outerUpPos = axisMatrix * outerUpPos + pos;
    outerDownPos = axisMatrix * outerDownPos + pos;
    innerUpPos = axisMatrix * innerUpPos + pos;
    innerDownPos = axisMatrix * innerDownPos + pos;

    Vertex outerUp;
    outerUp.SetColor(color.x(), color.y(), color.z(), color.w());
    outerUp.SetPosition(outerUpPos.x(), outerUpPos.y(), outerUpPos.z());
    Vertex outerDown;
    outerDown.SetColor(color.x(), color.y(), color.z(), color.w());
    outerDown.SetPosition(outerDownPos.x(), outerDownPos.y(), outerDownPos.z());
    Vertex innerUp;
    innerUp.SetColor(color.x(), color.y(), color.z(), color.w());
    innerUp.SetPosition(innerUpPos.x(), innerUpPos.y(), innerUpPos.z());
    Vertex innerDown;
    innerDown.SetColor(color.x(), color.y(), color.z(), color.w());
    innerDown.SetPosition(innerDownPos.x(), innerDownPos.y(), innerDownPos.z());

    m.vertices.push_back(outerUp);
    m.vertices.push_back(outerDown);
    m.vertices.push_back(innerUp);
    m.vertices.push_back(innerDown);
  }

  int outerUp = 0;
  int outerDown = 1;
  int innerUp = 2;
  int innerDown = 3;
  for (int i = 0; i < slice; ++i)
  {
    int crnt = i * 4;
    int next = (i + 1) * 4;
    m.indices.push_back(crnt + outerDown);
    m.indices.push_back(next + outerUp);
    m.indices.push_back(crnt + outerUp);
    m.indices.push_back(crnt + outerDown);
    m.indices.push_back(next + outerDown);
    m.indices.push_back(next + outerUp);

    m.indices.push_back(crnt + outerUp);
    m.indices.push_back(next + innerUp);
    m.indices.push_back(crnt + innerUp);
    m.indices.push_back(crnt + outerUp);
    m.indices.push_back(next + outerUp);
    m.indices.push_back(next + innerUp);

    m.indices.push_back(next + innerDown);
    m.indices.push_back(crnt + innerUp);
    m.indices.push_back(next + innerUp);
    m.indices.push_back(next + innerDown);
    m.indices.push_back(crnt + innerDown);
    m.indices.push_back(crnt + innerUp);

    m.indices.push_back(crnt + innerDown);
    m.indices.push_back(next + outerDown);
    m.indices.push_back(crnt + outerDown);
    m.indices.push_back(crnt + innerDown);
    m.indices.push_back(next + innerDown);
    m.indices.push_back(next + outerDown);
  }

  return m;
}

Mesh MeshHelper::MakeAxis(float scale)
{
  Mesh m;
  auto stick = [](float x, float y, float z, float r, float g, float b) -> std::pair<Vertex, Vertex> {
    Vertex v0;
    v0.SetPosition(0, 0, 0);
    v0.SetColor(r, g, b, 1);
    Vertex v1;
    v1.SetPosition(x, y, z);
    v1.SetColor(r, g, b, 1);
    return std::pair<Vertex, Vertex>(v0, v1);
  };

  auto x = stick(scale, 0, 0, 1, 0, 0);
  auto y = stick(0, scale, 0, 1, 1, 0);
  auto z = stick(0, 0, scale, 1, 0, 1);

  m.vertices.push_back(x.first);
  m.vertices.push_back(x.second);
  m.vertices.push_back(y.first);
  m.vertices.push_back(y.second);
  m.vertices.push_back(z.first);
  m.vertices.push_back(z.second);
  m.indices.push_back(0);
  m.indices.push_back(1);
  m.indices.push_back(2);
  m.indices.push_back(3);
  m.indices.push_back(4);
  m.indices.push_back(5);

  return m;
}

Mesh MeshHelper::MakeSphere(QVector4D color, const float radius, const int numSlice, const int numStack)
{
  const float dTheta = -(3.141592 * 2) / float(numSlice);
  const float dPhi = -3.141592 / float(numStack);
  Mesh object;

  for (int i = 0; i <= numStack; ++i)
  {
    Vertex stackStartPoint;
    stackStartPoint.x = (-radius) * (-sin(dPhi * i));
    stackStartPoint.y = (-radius) * cos(dPhi * i);
    stackStartPoint.z = 0;

    for (int j = 0; j <= numSlice; ++j)
    {
      Vertex vtx;
      vtx.x = stackStartPoint.x * cos(dTheta * j);
      vtx.y = stackStartPoint.y;
      vtx.z = stackStartPoint.x * (-sin(dTheta * j));
      float nFactor = sqrt(pow(vtx.x, 2) + pow(vtx.y, 2) + pow(vtx.z, 2));
      vtx.nx = vtx.x / nFactor;
      vtx.ny = vtx.y / nFactor;
      vtx.nz = vtx.z / nFactor;
      vtx.tx = float(j) / numSlice;
      vtx.ty = 1.0f - float(i) / numStack;
      vtx.SetColor(color);
      object.vertices.push_back(vtx);
    }
  }

  for (int j = 0; j < numStack; j++)
  {
    const int offset = (numSlice + 1) * j;
    for (int i = 0; i < numSlice; i++)
    {
      object.indices.push_back(offset + i);
      object.indices.push_back(offset + i + numSlice + 1);
      object.indices.push_back(offset + i + 1 + numSlice + 1);

      object.indices.push_back(offset + i);
      object.indices.push_back(offset + i + 1 + numSlice + 1);
      object.indices.push_back(offset + i + 1);
    }
  }

  return object;
}