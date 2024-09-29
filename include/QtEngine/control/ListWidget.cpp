#include "QtEngine/control/ListWidget.h"

QtEngine::ListWidget::ListWidget(ThemeType theme, ColorType color, QWidget* parent)
  : QListWidget(parent), Base(theme, color)
{
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
void QtEngine::ListWidget::SetThemeStyle(std::vector<Style> styles)
{
  auto dict = ThemeManager::instance().MakeDictonaryStyle(m_theme, m_color);
  std::stringstream stream;
  for (auto& style : styles)
  {
    stream << ThemeManager::instance().MakeDictonaryStyle(dict, style);
  }
  setStyleSheet(stream.str().c_str());
}