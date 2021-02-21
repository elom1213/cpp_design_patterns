#include "MenuBuilder.hpp"
#include "DrinkBuilder.hpp"
#include "MainMenuBuilder.hpp"

DrinkBuilder MenuBuilderBase::drink() const
{
  return {menu};
}

MainMenuBuilder MenuBuilderBase::main_menu() const
{
  return {menu};
}
