#pragma once

#include <string>

namespace QtEngine
{

class Border
{
public:
  Border();
  ~Border();

  // 1px
  std::string Width;

  // 1px
  std::string Radius;

  // none, solid, dot
  std::string Style;
};
}  // namespace QtEngine