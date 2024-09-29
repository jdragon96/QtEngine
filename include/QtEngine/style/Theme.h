#pragma once
#include "QtEngine/style/Palette.h"
#include "QtEngine/style/Border.h"
#include "QtEngine/style/Font.h"
#include "QtEngine/style/Alarm.h"

namespace QtEngine
{
template <typename T>
class ThemeFamily
{
public:
  T Primary;
  T Secondary;
  T Tertiary;
};

class Theme
{
public:
  Theme();
  ~Theme();

  void SetBlueTheme();

  Alarm AlarmFamily;
  ThemeFamily<Palette> BGColorFamily;
  ThemeFamily<Palette> BorderColorFamily;
  ThemeFamily<std::string> FontColorFamily;
  ThemeFamily<Border> BorderFamily;
  ThemeFamily<Font> FontFamily;
};
}  // namespace QtEngine