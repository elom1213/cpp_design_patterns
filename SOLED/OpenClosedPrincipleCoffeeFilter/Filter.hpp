#pragma once
#include <vector>
#include "Specification.hpp"

using namespace std;

template<typename T> struct BaseFilter
{
  virtual vector<T*> filter(vector<T*>, Specification<T>&) = 0;
};

struct Filter : BaseFilter<Coffee>
{
  vector<Coffee*> 
  filter(vector<Coffee*> items, Specification<Coffee>& spec) override
  {
    vector<Coffee*> result;
    for(auto& item : items)
      if(spec.is_satisfied(item))
        result.push_back(item);
    return result;
  }
};
