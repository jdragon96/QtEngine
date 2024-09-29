#include "QtEngine/viewer/content/ContentBase.h"

namespace QtEngine
{
ContentBase::ContentBase()
  : Widget(ThemeType::PRIMARY, ColorType::EMPTY), m_titleHeight(34), m_radius("0px"), m_borderColor("#000000")
{
  m_titleWidget = new Widget(ThemeType::PRIMARY, ColorType::DARKER);
  m_bodyWidget = new Widget(ThemeType::PRIMARY, ColorType::DARK);
  m_mainLayout = new VBoxLayout();
  m_mainLayout->addWidget(m_titleWidget);
  m_mainLayout->addWidget(m_bodyWidget);
  m_titleWidget->setContentsMargins(0, 0, 0, 0);
  m_mainLayout->setSpacing(0);
  this->SetTitleHeight(m_titleHeight);
  this->SetBorder(m_radius, m_borderColor);
  this->setLayout(m_mainLayout);
}

void ContentBase::SetTitleLayout(QBoxLayout* layout)
{
  m_titleWidget->setLayout(layout);
}
void ContentBase::SetBodyLayout(QBoxLayout* layout)
{
  m_bodyWidget->setLayout(layout);
}
void ContentBase::SetTitleHeight(int height)
{
  m_titleHeight = height;
  m_titleWidget->setFixedHeight(height);
}
void ContentBase::SetBorder(std::string radius, std::string color)
{
  m_borderColor = color;

  auto title = Style();
  title.control = "QWidget";
  title.borderRadius = "0px";
  title.borderTopRightRadius = radius;
  title.borderTopLeftRadius = radius;
  title.borderBottomRightRadius = "0px";
  title.borderBottonLeftRadius = "0px";
  title.borderWidth = "1px 1px 1px 1px";
  title.borderStyle = "solid";
  title.borderColor = color;
  auto body = Style();
  body.control = "QWidget";
  body.borderRadius = "0px";
  body.borderTopRightRadius = "0px";
  body.borderTopLeftRadius = "0px";
  body.borderBottomRightRadius = radius;
  body.borderBottonLeftRadius = radius;
  body.borderWidth = "0px 1px 1px 1px";
  body.borderStyle = "solid";
  body.borderColor = color;

  m_titleWidget->SetThemeStyle({ title });
  m_bodyWidget->SetThemeStyle({ body });
}
}  // namespace QtEngine