#pragma once

#include <QObject>
#include <QApplication>
#include <QFile>
#include <QPainter>
#include <QTextStream>
#include <QStyle>
#include <QSizePolicy>
#include <QStyleOption>
#include <QPaintEvent>

namespace QtEngine
{
class Application : public QApplication
{
  Q_OBJECT

public:
  explicit Application(std::string themePath = "", int argc = 0, char** argv = {}, int flag = ApplicationFlags);
};
}  // namespace QtEngine