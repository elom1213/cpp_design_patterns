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
  virtual void add_list_item(ostringstream&, const string&){}
  virtual void strat(ostringstream&){}
  virtual void end(ostringstream&){}
};

struct MarkdownListStrategy : ListStrategy
{
  void add_list_item(ostringstream& oss, const string& st) override
  {
    oss << "* " << st << '\n';
  }
};

struct HtmlListStrategy : ListStrategy
{
  void add_list_item(ostringstream& oss, const string& st) override
  {
    oss << "  <li> " << st << " </li>\n";
  }
  void strat(ostringstream& oss){ oss << "<ul>\n";}
  void end(ostringstream& oss){ oss << "<ul>\n";}
};

class TextProcessor
{
  ostringstream oss; // buffer stores output
  unique_ptr<ListStrategy> list_strategy;
  
public:
  void set_output_format(OutputFormat f)
  {
    switch(f)
    {
    case OutputFormat::Markdown:
      list_strategy = make_unique<MarkdownListStrategy>();
      break;
    case OutputFormat::Html:
      list_strategy = make_unique<HtmlListStrategy>();
      break;
    default:
      throw runtime_error("unknow format");
    }
  }

  void append_list(const vector<string>& items)
  {
    list_strategy->strat(oss);
    for(auto& item : items)
      list_strategy->add_list_item(oss, item);
    list_strategy->end(oss);
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
  TextProcessor tp;
  tp.set_output_format(OutputFormat::Markdown);
  tp.append_list({"foo", "bar", "baz"});
  cout << tp.str() << endl;

  // html
  tp.clear();
  tp.set_output_format(OutputFormat::Html);
  tp.append_list({"foo", "bar", "baz"});
  cout << tp.str() << endl;
}