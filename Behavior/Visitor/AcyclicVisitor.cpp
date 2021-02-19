#include <iostream>
#include <sstream>

using namespace std;

struct Expression;
struct DoubleExpression;
struct AdditionExpression;

/** 
 * marker calss
 * we'll take VisitorBase in Expression as accept's argument
 * and cast it to Visitor<T> where T is current class
 * if cast succeeds, call visit()
 * */
struct VisitorBase
{
  virtual ~VisitorBase(){};
};

template<typename Expression>
struct Visitor
{
  virtual void visit(Expression&)=0;
};

struct ExpressionPrinter : VisitorBase,
                           Visitor<DoubleExpression>,
                           Visitor<AdditionExpression>
{
  void visit(DoubleExpression&) override;
  void visit(AdditionExpression&) override;

  string str() const { return oss.str();}
private:
  ostringstream oss;
};

struct ExpressionEvaluator : VisitorBase,
                             Visitor<DoubleExpression>,
                             Visitor<AdditionExpression>
{
  void visit(DoubleExpression&) override;
  void visit(AdditionExpression&) override;
  
  double result;
};

//=======================================================
// Expression

struct Expression
{
  virtual ~Expression()=default;
  virtual void accept(VisitorBase& obj)
  {
    using VE = Visitor<Expression>;
    if(auto ex = dynamic_cast<VE*> (&obj))
      ex->visit(*this);
  }
};

struct DoubleExpression : Expression
{
  double value;

  DoubleExpression(const double va) : value{va} {}

  void accept(VisitorBase& obj) override
  {
    using VE = Visitor<DoubleExpression>;
    if(auto ex = dynamic_cast<VE*> (&obj))
      ex->visit(*this);
  }

};

struct AdditionExpression : Expression
{
  Expression *left, *right;

  AdditionExpression(Expression* const le, Expression* const ri) :
  left{le}, right{ri} {}

  void accept(VisitorBase& obj) override
  {
    using VE = Visitor<AdditionExpression>;
    if(auto ex = dynamic_cast<VE*> (&obj))
      ex->visit(*this);
  }
};

//=======================================================
//implement visit()

void ExpressionPrinter::visit(DoubleExpression& obj) { oss << obj.value; }
void ExpressionPrinter::visit(AdditionExpression& obj)
{
  oss << '(';
  obj.left->accept(*this);
  oss << " + ";
  obj.right->accept(*this);
  oss << ')';
}

void ExpressionEvaluator::visit(DoubleExpression& obj) { result = obj.value;}
void ExpressionEvaluator::visit(AdditionExpression& obj)
{
  obj.left->accept(*this);
  auto tmp = result;
  obj.right->accept(*this);
  result += tmp;
}

int main() {
  // 2 + (3 + 4)
 auto ae = new AdditionExpression{
              new DoubleExpression{2},
              new AdditionExpression{
                  new DoubleExpression{3},
                  new DoubleExpression{4}
              }
            };
  ExpressionPrinter ep;
  ExpressionEvaluator ee;
  ep.visit(*ae);
  ee.visit(*ae);

  cout << ep.str() << " = " << ee.result;
}