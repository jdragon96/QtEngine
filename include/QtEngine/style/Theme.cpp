#include "QtEngine/style/Theme.h"

namespace QtEngine
{
Theme::Theme()
{
}

Theme::~Theme()
{
}

void Theme::SetBlueTheme()
{
  AlarmFamily.Trace = "#FFFFFF";
  AlarmFamily.Debug = "#FFFFFF";
  AlarmFamily.Info = "#00FF00";
  AlarmFamily.Warning = "#FFFF00";
  AlarmFamily.Error = "#FF0000";
  AlarmFamily.Fatal = "#000000";

  BGColorFamily.Primary.Light = "#6B728E";
  BGColorFamily.Primary.Main = "#50577A";
  BGColorFamily.Primary.Dark = "#474E68";
  BGColorFamily.Primary.Darker = "#404258";

  // BGColorFamily.Secondary.Light = "#FEFFD2";
  // BGColorFamily.Secondary.Main = "#FFEEA9";
  // BGColorFamily.Secondary.Dark = "#FFBF78";
  // BGColorFamily.Secondary.Darker = "#FF7D29";
  BGColorFamily.Secondary.Light = "#7CF5FF";
  BGColorFamily.Secondary.Main = "#00CCDD";
  BGColorFamily.Secondary.Dark = "#4F75FF";
  BGColorFamily.Secondary.Darker = "#6439FF";

  BGColorFamily.Tertiary.Light = "#ECDFCC";
  BGColorFamily.Tertiary.Main = "#697565";
  BGColorFamily.Tertiary.Dark = "#3C3D37";
  BGColorFamily.Tertiary.Darker = "#181C14";

  BorderColorFamily.Primary.Light = "#0000FF";
  BorderColorFamily.Primary.Main = "#0000FF";
  BorderColorFamily.Primary.Dark = "#0000FF";
  BorderColorFamily.Primary.Darker = "#0000FF";

  BorderColorFamily.Secondary.Light = "#0000FF";
  BorderColorFamily.Secondary.Main = "#0000FF";
  BorderColorFamily.Secondary.Dark = "#0000FF";
  BorderColorFamily.Secondary.Darker = "#0000FF";

  BorderColorFamily.Tertiary.Light = "#0000FF";
  BorderColorFamily.Tertiary.Main = "#0000FF";
  BorderColorFamily.Tertiary.Dark = "#0000FF";
  BorderColorFamily.Tertiary.Darker = "#0000FF";

  BorderFamily.Primary.Style = "solid";
  BorderFamily.Primary.Width = "0px";
  BorderFamily.Primary.Radius = "0px";
  BorderFamily.Secondary.Style = "solid";
  BorderFamily.Secondary.Width = "1px";
  BorderFamily.Secondary.Radius = "4px";
  BorderFamily.Tertiary.Style = "solid";
  BorderFamily.Tertiary.Width = "2px";
  BorderFamily.Tertiary.Radius = "8px";

  FontFamily.Primary.Size = "13px";
  FontFamily.Primary.Family = "Aria";
  FontFamily.Primary.Weight = "none";
  FontFamily.Secondary.Size = "10px";
  FontFamily.Secondary.Family = "Aria";
  FontFamily.Secondary.Weight = "none";
  FontFamily.Tertiary.Size = "9px";
  FontFamily.Tertiary.Family = "Aria";
  FontFamily.Tertiary.Weight = "none";
}
}  // namespace QtEngine