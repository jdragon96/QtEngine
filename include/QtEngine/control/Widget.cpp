#include "QtEngine/control/Widget.h"

QtEngine::Widget::Widget(ThemeType theme, ColorType color, QWidget* parent) : QWidget(parent), Base(theme, color)
{
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setContentsMargins(0, 0, 0, 0);
  setStyleSheet(ThemeManager::instance().StyleString("QWidget", theme, color).c_str());
}

void QtEngine::Widget::paintEvent(QPaintEvent* e)
{
  auto option = QStyleOption();
  option.initFrom(this);
  auto painter = QPainter(this);
  this->style()->drawPrimitive(QStyle::PE_Widget, &option, &painter, this);
  painter.end();
}

void QtEngine::Widget::Update()
{
  setStyleSheet(ThemeManager::instance().StyleString("QWidget", m_theme, m_color).c_str());
  // update();
}
void QtEngine::Widget::SetThemeStyle(std::vector<Style> styles)
{
  std::stringstream stream;
  for (auto& style : styles)
  {
    auto dict = ThemeManager::instance().MakeDictonaryStyle(m_theme, m_color);
    stream << ThemeManager::instance().MakeDictonaryStyle(dict, style);
  }
  setStyleSheet(stream.str().c_str());
}