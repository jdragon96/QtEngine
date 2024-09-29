#include "QtEngine/OpenGL/Vertex.h"

using namespace QtEngine;

Vertex::Vertex()
{
}
Vertex::Vertex(QVector3D pos, QVector3D color)
{
  x = pos.x();
  y = pos.y();
  z = pos.z();
  r = color.x();
  g = color.y();
  b = color.z();
  a = 1.0;
}
Vertex::Vertex(QVector4D pos, QVector4D color)
{
  x = pos.x();
  y = pos.y();
  z = pos.z();
  r = color.x();
  g = color.y();
  b = color.z();
  a = color.w();
}

void Vertex::SetPosition(float _x, float _y, float _z)
{
  x = _x;
  y = _y;
  z = _z;
}

void Vertex::SetColor(float _r, float _g, float _b, float _a)
{
  r = _r;
  g = _g;
  b = _b;
  a = _a;
}
void Vertex::SetColor(QVector4D color)
{
  r = color.x();
  g = color.y();
  b = color.z();
  a = color.w();
}

void Vertex::SetNormal()
{
}

void Vertex::SetTextureCoord()
{
}