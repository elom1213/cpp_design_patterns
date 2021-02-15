#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct Person
{
  virtual string greet() = 0;
};

struct Man : Person
{
  string name;

  Man(){}
  Man(const string& name) : name(name) {}

  string greet() override
  {
    ostringstream oss;
    oss << "my name is " << name << '\n';
    return oss.str();
  }
  void change_name(const string& name){this->name = name;}
};

// static Decorator
template<typename T>
struct HandsomeMan : T
{
  static_assert(is_base_of<Person, T>::value, 
                "Template argument must be a Person");

  string looking_good;

  HandsomeMan(){}

  template<typename... Strs>                
  HandsomeMan(const string& looking_good, Strs ...strs) : 
  T(forward<Strs>(strs)...),
  looking_good{looking_good}
  {};

  string greet() override 
  {
    ostringstream oss;
    oss << T::greet() << "I'm so " << looking_good << '\n';
    return oss.str();
  }
};

template<typename T>
struct RichMan : T
{
  static_assert(is_base_of<Person, T>::value, 
                "Template argument must be a Person");

  int money;

  RichMan(){};

  template<typename... Strs>                
  RichMan(const int& money, Strs ...strs) : 
  T(forward<Strs>(strs)...),
  money{money}
  {}

  string greet() override 
  {
    ostringstream oss;
    oss << T::greet() << "I have " << money << " dollars in my wallet\n";
    return oss.str();
  }
};


int main()
{
  RichMan<HandsomeMan<Man>> person{ 1000 , "Handsome", "David"};
  cout << person.greet() << '\n';
  // chage_name isn't part of Person's interface
  // but your can call it since type deduced to Man in compile time
  person.change_name("John");
  cout << person.greet();
  return 0;
}