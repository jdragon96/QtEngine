#pragma once

#include <string>
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QStyle>
#include <QSizePolicy>
#include <QStyleOption>
#include <QPaintEvent>

#include "QtEngine/Enums.h"
#include "QtEngine/style/ThemeManager.h"

namespace QtEngine
{
class Base
{
public:
  Base(ThemeType theme, ColorType color);
  ~Base();

  ThemeType m_theme;
  ColorType m_color;

  virtual void Update() = 0;

  virtual void SetThemeStyle(std::vector<Style> styles) = 0;
};
}  // namespace QtEngine