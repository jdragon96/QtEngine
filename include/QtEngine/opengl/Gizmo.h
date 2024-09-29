#pragma once

#include <limits>

#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>

#include "QtEngine/opengl/MeshHelper.h"
#include "QtEngine/opengl/ShaderBuffer.h"
#include "QtEngine/opengl/MeshBuffer.h"
#include "QtEngine/opengl/Vertex.h"
#include "QtEngine/opengl/Ray.h"

namespace QtEngine
{
	class Gizmo
	{
	public:
		Gizmo();
		Gizmo(MeshBuffer::SharedPtr mesh, ShaderBuffer::SharedPtr shader);
		~Gizmo();

		void Render();
		void SetMatrix(QMatrix4x4& modelMat);
		void SetPosition();
		void SetRotation();
		void UpdateGizmo(bool mouseStatus);
		void UpdateRay(QMatrix4x4& projMat, QMatrix4x4& eye, QVector3D& camPos, double cursorX, double cursorY, double width,
			double height);
		void Rotate(float x, float y, float z);

		Ray m_ray;

	private:
		enum class GizmoType
		{
			UNKNOWN,
			TRANSLATE_X,
			TRANSLATE_Y,
			TRANSLATE_Z,
			ROTATE_X,
			ROTATE_Y,
			ROTATE_Z
		};

		void Rotate(QVector3D& axis, float& deg);
		void Move(QVector3D& axis);
		void FindPositionOfRayOnPlane(QVector3D& planePoint, QVector3D& planeNormal, QVector3D& pos);
		void MakeTranslateArrow();
		void MakeRotationTorus();
		QVector3D RotateAxis(QMatrix3x3& rotMatrix, QVector3D axis);

		GizmoType m_type;
		MeshBuffer::SharedPtr TranslateX;
		MeshBuffer::SharedPtr TranslateY;
		MeshBuffer::SharedPtr TranslateZ;
		MeshBuffer::SharedPtr RotationX;
		MeshBuffer::SharedPtr RotationY;
		MeshBuffer::SharedPtr RotationZ;
		MeshBuffer::SharedPtr Cursor;
		MeshBuffer::SharedPtr m_mesh;

		/* Shared */
		QVector3D crntObjectPos;
		QVector3D firstTracedPos;
		bool isPressedFirst = true;

		/* Move */
		QVector3D crntPosOnPlane;
		QVector3D prevPosOnPlane;
		bool isMoveStarted = false;
		QMatrix3x3 RotationMatrix;
		bool IsRotationStarted = false;
		float AngleX;
		float AngleY;
		float AngleZ;
		QVector3D AxisX;
		QVector3D AxisY;
		QVector3D AxisZ;

		QVector3D baseAxisX = QVector3D(1, 0, 0);
		QVector3D baseAxisY = QVector3D(0, 1, 0);
		QVector3D baseAxisZ = QVector3D(0, 0, 1);

		QQuaternion RotationAxis;
	};
}  // namespace QtEngine