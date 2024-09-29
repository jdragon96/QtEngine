#pragma once

#include <QVector3D>
#include <QVector4D>

namespace QtEngine
{
class Vertex
{
public:
  // position
  float x;
  float y;
  float z;
  // color
  float r;
  float g;
  float b;
  float a;
  // texture coord
  float tx;
  float ty;
  // normal
  float nx;
  float ny;
  float nz;

  Vertex();
  Vertex(QVector3D pos, QVector3D color);
  Vertex(QVector4D pos, QVector4D color);

  void SetPosition(float x, float y, float z);
  void SetColor(float r, float g, float b, float a);
  void SetColor(QVector4D color);
  void SetNormal();
  void SetTextureCoord();
};
}  // namespace QtEngine