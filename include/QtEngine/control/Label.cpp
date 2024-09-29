#include "QtEngine/control/Label.h"

QtEngine::Label::Label(ThemeType theme, ColorType color, QWidget* parent) : QLabel(parent), Base(theme, color)
{
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setAlignment(Qt::AlignmentFlag::AlignCenter);
  Update();
}

void QtEngine::Label::Update()
{
  setStyleSheet(ThemeManager::instance().StyleString("QLabel", m_theme, m_color).c_str());
  // update();
}
void QtEngine::Label::SetThemeStyle(std::vector<Style> styles)
{
  std::stringstream stream;
  for (auto& style : styles)
  {
    auto dict = ThemeManager::instance().MakeDictonaryStyle(m_theme, m_color);
    stream << ThemeManager::instance().MakeDictonaryStyle(dict, style);
  }
  setStyleSheet(stream.str().c_str());
}