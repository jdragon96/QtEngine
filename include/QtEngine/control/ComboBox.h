#pragma once

#include <QObject>
#include <functional>
#include <QComboBox>
#include <QSizePolicy>

#include "QtEngine/Enums.h"	

namespace QtEngine
{
	template <typename T>
	class ComboBox : public QComboBox
	{
	public:
		explicit ComboBox(ThemeType theme = ThemeType::PRIMARY, ColorType color = ColorType::MAIN, , QWidget* parent = nullptr) : QComboBox(parent)
		{
			this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		}

		void SetRule(std::function<std::string(T)> rule)
		{
			thumailRule = rule;
		}

		void SetValues(std::vector<T>* values)
		{
			this->clear();
			this->values = values;
			for (auto& value : (*values))
			{
				addItem(thumailRule(value).c_str());
			}
		}

		virtual void update()
		{
			QComboBox::update();
		}

		std::vector<T>* values;
		std::function<std::string(T)> thumailRule = [](T) -> std::string { return std::string(""); };
	};
}  // namespace QtEngine