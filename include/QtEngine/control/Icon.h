#pragma once

#include <string>
#include <QObject>
#include <QWidget>
#include <QPainter>
#include <QStyle>
#include <QSizePolicy>
#include <QStyleOption>
#include <QPaintEvent>
#include <QLabel>
#include <QPixmap>
#include <QSize>

#include "QtEngine/control/Base.h"

namespace QtEngine
{
class Icon : public QLabel, public Base
{
  Q_OBJECT

public:
  explicit Icon(ThemeType theme = ThemeType::PRIMARY, ColorType color = ColorType::MAIN, QWidget* parent = nullptr);

  void SetIcon(std::string path);

  void SetIconSIze(QSize size);

  virtual void Update();

  virtual void SetThemeStyle(std::vector<Style> styles);

  QPixmap m_img;
};
}  // namespace QtEngine