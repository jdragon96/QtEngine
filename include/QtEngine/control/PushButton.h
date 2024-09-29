#pragma once

#include <string>

#include <QObject>
#include <QPushButton>
#include <QWidget>
#include <QSize>

#include "QtEngine/control/Base.h"

namespace QtEngine
{
class PushButton : public QPushButton, public Base
{
  Q_OBJECT

public:
  PushButton(ThemeType theme = ThemeType::PRIMARY, ColorType color = ColorType::MAIN, QWidget* parent = nullptr);

  virtual void Update();

  void AddIcon(std::string path, QSize size = QSize(30, 30));

  void SetThemeStyle(std::vector<Style> styles);
};
}  // namespace QtEngine