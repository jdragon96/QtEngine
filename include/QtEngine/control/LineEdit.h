#pragma once

#include <QObject>
#include <QLineEdit>

#include "QtEngine/Enums.h"
#include "QtEngine/control/Base.h"
#include "QtEngine/style/ThemeManager.h"

namespace QtEngine
{
class LineEdit : public QLineEdit, public Base
{
  Q_OBJECT
public:
  LineEdit(ThemeType theme = ThemeType::PRIMARY, ColorType color = ColorType::MAIN, QWidget* parent = nullptr);
  void Update();
  virtual void SetThemeStyle(std::vector<Style> styles);
};
}  // namespace QtEngine