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
