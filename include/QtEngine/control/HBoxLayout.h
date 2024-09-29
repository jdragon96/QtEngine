#pragma once

#include <QHBoxLayout>
#include "QtEngine/Enums.h"

namespace QtEngine
{
	class HBoxLayout : public QHBoxLayout
	{
		Q_OBJECT

	public:
		explicit HBoxLayout(QWidget* parent = nullptr);
	};
}  // namespace QtEngine