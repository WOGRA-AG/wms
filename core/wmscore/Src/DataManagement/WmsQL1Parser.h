
#undef emit


// Generated from WmsQL1.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"




class  WmsQL1Parser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, SELECT = 4, DISTINCT = 5, AVG = 6, MAX = 7, 
    MIN = 8, SUM = 9, COUNT = 10, INSERT = 11, INTO = 12, UPDATE = 13, DELETE = 14, 
    VALUES = 15, DEFAULT = 16, SET = 17, FROM = 18, WHERE = 19, AND = 20, 
    OR = 21, NOT = 22, LIKE = 23, IN = 24, IS = 25, NULL_REPR = 26, MOD = 27, 
    LENGTH = 28, ABS = 29, SIZE = 30, PLUS = 31, MINUS = 32, STAR = 33, 
    SLASH = 34, EQ = 35, NEQ = 36, LT = 37, LEQ = 38, GT = 39, GEQ = 40, 
    BY = 41, GROUP = 42, ORDER = 43, ASC = 44, DESC = 45, LIMIT = 46, TRUE = 47, 
    FALSE = 48, ID = 49, CLASSID = 50, IDPATH = 51, STRING_TYPE = 52, CONCAT = 53, 
    SUBSTRING = 54, LOWER = 55, UPPER = 56, INT_TYPE = 57, FLOAT_TYPE = 58, 
    DATE_TYPE = 59, BLOCK_COMMENT = 60, LINE_COMMENT = 61, WS = 62
  };

  enum {
    RuleStatement = 0, RuleSelect_statement = 1, RuleInsert_statement = 2, 
    RuleUpdate_statement = 3, RuleDelete_statement = 4, RuleSelect_clause = 5, 
    RuleSelect_expression = 6, RuleAggregate_expression = 7, RuleInsert_clause = 8, 
    RuleUpdate_clause = 9, RuleDelete_clause = 10, RuleValue_clause = 11, 
    RuleValue_list = 12, RuleSet_clause = 13, RuleSet_assignment = 14, RuleFrom_clause = 15, 
    RuleWhere_clause = 16, RuleWhere_expression = 17, RuleCond_expression = 18, 
    RuleIn_condition = 19, RuleIn_items = 20, RuleLike_condition = 21, RuleCompare_condition = 22, 
    RuleCompare_sign = 23, RuleArithmetic_expression = 24, RuleArithmetic_factor = 25, 
    RuleNumeric_returning_function = 26, RuleGroupby_clause = 27, RuleOrderby_clause = 28, 
    RuleOrderby_expression = 29, RuleLimit_clause = 30, RuleValue_ref = 31, 
    RuleObject_ref = 32, RuleClass_ref = 33, RuleString_expression = 34
  };

  WmsQL1Parser(antlr4::TokenStream *input);
  ~WmsQL1Parser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class StatementContext;
  class Select_statementContext;
  class Insert_statementContext;
  class Update_statementContext;
  class Delete_statementContext;
  class Select_clauseContext;
  class Select_expressionContext;
  class Aggregate_expressionContext;
  class Insert_clauseContext;
  class Update_clauseContext;
  class Delete_clauseContext;
  class Value_clauseContext;
  class Value_listContext;
  class Set_clauseContext;
  class Set_assignmentContext;
  class From_clauseContext;
  class Where_clauseContext;
  class Where_expressionContext;
  class Cond_expressionContext;
  class In_conditionContext;
  class In_itemsContext;
  class Like_conditionContext;
  class Compare_conditionContext;
  class Compare_signContext;
  class Arithmetic_expressionContext;
  class Arithmetic_factorContext;
  class Numeric_returning_functionContext;
  class Groupby_clauseContext;
  class Orderby_clauseContext;
  class Orderby_expressionContext;
  class Limit_clauseContext;
  class Value_refContext;
  class Object_refContext;
  class Class_refContext;
  class String_expressionContext; 

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    Select_statementContext *select_statement();
    Insert_statementContext *insert_statement();
    Update_statementContext *update_statement();
    Delete_statementContext *delete_statement();

   
  };

  StatementContext* statement();

  class  Select_statementContext : public antlr4::ParserRuleContext {
  public:
    Select_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Select_clauseContext *select_clause();
    From_clauseContext *from_clause();
    Where_clauseContext *where_clause();
    Groupby_clauseContext *groupby_clause();
    Orderby_clauseContext *orderby_clause();
    Limit_clauseContext *limit_clause();

   
  };

  Select_statementContext* select_statement();

  class  Insert_statementContext : public antlr4::ParserRuleContext {
  public:
    Insert_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Insert_clauseContext *insert_clause();
    Value_clauseContext *value_clause();
    Set_clauseContext *set_clause();

   
  };

  Insert_statementContext* insert_statement();

  class  Update_statementContext : public antlr4::ParserRuleContext {
  public:
    Update_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Update_clauseContext *update_clause();
    Set_clauseContext *set_clause();
    Where_clauseContext *where_clause();
    Orderby_clauseContext *orderby_clause();
    Limit_clauseContext *limit_clause();

   
  };

  Update_statementContext* update_statement();

  class  Delete_statementContext : public antlr4::ParserRuleContext {
  public:
    Delete_statementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Delete_clauseContext *delete_clause();
    From_clauseContext *from_clause();
    Where_clauseContext *where_clause();
    Orderby_clauseContext *orderby_clause();
    Limit_clauseContext *limit_clause();

   
  };

  Delete_statementContext* delete_statement();

  class  Select_clauseContext : public antlr4::ParserRuleContext {
  public:
    Select_clauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SELECT();
    std::vector<Select_expressionContext *> select_expression();
    Select_expressionContext* select_expression(size_t i);

   
  };

  Select_clauseContext* select_clause();

  class  Select_expressionContext : public antlr4::ParserRuleContext {
  public:
    Select_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Aggregate_expressionContext *aggregate_expression();
    Object_refContext *object_ref();
    antlr4::tree::TerminalNode *DISTINCT();
    antlr4::tree::TerminalNode *STAR();

   
  };

  Select_expressionContext* select_expression();

  class  Aggregate_expressionContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *aggFunc = nullptr;;
    Aggregate_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Object_refContext *object_ref();
    antlr4::tree::TerminalNode *AVG();
    antlr4::tree::TerminalNode *MAX();
    antlr4::tree::TerminalNode *MIN();
    antlr4::tree::TerminalNode *SUM();
    antlr4::tree::TerminalNode *COUNT();
    antlr4::tree::TerminalNode *DISTINCT();
    antlr4::tree::TerminalNode *STAR();

   
  };

  Aggregate_expressionContext* aggregate_expression();

  class  Insert_clauseContext : public antlr4::ParserRuleContext {
  public:
    WmsQL1Parser::Object_refContext *object_refContext = nullptr;;
    std::vector<Object_refContext *> members;;
    Insert_clauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INSERT();
    Class_refContext *class_ref();
    antlr4::tree::TerminalNode *INTO();
    std::vector<Object_refContext *> object_ref();
    Object_refContext* object_ref(size_t i);

   
  };

  Insert_clauseContext* insert_clause();

  class  Update_clauseContext : public antlr4::ParserRuleContext {
  public:
    Update_clauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *UPDATE();
    std::vector<Class_refContext *> class_ref();
    Class_refContext* class_ref(size_t i);

   
  };

  Update_clauseContext* update_clause();

  class  Delete_clauseContext : public antlr4::ParserRuleContext {
  public:
    Delete_clauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DELETE();

   
  };

  Delete_clauseContext* delete_clause();

  class  Value_clauseContext : public antlr4::ParserRuleContext {
  public:
    Value_clauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VALUES();
    std::vector<Value_listContext *> value_list();
    Value_listContext* value_list(size_t i);

   
  };

  Value_clauseContext* value_clause();

  class  Value_listContext : public antlr4::ParserRuleContext {
  public:
    Value_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Value_refContext *> value_ref();
    Value_refContext* value_ref(size_t i);

   
  };

  Value_listContext* value_list();

  class  Set_clauseContext : public antlr4::ParserRuleContext {
  public:
    Set_clauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SET();
    std::vector<Set_assignmentContext *> set_assignment();
    Set_assignmentContext* set_assignment(size_t i);

   
  };

  Set_clauseContext* set_clause();

  class  Set_assignmentContext : public antlr4::ParserRuleContext {
  public:
    Set_assignmentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Object_refContext *object_ref();
    antlr4::tree::TerminalNode *EQ();
    Value_refContext *value_ref();

   
  };

  Set_assignmentContext* set_assignment();

  class  From_clauseContext : public antlr4::ParserRuleContext {
  public:
    From_clauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FROM();
    std::vector<Class_refContext *> class_ref();
    Class_refContext* class_ref(size_t i);

   
  };

  From_clauseContext* from_clause();

  class  Where_clauseContext : public antlr4::ParserRuleContext {
  public:
    Where_clauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHERE();
    Where_expressionContext *where_expression();

   
  };

  Where_clauseContext* where_clause();

  class  Where_expressionContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *logical_operator = nullptr;;
    Where_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Where_expressionContext *> where_expression();
    Where_expressionContext* where_expression(size_t i);
    antlr4::tree::TerminalNode *OR();
    antlr4::tree::TerminalNode *AND();
    antlr4::tree::TerminalNode *NOT();
    Cond_expressionContext *cond_expression();

   
  };

  Where_expressionContext* where_expression();
  Where_expressionContext* where_expression(int precedence);
  class  Cond_expressionContext : public antlr4::ParserRuleContext {
  public:
    Cond_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    In_conditionContext *in_condition();
    Like_conditionContext *like_condition();
    Compare_conditionContext *compare_condition();

   
  };

  Cond_expressionContext* cond_expression();

  class  In_conditionContext : public antlr4::ParserRuleContext {
  public:
    In_conditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Object_refContext *object_ref();
    antlr4::tree::TerminalNode *IN();
    In_itemsContext *in_items();
    antlr4::tree::TerminalNode *NOT();

   
  };

  In_conditionContext* in_condition();

  class  In_itemsContext : public antlr4::ParserRuleContext {
  public:
    In_itemsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<String_expressionContext *> string_expression();
    String_expressionContext* string_expression(size_t i);
    std::vector<Arithmetic_expressionContext *> arithmetic_expression();
    Arithmetic_expressionContext* arithmetic_expression(size_t i);

   
  };

  In_itemsContext* in_items();

  class  Like_conditionContext : public antlr4::ParserRuleContext {
  public:
    WmsQL1Parser::Object_refContext *object = nullptr;;
    WmsQL1Parser::String_expressionContext *compareString = nullptr;;
    Like_conditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LIKE();
    Object_refContext *object_ref();
    String_expressionContext *string_expression();
    antlr4::tree::TerminalNode *NOT();
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NEQ();

   
  };

  Like_conditionContext* like_condition();

  class  Compare_conditionContext : public antlr4::ParserRuleContext {
  public:
    Compare_conditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Object_refContext *> object_ref();
    Object_refContext* object_ref(size_t i);
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NEQ();
    antlr4::tree::TerminalNode *TRUE();
    antlr4::tree::TerminalNode *FALSE();
    antlr4::tree::TerminalNode *IS();
    antlr4::tree::TerminalNode *NULL_REPR();
    antlr4::tree::TerminalNode *NOT();
    Compare_signContext *compare_sign();
    Arithmetic_expressionContext *arithmetic_expression();

   
  };

  Compare_conditionContext* compare_condition();

  class  Compare_signContext : public antlr4::ParserRuleContext {
  public:
    Compare_signContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NEQ();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *LEQ();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *GEQ();

   
  };

  Compare_signContext* compare_sign();

  class  Arithmetic_expressionContext : public antlr4::ParserRuleContext {
  public:
    Arithmetic_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Arithmetic_expressionContext *> arithmetic_expression();
    Arithmetic_expressionContext* arithmetic_expression(size_t i);
    Arithmetic_factorContext *arithmetic_factor();
    antlr4::tree::TerminalNode *STAR();
    antlr4::tree::TerminalNode *SLASH();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

   
  };

  Arithmetic_expressionContext* arithmetic_expression();
  Arithmetic_expressionContext* arithmetic_expression(int precedence);
  class  Arithmetic_factorContext : public antlr4::ParserRuleContext {
  public:
    antlr4::Token *type = nullptr;;
    Arithmetic_factorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT_TYPE();
    antlr4::tree::TerminalNode *FLOAT_TYPE();
    antlr4::tree::TerminalNode *DATE_TYPE();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();
    Numeric_returning_functionContext *numeric_returning_function();
    String_expressionContext *string_expression();

   
  };

  Arithmetic_factorContext* arithmetic_factor();

  class  Numeric_returning_functionContext : public antlr4::ParserRuleContext {
  public:
    Numeric_returning_functionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MOD();
    std::vector<Arithmetic_factorContext *> arithmetic_factor();
    Arithmetic_factorContext* arithmetic_factor(size_t i);
    antlr4::tree::TerminalNode *ABS();
    antlr4::tree::TerminalNode *LENGTH();
    String_expressionContext *string_expression();

   
  };

  Numeric_returning_functionContext* numeric_returning_function();

  class  Groupby_clauseContext : public antlr4::ParserRuleContext {
  public:
    Groupby_clauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GROUP();
    antlr4::tree::TerminalNode *BY();
    std::vector<Object_refContext *> object_ref();
    Object_refContext* object_ref(size_t i);

   
  };

  Groupby_clauseContext* groupby_clause();

  class  Orderby_clauseContext : public antlr4::ParserRuleContext {
  public:
    Orderby_clauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ORDER();
    antlr4::tree::TerminalNode *BY();
    std::vector<Orderby_expressionContext *> orderby_expression();
    Orderby_expressionContext* orderby_expression(size_t i);

   
  };

  Orderby_clauseContext* orderby_clause();

  class  Orderby_expressionContext : public antlr4::ParserRuleContext {
  public:
    Orderby_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Object_refContext *object_ref();
    antlr4::tree::TerminalNode *ASC();
    antlr4::tree::TerminalNode *DESC();

   
  };

  Orderby_expressionContext* orderby_expression();

  class  Limit_clauseContext : public antlr4::ParserRuleContext {
  public:
    Limit_clauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LIMIT();
    std::vector<antlr4::tree::TerminalNode *> INT_TYPE();
    antlr4::tree::TerminalNode* INT_TYPE(size_t i);

   
  };

  Limit_clauseContext* limit_clause();

  class  Value_refContext : public antlr4::ParserRuleContext {
  public:
    Value_refContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT_TYPE();
    antlr4::tree::TerminalNode *FLOAT_TYPE();
    antlr4::tree::TerminalNode *DATE_TYPE();
    antlr4::tree::TerminalNode *STRING_TYPE();

   
  };

  Value_refContext* value_ref();

  class  Object_refContext : public antlr4::ParserRuleContext {
  public:
    Object_refContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *IDPATH();

   
  };

  Object_refContext* object_ref();

  class  Class_refContext : public antlr4::ParserRuleContext {
  public:
    Class_refContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *CLASSID();
    antlr4::tree::TerminalNode *STRING_TYPE();

   
  };

  Class_refContext* class_ref();

  class  String_expressionContext : public antlr4::ParserRuleContext {
  public:
    String_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SUBSTRING();
    std::vector<String_expressionContext *> string_expression();
    String_expressionContext* string_expression(size_t i);
    antlr4::tree::TerminalNode *CONCAT();
    antlr4::tree::TerminalNode *LOWER();
    antlr4::tree::TerminalNode *UPPER();
    antlr4::tree::TerminalNode *STRING_TYPE();
    Object_refContext *object_ref();
    Aggregate_expressionContext *aggregate_expression();

   
  };

  String_expressionContext* string_expression();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool where_expressionSempred(Where_expressionContext *_localctx, size_t predicateIndex);
  bool arithmetic_expressionSempred(Arithmetic_expressionContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

