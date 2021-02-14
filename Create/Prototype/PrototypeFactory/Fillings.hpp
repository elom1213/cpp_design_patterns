#pragma once
#include <string>

using namespace std;

struct Fillings
{
  string filling1, filling2, sauce;

  Fillings(const string& fill1, const string& fill2, const string& sauce) :
  filling1{fill1}, 
  filling2{fill2}, 
  sauce{sauce}
  {}

  Fillings(Fillings& other) :
  filling1{other.filling1},
  filling2{other.filling2},
  sauce{other.sauce}
  {}
};