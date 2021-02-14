#pragma once
#include "Prototypes.hpp"
#include <memory>
#include <string>

class MenuFactory
{
public:
  static unique_ptr<SubwayMenu> NewClassic(const string& name, const string& sauce)
  {
    return NewSubway(name, sauce, Classic);
  }
  static unique_ptr<SubwayMenu> NewBest(const string& name, const string& sauce)
  {
    return NewSubway(name, sauce, Best);
  }
  static unique_ptr<SubwayMenu> NewPremium(const string& name, const string& sauce)
  {
    return NewSubway(name, sauce, Premium);
  }
private:
  static unique_ptr<SubwayMenu> NewSubway(const string& name, const string& sauce, SubwayMenu& proto)
  {
    auto result = make_unique<SubwayMenu>(proto);
    result->name = name;
    result->fillings->sauce = sauce;
    return result;
  }
};
