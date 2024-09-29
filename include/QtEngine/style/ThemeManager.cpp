#include "QtEngine/style/ThemeManager.h"

namespace QtEngine
{
void ThemeManager::UpdateTheme(Theme theme)
{
  mainTheme = theme;
}

std::string ThemeManager::StyleString(std::string target, ThemeType theme, ColorType color)
{
  std::stringstream stream;
  stream << target << "{";
  switch (theme)
  {
    case ThemeType::PRIMARY:
      stream << "background-color: " << this->Color(&mainTheme.BGColorFamily.Primary, color) << ";";
      stream << "border-color: " << this->Color(&mainTheme.BorderColorFamily.Primary, color) << ";";
      stream << "border-width: " << mainTheme.BorderFamily.Primary.Width << ";";
      stream << "border-style: " << mainTheme.BorderFamily.Primary.Style << ";";
      stream << "border-radius: " << mainTheme.BorderFamily.Primary.Radius << ";";
      stream << "font-size: " << mainTheme.FontFamily.Primary.Size << ";";
      stream << "font-family: " << mainTheme.FontFamily.Primary.Family << ";";
      stream << "font-weight: " << mainTheme.FontFamily.Primary.Weight << ";";
      stream << "color: " << mainTheme.FontColorFamily.Primary << ";";
      break;
    case ThemeType::SECONDARY:
      stream << "background-color: " << this->Color(&mainTheme.BGColorFamily.Secondary, color) << ";";
      stream << "border-color: " << this->Color(&mainTheme.BorderColorFamily.Secondary, color) << ";";
      stream << "border-width: " << mainTheme.BorderFamily.Secondary.Width << ";";
      stream << "border-style: " << mainTheme.BorderFamily.Secondary.Style << ";";
      stream << "border-radius: " << mainTheme.BorderFamily.Secondary.Radius << ";";
      stream << "font-size: " << mainTheme.FontFamily.Secondary.Size << ";";
      stream << "font-family: " << mainTheme.FontFamily.Secondary.Family << ";";
      stream << "font-weight: " << mainTheme.FontFamily.Secondary.Weight << ";";
      stream << "color: " << mainTheme.FontColorFamily.Secondary << ";";
      break;
    case ThemeType::TERTIARY:
      stream << "background-color: " << this->Color(&mainTheme.BGColorFamily.Tertiary, color) << ";";
      stream << "border-color: " << this->Color(&mainTheme.BorderColorFamily.Tertiary, color) << ";";
      stream << "border-width: " << mainTheme.BorderFamily.Tertiary.Width << ";";
      stream << "border-style: " << mainTheme.BorderFamily.Tertiary.Style << ";";
      stream << "border-radius: " << mainTheme.BorderFamily.Tertiary.Radius << ";";
      stream << "font-size: " << mainTheme.FontFamily.Tertiary.Size << ";";
      stream << "font-family: " << mainTheme.FontFamily.Tertiary.Family << ";";
      stream << "font-weight: " << mainTheme.FontFamily.Tertiary.Weight << ";";
      stream << "color: " << mainTheme.FontColorFamily.Tertiary << ";";
      break;
  }
  stream << "}";
  return stream.str();
}

std::string ThemeManager::Color(Palette* value, ColorType type)
{
  switch (type)
  {
    case ColorType::LIGHT:
      return value->Light;
      break;
    case ColorType::MAIN:
      return value->Main;
      break;
    case ColorType::DARK:
      return value->Dark;
      break;
    case ColorType::DARKER:
      return value->Darker;
      break;
    case ColorType::EMPTY:
      return "transparent";
      break;
    default:
      return "";
      break;
  }
}
std::unordered_map<std::string, std::string> ThemeManager::MakeDictonaryStyle(ThemeType theme, ColorType color)
{
  std::unordered_map<std::string, std::string> hash;
  switch (theme)
  {
    case ThemeType::PRIMARY:
      hash["background-color"] = this->Color(&mainTheme.BGColorFamily.Primary, color);
      hash["border-color"] = this->Color(&mainTheme.BorderColorFamily.Primary, color);
      hash["border-width"] = mainTheme.BorderFamily.Primary.Width;
      hash["border-style"] = mainTheme.BorderFamily.Primary.Style;
      hash["border-radius"] = mainTheme.BorderFamily.Primary.Radius;
      hash["font-size"] = mainTheme.FontFamily.Primary.Size;
      hash["font-family"] = mainTheme.FontFamily.Primary.Family;
      hash["font-weight"] = mainTheme.FontFamily.Primary.Weight;
      hash["color"] = mainTheme.FontColorFamily.Primary;
      break;
    case ThemeType::SECONDARY:
      hash["background-color"] = this->Color(&mainTheme.BGColorFamily.Secondary, color);
      hash["border-color"] = this->Color(&mainTheme.BorderColorFamily.Secondary, color);
      hash["border-width"] = mainTheme.BorderFamily.Secondary.Width;
      hash["border-style"] = mainTheme.BorderFamily.Secondary.Style;
      hash["border-radius"] = mainTheme.BorderFamily.Secondary.Radius;
      hash["font-size"] = mainTheme.FontFamily.Secondary.Size;
      hash["font-family"] = mainTheme.FontFamily.Secondary.Family;
      hash["font-weight"] = mainTheme.FontFamily.Secondary.Weight;
     hash["color"] = mainTheme.FontColorFamily.Secondary;
      break;
    case ThemeType::TERTIARY:
      hash["background-color"] = this->Color(&mainTheme.BGColorFamily.Tertiary, color);
      hash["border-color"] = this->Color(&mainTheme.BorderColorFamily.Tertiary, color);
      hash["border-width"] = mainTheme.BorderFamily.Tertiary.Width;
      hash["border-style"] = mainTheme.BorderFamily.Tertiary.Style;
      hash["border-radius"] = mainTheme.BorderFamily.Tertiary.Radius;
      hash["font-size"] = mainTheme.FontFamily.Tertiary.Size;
      hash["font-family"] = mainTheme.FontFamily.Tertiary.Family;
      hash["font-weight"] = mainTheme.FontFamily.Tertiary.Weight;
      hash["color"] = mainTheme.FontColorFamily.Tertiary;
      break;
  }
  return hash;
}
std::string ThemeManager::MakeDictonaryStyle(std::unordered_map<std::string, std::string>& hash, Style& style)
{
  if (!style.borderRadius.empty())
  {
    if (style.borderBottomRightRadius.empty() && style.borderBottonLeftRadius.empty() &&
        style.borderTopLeftRadius.empty() && style.borderTopRightRadius.empty())
    {
      hash["border-radius"] = style.borderRadius;
    }
  }

  if (!style.backgroundColor.empty())
    hash["background-color"] = style.backgroundColor;

  if (!style.borderTopLeftRadius.empty())
  {
    hash["border-top-left-radius"] = style.borderTopLeftRadius;
    hash.erase("border-radius");
  }

  if (!style.borderTopRightRadius.empty())
  {
    hash["border-top-right-radius"] = style.borderTopRightRadius;
    hash.erase("border-radius");
  }

  if (!style.borderBottomRightRadius.empty())
  {
    hash["border-bottom-right-radius"] = style.borderBottomRightRadius;
    hash.erase("border-radius");
  }
  if (!style.borderBottonLeftRadius.empty())
  {
    hash["border-bottom-left-radius"] = style.borderBottonLeftRadius;
    hash.erase("border-radius");
  }

  if (!style.borderColor.empty())
    hash["border-color"] = style.borderColor;

  if (!style.borderStyle.empty())
    hash["border-style"] = style.borderStyle;

  if (!style.borderWidth.empty())
    hash["border-width"] = style.borderWidth;

  if (!style.font.empty())
    hash["font-family"] = style.font;

  if (!style.fontColor.empty())
    hash["color"] = style.fontColor;

  if (!style.fontWeight.empty())
    hash["font-weight"] = style.fontWeight;

  std::stringstream stream;
  stream << style.control << "{";
  for (auto value : hash)
  {
    stream << value.first << ": " << value.second << ";";
  }
  stream << "}";
  return stream.str();
}
}  // namespace QtEngine