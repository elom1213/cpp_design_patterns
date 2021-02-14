#include <string>

template<typename T> struct Observer
{
  virtual void field_changed(const T&, const std::string&) = 0;
};