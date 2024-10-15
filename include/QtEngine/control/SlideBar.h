#pragma once

#include <QDialog>
#include <QObject>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QMetaType>
#include "QtEngine/QtEngine.h"

namespace QtEngine
{
class SlideBar : public QtEngine::Widget
{
  Q_OBJECT

public:
  explicit SlideBar();
  virtual ~SlideBar();

  void ChangeControllerSize(float radius);
  void ChangeControllerColor(QColor color);
  void ChangeSlideOuterColor(QColor color);
  void ChangeSlideInnerColor(QColor color);
  void ChangeSlideBarSize(int height);
  void ChangeSliderBarMargin(int marign);
  void SetTick(int tick);
  void SetPercentage(float percent);

private:
  virtual void resizeEvent(QResizeEvent* e);
  virtual void mousePressEvent(QMouseEvent* e);
  virtual void mouseReleaseEvent(QMouseEvent* e);
  virtual void mouseMoveEvent(QMouseEvent* e);
  virtual void paintEvent(QPaintEvent* e);

protected:
  virtual void drawController(QPainter*);
  virtual void drawSlideBar(QPainter*);

signals:
  void changePercentage(float percent);

private:
  QColor m_controllerColor;
  QColor m_innerColor;
  QColor m_outerColor;
  QPointF m_pos;
  bool m_changeFlag;
  int m_slidebarHalfHeight;
  int m_slidebarMargin;
  float m_percentage;
  float m_tempPercentage;
  float m_radius;
  float m_startX;
  float m_endX;
  float m_margin;
  int m_tick;
};
}  // namespace experiment