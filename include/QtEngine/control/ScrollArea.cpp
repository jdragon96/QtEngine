#include "QtEngine/control/ScrollArea.h"

QtEngine::ScrollArea::ScrollArea(ThemeType theme, ColorType color, QWidget* parent)
  : QScrollArea(parent), Base(theme, color)
{
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void QtEngine::ScrollArea::Update()
{
  setStyleSheet(ThemeManager::instance().StyleString("QWidget", m_theme, m_color).c_str());
}
void QtEngine::ScrollArea::SetThemeStyle(std::vector<Style> styles)
{
  auto dict = ThemeManager::instance().MakeDictonaryStyle(m_theme, m_color);
  std::stringstream stream;
  for (auto& style : styles)
  {
    stream << ThemeManager::instance().MakeDictonaryStyle(dict, style);
  }
  setStyleSheet(stream.str().c_str());
}