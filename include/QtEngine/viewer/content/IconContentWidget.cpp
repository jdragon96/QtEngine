#include "QtEngine/viewer/content/IconContentWidget.h"

namespace QtEngine
{
IconContentWidget::IconContentWidget() : ContentBase(), m_iconColor("#000000")
{
  m_titleLayout = new HBoxLayout();
  m_titleLayout->setAlignment(Qt::AlignmentFlag::AlignLeft | Qt::AlignmentFlag::AlignVCenter);
  m_titleLayout->setMargin(0);
  icon = new Icon(ThemeType::PRIMARY, ColorType::DARK);
  m_titleLayout->addWidget(icon);
  ContentBase::SetTitleLayout(m_titleLayout);
}
void IconContentWidget::SetTitleLayout(QBoxLayout* layout)
{
  m_titleLayout->addLayout(layout);
}
void IconContentWidget::SetIcon(std::string path)
{
  icon->SetIcon(path);
  icon->setFixedSize(QSize(m_titleHeight, m_titleHeight));
  icon->SetIconSIze(QSize(m_titleHeight - 8, m_titleHeight - 8));
}
void IconContentWidget::SetPointColor(std::string radius, std::string borderColor, std::string iconBG)
{
  auto iconStyle = Style();
  iconStyle.control = "QLabel";
  iconStyle.borderRadius = "0px";
  iconStyle.borderTopLeftRadius = radius;
  iconStyle.borderTopRightRadius = "0px";
  iconStyle.borderBottomRightRadius = "0px";
  iconStyle.borderBottonLeftRadius = "0px";
  iconStyle.borderWidth = "1px";
  iconStyle.borderStyle = "solid";
  iconStyle.borderColor = borderColor;
  iconStyle.backgroundColor = m_iconColor = iconBG;
  icon->SetThemeStyle({ iconStyle });
}
}  // namespace QtEngine