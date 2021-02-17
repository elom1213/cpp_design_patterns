#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/**
 * Dynamic composition allows you to compose something at runntime, by passing around reference.
 * It allows flexibility since the composition can happens at runntime in response to
 * the user's input
*/

struct Shape
{
  virtual string str() const = 0;
};

struct Circle : Shape
{
  float radius;
  Circle(float r) : radius{r} {}
  string str() const override
  {
    ostringstream oss;
    oss << "A circle has a radius " << radius;
    return oss.str();
  }
  void resize(float factor){radius *= factor;}
};

struct Square : Shape
{
  float side;
  Square(float si) : side{si} {}
  string str() const override
  {
    ostringstream oss;
    oss << "A Sqare has a side " << side;
    return oss.str();
  }
  void resize(float factor){side *= factor;}
};

// dynamic decorator for colored shape
struct ColoredShape : Shape
{
  Shape& shape;
  string color;
  ColoredShape(Shape& shape, const string& color) : 
  shape{shape}, color{color} {}
  string str() const override
  {
    ostringstream oss;
    oss << shape.str() << " has a color " << color ;
    return oss.str();
  }
};

// dynamic decorator for transparent shape
struct TransparentShape : Shape
{
  Shape& shape;
  uint8_t transparency;
  TransparentShape(Shape& shape, const uint8_t transparency) :
  shape{shape}, transparency{transparency} {}
  string str() const override
  {
    ostringstream oss;
    oss << shape.str() << " has " 
        << static_cast<float>(transparency) / 255.f *100.f << "% of transparency";
    return oss.str();
  }
};

int main() {
  Circle circle{2};
  ColoredShape blueCircle{circle, "blue"};
  TransparentShape transparentCircle{blueCircle, 85};
  cout << circle.str() << '\n';
  cout << blueCircle.str() << '\n';
  cout << transparentCircle.str() << '\n';

  // we can't use object interface
  // we are limited to base interface
  Square square{3};
  ColoredShape redSquare{square, "red"};
  // redSquare.resize();
}