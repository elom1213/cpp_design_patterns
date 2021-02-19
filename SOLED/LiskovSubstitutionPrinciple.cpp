#include <iostream>

using namespace std;

class Rectangle
{
protected:
  int width, height;
public:
  Rectangle(int width, int height) : width{width}, height{height} {}
  int get_width() const {return width;}
  int get_height() const {return height;}
  virtual void set_width(int wid) { width = wid; }
  virtual void set_height(int hei) { height = hei; }
  int area() const { return width*height; }
};

class Square : public Rectangle
{
public:
  Square(int size) : Rectangle{size, size} {}
  void set_width(int wid) override{ width = height = wid; }
  void set_height(int hei) override { width = height = hei; }
};

void process(Rectangle& r)
{
  int w = r.get_width();
  r.set_height(10);

  cout << "expected area => " << (w*10) << '\n'
       << "got => " << r.area();
// expected area => 30
// got => 100
}

int main()
{
  Square sq{3};
  process(sq);
  return 0;
};