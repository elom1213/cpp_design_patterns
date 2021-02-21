#pragma once
#include<string>

enum class Color {White, Black, Brown, Yellow};
enum class Size {Short, Tall, Grande, Venti, Trenta};
enum class Temperature {Cold, Warm, Hot, SoHot};

struct Coffee 
{
  std::string name;
  Color color = Color::Black; 
  Size size; 
  Temperature temperature;
};

// menu
Coffee Americano  {"Americano", Color::Black, Size::Tall, Temperature::Warm};
Coffee Mix        {"Mix",       Color::Yellow, Size::Tall, Temperature::Hot};
Coffee Latte      {"Latte",     Color::Yellow, Size::Grande, Temperature::Warm};