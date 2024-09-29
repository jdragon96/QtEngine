#include "QtEngine/opengl/Ray.h"

namespace QtEngine
{
Ray::Ray() : isTraced(false)
{
}
Ray::~Ray()
{
}
void Ray::UpdateRay(QMatrix4x4& projMat, QMatrix4x4& eye, QVector3D& camPos, double cursorX, double cursorY,
                    double width, double height)
{
  // 1. NDC => -1 ~ 1
  const double ndcX = 2 * cursorX / width - 1;
  const double ndcY = 1 - 2 * cursorY / height;
  // 2. Clip coord(Projection coord)
  auto ray_near_clip = QVector4D(ndcX, ndcY, -1.0, 1.0);
  // 3. Eye coord
  // auto rayStartPosFromNearClip = ray_near_clip * projMat.inverted() * eye.inverted();
  auto rayStartPosFromNearClip = (eye.inverted() * (projMat.inverted() * ray_near_clip));
  rayStartPosFromNearClip /= rayStartPosFromNearClip.w();
  // 4. Update
  rayDirection.setX(rayStartPosFromNearClip.x() - camPos.x());
  rayDirection.setY(rayStartPosFromNearClip.y() - camPos.y());
  rayDirection.setZ(rayStartPosFromNearClip.z() - camPos.z());
  rayDirection.normalize();
  rayPos.setX(camPos.x());
  rayPos.setY(camPos.y());
  rayPos.setZ(camPos.z());
}
bool Ray::Trace(MeshBuffer::SharedPtr meshBuffer, double& shortestDistance)
{
  double crntDistance = std::numeric_limits<double>::infinity();
  isTraced = false;
  if (meshBuffer->m_type != QtEngine::MeshBuffer::MeshType::TRIANGLE)
  {
    return isTraced;
  }

  for (auto& mesh : meshBuffer->m_mesh)
  {
    QtEngine::Vertex* p0;
    QtEngine::Vertex* p1;
    QtEngine::Vertex* p2;
    for (size_t i = 0; i < mesh.indices.size(); i += 3)
    {
      // 1. 매쉬 내 모든 삼각형에 대해 거리를 비교
      p0 = (&mesh.vertices[mesh.indices[i]]);
      p1 = (&mesh.vertices[mesh.indices[i + 1]]);
      p2 = (&mesh.vertices[mesh.indices[i + 2]]);
      if (IsTriangleIntersected(p0, p1, p2, crntDistance))
      {
        // 2. 광선 원점에서 더 가까운 매쉬 탐색
        if (crntDistance < shortestDistance)
        {
          shortestDistance = crntDistance;
          isTraced = true;
        }
      }
    }
  }

  if (isTraced)
  {
    tracedPos = rayPos + rayDirection * shortestDistance;
  }
  return isTraced;
}
bool Ray::IsTriangleIntersected(Vertex* p0, Vertex* p1, Vertex* p2, double& best_t)
{
  QVector3D edge1 = QVector3D(p1->x - p0->x, p1->y - p0->y, p1->z - p0->z);
  QVector3D edge2 = QVector3D(p2->x - p0->x, p2->y - p0->y, p2->z - p0->z);
  QVector3D ray_cross_e2 = QVector3D::crossProduct(rayDirection, edge2);

  // 1. Ray가 트라이앵글 평면과 평행한가?
  auto det = QVector3D::dotProduct(edge1, ray_cross_e2);
  if (det < 1e-5)
    return false;

  // 2.
  double inv_det = 1.0 / det;
  QVector3D s = QVector3D(rayPos.x() - p0->x, rayPos.y() - p0->y, rayPos.z() - p0->z);

  double u = inv_det * QVector3D::dotProduct(s, ray_cross_e2);
  if (u < 0 || u > 1)
    return false;

  // 3.
  QVector3D s_cross_e1 = QVector3D::crossProduct(s, edge1);
  double v = inv_det * QVector3D::dotProduct(rayDirection, s_cross_e1);
  if (v < 0 || u + v > 1)
    return false;

  // 4. 마지막 단계에선, point가 라인 중 어디에 교차하는지 찾아냄
  double t = inv_det * QVector3D::dotProduct(edge2, s_cross_e1);
  if (t > std::numeric_limits<double>::epsilon())
  {
    best_t = t;
    return true;
  }
  return false;
}
QVector3D& Ray::GetDirection()
{
  return rayDirection;
}
QVector3D& Ray::GetPosition()
{
  return rayPos;
}
QVector3D& Ray::GetTracedPos()
{
  return tracedPos;
}
}  // namespace QtEngine