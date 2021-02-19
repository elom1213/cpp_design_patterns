#include <iostream>
#include <vector>
#include "Filter.hpp"

using namespace std;

/**
 * Open Closed Principle states that a type is open for
 * extension but closed for modification.
 * we want a filiter that is extensible without having
 * modify it
*/

/* 
   bad example!
   we have to keep modify structre time to time.
   instead, we con seperate class into Sepecification<T>
   and Filter<T>, implement interfaces whenever new filter needed

struct Filter{
   typedef vector<Coffee*> Menu

   Menu by_color(Menu menu, Color color){
      Menu result;
      for(auto& item : menu)
         if(i->color == color) result.push_back(i);
      return result;
   }
   Menu by_size(Menu, Size){ ... }
   Menu by_color_and_size(Menu, Color, Size){ ... }
};




*/

int main() {

  vector<Coffee*> menu{&Americano, &Mix, &Latte};

  Filter filter;
  SizeSpecification Tall_size(Size::Tall);
  auto black_and_warm = TemperatureSpecification(Temperature::Warm)&&
                        ColorSpecification(Color::Black);

  auto tall_size_coffee = filter.filter_menu(menu, Tall_size);
  auto black_and_warm_coffee = filter.filter_menu(menu, black_and_warm);

  cout << "tall size coffee : ";
  for(auto& r : tall_size_coffee)
     cout << r->name << ", ";
  // tall size coffee : Americano Mix 

  cout << "\nblack and warm coffee : ";
  for(auto& r : black_and_warm_coffee)
     cout << r->name << ", ";
  // black and warm coffee : Americano  

}