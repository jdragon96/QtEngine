#include "QtEngine/control/VBoxLayout.h"

namespace QtEngine
{
	VBoxLayout::VBoxLayout(QWidget* parent) : QVBoxLayout()
	{
		this->setMargin(0);
		this->setContentsMargins(0, 0, 0, 0);
	}
}