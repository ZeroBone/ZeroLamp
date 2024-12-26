#ifndef ZB_AST_H
#define ZB_AST_H

class AstNode {

  virtual ~AstNode() {}

};

class RootNode : public AstNode {

public:
  std::vector<StatementNode*> statements;

  RootNode(std::vector<StatementNode*> statements) : statements(statements) {}

  ~RootNode() {
    for (StatementNode* s : statements) {
      delete s;
    }
  }
};

class ActualParameterNode : public AstNode {

public:
  std::string name;
  ExpressionNode* value;

  ActualParameterNode(std::string name, ExpressionNode* value) : name(name), value(value) {}

  ActualParameterNode(ExpressionNode* value) : value(value) {}

  inline bool is_positional_parameter() {
    return name.empty();
  }

};

// abstract base class for all statements
class StatementNode : public AstNode {}

class FunctionDefinitionNode : public StatementNode {

public:
  std::vector<std::string> formal_parameters;
  std::vector<StatementNode*> body;

public:

  FunctionDefinitionNode(std::vector<std::string> formal_parameters, std::vector<StatementNode*> body) : 
    formal_parameters(formal_parameters), body(body) {}

  FunctionDefinitionNode(std::vector<StatementNode*> body) : body(body) {}

  ~FunctionDefinitionNode() {
    for (StatementNode* s : body) {
      delete s;
    }
  }

};

class EventHandlerDefinitionNode : public StatementNode {

public:
  std::vector<ActualParameterNode*> actual_parameters;
  std::vector<StatementNode*> body;

  EventHandlerDefinitionNode(std::vector<ActualParameterNode*> actual_parameters, std::vector<StatementNode*> body) : 
    actual_parameters(actual_parameters), body(body) {}

  EventHandlerDefinitionNode(std::vector<StatementNode*> body) : body(body) {}
  
};

class FunctionCallStatementNode : public StatementNode {

public:
  std::string name; // function name
  std::vector<ActualParameterNode*> parameters;

  FunctionCallStatementNode(std::string name, std::vector<ActualParameterNode*> parameters) : name(name), parameters(parameters) {}
  FunctionCallStatementNode(std::string name) : name(name) {}

};

class PushStatementNode : public StatementNode {

public:
  std::string display;
  std::string mode;
  ExpressionNode* condition;

  PushStatementNode(std::string display, std::string mode, ExpressionNode* condition = nullptr) : display(display), mode(mode), condition(condition) {}

};

// abstract base class for all expressions

class ExpressionNode : public AstNode {};

// simple expressions

class IdExpressionNode : public ExpressionNode {
public:
  std::string id;
  IdExpressionNode(std::string id) : id(id) {}
};

class IntLiteralExpressionNode : public ExpressionNode {
public:
  uint32_t value;
  IdExpressionNode(std::string value) : value(value) {}
};

class FloatLiteralExpressionNode : public ExpressionNode {
public:
  double value;
  IdExpressionNode(double value) : value(value) {}
};

class StringLiteralExpressionNode : public ExpressionNode {
public:
  std::string value;
  IdExpressionNode(std::string value) : value(value) {}
};

class BooleanLiteralExpressionNode : public ExpressionNode {
public:
  bool value;
  IdExpressionNode(bool value) : value(value) {}
};

// postfix

class IndexingExpressionNode : public ExpressionNode {
public:
  ExpressionNode* base;
  ExpressionNode* index;
  IndexingExpressionNode(ExpressionNode* base, ExpressionNode* index) : base(base), index(index) {}
};

class FunctionCallExpressionNode : public ExpressionNode {
public:
  std::vector<ActualParameterNode*> actual_parameters;
  FunctionCallExpressionNode() {}
};

class MemberAccessExpressionNode : public ExpressionNode {
public:
  ExpressionNode* base;
  std::string member_name;
  MemberAccessExpressionNode(ExpressionNode* base, std::string member_name) : base(base), member_name(member_name) {}
};

// pow
class PowExpressionNode : public ExpressionNode {
public:
  ExpressionNode* base;
  ExpressionNode* exponent;
  PowExpressionNode(ExpressionNode* base, ExpressionNode* exponent) : base(base), exponent(exponent) {}
}

// unary expressions

enum class UnaryExpressionType {
  NEGATION,
  BITWISE_INVERT,
  INVERT,
};

class UnaryExpressionNode : public ExpressionNode {
public:
  UnaryExpressionType type;
  ExpressionNode* operand;
  UnaryExpressionNode(UnaryExpressionType type, ExpressionNode* operand) : type(type), operand(operand) {}
};

// binary expression

enum class BinaryExpressionType {
  MULTIPLICATION,
  DIVISION,
  REMAINDER,
  ADDITION,
  SUBTRACTION,
  BITWISE_SHIFT_LEFT,
  BITWISE_SHIFT_RIGHT,
  LESS_THAN,
  GREATER_THAN,
  LESS_THAN_OR_EQUAL,
  GREATER_THAN_OR_EQUAL,
  EQUAL,
  NOT_EQUAL,
  BITWISE_AND,
  BITWISE_XOR,
  BITWISE_OR,
  AND,
  OR,
  ASSIGN,
  ASSIGN_MULTIPLY,
  ASSIGN_DIVIDE,
  ASSIGN_REMAINDER,
  ASSIGN_PLUS,
  ASSIGN_MINUS,
  ASSIGN_BITWISE_SHIFT_LEFT,
  ASSIGN_BITWISE_SHIFT_RIGHT,
  ASSIGN_BITWISE_AND,
  ASSIGN_BITWISE_XOR,
  ASSIGN_BITWISE_OR
};

class BinaryExpressionNode : public ExpressionNode {
public:
  BinaryExpressionType type;
  ExpressionNode* left_operand;
  ExpressionNode* right_operand;
  BinaryExpressionNode(BinaryExpressionType type, ExpressionNode* left_operand, ExpressionNode* right_operand) : type(type), left_operand(left_operand), right_operand(right_operand) {}
};

class TernaryExpressionNode : public ExpressionNode {
public:
  ExpressionNode* condition;
  ExpressionNode* if_expression;
  ExpressionNode* else_expression;
  TernaryExpressionNode(ExpressionNode* condition, ExpressionNode* if_expression, ExpressionNode* else_expression) : condition(condition), if_expression(if_expression), else_expression(else_expression) {}
};

class CommaExpressionNode : public ExpressionNode {
public:
  ExpressionNode* left;
  ExpressionNode* right;
  CommaExpressionNode(ExpressionNode* left, ExpressionNode* right) : left(left), right(right) {}
};

#endif