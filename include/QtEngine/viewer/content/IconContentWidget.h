#pragma once

#include <QBoxLayout>

#include "QtEngine/Enums.h"
#include "QtEngine/control/Base.h"
#include "QtEngine/control/HBoxLayout.h"
#include "QtEngine/control/Icon.h"
#include "QtEngine/viewer/content/ContentBase.h"

namespace QtEngine
{
class IconContentWidget : public ContentBase
{
public:
  IconContentWidget();
  virtual void SetTitleLayout(QBoxLayout* layout) override;
  void SetIcon(std::string path);
  void SetPointColor(std::string radius, std::string borderColor, std::string iconBG);

  HBoxLayout* m_titleLayout;
  Widget* m_realTitleWidget;
  Icon* icon;
  std::string m_iconColor;
};
}  // namespace QtEngine