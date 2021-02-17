#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template<typename T> struct Observer;
template<typename T>class Observable
{
  vector<Observer<T>*> observers;
public:
  void notify(const T& obj, const string& data)
  {
    for(auto& ob : observers)
      ob->field_changed(obj, data);
  }
  void subscribe(Observer<T>& ob)
  {
    observers.emplace_back(&ob);
  }
  void unsubscribe(Observer<T>& ob)
  {
    //  vector is not thread-safe!
    // if you call subscribe() and unsubscribe() at the same time
    // it could lead to unintended consequence
    // since both functions modify the vector
    observers.erase(remove(observers.begin(), observers.end(), &ob), 
                    observers.end());
  }
};
