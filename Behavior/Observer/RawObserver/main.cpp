#include <iostream>
#include <string>
#include "Observer.hpp"
#include "Observable.hpp"

using namespace std;

// Observable: Person notifies when the age field is changed.
class Person : public Observable<Person>
{
  int age{0};
public:
  Person(){}
  explicit Person(int age) : age{age} {}
  int get_age() const { return age; }
  void set_age(int age)
  {
    if(this->age==age)
      return;
    this->age = age;
    notify(*this, "age");
  }
};

struct Consol_person_data : Observer<Person>
{
private:
  void field_changed(const Person& person, const string& data ) override
  {
    cout << "Person's data \"" << data << "\" has changed to " << person.get_age() << '\n';
  }
};

int main() {
  Person p;
  Consol_person_data cpd;

  p.subscribe(cpd);

  p.set_age(15);
  p.set_age(16);
  p.set_age(17);

  p.unsubscribe(cpd);

  p.set_age(18);


}