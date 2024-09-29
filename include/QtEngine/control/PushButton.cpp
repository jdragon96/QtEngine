#include "QtEngine/control/PushButton.h"

QtEngine::PushButton::PushButton(ThemeType theme, ColorType color, QWidget* parent)
  : QPushButton(parent), Base(theme, color)
{
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  setStyleSheet(ThemeManager::instance().StyleString("QPushButton", theme, color).c_str());
}

void QtEngine::PushButton::AddIcon(std::string path, QSize size)
{
  QPixmap addPixmap;
  if (!addPixmap.load(path.c_str()))
    return;
  addPixmap =
      addPixmap.scaled(size, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
  QIcon addIcon;
  addIcon.addPixmap(addPixmap);
  setIcon(addIcon);
}

void QtEngine::PushButton::Update()
{
  setStyleSheet(ThemeManager::instance().StyleString("QPushButton", m_theme, m_color).c_str());
  // update();
}

void QtEngine::PushButton::SetThemeStyle(std::vector<Style> styles)
{
  std::stringstream stream;
  for (auto& style : styles)
  {
    auto dict = ThemeManager::instance().MakeDictonaryStyle(m_theme, m_color);
    stream << ThemeManager::instance().MakeDictonaryStyle(dict, style);
  }
  setStyleSheet(stream.str().c_str());
}