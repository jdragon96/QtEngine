#pragma once
#include <QString>

namespace QtEngine
{
class String
{
public:
  static QString Make(std::string value)
  {
    return QString::fromLocal8Bit(value.c_str());
  }
};
}  // namespace QtEngine