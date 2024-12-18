#ifndef ZB_AST_H
#define ZB_AST_H

class AstNode {

  virtual ~AstNode() {}

};

class RootNode : public AstNode {

public:
  std::vector<Definition*> definition_list;

  RootNode() {}

  ~RootNode() {
    for (Definition d : definition_list) {
      delete d;
    }
  }
};

// abstract base class for all definitions
class DefinitionNode : public AstNode {};

class FunctionDefinitionNode : public DefinitionNode {

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

class EventHandlerDefinitionNode : public DefinitionNode {

public:
  std::vector<ActualParameterNode*> actual_parameters;
  std::vector<StatementNode*> body;

  EventHandlerDefinitionNode(std::vector<ActualParameterNode*> actual_parameters, std::vector<StatementNode*> body) : 
    actual_parameters(actual_parameters), body(body) {}

  EventHandlerDefinitionNode(std::vector<StatementNode*> body) : body(body) {}
  
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

}

#endif