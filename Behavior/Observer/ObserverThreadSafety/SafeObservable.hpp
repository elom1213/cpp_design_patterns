#include <vector>
#include <mutex>
#include <algorithm>
#include <string>

using namespace std;

template<typename T> struct Observer;
template<typename T> class SafeObservable
{
  vector<Observer<T>*> observers;
  using mutex_t = mutex;
  mutex_t mtx;
public:
  void notify(T& source, const string& field_name)
  {
    scoped_lock<mutex_t> lock{mtx};
    for(auto& ob : observers)
      ob->field_changed(source, field_name);
  }
  void subscribe(Observer<T>& ob)
  {
    scoped_lock<mutex_t> lock{mtx};
    observers.emplace_back(&ob);
  }
  void unsubscribe(Observer<T>& ob)
  {
    scoped_lock<mutex_t> lock{mtx};
    observers.erase(remove(observers.begin(), observers.end(), &ob),
                    observers.end());
  }
};