#include "QtEngine/control/HBoxLayout.h"

namespace QtEngine
{
	HBoxLayout::HBoxLayout(QWidget* parent) : QHBoxLayout()
	{
		this->setMargin(0);
		this->setContentsMargins(0, 0, 0, 0);
    this->setSpacing(0);
	}
}