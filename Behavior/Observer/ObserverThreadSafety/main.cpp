// original code
// https://github.com/mpavezb/cpp_design_patterns/blob/master/Behavioral/observer/thread_safety.cpp

#include <iostream>
#include "Observer.hpp"
#include "SafeObservable.hpp"

using namespace std;

class Person : public SafeObservable<Person>
{
  int age{0};
public:
  Person(){};
  explicit Person(const int age) : age{age} {}
  
  int get_age() const { return age; }
  void set_age(const int age)
  {
    if(this->age == age) return;
    this->age = age;
    notify(*this, "age");
  }
};

class ConsolePersonObserver : public Observer<Person>
{
  void field_changed(Person& source, const string& field_name) override 
  {
    if(field_name == "age")
    {
      cout << "[ConsolePersonObserver] Person's data \"" << field_name <<
      "\" has changed into " << source.get_age() << "\n\n";
    }
  }
};

class TrafficAdministration : public Observer<Person>
{
  void field_changed(Person& source, const string& field_name) override 
  {
    if(field_name == "age")
    {
      if(source.get_age() < 17)
        cout << "[TrafficAdministration] you are not old enough to drive kid\n";
      else 
      {
        // if you call unsubscribe() while in notify, backtrace of stack would look like
        // notify() --> field_changed() --> unsubscribe()
        // both notify() and unsubscribe() tries to lock and that triggers deadlock!
        cout << "[TrafficAdministration] Ok. you can drive now\n";
        source.unsubscribe(*this);
      }
    }
  }
};


int main() {
  Person p;
  ConsolePersonObserver cpo;
  TrafficAdministration ta;
  p.subscribe(ta);
  p.subscribe(cpo);

  try {
    p.set_age(15);
    p.set_age(16);
    // p.set_age(17) will trigger deadlock
    p.set_age(17);
    p.set_age(18);
    p.set_age(19);
  } catch (const std::exception &e) {
    cout << "Oops, " << e.what() << "\n";
  }

  return 0;
}