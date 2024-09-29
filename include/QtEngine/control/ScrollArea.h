#pragma once

#include <QObject>
#include <QString>
#include <QLabel>
#include <QWidget>
#include <QScrollArea>

#include "QtEngine/Enums.h"
#include "QtEngine/control/Base.h"

namespace QtEngine
{
class ScrollArea : public QScrollArea, public Base
{
  Q_OBJECT

public:
  explicit ScrollArea(ThemeType theme = ThemeType::PRIMARY, ColorType color = ColorType::MAIN,
                      QWidget* parent = nullptr);

  void Update();
  virtual void SetThemeStyle(std::vector<Style> styles);
};
}  // namespace QtEngine