#include <iostream>
#include <sstream>

using namespace std;

/**
 * hierarchy of mathematical operations.
 * we would like to add print() 
 * in intrusive way, we'll add a virtual method print() 
 * to every single object in the hierarchy
 * it'll break opern_closed principle
*/

struct Expression
{
  virtual ~Expression()=default;
  
  // intrusive implementation
  virtual void print(ostringstream&) = 0 ;
};

struct DoubleExpression : Expression
{
  double value; 
  explicit DoubleExpression(double v) : value{v} {}

  // intrusive implementation
  void print(ostringstream& oss) override {oss << value;}
};

struct AdditionalExpression : Expression
{
  Expression *left, *right;
  explicit AdditionalExpression(Expression* const le, Expression* const ri) :
  left{le}, right{ri} {}

  // intrusive implementation
  void print(ostringstream& oss) override 
  {
    oss << "(";
    left->print(oss);
    oss << " + ";
    right->print(oss);
    oss << ")";
  }

  ~AdditionalExpression()
  { 
    delete left;
    delete right;
  }
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
  ostringstream os;
  e->print(os);
  cout << os.str();
  delete e;
  return 0;
}