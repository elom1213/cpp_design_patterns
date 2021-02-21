#pragma once
#include <vector>
#include "Specification.hpp"

using namespace std;

template<typename T> struct BaseFilter
{
  virtual vector<T*> filter_menu(vector<T*>, Specification<T>&) = 0;
};

struct Filter : BaseFilter<Coffee>
{
  vector<Coffee*> 
  filter_menu(vector<Coffee*> menu, Specification<Coffee>& spec) override
  {
    vector<Coffee*> result;
    for(auto& item : menu)
      if(spec.is_satisfied(item))
        result.push_back(item);
    return result;
  }
};
