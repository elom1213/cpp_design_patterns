#include "DrinkFactory.hpp"
#include "DrinkFactoryWithTime.hpp"
#include <iostream>

using namespace std;

int main() {
  DrinkFactory df;
  auto coffee = df.make_drink("Latte");
  cout << '\n';
  auto coffee2 = df.make_drink("Caffemocha");
  cout << '\n';
  // every coffee takes 2 minute to prepare without using DrinkFactoryWithTime

  DrinkFactoryWithTime dftime;
  auto coffee3 = dftime.make_drink("Caffemocha");
  // you can set each coffee's preparing time
  return 0;
}