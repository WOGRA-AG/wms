
#undef emit


// Generated from WmsQL1.g4 by ANTLR 4.7.2



#include "WmsQL1Parser.h"


using namespace antlrcpp;
using namespace antlr4;

WmsQL1Parser::WmsQL1Parser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

WmsQL1Parser::~WmsQL1Parser() {
  delete _interpreter;
}

std::string WmsQL1Parser::getGrammarFileName() const {
  return "WmsQL1.g4";
}

const std::vector<std::string>& WmsQL1Parser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& WmsQL1Parser::getVocabulary() const {
  return _vocabulary;
}


//----------------- StatementContext ------------------------------------------------------------------

WmsQL1Parser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::StatementContext::EOF() {
  return getToken(WmsQL1Parser::EOF, 0);
}

WmsQL1Parser::Select_statementContext* WmsQL1Parser::StatementContext::select_statement() {
  return getRuleContext<WmsQL1Parser::Select_statementContext>(0);
}

WmsQL1Parser::Insert_statementContext* WmsQL1Parser::StatementContext::insert_statement() {
  return getRuleContext<WmsQL1Parser::Insert_statementContext>(0);
}

WmsQL1Parser::Update_statementContext* WmsQL1Parser::StatementContext::update_statement() {
  return getRuleContext<WmsQL1Parser::Update_statementContext>(0);
}

WmsQL1Parser::Delete_statementContext* WmsQL1Parser::StatementContext::delete_statement() {
  return getRuleContext<WmsQL1Parser::Delete_statementContext>(0);
}


size_t WmsQL1Parser::StatementContext::getRuleIndex() const {
  return WmsQL1Parser::RuleStatement;
}


WmsQL1Parser::StatementContext* WmsQL1Parser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 0, WmsQL1Parser::RuleStatement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(74);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case WmsQL1Parser::SELECT: {
        setState(70);
        select_statement();
        break;
      }

      case WmsQL1Parser::INSERT: {
        setState(71);
        insert_statement();
        break;
      }

      case WmsQL1Parser::UPDATE: {
        setState(72);
        update_statement();
        break;
      }

      case WmsQL1Parser::DELETE: {
        setState(73);
        delete_statement();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(76);
    match(WmsQL1Parser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Select_statementContext ------------------------------------------------------------------

WmsQL1Parser::Select_statementContext::Select_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WmsQL1Parser::Select_clauseContext* WmsQL1Parser::Select_statementContext::select_clause() {
  return getRuleContext<WmsQL1Parser::Select_clauseContext>(0);
}

WmsQL1Parser::From_clauseContext* WmsQL1Parser::Select_statementContext::from_clause() {
  return getRuleContext<WmsQL1Parser::From_clauseContext>(0);
}

WmsQL1Parser::Where_clauseContext* WmsQL1Parser::Select_statementContext::where_clause() {
  return getRuleContext<WmsQL1Parser::Where_clauseContext>(0);
}

WmsQL1Parser::Groupby_clauseContext* WmsQL1Parser::Select_statementContext::groupby_clause() {
  return getRuleContext<WmsQL1Parser::Groupby_clauseContext>(0);
}

WmsQL1Parser::Orderby_clauseContext* WmsQL1Parser::Select_statementContext::orderby_clause() {
  return getRuleContext<WmsQL1Parser::Orderby_clauseContext>(0);
}

WmsQL1Parser::Limit_clauseContext* WmsQL1Parser::Select_statementContext::limit_clause() {
  return getRuleContext<WmsQL1Parser::Limit_clauseContext>(0);
}


size_t WmsQL1Parser::Select_statementContext::getRuleIndex() const {
  return WmsQL1Parser::RuleSelect_statement;
}


WmsQL1Parser::Select_statementContext* WmsQL1Parser::select_statement() {
  Select_statementContext *_localctx = _tracker.createInstance<Select_statementContext>(_ctx, getState());
  enterRule(_localctx, 2, WmsQL1Parser::RuleSelect_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(78);
    select_clause();
    setState(79);
    from_clause();
    setState(81);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WmsQL1Parser::WHERE) {
      setState(80);
      where_clause();
    }
    setState(84);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WmsQL1Parser::GROUP) {
      setState(83);
      groupby_clause();
    }
    setState(87);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WmsQL1Parser::ORDER) {
      setState(86);
      orderby_clause();
    }
    setState(90);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WmsQL1Parser::LIMIT) {
      setState(89);
      limit_clause();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Insert_statementContext ------------------------------------------------------------------

WmsQL1Parser::Insert_statementContext::Insert_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WmsQL1Parser::Insert_clauseContext* WmsQL1Parser::Insert_statementContext::insert_clause() {
  return getRuleContext<WmsQL1Parser::Insert_clauseContext>(0);
}

WmsQL1Parser::Value_clauseContext* WmsQL1Parser::Insert_statementContext::value_clause() {
  return getRuleContext<WmsQL1Parser::Value_clauseContext>(0);
}

WmsQL1Parser::Set_clauseContext* WmsQL1Parser::Insert_statementContext::set_clause() {
  return getRuleContext<WmsQL1Parser::Set_clauseContext>(0);
}


size_t WmsQL1Parser::Insert_statementContext::getRuleIndex() const {
  return WmsQL1Parser::RuleInsert_statement;
}


WmsQL1Parser::Insert_statementContext* WmsQL1Parser::insert_statement() {
  Insert_statementContext *_localctx = _tracker.createInstance<Insert_statementContext>(_ctx, getState());
  enterRule(_localctx, 4, WmsQL1Parser::RuleInsert_statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(98);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(92);
      insert_clause();
      setState(93);
      value_clause();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(95);
      insert_clause();
      setState(96);
      set_clause();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Update_statementContext ------------------------------------------------------------------

WmsQL1Parser::Update_statementContext::Update_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WmsQL1Parser::Update_clauseContext* WmsQL1Parser::Update_statementContext::update_clause() {
  return getRuleContext<WmsQL1Parser::Update_clauseContext>(0);
}

WmsQL1Parser::Set_clauseContext* WmsQL1Parser::Update_statementContext::set_clause() {
  return getRuleContext<WmsQL1Parser::Set_clauseContext>(0);
}

WmsQL1Parser::Where_clauseContext* WmsQL1Parser::Update_statementContext::where_clause() {
  return getRuleContext<WmsQL1Parser::Where_clauseContext>(0);
}

WmsQL1Parser::Orderby_clauseContext* WmsQL1Parser::Update_statementContext::orderby_clause() {
  return getRuleContext<WmsQL1Parser::Orderby_clauseContext>(0);
}

WmsQL1Parser::Limit_clauseContext* WmsQL1Parser::Update_statementContext::limit_clause() {
  return getRuleContext<WmsQL1Parser::Limit_clauseContext>(0);
}


size_t WmsQL1Parser::Update_statementContext::getRuleIndex() const {
  return WmsQL1Parser::RuleUpdate_statement;
}


WmsQL1Parser::Update_statementContext* WmsQL1Parser::update_statement() {
  Update_statementContext *_localctx = _tracker.createInstance<Update_statementContext>(_ctx, getState());
  enterRule(_localctx, 6, WmsQL1Parser::RuleUpdate_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(100);
    update_clause();
    setState(101);
    set_clause();
    setState(103);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WmsQL1Parser::WHERE) {
      setState(102);
      where_clause();
    }
    setState(106);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WmsQL1Parser::ORDER) {
      setState(105);
      orderby_clause();
    }
    setState(109);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WmsQL1Parser::LIMIT) {
      setState(108);
      limit_clause();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Delete_statementContext ------------------------------------------------------------------

WmsQL1Parser::Delete_statementContext::Delete_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WmsQL1Parser::Delete_clauseContext* WmsQL1Parser::Delete_statementContext::delete_clause() {
  return getRuleContext<WmsQL1Parser::Delete_clauseContext>(0);
}

WmsQL1Parser::From_clauseContext* WmsQL1Parser::Delete_statementContext::from_clause() {
  return getRuleContext<WmsQL1Parser::From_clauseContext>(0);
}

WmsQL1Parser::Where_clauseContext* WmsQL1Parser::Delete_statementContext::where_clause() {
  return getRuleContext<WmsQL1Parser::Where_clauseContext>(0);
}

WmsQL1Parser::Orderby_clauseContext* WmsQL1Parser::Delete_statementContext::orderby_clause() {
  return getRuleContext<WmsQL1Parser::Orderby_clauseContext>(0);
}

WmsQL1Parser::Limit_clauseContext* WmsQL1Parser::Delete_statementContext::limit_clause() {
  return getRuleContext<WmsQL1Parser::Limit_clauseContext>(0);
}


size_t WmsQL1Parser::Delete_statementContext::getRuleIndex() const {
  return WmsQL1Parser::RuleDelete_statement;
}


WmsQL1Parser::Delete_statementContext* WmsQL1Parser::delete_statement() {
  Delete_statementContext *_localctx = _tracker.createInstance<Delete_statementContext>(_ctx, getState());
  enterRule(_localctx, 8, WmsQL1Parser::RuleDelete_statement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(111);
    delete_clause();
    setState(112);
    from_clause();
    setState(114);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WmsQL1Parser::WHERE) {
      setState(113);
      where_clause();
    }
    setState(117);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WmsQL1Parser::ORDER) {
      setState(116);
      orderby_clause();
    }
    setState(120);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WmsQL1Parser::LIMIT) {
      setState(119);
      limit_clause();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Select_clauseContext ------------------------------------------------------------------

WmsQL1Parser::Select_clauseContext::Select_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::Select_clauseContext::SELECT() {
  return getToken(WmsQL1Parser::SELECT, 0);
}

std::vector<WmsQL1Parser::Select_expressionContext *> WmsQL1Parser::Select_clauseContext::select_expression() {
  return getRuleContexts<WmsQL1Parser::Select_expressionContext>();
}

WmsQL1Parser::Select_expressionContext* WmsQL1Parser::Select_clauseContext::select_expression(size_t i) {
  return getRuleContext<WmsQL1Parser::Select_expressionContext>(i);
}


size_t WmsQL1Parser::Select_clauseContext::getRuleIndex() const {
  return WmsQL1Parser::RuleSelect_clause;
}


WmsQL1Parser::Select_clauseContext* WmsQL1Parser::select_clause() {
  Select_clauseContext *_localctx = _tracker.createInstance<Select_clauseContext>(_ctx, getState());
  enterRule(_localctx, 10, WmsQL1Parser::RuleSelect_clause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(122);
    match(WmsQL1Parser::SELECT);
    setState(131);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << WmsQL1Parser::DISTINCT)
      | (1ULL << WmsQL1Parser::AVG)
      | (1ULL << WmsQL1Parser::MAX)
      | (1ULL << WmsQL1Parser::MIN)
      | (1ULL << WmsQL1Parser::SUM)
      | (1ULL << WmsQL1Parser::COUNT)
      | (1ULL << WmsQL1Parser::STAR)
      | (1ULL << WmsQL1Parser::ID)
      | (1ULL << WmsQL1Parser::IDPATH))) != 0)) {
      setState(123);
      select_expression();
      setState(128);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == WmsQL1Parser::T__0) {
        setState(124);
        match(WmsQL1Parser::T__0);
        setState(125);
        select_expression();
        setState(130);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Select_expressionContext ------------------------------------------------------------------

WmsQL1Parser::Select_expressionContext::Select_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WmsQL1Parser::Aggregate_expressionContext* WmsQL1Parser::Select_expressionContext::aggregate_expression() {
  return getRuleContext<WmsQL1Parser::Aggregate_expressionContext>(0);
}

WmsQL1Parser::Object_refContext* WmsQL1Parser::Select_expressionContext::object_ref() {
  return getRuleContext<WmsQL1Parser::Object_refContext>(0);
}

tree::TerminalNode* WmsQL1Parser::Select_expressionContext::DISTINCT() {
  return getToken(WmsQL1Parser::DISTINCT, 0);
}

tree::TerminalNode* WmsQL1Parser::Select_expressionContext::STAR() {
  return getToken(WmsQL1Parser::STAR, 0);
}


size_t WmsQL1Parser::Select_expressionContext::getRuleIndex() const {
  return WmsQL1Parser::RuleSelect_expression;
}


WmsQL1Parser::Select_expressionContext* WmsQL1Parser::select_expression() {
  Select_expressionContext *_localctx = _tracker.createInstance<Select_expressionContext>(_ctx, getState());
  enterRule(_localctx, 12, WmsQL1Parser::RuleSelect_expression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(139);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case WmsQL1Parser::AVG:
      case WmsQL1Parser::MAX:
      case WmsQL1Parser::MIN:
      case WmsQL1Parser::SUM:
      case WmsQL1Parser::COUNT: {
        enterOuterAlt(_localctx, 1);
        setState(133);
        aggregate_expression();
        break;
      }

      case WmsQL1Parser::DISTINCT:
      case WmsQL1Parser::ID:
      case WmsQL1Parser::IDPATH: {
        enterOuterAlt(_localctx, 2);
        setState(135);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == WmsQL1Parser::DISTINCT) {
          setState(134);
          match(WmsQL1Parser::DISTINCT);
        }
        setState(137);
        object_ref();
        break;
      }

      case WmsQL1Parser::STAR: {
        enterOuterAlt(_localctx, 3);
        setState(138);
        match(WmsQL1Parser::STAR);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Aggregate_expressionContext ------------------------------------------------------------------

WmsQL1Parser::Aggregate_expressionContext::Aggregate_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WmsQL1Parser::Object_refContext* WmsQL1Parser::Aggregate_expressionContext::object_ref() {
  return getRuleContext<WmsQL1Parser::Object_refContext>(0);
}

tree::TerminalNode* WmsQL1Parser::Aggregate_expressionContext::AVG() {
  return getToken(WmsQL1Parser::AVG, 0);
}

tree::TerminalNode* WmsQL1Parser::Aggregate_expressionContext::MAX() {
  return getToken(WmsQL1Parser::MAX, 0);
}

tree::TerminalNode* WmsQL1Parser::Aggregate_expressionContext::MIN() {
  return getToken(WmsQL1Parser::MIN, 0);
}

tree::TerminalNode* WmsQL1Parser::Aggregate_expressionContext::SUM() {
  return getToken(WmsQL1Parser::SUM, 0);
}

tree::TerminalNode* WmsQL1Parser::Aggregate_expressionContext::COUNT() {
  return getToken(WmsQL1Parser::COUNT, 0);
}

tree::TerminalNode* WmsQL1Parser::Aggregate_expressionContext::DISTINCT() {
  return getToken(WmsQL1Parser::DISTINCT, 0);
}

tree::TerminalNode* WmsQL1Parser::Aggregate_expressionContext::STAR() {
  return getToken(WmsQL1Parser::STAR, 0);
}


size_t WmsQL1Parser::Aggregate_expressionContext::getRuleIndex() const {
  return WmsQL1Parser::RuleAggregate_expression;
}


WmsQL1Parser::Aggregate_expressionContext* WmsQL1Parser::aggregate_expression() {
  Aggregate_expressionContext *_localctx = _tracker.createInstance<Aggregate_expressionContext>(_ctx, getState());
  enterRule(_localctx, 14, WmsQL1Parser::RuleAggregate_expression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(156);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(141);
      dynamic_cast<Aggregate_expressionContext *>(_localctx)->aggFunc = _input->LT(1);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << WmsQL1Parser::AVG)
        | (1ULL << WmsQL1Parser::MAX)
        | (1ULL << WmsQL1Parser::MIN)
        | (1ULL << WmsQL1Parser::SUM)
        | (1ULL << WmsQL1Parser::COUNT))) != 0))) {
        dynamic_cast<Aggregate_expressionContext *>(_localctx)->aggFunc = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(142);
      match(WmsQL1Parser::T__1);
      setState(144);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WmsQL1Parser::DISTINCT) {
        setState(143);
        match(WmsQL1Parser::DISTINCT);
      }
      setState(146);
      object_ref();
      setState(147);
      match(WmsQL1Parser::T__2);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(149);
      dynamic_cast<Aggregate_expressionContext *>(_localctx)->aggFunc = match(WmsQL1Parser::COUNT);
      setState(150);
      match(WmsQL1Parser::T__1);
      setState(152);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WmsQL1Parser::DISTINCT) {
        setState(151);
        match(WmsQL1Parser::DISTINCT);
      }
      setState(154);
      match(WmsQL1Parser::STAR);
      setState(155);
      match(WmsQL1Parser::T__2);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Insert_clauseContext ------------------------------------------------------------------

WmsQL1Parser::Insert_clauseContext::Insert_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::Insert_clauseContext::INSERT() {
  return getToken(WmsQL1Parser::INSERT, 0);
}

WmsQL1Parser::Class_refContext* WmsQL1Parser::Insert_clauseContext::class_ref() {
  return getRuleContext<WmsQL1Parser::Class_refContext>(0);
}

tree::TerminalNode* WmsQL1Parser::Insert_clauseContext::INTO() {
  return getToken(WmsQL1Parser::INTO, 0);
}

std::vector<WmsQL1Parser::Object_refContext *> WmsQL1Parser::Insert_clauseContext::object_ref() {
  return getRuleContexts<WmsQL1Parser::Object_refContext>();
}

WmsQL1Parser::Object_refContext* WmsQL1Parser::Insert_clauseContext::object_ref(size_t i) {
  return getRuleContext<WmsQL1Parser::Object_refContext>(i);
}


size_t WmsQL1Parser::Insert_clauseContext::getRuleIndex() const {
  return WmsQL1Parser::RuleInsert_clause;
}


WmsQL1Parser::Insert_clauseContext* WmsQL1Parser::insert_clause() {
  Insert_clauseContext *_localctx = _tracker.createInstance<Insert_clauseContext>(_ctx, getState());
  enterRule(_localctx, 16, WmsQL1Parser::RuleInsert_clause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(158);
    match(WmsQL1Parser::INSERT);
    setState(160);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WmsQL1Parser::INTO) {
      setState(159);
      match(WmsQL1Parser::INTO);
    }
    setState(162);
    class_ref();
    setState(175);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WmsQL1Parser::T__1) {
      setState(163);
      match(WmsQL1Parser::T__1);
      setState(172);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WmsQL1Parser::ID

      || _la == WmsQL1Parser::IDPATH) {
        setState(164);
        dynamic_cast<Insert_clauseContext *>(_localctx)->object_refContext = object_ref();
        dynamic_cast<Insert_clauseContext *>(_localctx)->members.push_back(dynamic_cast<Insert_clauseContext *>(_localctx)->object_refContext);
        setState(169);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == WmsQL1Parser::T__0) {
          setState(165);
          match(WmsQL1Parser::T__0);
          setState(166);
          dynamic_cast<Insert_clauseContext *>(_localctx)->object_refContext = object_ref();
          dynamic_cast<Insert_clauseContext *>(_localctx)->members.push_back(dynamic_cast<Insert_clauseContext *>(_localctx)->object_refContext);
          setState(171);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(174);
      match(WmsQL1Parser::T__2);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Update_clauseContext ------------------------------------------------------------------

WmsQL1Parser::Update_clauseContext::Update_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::Update_clauseContext::UPDATE() {
  return getToken(WmsQL1Parser::UPDATE, 0);
}

std::vector<WmsQL1Parser::Class_refContext *> WmsQL1Parser::Update_clauseContext::class_ref() {
  return getRuleContexts<WmsQL1Parser::Class_refContext>();
}

WmsQL1Parser::Class_refContext* WmsQL1Parser::Update_clauseContext::class_ref(size_t i) {
  return getRuleContext<WmsQL1Parser::Class_refContext>(i);
}


size_t WmsQL1Parser::Update_clauseContext::getRuleIndex() const {
  return WmsQL1Parser::RuleUpdate_clause;
}


WmsQL1Parser::Update_clauseContext* WmsQL1Parser::update_clause() {
  Update_clauseContext *_localctx = _tracker.createInstance<Update_clauseContext>(_ctx, getState());
  enterRule(_localctx, 18, WmsQL1Parser::RuleUpdate_clause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(177);
    match(WmsQL1Parser::UPDATE);
    setState(178);
    class_ref();
    setState(183);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == WmsQL1Parser::T__0) {
      setState(179);
      match(WmsQL1Parser::T__0);
      setState(180);
      class_ref();
      setState(185);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Delete_clauseContext ------------------------------------------------------------------

WmsQL1Parser::Delete_clauseContext::Delete_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::Delete_clauseContext::DELETE() {
  return getToken(WmsQL1Parser::DELETE, 0);
}


size_t WmsQL1Parser::Delete_clauseContext::getRuleIndex() const {
  return WmsQL1Parser::RuleDelete_clause;
}


WmsQL1Parser::Delete_clauseContext* WmsQL1Parser::delete_clause() {
  Delete_clauseContext *_localctx = _tracker.createInstance<Delete_clauseContext>(_ctx, getState());
  enterRule(_localctx, 20, WmsQL1Parser::RuleDelete_clause);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(186);
    match(WmsQL1Parser::DELETE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Value_clauseContext ------------------------------------------------------------------

WmsQL1Parser::Value_clauseContext::Value_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::Value_clauseContext::VALUES() {
  return getToken(WmsQL1Parser::VALUES, 0);
}

std::vector<WmsQL1Parser::Value_listContext *> WmsQL1Parser::Value_clauseContext::value_list() {
  return getRuleContexts<WmsQL1Parser::Value_listContext>();
}

WmsQL1Parser::Value_listContext* WmsQL1Parser::Value_clauseContext::value_list(size_t i) {
  return getRuleContext<WmsQL1Parser::Value_listContext>(i);
}


size_t WmsQL1Parser::Value_clauseContext::getRuleIndex() const {
  return WmsQL1Parser::RuleValue_clause;
}


WmsQL1Parser::Value_clauseContext* WmsQL1Parser::value_clause() {
  Value_clauseContext *_localctx = _tracker.createInstance<Value_clauseContext>(_ctx, getState());
  enterRule(_localctx, 22, WmsQL1Parser::RuleValue_clause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(188);
    match(WmsQL1Parser::VALUES);
    setState(189);
    value_list();
    setState(194);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == WmsQL1Parser::T__0) {
      setState(190);
      match(WmsQL1Parser::T__0);
      setState(191);
      value_list();
      setState(196);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Value_listContext ------------------------------------------------------------------

WmsQL1Parser::Value_listContext::Value_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WmsQL1Parser::Value_refContext *> WmsQL1Parser::Value_listContext::value_ref() {
  return getRuleContexts<WmsQL1Parser::Value_refContext>();
}

WmsQL1Parser::Value_refContext* WmsQL1Parser::Value_listContext::value_ref(size_t i) {
  return getRuleContext<WmsQL1Parser::Value_refContext>(i);
}


size_t WmsQL1Parser::Value_listContext::getRuleIndex() const {
  return WmsQL1Parser::RuleValue_list;
}


WmsQL1Parser::Value_listContext* WmsQL1Parser::value_list() {
  Value_listContext *_localctx = _tracker.createInstance<Value_listContext>(_ctx, getState());
  enterRule(_localctx, 24, WmsQL1Parser::RuleValue_list);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(210);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 26, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(197);
      match(WmsQL1Parser::T__1);
      setState(198);
      value_ref();
      setState(203);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == WmsQL1Parser::T__0) {
        setState(199);
        match(WmsQL1Parser::T__0);
        setState(200);
        value_ref();
        setState(205);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(206);
      match(WmsQL1Parser::T__2);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(208);
      match(WmsQL1Parser::T__1);
      setState(209);
      match(WmsQL1Parser::T__2);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Set_clauseContext ------------------------------------------------------------------

WmsQL1Parser::Set_clauseContext::Set_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::Set_clauseContext::SET() {
  return getToken(WmsQL1Parser::SET, 0);
}

std::vector<WmsQL1Parser::Set_assignmentContext *> WmsQL1Parser::Set_clauseContext::set_assignment() {
  return getRuleContexts<WmsQL1Parser::Set_assignmentContext>();
}

WmsQL1Parser::Set_assignmentContext* WmsQL1Parser::Set_clauseContext::set_assignment(size_t i) {
  return getRuleContext<WmsQL1Parser::Set_assignmentContext>(i);
}


size_t WmsQL1Parser::Set_clauseContext::getRuleIndex() const {
  return WmsQL1Parser::RuleSet_clause;
}


WmsQL1Parser::Set_clauseContext* WmsQL1Parser::set_clause() {
  Set_clauseContext *_localctx = _tracker.createInstance<Set_clauseContext>(_ctx, getState());
  enterRule(_localctx, 26, WmsQL1Parser::RuleSet_clause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(212);
    match(WmsQL1Parser::SET);
    setState(213);
    set_assignment();
    setState(218);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == WmsQL1Parser::T__0) {
      setState(214);
      match(WmsQL1Parser::T__0);
      setState(215);
      set_assignment();
      setState(220);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Set_assignmentContext ------------------------------------------------------------------

WmsQL1Parser::Set_assignmentContext::Set_assignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WmsQL1Parser::Object_refContext* WmsQL1Parser::Set_assignmentContext::object_ref() {
  return getRuleContext<WmsQL1Parser::Object_refContext>(0);
}

tree::TerminalNode* WmsQL1Parser::Set_assignmentContext::EQ() {
  return getToken(WmsQL1Parser::EQ, 0);
}

WmsQL1Parser::Value_refContext* WmsQL1Parser::Set_assignmentContext::value_ref() {
  return getRuleContext<WmsQL1Parser::Value_refContext>(0);
}


size_t WmsQL1Parser::Set_assignmentContext::getRuleIndex() const {
  return WmsQL1Parser::RuleSet_assignment;
}


WmsQL1Parser::Set_assignmentContext* WmsQL1Parser::set_assignment() {
  Set_assignmentContext *_localctx = _tracker.createInstance<Set_assignmentContext>(_ctx, getState());
  enterRule(_localctx, 28, WmsQL1Parser::RuleSet_assignment);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(221);
    object_ref();
    setState(222);
    match(WmsQL1Parser::EQ);
    setState(223);
    value_ref();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- From_clauseContext ------------------------------------------------------------------

WmsQL1Parser::From_clauseContext::From_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::From_clauseContext::FROM() {
  return getToken(WmsQL1Parser::FROM, 0);
}

std::vector<WmsQL1Parser::Class_refContext *> WmsQL1Parser::From_clauseContext::class_ref() {
  return getRuleContexts<WmsQL1Parser::Class_refContext>();
}

WmsQL1Parser::Class_refContext* WmsQL1Parser::From_clauseContext::class_ref(size_t i) {
  return getRuleContext<WmsQL1Parser::Class_refContext>(i);
}


size_t WmsQL1Parser::From_clauseContext::getRuleIndex() const {
  return WmsQL1Parser::RuleFrom_clause;
}


WmsQL1Parser::From_clauseContext* WmsQL1Parser::from_clause() {
  From_clauseContext *_localctx = _tracker.createInstance<From_clauseContext>(_ctx, getState());
  enterRule(_localctx, 30, WmsQL1Parser::RuleFrom_clause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(225);
    match(WmsQL1Parser::FROM);
    setState(226);
    class_ref();
    setState(231);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == WmsQL1Parser::T__0) {
      setState(227);
      match(WmsQL1Parser::T__0);
      setState(228);
      class_ref();
      setState(233);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Where_clauseContext ------------------------------------------------------------------

WmsQL1Parser::Where_clauseContext::Where_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::Where_clauseContext::WHERE() {
  return getToken(WmsQL1Parser::WHERE, 0);
}

WmsQL1Parser::Where_expressionContext* WmsQL1Parser::Where_clauseContext::where_expression() {
  return getRuleContext<WmsQL1Parser::Where_expressionContext>(0);
}


size_t WmsQL1Parser::Where_clauseContext::getRuleIndex() const {
  return WmsQL1Parser::RuleWhere_clause;
}


WmsQL1Parser::Where_clauseContext* WmsQL1Parser::where_clause() {
  Where_clauseContext *_localctx = _tracker.createInstance<Where_clauseContext>(_ctx, getState());
  enterRule(_localctx, 32, WmsQL1Parser::RuleWhere_clause);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(234);
    match(WmsQL1Parser::WHERE);
    setState(235);
    where_expression(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Where_expressionContext ------------------------------------------------------------------

WmsQL1Parser::Where_expressionContext::Where_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WmsQL1Parser::Where_expressionContext *> WmsQL1Parser::Where_expressionContext::where_expression() {
  return getRuleContexts<WmsQL1Parser::Where_expressionContext>();
}

WmsQL1Parser::Where_expressionContext* WmsQL1Parser::Where_expressionContext::where_expression(size_t i) {
  return getRuleContext<WmsQL1Parser::Where_expressionContext>(i);
}

tree::TerminalNode* WmsQL1Parser::Where_expressionContext::OR() {
  return getToken(WmsQL1Parser::OR, 0);
}

tree::TerminalNode* WmsQL1Parser::Where_expressionContext::AND() {
  return getToken(WmsQL1Parser::AND, 0);
}

tree::TerminalNode* WmsQL1Parser::Where_expressionContext::NOT() {
  return getToken(WmsQL1Parser::NOT, 0);
}

WmsQL1Parser::Cond_expressionContext* WmsQL1Parser::Where_expressionContext::cond_expression() {
  return getRuleContext<WmsQL1Parser::Cond_expressionContext>(0);
}


size_t WmsQL1Parser::Where_expressionContext::getRuleIndex() const {
  return WmsQL1Parser::RuleWhere_expression;
}



WmsQL1Parser::Where_expressionContext* WmsQL1Parser::where_expression() {
   return where_expression(0);
}

WmsQL1Parser::Where_expressionContext* WmsQL1Parser::where_expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  WmsQL1Parser::Where_expressionContext *_localctx = _tracker.createInstance<Where_expressionContext>(_ctx, parentState);
  WmsQL1Parser::Where_expressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 34;
  enterRecursionRule(_localctx, 34, WmsQL1Parser::RuleWhere_expression, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(258);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      setState(238);
      dynamic_cast<Where_expressionContext *>(_localctx)->logical_operator = _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == WmsQL1Parser::AND

      || _la == WmsQL1Parser::OR)) {
        dynamic_cast<Where_expressionContext *>(_localctx)->logical_operator = _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(239);
      match(WmsQL1Parser::T__1);
      setState(240);
      where_expression(0);
      setState(245);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == WmsQL1Parser::T__0) {
        setState(241);
        match(WmsQL1Parser::T__0);
        setState(242);
        where_expression(0);
        setState(247);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(248);
      match(WmsQL1Parser::T__2);
      break;
    }

    case 2: {
      setState(251);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WmsQL1Parser::NOT) {
        setState(250);
        dynamic_cast<Where_expressionContext *>(_localctx)->logical_operator = match(WmsQL1Parser::NOT);
      }
      setState(253);
      match(WmsQL1Parser::T__1);
      setState(254);
      where_expression(0);
      setState(255);
      match(WmsQL1Parser::T__2);
      break;
    }

    case 3: {
      setState(257);
      cond_expression();
      break;
    }

    }
    _ctx->stop = _input->LT(-1);
    setState(268);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(266);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Where_expressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleWhere_expression);
          setState(260);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(261);
          dynamic_cast<Where_expressionContext *>(_localctx)->logical_operator = match(WmsQL1Parser::AND);
          setState(262);
          where_expression(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Where_expressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleWhere_expression);
          setState(263);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(264);
          dynamic_cast<Where_expressionContext *>(_localctx)->logical_operator = match(WmsQL1Parser::OR);
          setState(265);
          where_expression(4);
          break;
        }

        } 
      }
      setState(270);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Cond_expressionContext ------------------------------------------------------------------

WmsQL1Parser::Cond_expressionContext::Cond_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WmsQL1Parser::In_conditionContext* WmsQL1Parser::Cond_expressionContext::in_condition() {
  return getRuleContext<WmsQL1Parser::In_conditionContext>(0);
}

WmsQL1Parser::Like_conditionContext* WmsQL1Parser::Cond_expressionContext::like_condition() {
  return getRuleContext<WmsQL1Parser::Like_conditionContext>(0);
}

WmsQL1Parser::Compare_conditionContext* WmsQL1Parser::Cond_expressionContext::compare_condition() {
  return getRuleContext<WmsQL1Parser::Compare_conditionContext>(0);
}


size_t WmsQL1Parser::Cond_expressionContext::getRuleIndex() const {
  return WmsQL1Parser::RuleCond_expression;
}


WmsQL1Parser::Cond_expressionContext* WmsQL1Parser::cond_expression() {
  Cond_expressionContext *_localctx = _tracker.createInstance<Cond_expressionContext>(_ctx, getState());
  enterRule(_localctx, 36, WmsQL1Parser::RuleCond_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(274);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(271);
      in_condition();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(272);
      like_condition();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(273);
      compare_condition();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- In_conditionContext ------------------------------------------------------------------

WmsQL1Parser::In_conditionContext::In_conditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WmsQL1Parser::Object_refContext* WmsQL1Parser::In_conditionContext::object_ref() {
  return getRuleContext<WmsQL1Parser::Object_refContext>(0);
}

tree::TerminalNode* WmsQL1Parser::In_conditionContext::IN() {
  return getToken(WmsQL1Parser::IN, 0);
}

WmsQL1Parser::In_itemsContext* WmsQL1Parser::In_conditionContext::in_items() {
  return getRuleContext<WmsQL1Parser::In_itemsContext>(0);
}

tree::TerminalNode* WmsQL1Parser::In_conditionContext::NOT() {
  return getToken(WmsQL1Parser::NOT, 0);
}


size_t WmsQL1Parser::In_conditionContext::getRuleIndex() const {
  return WmsQL1Parser::RuleIn_condition;
}


WmsQL1Parser::In_conditionContext* WmsQL1Parser::in_condition() {
  In_conditionContext *_localctx = _tracker.createInstance<In_conditionContext>(_ctx, getState());
  enterRule(_localctx, 38, WmsQL1Parser::RuleIn_condition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(276);
    object_ref();
    setState(278);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WmsQL1Parser::NOT) {
      setState(277);
      match(WmsQL1Parser::NOT);
    }
    setState(280);
    match(WmsQL1Parser::IN);
    setState(281);
    match(WmsQL1Parser::T__1);
    setState(282);
    in_items();
    setState(283);
    match(WmsQL1Parser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- In_itemsContext ------------------------------------------------------------------

WmsQL1Parser::In_itemsContext::In_itemsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WmsQL1Parser::String_expressionContext *> WmsQL1Parser::In_itemsContext::string_expression() {
  return getRuleContexts<WmsQL1Parser::String_expressionContext>();
}

WmsQL1Parser::String_expressionContext* WmsQL1Parser::In_itemsContext::string_expression(size_t i) {
  return getRuleContext<WmsQL1Parser::String_expressionContext>(i);
}

std::vector<WmsQL1Parser::Arithmetic_expressionContext *> WmsQL1Parser::In_itemsContext::arithmetic_expression() {
  return getRuleContexts<WmsQL1Parser::Arithmetic_expressionContext>();
}

WmsQL1Parser::Arithmetic_expressionContext* WmsQL1Parser::In_itemsContext::arithmetic_expression(size_t i) {
  return getRuleContext<WmsQL1Parser::Arithmetic_expressionContext>(i);
}


size_t WmsQL1Parser::In_itemsContext::getRuleIndex() const {
  return WmsQL1Parser::RuleIn_items;
}


WmsQL1Parser::In_itemsContext* WmsQL1Parser::in_items() {
  In_itemsContext *_localctx = _tracker.createInstance<In_itemsContext>(_ctx, getState());
  enterRule(_localctx, 40, WmsQL1Parser::RuleIn_items);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(301);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(285);
      string_expression();
      setState(290);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == WmsQL1Parser::T__0) {
        setState(286);
        match(WmsQL1Parser::T__0);
        setState(287);
        string_expression();
        setState(292);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(293);
      arithmetic_expression(0);
      setState(298);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == WmsQL1Parser::T__0) {
        setState(294);
        match(WmsQL1Parser::T__0);
        setState(295);
        arithmetic_expression(0);
        setState(300);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Like_conditionContext ------------------------------------------------------------------

WmsQL1Parser::Like_conditionContext::Like_conditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::Like_conditionContext::LIKE() {
  return getToken(WmsQL1Parser::LIKE, 0);
}

WmsQL1Parser::Object_refContext* WmsQL1Parser::Like_conditionContext::object_ref() {
  return getRuleContext<WmsQL1Parser::Object_refContext>(0);
}

WmsQL1Parser::String_expressionContext* WmsQL1Parser::Like_conditionContext::string_expression() {
  return getRuleContext<WmsQL1Parser::String_expressionContext>(0);
}

tree::TerminalNode* WmsQL1Parser::Like_conditionContext::NOT() {
  return getToken(WmsQL1Parser::NOT, 0);
}

tree::TerminalNode* WmsQL1Parser::Like_conditionContext::EQ() {
  return getToken(WmsQL1Parser::EQ, 0);
}

tree::TerminalNode* WmsQL1Parser::Like_conditionContext::NEQ() {
  return getToken(WmsQL1Parser::NEQ, 0);
}


size_t WmsQL1Parser::Like_conditionContext::getRuleIndex() const {
  return WmsQL1Parser::RuleLike_condition;
}


WmsQL1Parser::Like_conditionContext* WmsQL1Parser::like_condition() {
  Like_conditionContext *_localctx = _tracker.createInstance<Like_conditionContext>(_ctx, getState());
  enterRule(_localctx, 42, WmsQL1Parser::RuleLike_condition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(314);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(303);
      dynamic_cast<Like_conditionContext *>(_localctx)->object = object_ref();
      setState(305);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WmsQL1Parser::NOT) {
        setState(304);
        match(WmsQL1Parser::NOT);
      }
      setState(307);
      match(WmsQL1Parser::LIKE);
      setState(308);
      dynamic_cast<Like_conditionContext *>(_localctx)->compareString = string_expression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(310);
      dynamic_cast<Like_conditionContext *>(_localctx)->object = object_ref();
      setState(311);
      _la = _input->LA(1);
      if (!(_la == WmsQL1Parser::EQ

      || _la == WmsQL1Parser::NEQ)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(312);
      dynamic_cast<Like_conditionContext *>(_localctx)->compareString = string_expression();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Compare_conditionContext ------------------------------------------------------------------

WmsQL1Parser::Compare_conditionContext::Compare_conditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WmsQL1Parser::Object_refContext *> WmsQL1Parser::Compare_conditionContext::object_ref() {
  return getRuleContexts<WmsQL1Parser::Object_refContext>();
}

WmsQL1Parser::Object_refContext* WmsQL1Parser::Compare_conditionContext::object_ref(size_t i) {
  return getRuleContext<WmsQL1Parser::Object_refContext>(i);
}

tree::TerminalNode* WmsQL1Parser::Compare_conditionContext::EQ() {
  return getToken(WmsQL1Parser::EQ, 0);
}

tree::TerminalNode* WmsQL1Parser::Compare_conditionContext::NEQ() {
  return getToken(WmsQL1Parser::NEQ, 0);
}

tree::TerminalNode* WmsQL1Parser::Compare_conditionContext::TRUE() {
  return getToken(WmsQL1Parser::TRUE, 0);
}

tree::TerminalNode* WmsQL1Parser::Compare_conditionContext::FALSE() {
  return getToken(WmsQL1Parser::FALSE, 0);
}

tree::TerminalNode* WmsQL1Parser::Compare_conditionContext::IS() {
  return getToken(WmsQL1Parser::IS, 0);
}

tree::TerminalNode* WmsQL1Parser::Compare_conditionContext::NULL_REPR() {
  return getToken(WmsQL1Parser::NULL_REPR, 0);
}

tree::TerminalNode* WmsQL1Parser::Compare_conditionContext::NOT() {
  return getToken(WmsQL1Parser::NOT, 0);
}

WmsQL1Parser::Compare_signContext* WmsQL1Parser::Compare_conditionContext::compare_sign() {
  return getRuleContext<WmsQL1Parser::Compare_signContext>(0);
}

WmsQL1Parser::Arithmetic_expressionContext* WmsQL1Parser::Compare_conditionContext::arithmetic_expression() {
  return getRuleContext<WmsQL1Parser::Arithmetic_expressionContext>(0);
}


size_t WmsQL1Parser::Compare_conditionContext::getRuleIndex() const {
  return WmsQL1Parser::RuleCompare_condition;
}


WmsQL1Parser::Compare_conditionContext* WmsQL1Parser::compare_condition() {
  Compare_conditionContext *_localctx = _tracker.createInstance<Compare_conditionContext>(_ctx, getState());
  enterRule(_localctx, 44, WmsQL1Parser::RuleCompare_condition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(339);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 42, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(316);
      object_ref();
      setState(317);
      _la = _input->LA(1);
      if (!(_la == WmsQL1Parser::EQ

      || _la == WmsQL1Parser::NEQ)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(318);
      _la = _input->LA(1);
      if (!(_la == WmsQL1Parser::TRUE

      || _la == WmsQL1Parser::FALSE)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(320);
      object_ref();
      setState(321);
      match(WmsQL1Parser::IS);
      setState(323);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == WmsQL1Parser::NOT) {
        setState(322);
        match(WmsQL1Parser::NOT);
      }
      setState(325);
      match(WmsQL1Parser::NULL_REPR);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(327);
      object_ref();
      setState(328);
      compare_sign();
      setState(329);
      arithmetic_expression(0);
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(331);
      object_ref();
      setState(332);
      compare_sign();
      setState(333);
      object_ref();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(335);
      arithmetic_expression(0);
      setState(336);
      compare_sign();
      setState(337);
      object_ref();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Compare_signContext ------------------------------------------------------------------

WmsQL1Parser::Compare_signContext::Compare_signContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::Compare_signContext::EQ() {
  return getToken(WmsQL1Parser::EQ, 0);
}

tree::TerminalNode* WmsQL1Parser::Compare_signContext::NEQ() {
  return getToken(WmsQL1Parser::NEQ, 0);
}

tree::TerminalNode* WmsQL1Parser::Compare_signContext::LT() {
  return getToken(WmsQL1Parser::LT, 0);
}

tree::TerminalNode* WmsQL1Parser::Compare_signContext::LEQ() {
  return getToken(WmsQL1Parser::LEQ, 0);
}

tree::TerminalNode* WmsQL1Parser::Compare_signContext::GT() {
  return getToken(WmsQL1Parser::GT, 0);
}

tree::TerminalNode* WmsQL1Parser::Compare_signContext::GEQ() {
  return getToken(WmsQL1Parser::GEQ, 0);
}


size_t WmsQL1Parser::Compare_signContext::getRuleIndex() const {
  return WmsQL1Parser::RuleCompare_sign;
}


WmsQL1Parser::Compare_signContext* WmsQL1Parser::compare_sign() {
  Compare_signContext *_localctx = _tracker.createInstance<Compare_signContext>(_ctx, getState());
  enterRule(_localctx, 46, WmsQL1Parser::RuleCompare_sign);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(341);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << WmsQL1Parser::EQ)
      | (1ULL << WmsQL1Parser::NEQ)
      | (1ULL << WmsQL1Parser::LT)
      | (1ULL << WmsQL1Parser::LEQ)
      | (1ULL << WmsQL1Parser::GT)
      | (1ULL << WmsQL1Parser::GEQ))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Arithmetic_expressionContext ------------------------------------------------------------------

WmsQL1Parser::Arithmetic_expressionContext::Arithmetic_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<WmsQL1Parser::Arithmetic_expressionContext *> WmsQL1Parser::Arithmetic_expressionContext::arithmetic_expression() {
  return getRuleContexts<WmsQL1Parser::Arithmetic_expressionContext>();
}

WmsQL1Parser::Arithmetic_expressionContext* WmsQL1Parser::Arithmetic_expressionContext::arithmetic_expression(size_t i) {
  return getRuleContext<WmsQL1Parser::Arithmetic_expressionContext>(i);
}

WmsQL1Parser::Arithmetic_factorContext* WmsQL1Parser::Arithmetic_expressionContext::arithmetic_factor() {
  return getRuleContext<WmsQL1Parser::Arithmetic_factorContext>(0);
}

tree::TerminalNode* WmsQL1Parser::Arithmetic_expressionContext::STAR() {
  return getToken(WmsQL1Parser::STAR, 0);
}

tree::TerminalNode* WmsQL1Parser::Arithmetic_expressionContext::SLASH() {
  return getToken(WmsQL1Parser::SLASH, 0);
}

tree::TerminalNode* WmsQL1Parser::Arithmetic_expressionContext::PLUS() {
  return getToken(WmsQL1Parser::PLUS, 0);
}

tree::TerminalNode* WmsQL1Parser::Arithmetic_expressionContext::MINUS() {
  return getToken(WmsQL1Parser::MINUS, 0);
}


size_t WmsQL1Parser::Arithmetic_expressionContext::getRuleIndex() const {
  return WmsQL1Parser::RuleArithmetic_expression;
}



WmsQL1Parser::Arithmetic_expressionContext* WmsQL1Parser::arithmetic_expression() {
   return arithmetic_expression(0);
}

WmsQL1Parser::Arithmetic_expressionContext* WmsQL1Parser::arithmetic_expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  WmsQL1Parser::Arithmetic_expressionContext *_localctx = _tracker.createInstance<Arithmetic_expressionContext>(_ctx, parentState);
  WmsQL1Parser::Arithmetic_expressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 48;
  enterRecursionRule(_localctx, 48, WmsQL1Parser::RuleArithmetic_expression, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(349);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case WmsQL1Parser::T__1: {
        setState(344);
        match(WmsQL1Parser::T__1);
        setState(345);
        arithmetic_expression(0);
        setState(346);
        match(WmsQL1Parser::T__2);
        break;
      }

      case WmsQL1Parser::AVG:
      case WmsQL1Parser::MAX:
      case WmsQL1Parser::MIN:
      case WmsQL1Parser::SUM:
      case WmsQL1Parser::COUNT:
      case WmsQL1Parser::MOD:
      case WmsQL1Parser::LENGTH:
      case WmsQL1Parser::ABS:
      case WmsQL1Parser::PLUS:
      case WmsQL1Parser::MINUS:
      case WmsQL1Parser::ID:
      case WmsQL1Parser::IDPATH:
      case WmsQL1Parser::STRING_TYPE:
      case WmsQL1Parser::CONCAT:
      case WmsQL1Parser::SUBSTRING:
      case WmsQL1Parser::LOWER:
      case WmsQL1Parser::UPPER:
      case WmsQL1Parser::INT_TYPE:
      case WmsQL1Parser::FLOAT_TYPE:
      case WmsQL1Parser::DATE_TYPE: {
        setState(348);
        arithmetic_factor();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(359);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(357);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 44, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<Arithmetic_expressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleArithmetic_expression);
          setState(351);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(352);
          _la = _input->LA(1);
          if (!(_la == WmsQL1Parser::STAR

          || _la == WmsQL1Parser::SLASH)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(353);
          arithmetic_expression(5);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<Arithmetic_expressionContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleArithmetic_expression);
          setState(354);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(355);
          _la = _input->LA(1);
          if (!(_la == WmsQL1Parser::PLUS

          || _la == WmsQL1Parser::MINUS)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(356);
          arithmetic_expression(4);
          break;
        }

        } 
      }
      setState(361);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 45, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Arithmetic_factorContext ------------------------------------------------------------------

WmsQL1Parser::Arithmetic_factorContext::Arithmetic_factorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::Arithmetic_factorContext::INT_TYPE() {
  return getToken(WmsQL1Parser::INT_TYPE, 0);
}

tree::TerminalNode* WmsQL1Parser::Arithmetic_factorContext::FLOAT_TYPE() {
  return getToken(WmsQL1Parser::FLOAT_TYPE, 0);
}

tree::TerminalNode* WmsQL1Parser::Arithmetic_factorContext::DATE_TYPE() {
  return getToken(WmsQL1Parser::DATE_TYPE, 0);
}

tree::TerminalNode* WmsQL1Parser::Arithmetic_factorContext::PLUS() {
  return getToken(WmsQL1Parser::PLUS, 0);
}

tree::TerminalNode* WmsQL1Parser::Arithmetic_factorContext::MINUS() {
  return getToken(WmsQL1Parser::MINUS, 0);
}

WmsQL1Parser::Numeric_returning_functionContext* WmsQL1Parser::Arithmetic_factorContext::numeric_returning_function() {
  return getRuleContext<WmsQL1Parser::Numeric_returning_functionContext>(0);
}

WmsQL1Parser::String_expressionContext* WmsQL1Parser::Arithmetic_factorContext::string_expression() {
  return getRuleContext<WmsQL1Parser::String_expressionContext>(0);
}


size_t WmsQL1Parser::Arithmetic_factorContext::getRuleIndex() const {
  return WmsQL1Parser::RuleArithmetic_factor;
}


WmsQL1Parser::Arithmetic_factorContext* WmsQL1Parser::arithmetic_factor() {
  Arithmetic_factorContext *_localctx = _tracker.createInstance<Arithmetic_factorContext>(_ctx, getState());
  enterRule(_localctx, 50, WmsQL1Parser::RuleArithmetic_factor);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(368);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case WmsQL1Parser::PLUS:
      case WmsQL1Parser::MINUS:
      case WmsQL1Parser::INT_TYPE:
      case WmsQL1Parser::FLOAT_TYPE:
      case WmsQL1Parser::DATE_TYPE: {
        enterOuterAlt(_localctx, 1);
        setState(363);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == WmsQL1Parser::PLUS

        || _la == WmsQL1Parser::MINUS) {
          setState(362);
          _la = _input->LA(1);
          if (!(_la == WmsQL1Parser::PLUS

          || _la == WmsQL1Parser::MINUS)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
        }
        setState(365);
        dynamic_cast<Arithmetic_factorContext *>(_localctx)->type = _input->LT(1);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & ((1ULL << WmsQL1Parser::INT_TYPE)
          | (1ULL << WmsQL1Parser::FLOAT_TYPE)
          | (1ULL << WmsQL1Parser::DATE_TYPE))) != 0))) {
          dynamic_cast<Arithmetic_factorContext *>(_localctx)->type = _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

      case WmsQL1Parser::MOD:
      case WmsQL1Parser::LENGTH:
      case WmsQL1Parser::ABS: {
        enterOuterAlt(_localctx, 2);
        setState(366);
        numeric_returning_function();
        break;
      }

      case WmsQL1Parser::AVG:
      case WmsQL1Parser::MAX:
      case WmsQL1Parser::MIN:
      case WmsQL1Parser::SUM:
      case WmsQL1Parser::COUNT:
      case WmsQL1Parser::ID:
      case WmsQL1Parser::IDPATH:
      case WmsQL1Parser::STRING_TYPE:
      case WmsQL1Parser::CONCAT:
      case WmsQL1Parser::SUBSTRING:
      case WmsQL1Parser::LOWER:
      case WmsQL1Parser::UPPER: {
        enterOuterAlt(_localctx, 3);
        setState(367);
        string_expression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Numeric_returning_functionContext ------------------------------------------------------------------

WmsQL1Parser::Numeric_returning_functionContext::Numeric_returning_functionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::Numeric_returning_functionContext::MOD() {
  return getToken(WmsQL1Parser::MOD, 0);
}

std::vector<WmsQL1Parser::Arithmetic_factorContext *> WmsQL1Parser::Numeric_returning_functionContext::arithmetic_factor() {
  return getRuleContexts<WmsQL1Parser::Arithmetic_factorContext>();
}

WmsQL1Parser::Arithmetic_factorContext* WmsQL1Parser::Numeric_returning_functionContext::arithmetic_factor(size_t i) {
  return getRuleContext<WmsQL1Parser::Arithmetic_factorContext>(i);
}

tree::TerminalNode* WmsQL1Parser::Numeric_returning_functionContext::ABS() {
  return getToken(WmsQL1Parser::ABS, 0);
}

tree::TerminalNode* WmsQL1Parser::Numeric_returning_functionContext::LENGTH() {
  return getToken(WmsQL1Parser::LENGTH, 0);
}

WmsQL1Parser::String_expressionContext* WmsQL1Parser::Numeric_returning_functionContext::string_expression() {
  return getRuleContext<WmsQL1Parser::String_expressionContext>(0);
}


size_t WmsQL1Parser::Numeric_returning_functionContext::getRuleIndex() const {
  return WmsQL1Parser::RuleNumeric_returning_function;
}


WmsQL1Parser::Numeric_returning_functionContext* WmsQL1Parser::numeric_returning_function() {
  Numeric_returning_functionContext *_localctx = _tracker.createInstance<Numeric_returning_functionContext>(_ctx, getState());
  enterRule(_localctx, 52, WmsQL1Parser::RuleNumeric_returning_function);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(387);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case WmsQL1Parser::MOD: {
        enterOuterAlt(_localctx, 1);
        setState(370);
        match(WmsQL1Parser::MOD);
        setState(371);
        match(WmsQL1Parser::T__1);
        setState(372);
        arithmetic_factor();
        setState(373);
        match(WmsQL1Parser::T__0);
        setState(374);
        arithmetic_factor();
        setState(375);
        match(WmsQL1Parser::T__2);
        break;
      }

      case WmsQL1Parser::ABS: {
        enterOuterAlt(_localctx, 2);
        setState(377);
        match(WmsQL1Parser::ABS);
        setState(378);
        match(WmsQL1Parser::T__1);
        setState(379);
        arithmetic_factor();
        setState(380);
        match(WmsQL1Parser::T__2);
        break;
      }

      case WmsQL1Parser::LENGTH: {
        enterOuterAlt(_localctx, 3);
        setState(382);
        match(WmsQL1Parser::LENGTH);
        setState(383);
        match(WmsQL1Parser::T__1);
        setState(384);
        string_expression();
        setState(385);
        match(WmsQL1Parser::T__2);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Groupby_clauseContext ------------------------------------------------------------------

WmsQL1Parser::Groupby_clauseContext::Groupby_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::Groupby_clauseContext::GROUP() {
  return getToken(WmsQL1Parser::GROUP, 0);
}

tree::TerminalNode* WmsQL1Parser::Groupby_clauseContext::BY() {
  return getToken(WmsQL1Parser::BY, 0);
}

std::vector<WmsQL1Parser::Object_refContext *> WmsQL1Parser::Groupby_clauseContext::object_ref() {
  return getRuleContexts<WmsQL1Parser::Object_refContext>();
}

WmsQL1Parser::Object_refContext* WmsQL1Parser::Groupby_clauseContext::object_ref(size_t i) {
  return getRuleContext<WmsQL1Parser::Object_refContext>(i);
}


size_t WmsQL1Parser::Groupby_clauseContext::getRuleIndex() const {
  return WmsQL1Parser::RuleGroupby_clause;
}


WmsQL1Parser::Groupby_clauseContext* WmsQL1Parser::groupby_clause() {
  Groupby_clauseContext *_localctx = _tracker.createInstance<Groupby_clauseContext>(_ctx, getState());
  enterRule(_localctx, 54, WmsQL1Parser::RuleGroupby_clause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(389);
    match(WmsQL1Parser::GROUP);
    setState(390);
    match(WmsQL1Parser::BY);
    setState(391);
    object_ref();
    setState(396);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == WmsQL1Parser::T__0) {
      setState(392);
      match(WmsQL1Parser::T__0);
      setState(393);
      object_ref();
      setState(398);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Orderby_clauseContext ------------------------------------------------------------------

WmsQL1Parser::Orderby_clauseContext::Orderby_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::Orderby_clauseContext::ORDER() {
  return getToken(WmsQL1Parser::ORDER, 0);
}

tree::TerminalNode* WmsQL1Parser::Orderby_clauseContext::BY() {
  return getToken(WmsQL1Parser::BY, 0);
}

std::vector<WmsQL1Parser::Orderby_expressionContext *> WmsQL1Parser::Orderby_clauseContext::orderby_expression() {
  return getRuleContexts<WmsQL1Parser::Orderby_expressionContext>();
}

WmsQL1Parser::Orderby_expressionContext* WmsQL1Parser::Orderby_clauseContext::orderby_expression(size_t i) {
  return getRuleContext<WmsQL1Parser::Orderby_expressionContext>(i);
}


size_t WmsQL1Parser::Orderby_clauseContext::getRuleIndex() const {
  return WmsQL1Parser::RuleOrderby_clause;
}


WmsQL1Parser::Orderby_clauseContext* WmsQL1Parser::orderby_clause() {
  Orderby_clauseContext *_localctx = _tracker.createInstance<Orderby_clauseContext>(_ctx, getState());
  enterRule(_localctx, 56, WmsQL1Parser::RuleOrderby_clause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(399);
    match(WmsQL1Parser::ORDER);
    setState(400);
    match(WmsQL1Parser::BY);
    setState(401);
    orderby_expression();
    setState(406);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == WmsQL1Parser::T__0) {
      setState(402);
      match(WmsQL1Parser::T__0);
      setState(403);
      orderby_expression();
      setState(408);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Orderby_expressionContext ------------------------------------------------------------------

WmsQL1Parser::Orderby_expressionContext::Orderby_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

WmsQL1Parser::Object_refContext* WmsQL1Parser::Orderby_expressionContext::object_ref() {
  return getRuleContext<WmsQL1Parser::Object_refContext>(0);
}

tree::TerminalNode* WmsQL1Parser::Orderby_expressionContext::ASC() {
  return getToken(WmsQL1Parser::ASC, 0);
}

tree::TerminalNode* WmsQL1Parser::Orderby_expressionContext::DESC() {
  return getToken(WmsQL1Parser::DESC, 0);
}


size_t WmsQL1Parser::Orderby_expressionContext::getRuleIndex() const {
  return WmsQL1Parser::RuleOrderby_expression;
}


WmsQL1Parser::Orderby_expressionContext* WmsQL1Parser::orderby_expression() {
  Orderby_expressionContext *_localctx = _tracker.createInstance<Orderby_expressionContext>(_ctx, getState());
  enterRule(_localctx, 58, WmsQL1Parser::RuleOrderby_expression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(409);
    object_ref();
    setState(411);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WmsQL1Parser::ASC

    || _la == WmsQL1Parser::DESC) {
      setState(410);
      _la = _input->LA(1);
      if (!(_la == WmsQL1Parser::ASC

      || _la == WmsQL1Parser::DESC)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Limit_clauseContext ------------------------------------------------------------------

WmsQL1Parser::Limit_clauseContext::Limit_clauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::Limit_clauseContext::LIMIT() {
  return getToken(WmsQL1Parser::LIMIT, 0);
}

std::vector<tree::TerminalNode *> WmsQL1Parser::Limit_clauseContext::INT_TYPE() {
  return getTokens(WmsQL1Parser::INT_TYPE);
}

tree::TerminalNode* WmsQL1Parser::Limit_clauseContext::INT_TYPE(size_t i) {
  return getToken(WmsQL1Parser::INT_TYPE, i);
}


size_t WmsQL1Parser::Limit_clauseContext::getRuleIndex() const {
  return WmsQL1Parser::RuleLimit_clause;
}


WmsQL1Parser::Limit_clauseContext* WmsQL1Parser::limit_clause() {
  Limit_clauseContext *_localctx = _tracker.createInstance<Limit_clauseContext>(_ctx, getState());
  enterRule(_localctx, 60, WmsQL1Parser::RuleLimit_clause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(413);
    match(WmsQL1Parser::LIMIT);
    setState(414);
    match(WmsQL1Parser::INT_TYPE);
    setState(417);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == WmsQL1Parser::T__0) {
      setState(415);
      match(WmsQL1Parser::T__0);
      setState(416);
      match(WmsQL1Parser::INT_TYPE);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Value_refContext ------------------------------------------------------------------

WmsQL1Parser::Value_refContext::Value_refContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::Value_refContext::INT_TYPE() {
  return getToken(WmsQL1Parser::INT_TYPE, 0);
}

tree::TerminalNode* WmsQL1Parser::Value_refContext::FLOAT_TYPE() {
  return getToken(WmsQL1Parser::FLOAT_TYPE, 0);
}

tree::TerminalNode* WmsQL1Parser::Value_refContext::DATE_TYPE() {
  return getToken(WmsQL1Parser::DATE_TYPE, 0);
}

tree::TerminalNode* WmsQL1Parser::Value_refContext::STRING_TYPE() {
  return getToken(WmsQL1Parser::STRING_TYPE, 0);
}


size_t WmsQL1Parser::Value_refContext::getRuleIndex() const {
  return WmsQL1Parser::RuleValue_ref;
}


WmsQL1Parser::Value_refContext* WmsQL1Parser::value_ref() {
  Value_refContext *_localctx = _tracker.createInstance<Value_refContext>(_ctx, getState());
  enterRule(_localctx, 62, WmsQL1Parser::RuleValue_ref);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(419);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << WmsQL1Parser::STRING_TYPE)
      | (1ULL << WmsQL1Parser::INT_TYPE)
      | (1ULL << WmsQL1Parser::FLOAT_TYPE)
      | (1ULL << WmsQL1Parser::DATE_TYPE))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Object_refContext ------------------------------------------------------------------

WmsQL1Parser::Object_refContext::Object_refContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::Object_refContext::ID() {
  return getToken(WmsQL1Parser::ID, 0);
}

tree::TerminalNode* WmsQL1Parser::Object_refContext::IDPATH() {
  return getToken(WmsQL1Parser::IDPATH, 0);
}


size_t WmsQL1Parser::Object_refContext::getRuleIndex() const {
  return WmsQL1Parser::RuleObject_ref;
}


WmsQL1Parser::Object_refContext* WmsQL1Parser::object_ref() {
  Object_refContext *_localctx = _tracker.createInstance<Object_refContext>(_ctx, getState());
  enterRule(_localctx, 64, WmsQL1Parser::RuleObject_ref);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(421);
    _la = _input->LA(1);
    if (!(_la == WmsQL1Parser::ID

    || _la == WmsQL1Parser::IDPATH)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Class_refContext ------------------------------------------------------------------

WmsQL1Parser::Class_refContext::Class_refContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::Class_refContext::ID() {
  return getToken(WmsQL1Parser::ID, 0);
}

tree::TerminalNode* WmsQL1Parser::Class_refContext::CLASSID() {
  return getToken(WmsQL1Parser::CLASSID, 0);
}

tree::TerminalNode* WmsQL1Parser::Class_refContext::STRING_TYPE() {
  return getToken(WmsQL1Parser::STRING_TYPE, 0);
}


size_t WmsQL1Parser::Class_refContext::getRuleIndex() const {
  return WmsQL1Parser::RuleClass_ref;
}


WmsQL1Parser::Class_refContext* WmsQL1Parser::class_ref() {
  Class_refContext *_localctx = _tracker.createInstance<Class_refContext>(_ctx, getState());
  enterRule(_localctx, 66, WmsQL1Parser::RuleClass_ref);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(423);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << WmsQL1Parser::ID)
      | (1ULL << WmsQL1Parser::CLASSID)
      | (1ULL << WmsQL1Parser::STRING_TYPE))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- String_expressionContext ------------------------------------------------------------------

WmsQL1Parser::String_expressionContext::String_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* WmsQL1Parser::String_expressionContext::SUBSTRING() {
  return getToken(WmsQL1Parser::SUBSTRING, 0);
}

std::vector<WmsQL1Parser::String_expressionContext *> WmsQL1Parser::String_expressionContext::string_expression() {
  return getRuleContexts<WmsQL1Parser::String_expressionContext>();
}

WmsQL1Parser::String_expressionContext* WmsQL1Parser::String_expressionContext::string_expression(size_t i) {
  return getRuleContext<WmsQL1Parser::String_expressionContext>(i);
}

tree::TerminalNode* WmsQL1Parser::String_expressionContext::CONCAT() {
  return getToken(WmsQL1Parser::CONCAT, 0);
}

tree::TerminalNode* WmsQL1Parser::String_expressionContext::LOWER() {
  return getToken(WmsQL1Parser::LOWER, 0);
}

tree::TerminalNode* WmsQL1Parser::String_expressionContext::UPPER() {
  return getToken(WmsQL1Parser::UPPER, 0);
}

tree::TerminalNode* WmsQL1Parser::String_expressionContext::STRING_TYPE() {
  return getToken(WmsQL1Parser::STRING_TYPE, 0);
}

WmsQL1Parser::Object_refContext* WmsQL1Parser::String_expressionContext::object_ref() {
  return getRuleContext<WmsQL1Parser::Object_refContext>(0);
}

WmsQL1Parser::Aggregate_expressionContext* WmsQL1Parser::String_expressionContext::aggregate_expression() {
  return getRuleContext<WmsQL1Parser::Aggregate_expressionContext>(0);
}


size_t WmsQL1Parser::String_expressionContext::getRuleIndex() const {
  return WmsQL1Parser::RuleString_expression;
}


WmsQL1Parser::String_expressionContext* WmsQL1Parser::string_expression() {
  String_expressionContext *_localctx = _tracker.createInstance<String_expressionContext>(_ctx, getState());
  enterRule(_localctx, 68, WmsQL1Parser::RuleString_expression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(449);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case WmsQL1Parser::SUBSTRING: {
        enterOuterAlt(_localctx, 1);
        setState(425);
        match(WmsQL1Parser::SUBSTRING);
        setState(426);
        match(WmsQL1Parser::T__1);
        setState(427);
        string_expression();
        setState(428);
        match(WmsQL1Parser::T__0);
        setState(429);
        string_expression();
        setState(430);
        match(WmsQL1Parser::T__0);
        setState(431);
        string_expression();
        setState(432);
        match(WmsQL1Parser::T__2);
        break;
      }

      case WmsQL1Parser::CONCAT: {
        enterOuterAlt(_localctx, 2);
        setState(434);
        match(WmsQL1Parser::CONCAT);
        setState(435);
        match(WmsQL1Parser::T__1);
        setState(436);
        string_expression();
        setState(437);
        match(WmsQL1Parser::T__0);
        setState(438);
        string_expression();
        setState(439);
        match(WmsQL1Parser::T__2);
        break;
      }

      case WmsQL1Parser::LOWER:
      case WmsQL1Parser::UPPER: {
        enterOuterAlt(_localctx, 3);
        setState(441);
        _la = _input->LA(1);
        if (!(_la == WmsQL1Parser::LOWER

        || _la == WmsQL1Parser::UPPER)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(442);
        match(WmsQL1Parser::T__1);
        setState(443);
        string_expression();
        setState(444);
        match(WmsQL1Parser::T__2);
        break;
      }

      case WmsQL1Parser::STRING_TYPE: {
        enterOuterAlt(_localctx, 4);
        setState(446);
        match(WmsQL1Parser::STRING_TYPE);
        break;
      }

      case WmsQL1Parser::ID:
      case WmsQL1Parser::IDPATH: {
        enterOuterAlt(_localctx, 5);
        setState(447);
        object_ref();
        break;
      }

      case WmsQL1Parser::AVG:
      case WmsQL1Parser::MAX:
      case WmsQL1Parser::MIN:
      case WmsQL1Parser::SUM:
      case WmsQL1Parser::COUNT: {
        enterOuterAlt(_localctx, 6);
        setState(448);
        aggregate_expression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool WmsQL1Parser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 17: return where_expressionSempred(dynamic_cast<Where_expressionContext *>(context), predicateIndex);
    case 24: return arithmetic_expressionSempred(dynamic_cast<Arithmetic_expressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool WmsQL1Parser::where_expressionSempred(Where_expressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 4);
    case 1: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

bool WmsQL1Parser::arithmetic_expressionSempred(Arithmetic_expressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 4);
    case 3: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> WmsQL1Parser::_decisionToDFA;
atn::PredictionContextCache WmsQL1Parser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN WmsQL1Parser::_atn;
std::vector<uint16_t> WmsQL1Parser::_serializedATN;

std::vector<std::string> WmsQL1Parser::_ruleNames = {
  "statement", "select_statement", "insert_statement", "update_statement", 
  "delete_statement", "select_clause", "select_expression", "aggregate_expression", 
  "insert_clause", "update_clause", "delete_clause", "value_clause", "value_list", 
  "set_clause", "set_assignment", "from_clause", "where_clause", "where_expression", 
  "cond_expression", "in_condition", "in_items", "like_condition", "compare_condition", 
  "compare_sign", "arithmetic_expression", "arithmetic_factor", "numeric_returning_function", 
  "groupby_clause", "orderby_clause", "orderby_expression", "limit_clause", 
  "value_ref", "object_ref", "class_ref", "string_expression"
};

std::vector<std::string> WmsQL1Parser::_literalNames = {
  "", "','", "'('", "')'", "", "", "", "", "", "", "", "", "", "", "", "", 
  "'DEFAULT'", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "'+'", 
  "'-'", "'*'", "'/'", "'='", "'<>'", "'<'", "", "'>'"
};

std::vector<std::string> WmsQL1Parser::_symbolicNames = {
  "", "", "", "", "SELECT", "DISTINCT", "AVG", "MAX", "MIN", "SUM", "COUNT", 
  "INSERT", "INTO", "UPDATE", "DELETE", "VALUES", "DEFAULT", "SET", "FROM", 
  "WHERE", "AND", "OR", "NOT", "LIKE", "IN", "IS", "NULL_REPR", "MOD", "LENGTH", 
  "ABS", "SIZE", "PLUS", "MINUS", "STAR", "SLASH", "EQ", "NEQ", "LT", "LEQ", 
  "GT", "GEQ", "BY", "GROUP", "ORDER", "ASC", "DESC", "LIMIT", "TRUE", "FALSE", 
  "ID", "CLASSID", "IDPATH", "STRING_TYPE", "CONCAT", "SUBSTRING", "LOWER", 
  "UPPER", "INT_TYPE", "FLOAT_TYPE", "DATE_TYPE", "BLOCK_COMMENT", "LINE_COMMENT", 
  "WS"
};

dfa::Vocabulary WmsQL1Parser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> WmsQL1Parser::_tokenNames;

WmsQL1Parser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x40, 0x1c6, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x3, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0x4d, 0xa, 0x2, 0x3, 0x2, 0x3, 0x2, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x54, 0xa, 0x3, 0x3, 0x3, 0x5, 
    0x3, 0x57, 0xa, 0x3, 0x3, 0x3, 0x5, 0x3, 0x5a, 0xa, 0x3, 0x3, 0x3, 0x5, 
    0x3, 0x5d, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x5, 0x4, 0x65, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 
    0x5, 0x6a, 0xa, 0x5, 0x3, 0x5, 0x5, 0x5, 0x6d, 0xa, 0x5, 0x3, 0x5, 0x5, 
    0x5, 0x70, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0x75, 0xa, 
    0x6, 0x3, 0x6, 0x5, 0x6, 0x78, 0xa, 0x6, 0x3, 0x6, 0x5, 0x6, 0x7b, 0xa, 
    0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x81, 0xa, 0x7, 
    0xc, 0x7, 0xe, 0x7, 0x84, 0xb, 0x7, 0x5, 0x7, 0x86, 0xa, 0x7, 0x3, 0x8, 
    0x3, 0x8, 0x5, 0x8, 0x8a, 0xa, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x8e, 
    0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x93, 0xa, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x9b, 
    0xa, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x9f, 0xa, 0x9, 0x3, 0xa, 0x3, 
    0xa, 0x5, 0xa, 0xa3, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x3, 0xa, 0x7, 0xa, 0xaa, 0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0xad, 0xb, 0xa, 
    0x5, 0xa, 0xaf, 0xa, 0xa, 0x3, 0xa, 0x5, 0xa, 0xb2, 0xa, 0xa, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x7, 0xb, 0xb8, 0xa, 0xb, 0xc, 0xb, 0xe, 
    0xb, 0xbb, 0xb, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x7, 0xd, 0xc3, 0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0xc6, 0xb, 0xd, 
    0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 0xcc, 0xa, 0xe, 0xc, 
    0xe, 0xe, 0xe, 0xcf, 0xb, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 
    0x5, 0xe, 0xd5, 0xa, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x7, 
    0xf, 0xdb, 0xa, 0xf, 0xc, 0xf, 0xe, 0xf, 0xde, 0xb, 0xf, 0x3, 0x10, 
    0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 
    0x11, 0x7, 0x11, 0xe8, 0xa, 0x11, 0xc, 0x11, 0xe, 0x11, 0xeb, 0xb, 0x11, 
    0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x13, 0x3, 0x13, 0x7, 0x13, 0xf6, 0xa, 0x13, 0xc, 0x13, 0xe, 
    0x13, 0xf9, 0xb, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0xfe, 
    0xa, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 
    0x13, 0x105, 0xa, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x7, 0x13, 0x10d, 0xa, 0x13, 0xc, 0x13, 0xe, 0x13, 
    0x110, 0xb, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0x115, 
    0xa, 0x14, 0x3, 0x15, 0x3, 0x15, 0x5, 0x15, 0x119, 0xa, 0x15, 0x3, 0x15, 
    0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 
    0x16, 0x7, 0x16, 0x123, 0xa, 0x16, 0xc, 0x16, 0xe, 0x16, 0x126, 0xb, 
    0x16, 0x3, 0x16, 0x3, 0x16, 0x3, 0x16, 0x7, 0x16, 0x12b, 0xa, 0x16, 
    0xc, 0x16, 0xe, 0x16, 0x12e, 0xb, 0x16, 0x5, 0x16, 0x130, 0xa, 0x16, 
    0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0x134, 0xa, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0x13d, 
    0xa, 0x17, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 
    0x18, 0x3, 0x18, 0x5, 0x18, 0x146, 0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 
    0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 
    0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 
    0x156, 0xa, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 
    0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x5, 0x1a, 0x160, 0xa, 0x1a, 0x3, 0x1a, 
    0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x7, 0x1a, 0x168, 
    0xa, 0x1a, 0xc, 0x1a, 0xe, 0x1a, 0x16b, 0xb, 0x1a, 0x3, 0x1b, 0x5, 0x1b, 
    0x16e, 0xa, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x173, 
    0xa, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 
    0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 
    0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0x186, 
    0xa, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x7, 
    0x1d, 0x18d, 0xa, 0x1d, 0xc, 0x1d, 0xe, 0x1d, 0x190, 0xb, 0x1d, 0x3, 
    0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x7, 0x1e, 0x197, 
    0xa, 0x1e, 0xc, 0x1e, 0xe, 0x1e, 0x19a, 0xb, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 
    0x5, 0x1f, 0x19e, 0xa, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x5, 0x20, 0x1a4, 0xa, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x22, 0x3, 0x22, 
    0x3, 0x23, 0x3, 0x23, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 
    0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 
    0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 
    0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x24, 
    0x5, 0x24, 0x1c4, 0xa, 0x24, 0x3, 0x24, 0x2, 0x4, 0x24, 0x32, 0x25, 
    0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 
    0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 
    0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 0x2, 0xf, 
    0x3, 0x2, 0x8, 0xc, 0x3, 0x2, 0x16, 0x17, 0x3, 0x2, 0x25, 0x26, 0x3, 
    0x2, 0x31, 0x32, 0x3, 0x2, 0x25, 0x2a, 0x3, 0x2, 0x23, 0x24, 0x3, 0x2, 
    0x21, 0x22, 0x3, 0x2, 0x3b, 0x3d, 0x3, 0x2, 0x2e, 0x2f, 0x4, 0x2, 0x36, 
    0x36, 0x3b, 0x3d, 0x4, 0x2, 0x33, 0x33, 0x35, 0x35, 0x4, 0x2, 0x33, 
    0x34, 0x36, 0x36, 0x3, 0x2, 0x39, 0x3a, 0x2, 0x1e6, 0x2, 0x4c, 0x3, 
    0x2, 0x2, 0x2, 0x4, 0x50, 0x3, 0x2, 0x2, 0x2, 0x6, 0x64, 0x3, 0x2, 0x2, 
    0x2, 0x8, 0x66, 0x3, 0x2, 0x2, 0x2, 0xa, 0x71, 0x3, 0x2, 0x2, 0x2, 0xc, 
    0x7c, 0x3, 0x2, 0x2, 0x2, 0xe, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x10, 0x9e, 
    0x3, 0x2, 0x2, 0x2, 0x12, 0xa0, 0x3, 0x2, 0x2, 0x2, 0x14, 0xb3, 0x3, 
    0x2, 0x2, 0x2, 0x16, 0xbc, 0x3, 0x2, 0x2, 0x2, 0x18, 0xbe, 0x3, 0x2, 
    0x2, 0x2, 0x1a, 0xd4, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xd6, 0x3, 0x2, 0x2, 
    0x2, 0x1e, 0xdf, 0x3, 0x2, 0x2, 0x2, 0x20, 0xe3, 0x3, 0x2, 0x2, 0x2, 
    0x22, 0xec, 0x3, 0x2, 0x2, 0x2, 0x24, 0x104, 0x3, 0x2, 0x2, 0x2, 0x26, 
    0x114, 0x3, 0x2, 0x2, 0x2, 0x28, 0x116, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x12f, 
    0x3, 0x2, 0x2, 0x2, 0x2c, 0x13c, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x155, 0x3, 
    0x2, 0x2, 0x2, 0x30, 0x157, 0x3, 0x2, 0x2, 0x2, 0x32, 0x15f, 0x3, 0x2, 
    0x2, 0x2, 0x34, 0x172, 0x3, 0x2, 0x2, 0x2, 0x36, 0x185, 0x3, 0x2, 0x2, 
    0x2, 0x38, 0x187, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x191, 0x3, 0x2, 0x2, 0x2, 
    0x3c, 0x19b, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x19f, 0x3, 0x2, 0x2, 0x2, 0x40, 
    0x1a5, 0x3, 0x2, 0x2, 0x2, 0x42, 0x1a7, 0x3, 0x2, 0x2, 0x2, 0x44, 0x1a9, 
    0x3, 0x2, 0x2, 0x2, 0x46, 0x1c3, 0x3, 0x2, 0x2, 0x2, 0x48, 0x4d, 0x5, 
    0x4, 0x3, 0x2, 0x49, 0x4d, 0x5, 0x6, 0x4, 0x2, 0x4a, 0x4d, 0x5, 0x8, 
    0x5, 0x2, 0x4b, 0x4d, 0x5, 0xa, 0x6, 0x2, 0x4c, 0x48, 0x3, 0x2, 0x2, 
    0x2, 0x4c, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x4a, 0x3, 0x2, 0x2, 0x2, 
    0x4c, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x4e, 
    0x4f, 0x7, 0x2, 0x2, 0x3, 0x4f, 0x3, 0x3, 0x2, 0x2, 0x2, 0x50, 0x51, 
    0x5, 0xc, 0x7, 0x2, 0x51, 0x53, 0x5, 0x20, 0x11, 0x2, 0x52, 0x54, 0x5, 
    0x22, 0x12, 0x2, 0x53, 0x52, 0x3, 0x2, 0x2, 0x2, 0x53, 0x54, 0x3, 0x2, 
    0x2, 0x2, 0x54, 0x56, 0x3, 0x2, 0x2, 0x2, 0x55, 0x57, 0x5, 0x38, 0x1d, 
    0x2, 0x56, 0x55, 0x3, 0x2, 0x2, 0x2, 0x56, 0x57, 0x3, 0x2, 0x2, 0x2, 
    0x57, 0x59, 0x3, 0x2, 0x2, 0x2, 0x58, 0x5a, 0x5, 0x3a, 0x1e, 0x2, 0x59, 
    0x58, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5a, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x5c, 
    0x3, 0x2, 0x2, 0x2, 0x5b, 0x5d, 0x5, 0x3e, 0x20, 0x2, 0x5c, 0x5b, 0x3, 
    0x2, 0x2, 0x2, 0x5c, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x5d, 0x5, 0x3, 0x2, 
    0x2, 0x2, 0x5e, 0x5f, 0x5, 0x12, 0xa, 0x2, 0x5f, 0x60, 0x5, 0x18, 0xd, 
    0x2, 0x60, 0x65, 0x3, 0x2, 0x2, 0x2, 0x61, 0x62, 0x5, 0x12, 0xa, 0x2, 
    0x62, 0x63, 0x5, 0x1c, 0xf, 0x2, 0x63, 0x65, 0x3, 0x2, 0x2, 0x2, 0x64, 
    0x5e, 0x3, 0x2, 0x2, 0x2, 0x64, 0x61, 0x3, 0x2, 0x2, 0x2, 0x65, 0x7, 
    0x3, 0x2, 0x2, 0x2, 0x66, 0x67, 0x5, 0x14, 0xb, 0x2, 0x67, 0x69, 0x5, 
    0x1c, 0xf, 0x2, 0x68, 0x6a, 0x5, 0x22, 0x12, 0x2, 0x69, 0x68, 0x3, 0x2, 
    0x2, 0x2, 0x69, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6a, 0x6c, 0x3, 0x2, 0x2, 
    0x2, 0x6b, 0x6d, 0x5, 0x3a, 0x1e, 0x2, 0x6c, 0x6b, 0x3, 0x2, 0x2, 0x2, 
    0x6c, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x6d, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x6e, 
    0x70, 0x5, 0x3e, 0x20, 0x2, 0x6f, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x70, 
    0x3, 0x2, 0x2, 0x2, 0x70, 0x9, 0x3, 0x2, 0x2, 0x2, 0x71, 0x72, 0x5, 
    0x16, 0xc, 0x2, 0x72, 0x74, 0x5, 0x20, 0x11, 0x2, 0x73, 0x75, 0x5, 0x22, 
    0x12, 0x2, 0x74, 0x73, 0x3, 0x2, 0x2, 0x2, 0x74, 0x75, 0x3, 0x2, 0x2, 
    0x2, 0x75, 0x77, 0x3, 0x2, 0x2, 0x2, 0x76, 0x78, 0x5, 0x3a, 0x1e, 0x2, 
    0x77, 0x76, 0x3, 0x2, 0x2, 0x2, 0x77, 0x78, 0x3, 0x2, 0x2, 0x2, 0x78, 
    0x7a, 0x3, 0x2, 0x2, 0x2, 0x79, 0x7b, 0x5, 0x3e, 0x20, 0x2, 0x7a, 0x79, 
    0x3, 0x2, 0x2, 0x2, 0x7a, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x7b, 0xb, 0x3, 
    0x2, 0x2, 0x2, 0x7c, 0x85, 0x7, 0x6, 0x2, 0x2, 0x7d, 0x82, 0x5, 0xe, 
    0x8, 0x2, 0x7e, 0x7f, 0x7, 0x3, 0x2, 0x2, 0x7f, 0x81, 0x5, 0xe, 0x8, 
    0x2, 0x80, 0x7e, 0x3, 0x2, 0x2, 0x2, 0x81, 0x84, 0x3, 0x2, 0x2, 0x2, 
    0x82, 0x80, 0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 0x3, 0x2, 0x2, 0x2, 0x83, 
    0x86, 0x3, 0x2, 0x2, 0x2, 0x84, 0x82, 0x3, 0x2, 0x2, 0x2, 0x85, 0x7d, 
    0x3, 0x2, 0x2, 0x2, 0x85, 0x86, 0x3, 0x2, 0x2, 0x2, 0x86, 0xd, 0x3, 
    0x2, 0x2, 0x2, 0x87, 0x8e, 0x5, 0x10, 0x9, 0x2, 0x88, 0x8a, 0x7, 0x7, 
    0x2, 0x2, 0x89, 0x88, 0x3, 0x2, 0x2, 0x2, 0x89, 0x8a, 0x3, 0x2, 0x2, 
    0x2, 0x8a, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x8b, 0x8e, 0x5, 0x42, 0x22, 0x2, 
    0x8c, 0x8e, 0x7, 0x23, 0x2, 0x2, 0x8d, 0x87, 0x3, 0x2, 0x2, 0x2, 0x8d, 
    0x89, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x8e, 0xf, 
    0x3, 0x2, 0x2, 0x2, 0x8f, 0x90, 0x9, 0x2, 0x2, 0x2, 0x90, 0x92, 0x7, 
    0x4, 0x2, 0x2, 0x91, 0x93, 0x7, 0x7, 0x2, 0x2, 0x92, 0x91, 0x3, 0x2, 
    0x2, 0x2, 0x92, 0x93, 0x3, 0x2, 0x2, 0x2, 0x93, 0x94, 0x3, 0x2, 0x2, 
    0x2, 0x94, 0x95, 0x5, 0x42, 0x22, 0x2, 0x95, 0x96, 0x7, 0x5, 0x2, 0x2, 
    0x96, 0x9f, 0x3, 0x2, 0x2, 0x2, 0x97, 0x98, 0x7, 0xc, 0x2, 0x2, 0x98, 
    0x9a, 0x7, 0x4, 0x2, 0x2, 0x99, 0x9b, 0x7, 0x7, 0x2, 0x2, 0x9a, 0x99, 
    0x3, 0x2, 0x2, 0x2, 0x9a, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x9b, 0x9c, 0x3, 
    0x2, 0x2, 0x2, 0x9c, 0x9d, 0x7, 0x23, 0x2, 0x2, 0x9d, 0x9f, 0x7, 0x5, 
    0x2, 0x2, 0x9e, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x9e, 0x97, 0x3, 0x2, 0x2, 
    0x2, 0x9f, 0x11, 0x3, 0x2, 0x2, 0x2, 0xa0, 0xa2, 0x7, 0xd, 0x2, 0x2, 
    0xa1, 0xa3, 0x7, 0xe, 0x2, 0x2, 0xa2, 0xa1, 0x3, 0x2, 0x2, 0x2, 0xa2, 
    0xa3, 0x3, 0x2, 0x2, 0x2, 0xa3, 0xa4, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xb1, 
    0x5, 0x44, 0x23, 0x2, 0xa5, 0xae, 0x7, 0x4, 0x2, 0x2, 0xa6, 0xab, 0x5, 
    0x42, 0x22, 0x2, 0xa7, 0xa8, 0x7, 0x3, 0x2, 0x2, 0xa8, 0xaa, 0x5, 0x42, 
    0x22, 0x2, 0xa9, 0xa7, 0x3, 0x2, 0x2, 0x2, 0xaa, 0xad, 0x3, 0x2, 0x2, 
    0x2, 0xab, 0xa9, 0x3, 0x2, 0x2, 0x2, 0xab, 0xac, 0x3, 0x2, 0x2, 0x2, 
    0xac, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xad, 0xab, 0x3, 0x2, 0x2, 0x2, 0xae, 
    0xa6, 0x3, 0x2, 0x2, 0x2, 0xae, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xaf, 0xb0, 
    0x3, 0x2, 0x2, 0x2, 0xb0, 0xb2, 0x7, 0x5, 0x2, 0x2, 0xb1, 0xa5, 0x3, 
    0x2, 0x2, 0x2, 0xb1, 0xb2, 0x3, 0x2, 0x2, 0x2, 0xb2, 0x13, 0x3, 0x2, 
    0x2, 0x2, 0xb3, 0xb4, 0x7, 0xf, 0x2, 0x2, 0xb4, 0xb9, 0x5, 0x44, 0x23, 
    0x2, 0xb5, 0xb6, 0x7, 0x3, 0x2, 0x2, 0xb6, 0xb8, 0x5, 0x44, 0x23, 0x2, 
    0xb7, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xb8, 0xbb, 0x3, 0x2, 0x2, 0x2, 0xb9, 
    0xb7, 0x3, 0x2, 0x2, 0x2, 0xb9, 0xba, 0x3, 0x2, 0x2, 0x2, 0xba, 0x15, 
    0x3, 0x2, 0x2, 0x2, 0xbb, 0xb9, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbd, 0x7, 
    0x10, 0x2, 0x2, 0xbd, 0x17, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xbf, 0x7, 0x11, 
    0x2, 0x2, 0xbf, 0xc4, 0x5, 0x1a, 0xe, 0x2, 0xc0, 0xc1, 0x7, 0x3, 0x2, 
    0x2, 0xc1, 0xc3, 0x5, 0x1a, 0xe, 0x2, 0xc2, 0xc0, 0x3, 0x2, 0x2, 0x2, 
    0xc3, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xc4, 
    0xc5, 0x3, 0x2, 0x2, 0x2, 0xc5, 0x19, 0x3, 0x2, 0x2, 0x2, 0xc6, 0xc4, 
    0x3, 0x2, 0x2, 0x2, 0xc7, 0xc8, 0x7, 0x4, 0x2, 0x2, 0xc8, 0xcd, 0x5, 
    0x40, 0x21, 0x2, 0xc9, 0xca, 0x7, 0x3, 0x2, 0x2, 0xca, 0xcc, 0x5, 0x40, 
    0x21, 0x2, 0xcb, 0xc9, 0x3, 0x2, 0x2, 0x2, 0xcc, 0xcf, 0x3, 0x2, 0x2, 
    0x2, 0xcd, 0xcb, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xce, 0x3, 0x2, 0x2, 0x2, 
    0xce, 0xd0, 0x3, 0x2, 0x2, 0x2, 0xcf, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xd0, 
    0xd1, 0x7, 0x5, 0x2, 0x2, 0xd1, 0xd5, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xd3, 
    0x7, 0x4, 0x2, 0x2, 0xd3, 0xd5, 0x7, 0x5, 0x2, 0x2, 0xd4, 0xc7, 0x3, 
    0x2, 0x2, 0x2, 0xd4, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xd5, 0x1b, 0x3, 0x2, 
    0x2, 0x2, 0xd6, 0xd7, 0x7, 0x13, 0x2, 0x2, 0xd7, 0xdc, 0x5, 0x1e, 0x10, 
    0x2, 0xd8, 0xd9, 0x7, 0x3, 0x2, 0x2, 0xd9, 0xdb, 0x5, 0x1e, 0x10, 0x2, 
    0xda, 0xd8, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xde, 0x3, 0x2, 0x2, 0x2, 0xdc, 
    0xda, 0x3, 0x2, 0x2, 0x2, 0xdc, 0xdd, 0x3, 0x2, 0x2, 0x2, 0xdd, 0x1d, 
    0x3, 0x2, 0x2, 0x2, 0xde, 0xdc, 0x3, 0x2, 0x2, 0x2, 0xdf, 0xe0, 0x5, 
    0x42, 0x22, 0x2, 0xe0, 0xe1, 0x7, 0x25, 0x2, 0x2, 0xe1, 0xe2, 0x5, 0x40, 
    0x21, 0x2, 0xe2, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xe4, 0x7, 0x14, 0x2, 
    0x2, 0xe4, 0xe9, 0x5, 0x44, 0x23, 0x2, 0xe5, 0xe6, 0x7, 0x3, 0x2, 0x2, 
    0xe6, 0xe8, 0x5, 0x44, 0x23, 0x2, 0xe7, 0xe5, 0x3, 0x2, 0x2, 0x2, 0xe8, 
    0xeb, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xea, 
    0x3, 0x2, 0x2, 0x2, 0xea, 0x21, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xe9, 0x3, 
    0x2, 0x2, 0x2, 0xec, 0xed, 0x7, 0x15, 0x2, 0x2, 0xed, 0xee, 0x5, 0x24, 
    0x13, 0x2, 0xee, 0x23, 0x3, 0x2, 0x2, 0x2, 0xef, 0xf0, 0x8, 0x13, 0x1, 
    0x2, 0xf0, 0xf1, 0x9, 0x3, 0x2, 0x2, 0xf1, 0xf2, 0x7, 0x4, 0x2, 0x2, 
    0xf2, 0xf7, 0x5, 0x24, 0x13, 0x2, 0xf3, 0xf4, 0x7, 0x3, 0x2, 0x2, 0xf4, 
    0xf6, 0x5, 0x24, 0x13, 0x2, 0xf5, 0xf3, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf9, 
    0x3, 0x2, 0x2, 0x2, 0xf7, 0xf5, 0x3, 0x2, 0x2, 0x2, 0xf7, 0xf8, 0x3, 
    0x2, 0x2, 0x2, 0xf8, 0xfa, 0x3, 0x2, 0x2, 0x2, 0xf9, 0xf7, 0x3, 0x2, 
    0x2, 0x2, 0xfa, 0xfb, 0x7, 0x5, 0x2, 0x2, 0xfb, 0x105, 0x3, 0x2, 0x2, 
    0x2, 0xfc, 0xfe, 0x7, 0x18, 0x2, 0x2, 0xfd, 0xfc, 0x3, 0x2, 0x2, 0x2, 
    0xfd, 0xfe, 0x3, 0x2, 0x2, 0x2, 0xfe, 0xff, 0x3, 0x2, 0x2, 0x2, 0xff, 
    0x100, 0x7, 0x4, 0x2, 0x2, 0x100, 0x101, 0x5, 0x24, 0x13, 0x2, 0x101, 
    0x102, 0x7, 0x5, 0x2, 0x2, 0x102, 0x105, 0x3, 0x2, 0x2, 0x2, 0x103, 
    0x105, 0x5, 0x26, 0x14, 0x2, 0x104, 0xef, 0x3, 0x2, 0x2, 0x2, 0x104, 
    0xfd, 0x3, 0x2, 0x2, 0x2, 0x104, 0x103, 0x3, 0x2, 0x2, 0x2, 0x105, 0x10e, 
    0x3, 0x2, 0x2, 0x2, 0x106, 0x107, 0xc, 0x6, 0x2, 0x2, 0x107, 0x108, 
    0x7, 0x16, 0x2, 0x2, 0x108, 0x10d, 0x5, 0x24, 0x13, 0x7, 0x109, 0x10a, 
    0xc, 0x5, 0x2, 0x2, 0x10a, 0x10b, 0x7, 0x17, 0x2, 0x2, 0x10b, 0x10d, 
    0x5, 0x24, 0x13, 0x6, 0x10c, 0x106, 0x3, 0x2, 0x2, 0x2, 0x10c, 0x109, 
    0x3, 0x2, 0x2, 0x2, 0x10d, 0x110, 0x3, 0x2, 0x2, 0x2, 0x10e, 0x10c, 
    0x3, 0x2, 0x2, 0x2, 0x10e, 0x10f, 0x3, 0x2, 0x2, 0x2, 0x10f, 0x25, 0x3, 
    0x2, 0x2, 0x2, 0x110, 0x10e, 0x3, 0x2, 0x2, 0x2, 0x111, 0x115, 0x5, 
    0x28, 0x15, 0x2, 0x112, 0x115, 0x5, 0x2c, 0x17, 0x2, 0x113, 0x115, 0x5, 
    0x2e, 0x18, 0x2, 0x114, 0x111, 0x3, 0x2, 0x2, 0x2, 0x114, 0x112, 0x3, 
    0x2, 0x2, 0x2, 0x114, 0x113, 0x3, 0x2, 0x2, 0x2, 0x115, 0x27, 0x3, 0x2, 
    0x2, 0x2, 0x116, 0x118, 0x5, 0x42, 0x22, 0x2, 0x117, 0x119, 0x7, 0x18, 
    0x2, 0x2, 0x118, 0x117, 0x3, 0x2, 0x2, 0x2, 0x118, 0x119, 0x3, 0x2, 
    0x2, 0x2, 0x119, 0x11a, 0x3, 0x2, 0x2, 0x2, 0x11a, 0x11b, 0x7, 0x1a, 
    0x2, 0x2, 0x11b, 0x11c, 0x7, 0x4, 0x2, 0x2, 0x11c, 0x11d, 0x5, 0x2a, 
    0x16, 0x2, 0x11d, 0x11e, 0x7, 0x5, 0x2, 0x2, 0x11e, 0x29, 0x3, 0x2, 
    0x2, 0x2, 0x11f, 0x124, 0x5, 0x46, 0x24, 0x2, 0x120, 0x121, 0x7, 0x3, 
    0x2, 0x2, 0x121, 0x123, 0x5, 0x46, 0x24, 0x2, 0x122, 0x120, 0x3, 0x2, 
    0x2, 0x2, 0x123, 0x126, 0x3, 0x2, 0x2, 0x2, 0x124, 0x122, 0x3, 0x2, 
    0x2, 0x2, 0x124, 0x125, 0x3, 0x2, 0x2, 0x2, 0x125, 0x130, 0x3, 0x2, 
    0x2, 0x2, 0x126, 0x124, 0x3, 0x2, 0x2, 0x2, 0x127, 0x12c, 0x5, 0x32, 
    0x1a, 0x2, 0x128, 0x129, 0x7, 0x3, 0x2, 0x2, 0x129, 0x12b, 0x5, 0x32, 
    0x1a, 0x2, 0x12a, 0x128, 0x3, 0x2, 0x2, 0x2, 0x12b, 0x12e, 0x3, 0x2, 
    0x2, 0x2, 0x12c, 0x12a, 0x3, 0x2, 0x2, 0x2, 0x12c, 0x12d, 0x3, 0x2, 
    0x2, 0x2, 0x12d, 0x130, 0x3, 0x2, 0x2, 0x2, 0x12e, 0x12c, 0x3, 0x2, 
    0x2, 0x2, 0x12f, 0x11f, 0x3, 0x2, 0x2, 0x2, 0x12f, 0x127, 0x3, 0x2, 
    0x2, 0x2, 0x130, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x131, 0x133, 0x5, 0x42, 
    0x22, 0x2, 0x132, 0x134, 0x7, 0x18, 0x2, 0x2, 0x133, 0x132, 0x3, 0x2, 
    0x2, 0x2, 0x133, 0x134, 0x3, 0x2, 0x2, 0x2, 0x134, 0x135, 0x3, 0x2, 
    0x2, 0x2, 0x135, 0x136, 0x7, 0x19, 0x2, 0x2, 0x136, 0x137, 0x5, 0x46, 
    0x24, 0x2, 0x137, 0x13d, 0x3, 0x2, 0x2, 0x2, 0x138, 0x139, 0x5, 0x42, 
    0x22, 0x2, 0x139, 0x13a, 0x9, 0x4, 0x2, 0x2, 0x13a, 0x13b, 0x5, 0x46, 
    0x24, 0x2, 0x13b, 0x13d, 0x3, 0x2, 0x2, 0x2, 0x13c, 0x131, 0x3, 0x2, 
    0x2, 0x2, 0x13c, 0x138, 0x3, 0x2, 0x2, 0x2, 0x13d, 0x2d, 0x3, 0x2, 0x2, 
    0x2, 0x13e, 0x13f, 0x5, 0x42, 0x22, 0x2, 0x13f, 0x140, 0x9, 0x4, 0x2, 
    0x2, 0x140, 0x141, 0x9, 0x5, 0x2, 0x2, 0x141, 0x156, 0x3, 0x2, 0x2, 
    0x2, 0x142, 0x143, 0x5, 0x42, 0x22, 0x2, 0x143, 0x145, 0x7, 0x1b, 0x2, 
    0x2, 0x144, 0x146, 0x7, 0x18, 0x2, 0x2, 0x145, 0x144, 0x3, 0x2, 0x2, 
    0x2, 0x145, 0x146, 0x3, 0x2, 0x2, 0x2, 0x146, 0x147, 0x3, 0x2, 0x2, 
    0x2, 0x147, 0x148, 0x7, 0x1c, 0x2, 0x2, 0x148, 0x156, 0x3, 0x2, 0x2, 
    0x2, 0x149, 0x14a, 0x5, 0x42, 0x22, 0x2, 0x14a, 0x14b, 0x5, 0x30, 0x19, 
    0x2, 0x14b, 0x14c, 0x5, 0x32, 0x1a, 0x2, 0x14c, 0x156, 0x3, 0x2, 0x2, 
    0x2, 0x14d, 0x14e, 0x5, 0x42, 0x22, 0x2, 0x14e, 0x14f, 0x5, 0x30, 0x19, 
    0x2, 0x14f, 0x150, 0x5, 0x42, 0x22, 0x2, 0x150, 0x156, 0x3, 0x2, 0x2, 
    0x2, 0x151, 0x152, 0x5, 0x32, 0x1a, 0x2, 0x152, 0x153, 0x5, 0x30, 0x19, 
    0x2, 0x153, 0x154, 0x5, 0x42, 0x22, 0x2, 0x154, 0x156, 0x3, 0x2, 0x2, 
    0x2, 0x155, 0x13e, 0x3, 0x2, 0x2, 0x2, 0x155, 0x142, 0x3, 0x2, 0x2, 
    0x2, 0x155, 0x149, 0x3, 0x2, 0x2, 0x2, 0x155, 0x14d, 0x3, 0x2, 0x2, 
    0x2, 0x155, 0x151, 0x3, 0x2, 0x2, 0x2, 0x156, 0x2f, 0x3, 0x2, 0x2, 0x2, 
    0x157, 0x158, 0x9, 0x6, 0x2, 0x2, 0x158, 0x31, 0x3, 0x2, 0x2, 0x2, 0x159, 
    0x15a, 0x8, 0x1a, 0x1, 0x2, 0x15a, 0x15b, 0x7, 0x4, 0x2, 0x2, 0x15b, 
    0x15c, 0x5, 0x32, 0x1a, 0x2, 0x15c, 0x15d, 0x7, 0x5, 0x2, 0x2, 0x15d, 
    0x160, 0x3, 0x2, 0x2, 0x2, 0x15e, 0x160, 0x5, 0x34, 0x1b, 0x2, 0x15f, 
    0x159, 0x3, 0x2, 0x2, 0x2, 0x15f, 0x15e, 0x3, 0x2, 0x2, 0x2, 0x160, 
    0x169, 0x3, 0x2, 0x2, 0x2, 0x161, 0x162, 0xc, 0x6, 0x2, 0x2, 0x162, 
    0x163, 0x9, 0x7, 0x2, 0x2, 0x163, 0x168, 0x5, 0x32, 0x1a, 0x7, 0x164, 
    0x165, 0xc, 0x5, 0x2, 0x2, 0x165, 0x166, 0x9, 0x8, 0x2, 0x2, 0x166, 
    0x168, 0x5, 0x32, 0x1a, 0x6, 0x167, 0x161, 0x3, 0x2, 0x2, 0x2, 0x167, 
    0x164, 0x3, 0x2, 0x2, 0x2, 0x168, 0x16b, 0x3, 0x2, 0x2, 0x2, 0x169, 
    0x167, 0x3, 0x2, 0x2, 0x2, 0x169, 0x16a, 0x3, 0x2, 0x2, 0x2, 0x16a, 
    0x33, 0x3, 0x2, 0x2, 0x2, 0x16b, 0x169, 0x3, 0x2, 0x2, 0x2, 0x16c, 0x16e, 
    0x9, 0x8, 0x2, 0x2, 0x16d, 0x16c, 0x3, 0x2, 0x2, 0x2, 0x16d, 0x16e, 
    0x3, 0x2, 0x2, 0x2, 0x16e, 0x16f, 0x3, 0x2, 0x2, 0x2, 0x16f, 0x173, 
    0x9, 0x9, 0x2, 0x2, 0x170, 0x173, 0x5, 0x36, 0x1c, 0x2, 0x171, 0x173, 
    0x5, 0x46, 0x24, 0x2, 0x172, 0x16d, 0x3, 0x2, 0x2, 0x2, 0x172, 0x170, 
    0x3, 0x2, 0x2, 0x2, 0x172, 0x171, 0x3, 0x2, 0x2, 0x2, 0x173, 0x35, 0x3, 
    0x2, 0x2, 0x2, 0x174, 0x175, 0x7, 0x1d, 0x2, 0x2, 0x175, 0x176, 0x7, 
    0x4, 0x2, 0x2, 0x176, 0x177, 0x5, 0x34, 0x1b, 0x2, 0x177, 0x178, 0x7, 
    0x3, 0x2, 0x2, 0x178, 0x179, 0x5, 0x34, 0x1b, 0x2, 0x179, 0x17a, 0x7, 
    0x5, 0x2, 0x2, 0x17a, 0x186, 0x3, 0x2, 0x2, 0x2, 0x17b, 0x17c, 0x7, 
    0x1f, 0x2, 0x2, 0x17c, 0x17d, 0x7, 0x4, 0x2, 0x2, 0x17d, 0x17e, 0x5, 
    0x34, 0x1b, 0x2, 0x17e, 0x17f, 0x7, 0x5, 0x2, 0x2, 0x17f, 0x186, 0x3, 
    0x2, 0x2, 0x2, 0x180, 0x181, 0x7, 0x1e, 0x2, 0x2, 0x181, 0x182, 0x7, 
    0x4, 0x2, 0x2, 0x182, 0x183, 0x5, 0x46, 0x24, 0x2, 0x183, 0x184, 0x7, 
    0x5, 0x2, 0x2, 0x184, 0x186, 0x3, 0x2, 0x2, 0x2, 0x185, 0x174, 0x3, 
    0x2, 0x2, 0x2, 0x185, 0x17b, 0x3, 0x2, 0x2, 0x2, 0x185, 0x180, 0x3, 
    0x2, 0x2, 0x2, 0x186, 0x37, 0x3, 0x2, 0x2, 0x2, 0x187, 0x188, 0x7, 0x2c, 
    0x2, 0x2, 0x188, 0x189, 0x7, 0x2b, 0x2, 0x2, 0x189, 0x18e, 0x5, 0x42, 
    0x22, 0x2, 0x18a, 0x18b, 0x7, 0x3, 0x2, 0x2, 0x18b, 0x18d, 0x5, 0x42, 
    0x22, 0x2, 0x18c, 0x18a, 0x3, 0x2, 0x2, 0x2, 0x18d, 0x190, 0x3, 0x2, 
    0x2, 0x2, 0x18e, 0x18c, 0x3, 0x2, 0x2, 0x2, 0x18e, 0x18f, 0x3, 0x2, 
    0x2, 0x2, 0x18f, 0x39, 0x3, 0x2, 0x2, 0x2, 0x190, 0x18e, 0x3, 0x2, 0x2, 
    0x2, 0x191, 0x192, 0x7, 0x2d, 0x2, 0x2, 0x192, 0x193, 0x7, 0x2b, 0x2, 
    0x2, 0x193, 0x198, 0x5, 0x3c, 0x1f, 0x2, 0x194, 0x195, 0x7, 0x3, 0x2, 
    0x2, 0x195, 0x197, 0x5, 0x3c, 0x1f, 0x2, 0x196, 0x194, 0x3, 0x2, 0x2, 
    0x2, 0x197, 0x19a, 0x3, 0x2, 0x2, 0x2, 0x198, 0x196, 0x3, 0x2, 0x2, 
    0x2, 0x198, 0x199, 0x3, 0x2, 0x2, 0x2, 0x199, 0x3b, 0x3, 0x2, 0x2, 0x2, 
    0x19a, 0x198, 0x3, 0x2, 0x2, 0x2, 0x19b, 0x19d, 0x5, 0x42, 0x22, 0x2, 
    0x19c, 0x19e, 0x9, 0xa, 0x2, 0x2, 0x19d, 0x19c, 0x3, 0x2, 0x2, 0x2, 
    0x19d, 0x19e, 0x3, 0x2, 0x2, 0x2, 0x19e, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x19f, 
    0x1a0, 0x7, 0x30, 0x2, 0x2, 0x1a0, 0x1a3, 0x7, 0x3b, 0x2, 0x2, 0x1a1, 
    0x1a2, 0x7, 0x3, 0x2, 0x2, 0x1a2, 0x1a4, 0x7, 0x3b, 0x2, 0x2, 0x1a3, 
    0x1a1, 0x3, 0x2, 0x2, 0x2, 0x1a3, 0x1a4, 0x3, 0x2, 0x2, 0x2, 0x1a4, 
    0x3f, 0x3, 0x2, 0x2, 0x2, 0x1a5, 0x1a6, 0x9, 0xb, 0x2, 0x2, 0x1a6, 0x41, 
    0x3, 0x2, 0x2, 0x2, 0x1a7, 0x1a8, 0x9, 0xc, 0x2, 0x2, 0x1a8, 0x43, 0x3, 
    0x2, 0x2, 0x2, 0x1a9, 0x1aa, 0x9, 0xd, 0x2, 0x2, 0x1aa, 0x45, 0x3, 0x2, 
    0x2, 0x2, 0x1ab, 0x1ac, 0x7, 0x38, 0x2, 0x2, 0x1ac, 0x1ad, 0x7, 0x4, 
    0x2, 0x2, 0x1ad, 0x1ae, 0x5, 0x46, 0x24, 0x2, 0x1ae, 0x1af, 0x7, 0x3, 
    0x2, 0x2, 0x1af, 0x1b0, 0x5, 0x46, 0x24, 0x2, 0x1b0, 0x1b1, 0x7, 0x3, 
    0x2, 0x2, 0x1b1, 0x1b2, 0x5, 0x46, 0x24, 0x2, 0x1b2, 0x1b3, 0x7, 0x5, 
    0x2, 0x2, 0x1b3, 0x1c4, 0x3, 0x2, 0x2, 0x2, 0x1b4, 0x1b5, 0x7, 0x37, 
    0x2, 0x2, 0x1b5, 0x1b6, 0x7, 0x4, 0x2, 0x2, 0x1b6, 0x1b7, 0x5, 0x46, 
    0x24, 0x2, 0x1b7, 0x1b8, 0x7, 0x3, 0x2, 0x2, 0x1b8, 0x1b9, 0x5, 0x46, 
    0x24, 0x2, 0x1b9, 0x1ba, 0x7, 0x5, 0x2, 0x2, 0x1ba, 0x1c4, 0x3, 0x2, 
    0x2, 0x2, 0x1bb, 0x1bc, 0x9, 0xe, 0x2, 0x2, 0x1bc, 0x1bd, 0x7, 0x4, 
    0x2, 0x2, 0x1bd, 0x1be, 0x5, 0x46, 0x24, 0x2, 0x1be, 0x1bf, 0x7, 0x5, 
    0x2, 0x2, 0x1bf, 0x1c4, 0x3, 0x2, 0x2, 0x2, 0x1c0, 0x1c4, 0x7, 0x36, 
    0x2, 0x2, 0x1c1, 0x1c4, 0x5, 0x42, 0x22, 0x2, 0x1c2, 0x1c4, 0x5, 0x10, 
    0x9, 0x2, 0x1c3, 0x1ab, 0x3, 0x2, 0x2, 0x2, 0x1c3, 0x1b4, 0x3, 0x2, 
    0x2, 0x2, 0x1c3, 0x1bb, 0x3, 0x2, 0x2, 0x2, 0x1c3, 0x1c0, 0x3, 0x2, 
    0x2, 0x2, 0x1c3, 0x1c1, 0x3, 0x2, 0x2, 0x2, 0x1c3, 0x1c2, 0x3, 0x2, 
    0x2, 0x2, 0x1c4, 0x47, 0x3, 0x2, 0x2, 0x2, 0x38, 0x4c, 0x53, 0x56, 0x59, 
    0x5c, 0x64, 0x69, 0x6c, 0x6f, 0x74, 0x77, 0x7a, 0x82, 0x85, 0x89, 0x8d, 
    0x92, 0x9a, 0x9e, 0xa2, 0xab, 0xae, 0xb1, 0xb9, 0xc4, 0xcd, 0xd4, 0xdc, 
    0xe9, 0xf7, 0xfd, 0x104, 0x10c, 0x10e, 0x114, 0x118, 0x124, 0x12c, 0x12f, 
    0x133, 0x13c, 0x145, 0x155, 0x15f, 0x167, 0x169, 0x16d, 0x172, 0x185, 
    0x18e, 0x198, 0x19d, 0x1a3, 0x1c3, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

WmsQL1Parser::Initializer WmsQL1Parser::_init;
