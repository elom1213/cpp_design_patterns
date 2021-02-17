#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <sstream>

using namespace std;

enum class OutputFormat{ Markdown, Html };

struct ListStrategy
{
  virtual ~ListStrategy() = default;
  virtual void add_list_item(ostringstream&, const string&) = 0;
  virtual void strat(ostringstream&) = 0;
  virtual void end(ostringstream&) = 0;
};

// there is no dynamic polymorphism so we are forced to implement
// the virtual methods start() and end()
struct MarkdownListStrategy : ListStrategy
{
  void add_list_item(ostringstream& oss, const string& st) override
  {
    oss << "* " << st << '\n';
  }
  void strat(ostringstream&) override{};
  void end(ostringstream&) override{};
};

struct HtmlListStrategy : ListStrategy
{
  void add_list_item(ostringstream& oss, const string& st) override
  {
    oss << "  <li> " << st << " </li>\n";
  }
  void strat(ostringstream& oss) override { oss << "<ul>\n";}
  void end(ostringstream& oss) override { oss << "<ul>\n";}
};

// template allows to define strategy staticlly
// but we can't switch it at runtime
template<typename T> class TextProcessor
{
  ostringstream oss; // buffer stores output
  T list_strategy;  // no need to use pointer or ref anymore
  
public:
  void append_list(const vector<string>& items)
  {
    list_strategy.strat(oss);
    for(auto& item : items)
      list_strategy.add_list_item(oss, item);
    list_strategy.end(oss);
  }

  string str() { return oss.str();}
  
  void clear()
  {
    oss.str("");
    oss.clear();
  }
};

int main() {
  // markdown
  TextProcessor<MarkdownListStrategy> tpm;
  tpm.append_list({"foo", "bar", "baz"});
  cout << tpm.str() << endl;

  // html
  TextProcessor<HtmlListStrategy> tph;
  tph.append_list({"foo", "bar", "baz"});
  cout << tph.str() << endl;
}