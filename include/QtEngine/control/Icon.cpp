#include "QtEngine/control/Icon.h"

QtEngine::Icon::Icon(ThemeType theme, ColorType color, QWidget* parent) : QLabel(parent), Base(theme, color)
{
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setContentsMargins(0, 0, 0, 0);
  setStyleSheet(ThemeManager::instance().StyleString("QWidget", theme, color).c_str());
  setAlignment(Qt::AlignmentFlag::AlignCenter);
}

void QtEngine::Icon::SetIcon(std::string path)
{
  if (!m_img.load(path.c_str()))
    return;
}

void QtEngine::Icon::SetIconSIze(QSize size)
{
  auto img = m_img.scaled(size, Qt::AspectRatioMode::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);
  setPixmap(img);
}

void QtEngine::Icon::Update()
{
  setStyleSheet(ThemeManager::instance().StyleString("QWidget", m_theme, m_color).c_str());
}

void QtEngine::Icon::SetThemeStyle(std::vector<Style> styles)
{
  std::stringstream stream;
  for (auto& style : styles)
  {
    auto dict = ThemeManager::instance().MakeDictonaryStyle(m_theme, m_color);
    stream << ThemeManager::instance().MakeDictonaryStyle(dict, style);
  }
  setStyleSheet(stream.str().c_str());
}