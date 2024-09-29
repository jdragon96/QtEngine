#pragma once
#include "QtEngine/Macro.h"
#include "QtEngine/control/Widget.h"
#include "QtEngine/control/PushButton.h"
#include "QtEngine/control/VBoxLayout.h"
#include "QtEngine/control/HBoxLayout.h"

namespace QtEngine
{
class ThemeTester : public Widget
{
public:
  ThemeTester() : Widget(ThemeType::PRIMARY, ColorType::EMPTY)
  {
    auto mainLayout = new VBoxLayout();
    auto primary = new HBoxLayout();
    primary->addWidget(new PushButton(ThemeType::PRIMARY, ColorType::LIGHT));
    primary->addWidget(new PushButton(ThemeType::PRIMARY, ColorType::MAIN));
    primary->addWidget(new PushButton(ThemeType::PRIMARY, ColorType::DARK));
    primary->addWidget(new PushButton(ThemeType::PRIMARY, ColorType::DARKER));

    auto secondary = new HBoxLayout();
    secondary->addWidget(new PushButton(ThemeType::SECONDARY, ColorType::LIGHT));
    secondary->addWidget(new PushButton(ThemeType::SECONDARY, ColorType::MAIN));
    secondary->addWidget(new PushButton(ThemeType::SECONDARY, ColorType::DARK));
    secondary->addWidget(new PushButton(ThemeType::SECONDARY, ColorType::DARKER));

    auto tertiary = new HBoxLayout();
    tertiary->addWidget(new PushButton(ThemeType::TERTIARY, ColorType::LIGHT));
    tertiary->addWidget(new PushButton(ThemeType::TERTIARY, ColorType::MAIN));
    tertiary->addWidget(new PushButton(ThemeType::TERTIARY, ColorType::DARK));
    tertiary->addWidget(new PushButton(ThemeType::TERTIARY, ColorType::DARKER));
    mainLayout->addLayout(primary);
    mainLayout->addLayout(secondary);
    mainLayout->addLayout(tertiary);
    setLayout(mainLayout);
  }
};

}  // namespace QtEngine