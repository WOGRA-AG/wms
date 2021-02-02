
#undef emit


// Generated from WmsQL1.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"




class  WmsQL1Lexer : public antlr4::Lexer {
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

  WmsQL1Lexer(antlr4::CharStream *input);
  ~WmsQL1Lexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

