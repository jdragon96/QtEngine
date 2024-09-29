#pragma once

#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>

#include "QtEngine/style/Theme.h"
#include "QtEngine/style/Style.h"
#include "QtEngine/Enums.h"

namespace QtEngine
{
class ThemeManager
{
public:
  static ThemeManager& instance()
  {
    static ThemeManager inst;
    return inst;
  }

  std::unordered_map<std::string, std::string> MakeDictonaryStyle(ThemeType theme, ColorType color);
  std::string MakeDictonaryStyle(std::unordered_map<std::string, std::string>& hash, Style& style);

  void UpdateTheme(Theme theme);

  std::string StyleString(std::string target, ThemeType theme, ColorType color);

  Theme mainTheme;

private:
  std::string Color(Palette* value, ColorType type);
};
}  // namespace QtEngine