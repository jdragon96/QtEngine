#include "SlideBar.h"

namespace experiment
{
SlideBar::SlideBar()
  : QtEngine::Widget(QtEngine::ThemeType::SECONDARY, QtEngine::ColorType::EMPTY)
  , m_radius(5)
  , m_changeFlag(false)
  , m_percentage(0.f)
  , m_slidebarHalfHeight(4)
  , m_slidebarMargin(2)
  , m_controllerColor(QColor(0, 0, 200))
  , m_innerColor(QColor(150, 150, 150))
  , m_outerColor(QColor(200, 200, 200))
  , m_tick(100)
{
  m_startX = m_radius;
  m_endX = width() - m_radius;
  m_margin = 2.f * m_radius;
  m_pos.setX(m_radius);
}
SlideBar::~SlideBar()
{
}
void SlideBar::ChangeControllerSize(float radius)
{
  if (width() < 2.f * m_radius)
    return;
  m_radius = radius;
  m_startX = m_radius;
  m_endX = width() - m_radius;
  m_margin = 2.f * m_radius;
  SetPercentage(m_percentage);
  setMinimumHeight(m_radius * 2 + 4);
}
void SlideBar::resizeEvent(QResizeEvent* e)
{
  QtEngine::Widget::resizeEvent(e);
  m_pos.setY(0.5f * e->size().height());
}
void SlideBar::mousePressEvent(QMouseEvent* e)
{
  QtEngine::Widget::mousePressEvent(e);
  if ((abs(e->pos().y() - m_pos.y()) < m_radius) && (abs(e->pos().x() - m_pos.x()) < m_radius))
  {
    m_changeFlag = true;
    update();
  }
}
void SlideBar::SetPercentage(float percent)
{
  m_percentage = percent;
  float posX = percent * (static_cast<float>(width()) - m_margin) + m_radius;
  m_pos.setX(posX);
  update();
}
void SlideBar::mouseReleaseEvent(QMouseEvent* e)
{
  QtEngine::Widget::mouseReleaseEvent(e);
  m_changeFlag = false;
}
void SlideBar::mouseMoveEvent(QMouseEvent* evt)
{
  QtEngine::Widget::mouseMoveEvent(evt);
  if (false == m_changeFlag)
    return;
  m_pos.setX(evt->pos().x());
  if (m_pos.x() <= m_radius)
    m_pos.setX(m_radius);
  if (m_pos.x() >= (static_cast<float>(width()) - m_radius))
    m_pos.setX(static_cast<float>(width()) - m_radius);
  m_tempPercentage = static_cast<float>(m_pos.x() - m_radius) /
                     (static_cast<float>(width()) - m_margin);  // 계산결과가 동일한 경우 무시하기
  m_tempPercentage = ceil(m_tempPercentage * m_tick) / m_tick;
  if (m_tempPercentage == m_percentage)
    return;
  emit changePercentage(m_tempPercentage);
  m_percentage = m_tempPercentage;
  update();
}
void SlideBar::drawController(QPainter* painter)
{
  painter->setBrush(QBrush(m_controllerColor, Qt::SolidPattern));
  painter->drawEllipse(
      QRectF(QPointF(m_pos.x() - m_radius, m_pos.y() - m_radius), QPointF(m_pos.x() + m_radius, m_pos.y() + m_radius)));
}
void SlideBar::drawSlideBar(QPainter* painter)
{
  painter->setBrush(QBrush(m_innerColor, Qt::SolidPattern));
  painter->drawRect(QRectF(QPointF(m_radius, m_pos.y() - m_slidebarHalfHeight),
                           QPointF(width() - m_radius, m_pos.y() + m_slidebarHalfHeight)));
  painter->setBrush(QBrush(m_outerColor, Qt::SolidPattern));
  painter->drawRect(QRectF(QPointF(m_radius + m_slidebarMargin, m_pos.y() - m_slidebarMargin),
                           QPointF(width() - m_radius - m_slidebarMargin, m_pos.y() + m_slidebarMargin)));
}
void SlideBar::ChangeControllerColor(QColor color)
{
  m_controllerColor = color;
}
void SlideBar::ChangeSlideOuterColor(QColor color)
{
  m_outerColor = color;
}
void SlideBar::ChangeSlideInnerColor(QColor color)
{
  m_innerColor = color;
}
void SlideBar::ChangeSlideBarSize(int height)
{
}
void SlideBar::ChangeSliderBarMargin(int marign)
{
}
void SlideBar::SetTick(int tick)
{
  m_tick = tick;
}
void SlideBar::paintEvent(QPaintEvent* e)
{
  QtEngine::Widget::paintEvent(e);
  QPainter painter(this);
  painter.setRenderHints(QPainter::Antialiasing);
  painter.setPen(Qt::PenStyle::NoPen);
  drawSlideBar(&painter);
  drawController(&painter);
}
}  // namespace experiment