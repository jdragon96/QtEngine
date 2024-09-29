#include "QtEngine/opengl/Gizmo.h"
#include <cstdlib>
#include <QQuaternion>

namespace QtEngine
{
	Gizmo::Gizmo()
	{
	}
	Gizmo::Gizmo(MeshBuffer::SharedPtr mesh, ShaderBuffer::SharedPtr shader)
		: m_type(GizmoType::UNKNOWN), m_mesh(mesh), crntObjectPos(QVector3D(0, 0, 0))
	{
		RotationMatrix.setToIdentity();
		AxisX = QVector3D(1, 0, 0);
		AxisY = QVector3D(0, 1, 0);
		AxisZ = QVector3D(0, 0, 1);
		AngleX = 0.f;
		AngleY = 0.f;
		AngleZ = 0.f;
		Rotate(AngleX, AngleY, AngleZ);
		RotationAxis.setScalar(1);
		RotationAxis.setVector(QVector3D(0, 0, 0));

		TranslateX = MeshBuffer::MakeShared();
		TranslateX->SetShader(shader);
		TranslateX->SetMeshType(QtEngine::MeshBuffer::MeshType::TRIANGLE);
		TranslateX->SetMesh({ QtEngine::MeshHelper::MakeArrow(QVector3D(0, 0, 0), AxisX, QVector4D(1, 0, 0, 0.6),
																													crntObjectPos, 0.02, 0.05, 0.3) });
		TranslateY = MeshBuffer::MakeShared();
		TranslateY->SetShader(shader);
		TranslateY->SetMeshType(QtEngine::MeshBuffer::MeshType::TRIANGLE);
		TranslateY->SetMesh({ QtEngine::MeshHelper::MakeArrow(QVector3D(0, 0, 0), AxisY, QVector4D(0, 1, 0, 0.6),
																													crntObjectPos, 0.02, 0.05, 0.3) });
		TranslateZ = MeshBuffer::MakeShared();
		TranslateZ->SetShader(shader);
		TranslateZ->SetMeshType(QtEngine::MeshBuffer::MeshType::TRIANGLE);
		TranslateZ->SetMesh({ QtEngine::MeshHelper::MakeArrow(QVector3D(0, 0, 0), AxisZ, QVector4D(0, 0, 1, 0.6),
																													crntObjectPos, 0.02, 0.05, 0.3) });

		RotationX = MeshBuffer::MakeShared();
		RotationX->SetShader(shader);
		RotationX->SetMeshType(QtEngine::MeshBuffer::MeshType::TRIANGLE);
		RotationX->SetMesh({ QtEngine::MeshHelper::MakeTorus(QVector3D(AxisX), QVector4D(1, 0, 0, 1)) });

		RotationY = MeshBuffer::MakeShared();
		RotationY->SetShader(shader);
		RotationY->SetMeshType(QtEngine::MeshBuffer::MeshType::TRIANGLE);
		RotationY->SetMesh({ QtEngine::MeshHelper::MakeTorus(QVector3D(AxisY), QVector4D(0, 1, 0, 1)) });

		RotationZ = MeshBuffer::MakeShared();
		RotationZ->SetShader(shader);
		RotationZ->SetMeshType(QtEngine::MeshBuffer::MeshType::TRIANGLE);
		RotationZ->SetMesh({ QtEngine::MeshHelper::MakeTorus(QVector3D(AxisZ), QVector4D(0, 0, 1, 1)) });

		Cursor = MeshBuffer::MakeShared();
		Cursor->SetShader(shader);
		Cursor->SetMeshType(QtEngine::MeshBuffer::MeshType::TRIANGLE);
		Cursor->SetMesh({ QtEngine::MeshHelper::MakeSphere(QVector4D(1, 0, 1, 1), 0.04, 20, 20) });

		TranslateX->Initialize();
		TranslateY->Initialize();
		TranslateZ->Initialize();
		RotationX->Initialize();
		RotationY->Initialize();
		RotationZ->Initialize();
		Cursor->Initialize();
	}
	Gizmo::~Gizmo()
	{
	}
	void Gizmo::Render()
	{
		TranslateX->Render();
		TranslateY->Render();
		TranslateZ->Render();
		RotationX->Render();
		RotationY->Render();
		RotationZ->Render();
		Cursor->Render();
	}
	void Gizmo::SetMatrix(QMatrix4x4& modelMat)
	{
		// modelMatrix = modelMat;
	}
	void Gizmo::SetPosition()
	{
	}
	void Gizmo::SetRotation()
	{
	}
	void Gizmo::Rotate(float x, float y, float z)
	{
		// float radX = x / 180.f * 3.141592f;
		// float radY = y / 180.f * 3.141592f;
		// float radZ = z / 180.f * 3.141592f;
		// QMatrix3x3 rotZ;
		// rotZ.setToIdentity();
		// rotZ(0, 0) = cos(radZ);
		// rotZ(0, 1) = -sin(radZ);
		// rotZ(1, 0) = sin(radZ);
		// rotZ(1, 1) = cos(radZ);
		// QMatrix3x3 rotY;
		// rotY.setToIdentity();
		// rotY(0, 0) = cos(radY);
		// rotY(0, 2) = sin(radY);
		// rotY(2, 0) = -sin(radY);
		// rotY(2, 2) = cos(radY);
		// QMatrix3x3 rotX;
		// rotX.setToIdentity();
		// rotX(1, 1) = cos(radX);
		// rotX(1, 2) = -sin(radX);
		// rotX(2, 1) = sin(radX);
		// rotX(2, 2) = cos(radX);
		// RotationMatrix = ((rotZ * rotY) * rotX);
		//// RotationMatrix = ((rotX * rotY) * rotZ);,

		// AxisX = RotateAxis(RotationMatrix, baseAxisX);
		// AxisY = RotateAxis(RotationMatrix, baseAxisY);
		// AxisZ = RotateAxis(RotationMatrix, baseAxisZ);
		RotationAxis.getAxes(&AxisX, &AxisY, &AxisZ);
		RotationAxis.getEulerAngles(&AngleX, &AngleY, &AngleZ);
	}
	void Gizmo::UpdateGizmo(bool mouseStatus)
	{
		if (!mouseStatus)
		{
			isPressedFirst = false;
			isMoveStarted = false;
			IsRotationStarted = false;
			m_type = GizmoType::UNKNOWN;
			return;
		}

		// 1. Trace
		// 1.1. 처음 눌렸을 때, 어떤 유형이 선택된 것인지 파악한다.
		if (!isPressedFirst)
		{
			double shortestDist = std::numeric_limits<double>::infinity();
			if (m_ray.Trace(TranslateX, shortestDist))
				m_type = GizmoType::TRANSLATE_X;
			if (m_ray.Trace(TranslateY, shortestDist))
				m_type = GizmoType::TRANSLATE_Y;
			if (m_ray.Trace(TranslateZ, shortestDist))
				m_type = GizmoType::TRANSLATE_Z;
			if (m_ray.Trace(RotationX, shortestDist))
				m_type = GizmoType::ROTATE_X;
			if (m_ray.Trace(RotationY, shortestDist))
				m_type = GizmoType::ROTATE_Y;
			if (m_ray.Trace(RotationZ, shortestDist))
				m_type = GizmoType::ROTATE_Z;

			firstTracedPos = m_ray.GetPosition() + m_ray.GetDirection() * shortestDist;
			isPressedFirst = true;
		}

		if ((!isPressedFirst) || (m_type == GizmoType::UNKNOWN))
			return;

		// 2. Translate
		switch (m_type)
		{
		case GizmoType::TRANSLATE_X:
			Move(AxisX);
			break;
		case GizmoType::TRANSLATE_Y:
			Move(AxisY);
			break;
		case GizmoType::TRANSLATE_Z:
			Move(AxisZ);
			break;
		case GizmoType::ROTATE_X:
			Rotate(AxisX, AngleX);
			Rotate(AngleX, AngleY, AngleZ);
			break;
		case GizmoType::ROTATE_Y:
			// Rotate(AxisY, AngleY);
			Rotate(AxisY, AngleY);
			Rotate(AngleX, AngleY, AngleZ);
			break;
		case GizmoType::ROTATE_Z:
			// Rotate(AxisZ, AngleZ);
			Rotate(AxisZ, AngleZ);
			Rotate(AngleX, AngleY, AngleZ);
			break;
		}
		MakeTranslateArrow();
	}
	void Gizmo::UpdateRay(QMatrix4x4& projMat, QMatrix4x4& eye, QVector3D& camPos, double cursorX, double cursorY,
		double width, double height)
	{
		// std::cout << "Cursor : " << cursorX << ", " << cursorY << std::endl;
		m_ray.UpdateRay(projMat, eye, camPos, cursorX, cursorY, width, height);
	}
	void Gizmo::Rotate(QVector3D& axis, float& deg)
	{
		FindPositionOfRayOnPlane(firstTracedPos, axis, crntPosOnPlane);
		if (IsRotationStarted)
		{
			// QVector3D prevVec = (prevPosOnPlane - crntObjectPos).normalized();
			// QVector3D crntVec = (crntPosOnPlane - crntObjectPos).normalized();
			// float betRad = QVector3D::dotProduct(prevVec, crntVec);
			// if (betRad > 0.999f)
			//   return;

			// float d = QVector3D::dotProduct(QVector3D::crossProduct(prevVec, crntVec), axis);
			// float deltaRad = acos(betRad);
			// if (deltaRad < 1e-3)
			//   return;
			// float deltaDeg = deltaRad / 3.141592f * 180.f;
			// if (d > 0)
			//   deg += deltaDeg;
			// else
			//   deg -= deltaDeg;
			// if (deg > 360.f)
			//   deg = 0.f;
			// if (deg < 0)
			//   deg = 360.f;
			// std::cout << "[Rotate - " << deltaDeg << "] " << AngleX << ", " << AngleY << ", " << AngleZ << std::endl;
			QVector3D prevVec = (prevPosOnPlane - crntObjectPos).normalized();
			QVector3D crntVec = (crntPosOnPlane - crntObjectPos).normalized();
			float betRad = QVector3D::dotProduct(prevVec, crntVec);
			if (betRad > 0.999f)
				return;

			float d = QVector3D::dotProduct(QVector3D::crossProduct(prevVec, crntVec), axis);
			float deltaRad = acos(betRad);
			if (deltaRad < 1e-3)
				return;
			float deltaDeg = deltaRad / 3.141592f * 180.f;
			if (d > 0)
				deg += deltaDeg;
			else
				deg -= deltaDeg;
			if (deg > 360.f)
				deg = 0.f;
			if (deg < 0)
				deg = 360.f;
			// float r = deg / 180.f * 3.141592 * 0.5f;
			axis *= QVector3D::dotProduct(axis, QVector3D::crossProduct(prevVec, crntVec));
			axis.normalize();
			float r = deltaRad * 0.5f;
			QQuaternion q;
			q.setScalar(cos(r));
			q.setVector(QVector3D(sin(r) * axis.x(), sin(r) * axis.y(), sin(r) * axis.z()));
			RotationAxis = q * RotationAxis;
			std::cout << "[Rotate - " << deltaDeg << "] " << AngleX << ", " << AngleY << ", " << AngleZ << std::endl;
		}
		else
		{
			IsRotationStarted = true;
		}
		prevPosOnPlane = crntPosOnPlane;
	}
	void Gizmo::Move(QVector3D& axis)
	{
		QVector3D tangent = QVector3D::crossProduct(axis, firstTracedPos - m_ray.GetPosition());
		QVector3D planeNorm = QVector3D::crossProduct(axis, tangent);
		planeNorm.normalize();
		FindPositionOfRayOnPlane(firstTracedPos, planeNorm, crntPosOnPlane);
		if (isMoveStarted)
		{
			auto posterior = QVector3D::dotProduct(crntPosOnPlane - crntObjectPos, axis);
			auto prior = QVector3D::dotProduct(prevPosOnPlane - crntObjectPos, axis);
			crntObjectPos = crntObjectPos + axis * (posterior - prior);
			Cursor->SetPosition(crntObjectPos);
			std::cout << crntObjectPos.x() << ", " << crntObjectPos.y() << ", " << crntObjectPos.z() << std::endl;
		}
		else
		{
			isMoveStarted = true;
		}
		prevPosOnPlane = crntPosOnPlane;
	}
	void Gizmo::FindPositionOfRayOnPlane(QVector3D& planePoint, QVector3D& planeNormal, QVector3D& pos)
	{
		// 1. 이동 방향과 ray 방향이 동일하면 무시한다.
		double c = QVector3D::dotProduct(m_ray.GetDirection(), planeNormal);
		if (std::abs(c) < 1e-3)
			return;

		// 2. distance 계산
		double dist = QVector3D::dotProduct(planePoint - m_ray.GetPosition(), planeNormal) / c;
		if (dist < 1e-3)
			return;
		pos = m_ray.GetPosition() + dist * m_ray.GetDirection();
		// auto dir = m_ray.GetDirection();
		// std::cout << "Ray Direction : " << dir.x() << ", " << dir.y() << ", " << dir.z() << std::endl;
	}
	void Gizmo::MakeTranslateArrow()
	{
		TranslateX->UpdateMesh({ QtEngine::MeshHelper::MakeArrow(QVector3D(0, 0, 0), AxisX, QVector4D(1, 0, 0, 0.6),
																														 crntObjectPos, 0.02, 0.05, 0.3) });
		TranslateY->UpdateMesh({ QtEngine::MeshHelper::MakeArrow(QVector3D(0, 0, 0), AxisY, QVector4D(0, 1, 0, 0.6),
																														 crntObjectPos, 0.02, 0.05, 0.3) });
		TranslateZ->UpdateMesh({ QtEngine::MeshHelper::MakeArrow(QVector3D(0, 0, 0), AxisZ, QVector4D(0, 0, 1, 0.6),
																														 crntObjectPos, 0.02, 0.05, 0.3) });
		RotationX->UpdateMesh({ QtEngine::MeshHelper::MakeTorus(QVector3D(AxisX), QVector4D(1, 0, 0, 1), crntObjectPos) });
		RotationY->UpdateMesh({ QtEngine::MeshHelper::MakeTorus(QVector3D(AxisY), QVector4D(0, 1, 0, 1), crntObjectPos) });
		RotationZ->UpdateMesh({ QtEngine::MeshHelper::MakeTorus(QVector3D(AxisZ), QVector4D(0, 0, 1, 1), crntObjectPos) });
	}

	void Gizmo::MakeRotationTorus()
	{
	}

	QVector3D Gizmo::RotateAxis(QMatrix3x3& rotMatrix, QVector3D axis)
	{
		QVector3D newAxis;
		newAxis.setX(rotMatrix(0, 0) * axis.x() + rotMatrix(0, 1) * axis.y() + rotMatrix(0, 2) * axis.z());
		newAxis.setY(rotMatrix(1, 0) * axis.x() + rotMatrix(1, 1) * axis.y() + rotMatrix(1, 2) * axis.z());
		newAxis.setZ(rotMatrix(2, 0) * axis.x() + rotMatrix(2, 1) * axis.y() + rotMatrix(2, 2) * axis.z());
		return newAxis;
	}

}  // namespace QtEngine