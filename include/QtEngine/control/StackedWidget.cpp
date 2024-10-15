#include "QtEngine/control/StackedWidget.h"

QtEngine::StackedWidget::StackedWidget(ThemeType theme, ColorType color, QWidget* parent)
  : QStackedWidget(parent), Base(theme, color)
{
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setContentsMargins(0, 0, 0, 0);
  setStyleSheet(ThemeManager::instance().StyleString("QStackedWidget", theme, color).c_str());
}

void QtEngine::StackedWidget::Update()
{
  setStyleSheet(ThemeManager::instance().StyleString("QStackedWidget", m_theme, m_color).c_str());
  // update();
}
void QtEngine::StackedWidget::SetThemeStyle(std::vector<Style> styles)
{
  std::stringstream stream;
  for (auto& style : styles)
  {
    auto dict = ThemeManager::instance().MakeDictonaryStyle(m_theme, m_color);
    stream << ThemeManager::instance().MakeDictonaryStyle(dict, style);
  }
  setStyleSheet(stream.str().c_str());
}