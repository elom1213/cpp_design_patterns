#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

/**
 * grab the text and captalize it
 * keep the underlying plain text in its original state
 * only capitalize when we use the stream output operator
 * and saves the the amount of memory use
*/

struct Spec
{
  const int begin, end;
  bool capitalize{false};

  Spec(int be, int end) : begin{be}, end{end} {}
  bool is_cover(const int position) const
  {
    return position>=begin && position<=end ;
  }
};

struct FormattedText
{
  FormattedText(const string& text) : text{text}, specs(){}

  Spec& get_range(int begin, int end)
  {
    specs.emplace_back(begin, end);
    return *specs.rbegin();
  }

  friend ostream& operator<<(ostream& os, const FormattedText& obj)
  {
    string str;
    for(int i=0; i< obj.text.size(); ++i)
    {
      auto c = obj.text[i];
      for(const auto& spec : obj.specs)
        if(spec.capitalize && spec.is_cover(i)) c = toupper(c);
      str += c;
    }
    return os << str;
  }

private:
  string text;
  vector<Spec> specs;
};

int main() {

  FormattedText ft("this is a brave new world");
  ft.get_range(10, 15).capitalize = true;
  ft.get_range(-4, 7).capitalize = true;
  ft.get_range(20, 100).capitalize = true;
  cout << ft << endl;

}