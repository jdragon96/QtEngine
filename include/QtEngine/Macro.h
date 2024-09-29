#pragma once
#include <memory>

#define SHARED_PTR(CLASS)                                                                                              \
  using SharedPtr = std::shared_ptr<CLASS>;                                                                            \
  static SharedPtr MakeShared()                                                                                \
  {                                                                                                                    \
    return std::make_shared<CLASS>();                                                                                  \
  };

#define SINGLETON(CLASS)                                                                                               \
  static CLASS& instance()                                                                                             \
  {                                                                                                                    \
    static CLASS inst;                                                                                                 \
    return inst;                                                                                                       \
  };