#include <string>

template<typename T> struct Observer
{
  virtual void field_changed(T&, const std::string&) = 0;
};