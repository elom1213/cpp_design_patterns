#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/**
 * hierarchy of mathematical operations.
 * we would like to add print() 
*/
struct Expression
{
  virtual ~Expression()=default;
};

struct DoubleExpression : Expression
{
  double value; 
  explicit DoubleExpression(double v) : value{v} {}
};

struct AdditionalExpression : Expression
{
  Expression *left, *right;
  explicit AdditionalExpression(Expression* const le, Expression* const ri) :
  left{le}, right{ri} {}
  
  ~AdditionalExpression()
  { 
    delete left;
    delete right;
  }
};

/**
 * c++ konws ae->left is an Expression but dosen't check the type at runtime
 * it dosen't konw which overload to call
 * we have to use if_else and dynamic_cast
struct ExpressionPrinter
{
  void print(DoubleExpression* de, ostringstream& oss) const
  {
    oss << de->value;
  }
  void print(AdditionalExpression* ae, ostringstream& oss) const
  {
    oss << "(";
    print(ae->left, oss);
    oss << " + ";
    print(ae->left, oss);
    oss << ")";
  }
};*/


struct ExpressionPrinter
{
  void print(Expression* ex)
  {
    if(auto de = dynamic_cast<DoubleExpression*>(ex))
    {
      oss << de->value;
    }
    else if(auto ae = dynamic_cast<AdditionalExpression*>(ex))
    {
      oss << "(";
      print(ae->left);
      oss << " + ";
      print(ae->right);
      oss << ")";
    }
  }
  string str() const { return oss.str(); }
private:
  ostringstream oss; 
};



int main() {
  // (1.0 + (2.0 + 3.0))
  auto e = new AdditionalExpression{
              new DoubleExpression{1},
              new AdditionalExpression{
                  new DoubleExpression{2},
                  new DoubleExpression{3}
              }
          };

  ExpressionPrinter ep;
  ep.print(e);
  cout << ep.str();

  delete e;
  return 0;
}