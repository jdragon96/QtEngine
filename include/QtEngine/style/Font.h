#pragma once

#include <string>

namespace QtEngine
{

class Font
{
public:
  Font();
  ~Font();

  // font-family > Arial
  std::string Family;

  // font-size > 10px
  std::string Size;

  // font-weight > bold
  std::string Weight;
};
}  // namespace QtEngine