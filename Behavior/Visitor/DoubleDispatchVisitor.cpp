#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/**
 * hierarchy of mathematical operations.
 * We would like to add printing and evaluating behavior.
 * using visitor, yoir just need to implement the accept()
 * through the hierarchy junst once
 * your never have to touch a member of the hieracrhy again
*/

struct DoubleExpression;
struct AdditionExpression;
struct SubtractionExpresstion;

struct ExpressionVisitor
{
  virtual void visit(DoubleExpression*) = 0;
  virtual void visit(AdditionExpression*) = 0;
  virtual void visit(SubtractionExpresstion*) = 0;
};


struct ExpressionPrinter : ExpressionVisitor
{
  void visit(DoubleExpression*) override;
  void visit(AdditionExpression*) override;
  void visit(SubtractionExpresstion*) override;
  string str() const { return oss.str(); }
private:
  ostringstream oss; 
};

struct ExpressionEvaluator : ExpressionVisitor
{
  void visit(DoubleExpression*) override;
  void visit(AdditionExpression*) override;
  void visit(SubtractionExpresstion*) override;
  int result;
};

// ===============================================================
// hierarchy :  
//                       Expression
//                 /       /            \
// DoubleExpression  AdditionExpression  SubtractionExpresstion

struct Expression
{
  virtual ~Expression(){}
  virtual void accept(ExpressionVisitor*)=0;
};

struct DoubleExpression : Expression
{
  double value; 
  explicit DoubleExpression(double v) : value{v} {}

  // `this` pointer forces using the specific visit() overload.
  void accept(ExpressionVisitor* visitor) { visitor->visit(this); }
};

struct AdditionExpression : Expression
{
  Expression *left, *right;

  explicit AdditionExpression(Expression* const le, Expression* const ri) :
  left{le}, right{ri} {}

  void accept(ExpressionVisitor* visitor) { visitor->visit(this); }
  
  ~AdditionExpression()
  { 
    delete left;
    delete right;
  }
};

struct SubtractionExpresstion : Expression
{
  Expression *left, *right;

  explicit SubtractionExpresstion(Expression* const le, Expression* const ri) :
  left{le}, right{ri} {}

  void accept(ExpressionVisitor* visitor) { visitor->visit(this); }
  
  ~SubtractionExpresstion()
  { 
    delete left;
    delete right;
  }
};


// ===============================================================
// Classic Visitor

void ExpressionPrinter::visit(DoubleExpression* de) { oss << de->value; }

void ExpressionPrinter::visit(AdditionExpression* ae)
{
  // not using brace unless right expression contains sub
  bool need_brace = dynamic_cast<SubtractionExpresstion*>(ae->right);
  ae->left->accept(this);
  oss << " + ";
  if(need_brace)
    oss << '(';
  ae->right->accept(this);
  if(need_brace)
    oss << ')';
}

void ExpressionPrinter::visit(SubtractionExpresstion* se)
{
  bool need_brace = dynamic_cast<SubtractionExpresstion*>(se->right);
  se->left->accept(this);
  oss << " - ";
  if(need_brace)
    oss << '(';
  se->right->accept(this);
  if(need_brace)
    oss << ')';
}

void ExpressionEvaluator::visit(DoubleExpression* de) { result = de->value; }

void ExpressionEvaluator::visit(AdditionExpression* ae)
{
  // depnnds on left type, this will modify current result
  // ae->left->accept(this)->visit(DoubleExpression or AdditionExpression)
  // the recursive call's end condition is implemented in DoubleExpression
  ae->left->accept(this);
  auto tmp = result;
  ae->right->accept(this);
  result += tmp;
}

void ExpressionEvaluator::visit(SubtractionExpresstion* se)
{
  se->left->accept(this);
  auto tmp = result;
  se->right->accept(this);
  result = tmp - result;
}


int main() {
  // 1 + (7 - 3)
  auto ae = new AdditionExpression{
              new DoubleExpression{1},
              new SubtractionExpresstion{
                  new DoubleExpression{7},
                  new DoubleExpression{3}
              }
          };
  ExpressionPrinter ep;
  ExpressionEvaluator ee;
  ep.visit(ae);
  ee.visit(ae);
  cout << ep.str() << " = " << ee.result;

  delete ae;
  return 0;
}