#include "DrinkFactory.hpp"
#include <memory>
#include <map>
#include <string>

using namespace std;

DrinkFactory::DrinkFactory()
{
  coffeefactories["Latte"] = make_unique<LatteFactory>();
  coffeefactories["Americano"] = make_unique<AmericanoFactory>();
  coffeefactories["Caffemocha"] = make_unique<CaffemochaFactory>();
}

unique_ptr<Coffee> DrinkFactory::make_drink(const string& type)
{
  auto coffee = coffeefactories[type]->make_coffee();
  coffee->prepare();
  return coffee;
}