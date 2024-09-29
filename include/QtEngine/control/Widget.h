#pragma once

#include <string>
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QStyle>
#include <QSizePolicy>
#include <QStyleOption>
#include <QPaintEvent>

#include "QtEngine/control/Base.h"

namespace QtEngine
{
class Widget : public QWidget, public Base
{
  Q_OBJECT

public:
  explicit Widget(ThemeType theme = ThemeType::PRIMARY, ColorType color = ColorType::MAIN, QWidget* parent = nullptr);

  virtual void Update();

  virtual void SetThemeStyle(std::vector<Style> styles);

protected:
  virtual void paintEvent(QPaintEvent* e);
};
}  // namespace QtEngine