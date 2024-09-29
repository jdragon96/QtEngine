
#include "QtEngine/control/TreeWidget.h"

QtEngine::TreeWidget::TreeWidget(ThemeType theme, ColorType color, QWidget* parent)
  : QTreeWidget(parent), Base(theme, color)
{
  this->setSelectionMode(QAbstractItemView::NoSelection);
  this->setFocusPolicy(Qt::NoFocus);
  this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  this->setContentsMargins(0, 0, 0, 0);
}
void QtEngine::TreeWidget::SetThemeStyle(std::vector<Style> styles)
{
  auto dict = ThemeManager::instance().MakeDictonaryStyle(m_theme, m_color);
  std::stringstream stream;
  for (auto& style : styles)
  {
    stream << ThemeManager::instance().MakeDictonaryStyle(dict, style);
  }
  setStyleSheet(stream.str().c_str());
}

void QtEngine::TreeWidget::Update()
{
}