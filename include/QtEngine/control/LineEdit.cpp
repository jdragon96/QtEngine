#include "QtEngine/control/LineEdit.h"

QtEngine::LineEdit::LineEdit(ThemeType theme, ColorType color, QWidget* parent) : QLineEdit(parent), Base(theme, color)
{
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  setStyleSheet(ThemeManager::instance().StyleString("QLineEdit", m_theme, m_color).c_str());
}

void QtEngine::LineEdit::Update()
{
  setStyleSheet(ThemeManager::instance().StyleString("QLineEdit", m_theme, m_color).c_str());
  // update();
}
void QtEngine::LineEdit::SetThemeStyle(std::vector<Style> styles)
{
  auto dict = ThemeManager::instance().MakeDictonaryStyle(m_theme, m_color);
  std::stringstream stream;
  for (auto& style : styles)
  {
    stream << ThemeManager::instance().MakeDictonaryStyle(dict, style);
  }
  setStyleSheet(stream.str().c_str());
}