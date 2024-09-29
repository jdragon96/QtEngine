#pragma once

#include <QBoxLayout>

#include "QtEngine/Enums.h"
#include "QtEngine/control/Base.h"
#include "QtEngine/control/Widget.h"
#include "QtEngine/control/VBoxLayout.h"

namespace QtEngine
{
class ContentBase : public Widget
{
public:
  ContentBase();

  virtual void SetTitleLayout(QBoxLayout* layout) = 0;
  virtual void SetBodyLayout(QBoxLayout* layout);
  virtual void SetTitleHeight(int height);
  virtual void SetBorder(std::string radius, std::string color);

  VBoxLayout* m_mainLayout;
  Widget* m_titleWidget;
  Widget* m_bodyWidget;
  int m_titleHeight;
  std::string m_radius;
  std::string m_borderColor;
};
}  // namespace QtEngine