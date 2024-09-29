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
   * start: Arrow ������
   * end: Arrow ����
   * color: Arrow �÷�
   * smallRadius: Arrow ���� ������
   * largeRadius: Arrow �Ӹ� ������
   * headRatio: ��ü ���̿� ���� �Ӹ� ���� ����
   * sliceNum: �� ������ ����ϴ� vertex ����
   */
  static Mesh MakeArrow(QVector3D start, QVector3D end, QVector4D color, QVector3D translate, float smallRadius,
                        float largeRadius, float headRatio);

  /*
   * radius : ������
   * slice: �� ���� �� ����ϴ� vertex ����
   * rotAxis: Torus ���� ��
   * startPos: Torus ����
   * color: Torus ����
   */
  static Mesh MakeTorus(QVector3D axis, QVector4D color, QVector3D pos = QVector3D(0, 0, 0));

  static Mesh MakeAxis(float scale);

  static Mesh MakeSphere(QVector4D color, const float radius, const int numSlice, const int numStack);
};
}  // namespace QtEngine