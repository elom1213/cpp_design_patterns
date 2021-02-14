#pragma once
#include <iostream>
#define AVG_TIME  2

using namespace std;

struct Coffee
{
  virtual ~Coffee() = default;
  virtual void prepare(int time=AVG_TIME) = 0;
};

struct Latte : Coffee
{
  void prepare(int time) 
  { 
    cout << "preparing Latte.\n";
    cout << time << " minute to prepare." << endl;
  }
};

struct Americano : Coffee
{
  void prepare(int time) 
  { 
    cout << "preparing Americano\n" ;
    cout << time << " minute to prepare" << endl;
  }
};

struct Caffemocha : Coffee
{
  void prepare(int time) 
  { 
    cout << "preparing Caffemocha\n";
    cout << time << " minute to prepare" << endl;
  }
};