#include <iostream>
#include <vector>
#include "Filter.hpp"
#include "Menu.hpp"

using namespace std;

int main() {

  vector<Coffee*> menu{&Americano, &Mix, &Latte};

  Filter filter;
  SizeSpecification Tall_size(Size::Tall);
  auto black_and_warm = TemperatureSpecification(Temperature::Warm)&&
                                                  ColorSpecification(Color::Black);

  auto tall_size_coffee = filter.filter(menu, Tall_size);
  auto black_and_warm_coffee = filter.filter(menu, black_and_warm);

  cout << "tall size coffee : ";
  for(auto& r : tall_size_coffee)
     cout << r->name << " ";
  // tall size coffee : Americano Mix 

  cout << "\nblack and warm coffee : ";
  for(auto& r : black_and_warm_coffee)
     cout << r->name << " ";
  // black and warm coffee : Americano  

}