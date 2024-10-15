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

namespace experiment
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

class DetachTitleBar : public QtEngine::Widget
{
  Q_OBJECT

public:
  explicit DetachTitleBar() : QtEngine::Widget(QtEngine::ThemeType::PRIMARY, QtEngine::ColorType::DARK)
  {
    QHBoxLayout* layout = new QtEngine::HBoxLayout();
    maxButton = new QtEngine::PushButton(QtEngine::ThemeType::SECONDARY, QtEngine::ColorType::DARK);
    maxButton->setFixedSize(25, 25);
    maxButton->setText("+");
    closeButton = new QtEngine::PushButton(QtEngine::ThemeType::SECONDARY, QtEngine::ColorType::DARK);
    closeButton->setFixedSize(25, 25);
    closeButton->setText("x");
    layout->addStretch();
    layout->addWidget(maxButton);
    layout->addWidget(closeButton);
    layout->setContentsMargins(0, 0, 4, 0);
    layout->setAlignment(Qt::AlignmentFlag::AlignRight | Qt::AlignmentFlag::AlignVCenter);
    setLayout(layout);
    connect(maxButton, &QPushButton::clicked, this, [&]() { emit DetachTitleBar::maximizeWindow(); });
    connect(closeButton, &QPushButton::clicked, this, [&]() { emit DetachTitleBar::closeWindow(); });
  }

signals:
  void maximizeWindow();
  void closeWindow();

protected:
  void mousePressEvent(QMouseEvent* event) override
  {
    if (event->button() == Qt::LeftButton)
    {
      dragging = true;
      dragStartPosition = event->globalPos() - parentWidget()->frameGeometry().topLeft();
      event->accept();
    }
  }

  void mouseMoveEvent(QMouseEvent* event) override
  {
    if (dragging && (event->buttons() & Qt::LeftButton))
    {
      parentWidget()->move(event->globalPos() - dragStartPosition);
      event->accept();
    }
  }

  void mouseReleaseEvent(QMouseEvent* event) override
  {
    if (event->button() == Qt::LeftButton)
    {
      dragging = false;
      event->accept();
    }
  }

private:
  QPushButton* maxButton;
  QPushButton* closeButton;
  bool dragging = false;
  QPoint dragStartPosition;
};
class DetachDialog : public QtEngine::Dialog
{
  Q_OBJECT

public:
  explicit DetachDialog() : QtEngine::Dialog(QtEngine::ThemeType::PRIMARY, QtEngine::ColorType::EMPTY)
  {
    mainLayout = new QtEngine::VBoxLayout();
    title = new DetachTitleBar();
    mainLayout->addWidget(title);
    setLayout(mainLayout);

    connect(title, &DetachTitleBar::maximizeWindow, [&]() {

    });
    connect(title, &DetachTitleBar::closeWindow, [&]() { emit closeDetachedDialog(); });
  }

  void SetWidget(QWidget* wiz)
  {
    bodyWiz = wiz;
    mainLayout->addWidget(wiz);
  }

  void RemoveBodyWiz()
  {
    layout()->removeWidget(bodyWiz);
  }

  QWidget* GetBodyWiz()
  {
    return bodyWiz;
  }

  QWidget* bodyWiz;
  DetachTitleBar* title;
  QVBoxLayout* mainLayout;

signals:
  void closeDetachedDialog();
};
}  // namespace experiment