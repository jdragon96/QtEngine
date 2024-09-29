#pragma once
#include <iostream>
#include <memory>
#include <string>

#include <QtGui/qevent.h>
#include <QtGui/qopenglfunctions.h>
#include <QtGui/qopenglshaderprogram.h>
#include <QtGui/qopenglvertexarrayobject.h>
#include <glm/common.hpp>
#include <glm/matrix.hpp>

#include <QtWidgets/qopenglwidget.h>

#include "QtEngine/Macro.h"
#include "QtEngine/opengl/Mesh.h"

namespace QtEngine
{
	class QGLHelper
	{
	public:
		static void BindVertexBuffer(QOpenGLVertexArrayObject& vao, unsigned int& vbo, unsigned int& ebo, QtEngine::Mesh& mesh)
		{
			auto func = QOpenGLContext::currentContext()->functions();
			vao.create();
			func->glGenBuffers(1, &vbo);
			func->glGenBuffers(1, &ebo);

			int vertexBufferSize = sizeof(QtEngine::Vertex) * mesh.vertices.size();
			int indexBufferSize = sizeof(uint32_t) * mesh.indices.size();

			// glBindVertexArray(vao);
			vao.bind();
			func->glBindBuffer(GL_ARRAY_BUFFER, vbo);
			func->glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, mesh.vertices.data(), GL_STATIC_DRAW);

			func->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			func->glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, mesh.indices.data(), GL_STATIC_DRAW);

			int vtxSize = sizeof(QtEngine::Vertex);
			int xyzOffset = 0;
			int rgbOffset = sizeof(float) * 3;
			int normalOffset = sizeof(float) * 7;
			int textureOffset = sizeof(float) * 10;

			func->glEnableVertexAttribArray(0);
			func->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vtxSize, (void*)xyzOffset);

			func->glEnableVertexAttribArray(1);
			func->glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vtxSize, (void*)rgbOffset);

			func->glEnableVertexAttribArray(2);
			func->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vtxSize, (void*)normalOffset);

			func->glEnableVertexAttribArray(3);
			func->glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, vtxSize, (void*)textureOffset);

			func->glBindBuffer(GL_ARRAY_BUFFER, 0);
			// glBindVertexArray(0);
			vao.release();
		}

		static void BindShader(QOpenGLShaderProgram* shader, std::string vertexPath, std::string fragPath)
		{
			shader->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexPath.c_str());
			shader->addShaderFromSourceFile(QOpenGLShader::Fragment, fragPath.c_str());
			if (!shader->link())
			{
				std::cout << "링크실패" << std::endl;
			}
		}

		static void glmToQMatrix44(glm::mat4& glMat, QMatrix4x4& qMat)
		{
			// QMatrix: (row, column)
			// glm::mat4: [column, row]
			qMat(0, 0) = glMat[0][0];
			qMat(0, 1) = glMat[1][0];
			qMat(0, 2) = glMat[2][0];
			qMat(0, 3) = glMat[3][0];

			qMat(1, 0) = glMat[0][1];
			qMat(1, 1) = glMat[1][1];
			qMat(1, 2) = glMat[2][1];
			qMat(1, 3) = glMat[3][1];

			qMat(2, 0) = glMat[0][2];
			qMat(2, 1) = glMat[1][2];
			qMat(2, 2) = glMat[2][2];
			qMat(2, 3) = glMat[3][2];

			qMat(3, 0) = glMat[0][3];
			qMat(3, 1) = glMat[1][3];
			qMat(3, 2) = glMat[2][3];
			qMat(3, 3) = glMat[3][3];
		}
	};
}  // namespace QtEngine