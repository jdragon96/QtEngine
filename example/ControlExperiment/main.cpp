#include "QtEngine/QtEngine.h"
#include "SlideBar.h"
#include <iostream>
#include <QDockWidget>
#include <QStackedWidget>
#include <QDateTime>
#include <QTabWidget>
#include <QSizeGrip>

int main()
{
  // QWidget::setParent()
  QtEngine::Application app;
  QTabWidget wiz;
  experiment::SlideBar w;
  w.setFixedWidth(400);
  w.ChangeControllerSize(20);
  w.SetTick(10);
  w.SetPercentage(0.50f);
  experiment::SlideBar w2;
  w2.setFixedWidth(400);
  w2.ChangeControllerSize(20);
  w2.SetPercentage(0.50f);
  w2.ChangeControllerColor(QColor(0, 255, 0));
  wiz.addTab(&w, "W1");
  wiz.addTab(&w2, "W2");
  // wiz.addWidget(&w2);
  wiz.show();
  wiz.setEnabled(false);
  wiz.setStyleSheet("QTabBar::tab::disabled {width: 0; height: 0; margin: 0; padding: 0; border: none;} ");
  wiz.setCurrentWidget(&w);
  wiz.addTab(&w2, "WEQWE");
  wiz.setCurrentWidget(&w2);
  if (wiz.currentWidget() == &w2)
  {
    std::cout << "위젯이 동일합니다.." << std::endl;
    std::cout << "자식 개수" << wiz.children().size() << std::endl;
    auto idx = wiz.currentIndex();
    for (int i = 0; i < wiz.children().size(); ++i)
    {
      if (i == idx)
        continue;
      wiz.setCurrentIndex(i);
    }
  }
  else
  {
    std::cout << "다릅니다!" << std::endl;
  }
  experiment::DetachTitleBar d;
  d.show();
  QObject::connect(&w, &experiment::SlideBar::changePercentage,
                   [&](float percent) { std::cout << percent << std::endl; });
  app.exec();
  return 0;
}