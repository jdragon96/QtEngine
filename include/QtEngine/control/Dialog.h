#pragma once

#include <string>
#include <QObject>
#include <QDialog>
#include <QPainter>
#include <QStyle>
#include <QSizePolicy>
#include <QStyleOption>
#include <QPaintEvent>

#include "QtEngine/control/Base.h"

namespace QtEngine
{
class Dialog : public QDialog, public Base
{
  Q_OBJECT

public:
  explicit Dialog(ThemeType theme = ThemeType::PRIMARY, ColorType color = ColorType::MAIN, QWidget* parent = nullptr);

  virtual void Update();

  virtual void SetThemeStyle(std::vector<Style> styles);
};
}  // namespace QtEngine