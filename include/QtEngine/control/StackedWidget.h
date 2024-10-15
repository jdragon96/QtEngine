#pragma once

#include <string>
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QStyle>
#include <QSizePolicy>
#include <QStyleOption>
#include <QPaintEvent>
#include <QStackedWidget>

#include "QtEngine/control/Base.h"

namespace QtEngine
{
class StackedWidget : public QStackedWidget, public Base
{
  Q_OBJECT

public:
  explicit StackedWidget(ThemeType theme = ThemeType::PRIMARY, ColorType color = ColorType::MAIN,
                         QWidget* parent = nullptr);

  virtual void Update();

  virtual void SetThemeStyle(std::vector<Style> styles);
};
}  // namespace QtEngine