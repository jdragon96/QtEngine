#include "QtEngine/control/Base.h"

namespace QtEngine
{
Base::Base(ThemeType theme, ColorType color)
{
  m_theme = theme;
  m_color = color;
}

Base::~Base()
{
}
}  // namespace QtEngine