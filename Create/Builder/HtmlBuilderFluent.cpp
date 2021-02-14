#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class HtmlBuilder;

class HtmlElement
{
  friend HtmlBuilder;

  string name, text;
  vector<HtmlElement> children;
  const int indent_siz = 2;

  explicit HtmlElement(){};
  HtmlElement(const string& name) :name{name}, text{""}, indent_siz{2} {}
  HtmlElement(const string& name, const string& text) : name{name}, text{text}, indent_siz{2} {}
public:
  string str(int indent=0) const
  {
    ostringstream oss;
    string i(indent_siz*indent, ' ');

    oss << i << '<' << name << ">\n";

    if(this->text.size()>0)
      oss << string(indent_siz*(indent+1), ' ') << text << '\n';

    for(const auto& c : children) oss << c.str(1+indent);

    oss << i << "</" << name << ">\n";
    
    return oss.str();
  };
};

class HtmlBuilder
{
  HtmlElement root;
  explicit HtmlBuilder();

public:
  HtmlBuilder(const string& name) : root{name}{}
  HtmlBuilder(const string& name, const string& text) : root{name, text}{}

  static HtmlBuilder create(const string& name){ return {name}; }
  static HtmlBuilder create(const string& name, const string& text){ return {name, text}; }

  HtmlBuilder& add_childe(const string& name, const string& text)
  {
    this->root.children.push_back({name, text});
    return *this;
  }

  HtmlBuilder& add_childe(const HtmlElement& ele)
  {
    this->root.children.push_back(ele);
    return *this;
  }

  operator HtmlElement() const { return this->root;}
  string str() const { return this->root.str(); }
  HtmlElement build() const { return move(this->root); }
};

int main() {

 auto ele1 = HtmlBuilder::create("ol");
 ele1.add_childe("li", "ele1 is auto type").add_childe("li", "made by chain");
 cout << ele1.str() << "\n\n";

 HtmlElement ele2 = HtmlBuilder::create("ul").
                    add_childe("li", "invoke conversion funtion").
                    add_childe("li", "didn't call build()");
 cout << ele2.str() << "\n\n";

 HtmlElement ele3 = HtmlBuilder::create("ul").
                    add_childe("li", "use build() method explicitly").
                    add_childe("li", "this can be inserted into other elements").
                    build();
  cout << ele3.str() << "\n\n";

  HtmlBuilder ele4{"html"};
  ele4.add_childe(ele3);
  cout << ele4.str() << "\n\n";
}