#pragma once

#include <QBoxLayout>
#include "QtEngine/control/Base.h"
#include "QtEngine/control/Widget.h"

namespace QtEngine
{
class SidebarBase : public Widget
{
public:
  SidebarBase();

  virtual void SetTitleLayout(QBoxLayout* layout) = 0;
  virtual void SetBodyLayout(QBoxLayout* layout) = 0;
};
}  // namespace QtEngine