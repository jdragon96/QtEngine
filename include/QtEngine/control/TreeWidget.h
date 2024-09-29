#pragma once

#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QStyle>
#include <QSizePolicy>
#include <QStyleOption>
#include <QPaintEvent>
#include <QListWidget>
#include <QTreeWidget>

#include "QtEngine/Enums.h"
#include "QtEngine/QtEngine.h"

#include <string>

namespace QtEngine
{
class TreeWidget : public QTreeWidget, public Base
{
  Q_OBJECT
public:
  explicit TreeWidget(ThemeType theme = ThemeType::PRIMARY, ColorType color = ColorType::MAIN,
                      QWidget* parent = nullptr);
  virtual void SetThemeStyle(std::vector<Style> styles);

  virtual void Update();
};
}  // namespace QtEngine