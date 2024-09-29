#pragma once

#include <QVBoxLayout>

#include "QtEngine/Enums.h"

namespace QtEngine
{
	class VBoxLayout : public QVBoxLayout
	{
		Q_OBJECT
	public:
		explicit VBoxLayout(QWidget* parent = nullptr);
	};
}  // namespace QtEngine