#pragma once

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QStyle>
#include <QSizePolicy>
#include <QStyleOption>
#include <QPaintEvent>
#include <QListWidget>
#include "QtEngine/QtEngine.h"

#include <string>


namespace QtEngine
{
class ListWidget : public QListWidget, public Base
{
  Q_OBJECT
public:
  explicit ListWidget(ThemeType theme = ThemeType::PRIMARY, ColorType color = ColorType::MAIN, QWidget* parent = nullptr);
  virtual void SetThemeStyle(std::vector<Style> styles);
};
}  // namespace QtEngine