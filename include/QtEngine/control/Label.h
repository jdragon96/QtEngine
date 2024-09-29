#pragma once

#include <QObject>
#include <QString>
#include <QLabel>
#include <QWidget>
#include "QtEngine/Enums.h"
#include "QtEngine/style/ThemeManager.h"
#include "QtEngine/control/Base.h"

namespace QtEngine
{
class Label : public QLabel, public Base
{
  Q_OBJECT
public:
  explicit Label(ThemeType theme = ThemeType::PRIMARY, ColorType color = ColorType::MAIN, QWidget* parent = nullptr);

  virtual void Update();

  virtual void SetThemeStyle(std::vector<Style> styles);
};
}  // namespace QtEngine