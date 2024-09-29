#pragma once

#include <vector>
#include <QVector4D>
#include <QVector3D>
#include <QtEngine/OpenGL/Vertex.h>
#include <QtEngine/OpenGL/Mesh.h>

namespace QtEngine
{
class MeshHelper
{
public:
  /*
   * start: Arrow 시작점
   * end: Arrow 끝점
   * color: Arrow 컬러
   * smallRadius: Arrow 몸통 반지름
   * largeRadius: Arrow 머리 반지름
   * headRatio: 전체 길이에 대한 머리 길이 비율
   * sliceNum: 원 생성시 사용하는 vertex 개수
   */
  static Mesh MakeArrow(QVector3D start, QVector3D end, QVector4D color, QVector3D translate, float smallRadius,
                        float largeRadius, float headRatio);

  /*
   * radius : 반지름
   * slice: 원 생성 시 사용하는 vertex 개수
   * rotAxis: Torus 기준 축
   * startPos: Torus 원점
   * color: Torus 색상값
   */
  static Mesh MakeTorus(QVector3D axis, QVector4D color, QVector3D pos = QVector3D(0, 0, 0));

  static Mesh MakeAxis(float scale);

  static Mesh MakeSphere(QVector4D color, const float radius, const int numSlice, const int numStack);
};
}  // namespace QtEngine