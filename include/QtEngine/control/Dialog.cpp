#include "QtEngine/control/Dialog.h"

QtEngine::Dialog::Dialog(ThemeType theme, ColorType color, QWidget* parent) : QDialog(parent), Base(theme, color)
{
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setContentsMargins(0, 0, 0, 0);
  setStyleSheet(ThemeManager::instance().StyleString("QDialog", theme, color).c_str());
}

void QtEngine::Dialog::Update()
{
  setStyleSheet(ThemeManager::instance().StyleString("QDialog", m_theme, m_color).c_str());
  // update();
}

void QtEngine::Dialog::SetThemeStyle(std::vector<Style> styles)
{
  auto dict = ThemeManager::instance().MakeDictonaryStyle(m_theme, m_color);
  std::stringstream stream;
  for (auto& style : styles)
  {
    stream << ThemeManager::instance().MakeDictonaryStyle(dict, style);
  }
  setStyleSheet(stream.str().c_str());
}