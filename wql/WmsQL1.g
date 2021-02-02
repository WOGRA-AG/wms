grammar WmsQL1;

options 
{	
	k=3;
   output=AST;
	language=C;
	ASTLabelType=pANTLR3_BASE_TREE;
}


tokens{
	OBJ_REF;
	CLASS_REF;
	INT_TYPE;
	FLOAT_TYPE;
	STRING_TYPE;
	DATE_TYPE;
	NOT_IN;
	NOT_LIKE;
}

/*
@parser::header {
       package com.wogra.wms.wql.grammar;
       import com.wogra.wms.wql.grammar.util.IErrorReporter;
}

@lexer::header {
       package com.wogra.wms.wql.grammar;
}


@members {
    private IErrorReporter errorReporter = null;
    public void setErrorReporter(IErrorReporter errorReporter) {
        this.errorReporter = errorReporter;
    }
    @Override
    public void emitErrorMessage(String msg) {
    	  errorReporter.reportError(msg);
    }
}
*/

select_statement
	: select_clause from_clause where_clause? groupby_clause? orderby_clause? limit_clause? EOF!;
	
select_clause: SELECT^ (select_expression (','! select_expression)*)?;
select_expression : object_ref | aggregate_expression;
aggregate_expression : ( AVG | MAX | MIN |SUM )^ '('! (DISTINCT)? object_ref')'!
	| COUNT '('! (DISTINCT)? object_ref ')'!;

from_clause: FROM^ class_reference (','! class_reference)*;

groupby_clause: GROUP^ BY! groupby_item (','! groupby_item)*;

groupby_item: object_ref;

class_reference: id=idOrString-> ^(CLASS_REF $id);

idOrString: ID | STRING;

where_clause: WHERE^ conditional_expression;
conditional_expression: 
	  (OR|AND)^ '('! conditional_expression (','! conditional_expression)* ')'! 
	| NOT^ '('! conditional_expression ')'! 
	| simple_cond_expression;

simple_cond_expression
	: comparison_expression
	| (string_expression NOT? LIKE)=> like_expression
	| (object_ref (NOT)? IN)=> in_expression;
	
comparison_expression: 
	object_ref ('=' | '<>')^ boolean_expression
	| arithmetic_expression comparison_operator^ arithmetic_expression;

arithmetic_expression: simple_arithmetic_expression;

comparison_operator
	: '='
	| '>'
	| '>='
	| '<'
	| '<='
	| '<>';
	
like_expression
	: e=string_expression LIKE p=pattern_value -> ^(LIKE["LIKE"] $e $p)
	| (string_expression NOT LIKE)=> e=string_expression NOT LIKE p=pattern_value -> ^(NOT_LIKE["NOT_LIKE"] $e $p);

pattern_value: string_type;	
	
in_expression
	: o=object_ref IN '(' (i+=in_item (',' i+=in_item)*) ')' -> ^(IN["IN"] $o $i*)
	| (object_ref NOT IN)=> o=object_ref NOT IN '(' (i+=in_item (',' i+=in_item)*) ')' -> ^(NOT_IN["NOT_IN"] $o $i*);

in_item: simple_arithmetic_expression;

orderby_clause: ORDER^ BY! object_ref (ASC | DESC)?;

limit_clause: LIMIT^ INT (','! INT)?;

boolean_expression
	: boolean_primary;

boolean_primary
	: boolean_literal;

string_expression
	: string_primary;

string_primary
	: string_type
	| functions_returning_strings
	| aggregate_expression
	| object_ref;
	
string_type: s=STRING  -> ^(STRING_TYPE $s);	
	
functions_returning_strings
	: CONCAT^ '('! string_expression ','! string_expression ')'!
	| SUBSTRING^ '('! string_expression ','! string_expression ','! string_expression ')'!
	| LOWER^ '('! string_expression ')'!
	| UPPER^ '('! string_expression ')'!
    ;

arithmetic_primary
	: int_type
	| float_type
	| date_type
	| '('simple_arithmetic_expression')'
	| functions_returning_numerics
	| string_expression
	;
	
int_type: i=INT -> ^(INT_TYPE $i);
float_type: f=FLOAT -> ^(FLOAT_TYPE $f);
date_type: d=DATE -> ^(DATE_TYPE $d);
	
simple_arithmetic_expression
	: (arithmetic_term) (( '+' | '-' )^ arithmetic_term)*;

arithmetic_term
	: (arithmetic_factor) (( '*' | '/' )^ arithmetic_factor)*;

arithmetic_factor
	: ( ('+' | '-')=> ('+' | '-')^ )? arithmetic_primary;
	
object_ref : i=idpath -> ^(OBJ_REF $i);

idpath : ID | IDPATH;

boolean_literal : 'true' | 'TRUE' | 'false' | 'FALSE';
functions_returning_numerics
	: LENGTH^ '('! ID ')'!
	| ABS^    '('! ID ')'!
	| MOD^    '('! ID ','! ID ')'!
	| SIZE^   '('! ID ')'!;

AVG : 'AVG' | 'avg';
MAX : 'MAX' | 'max';
MIN : 'MIN' | 'min';
SUM : 'SUM' | 'sum';
DISTINCT : 'DISTINCT' | 'distinct';
SELECT : 'SELECT' | 'select';
FROM : 'FROM' | 'from';
WHERE : 'WHERE' | 'where';
ORDER : 'ORDER' | 'order';
BY : 'BY' | 'by';
ASC : 'ASC' | 'asc';
DESC : 'DESC' | 'desc';
AND: 'AND' | 'and';
OR : 'OR' | 'or';
NOT :'NOT' | 'not';
COUNT: 'COUNT' | 'count';
LIKE: 'LIKE' | 'like';
IN: 'IN' | 'in';
CONCAT : 'CONCAT' | 'concat';
SUBSTRING : 'SUBSTRING' | 'substring';
LOWER : 'LOWER' | 'lower';
UPPER : 'UPPER' | 'upper';
LENGTH : 'LENGTH' | 'length';
ABS : 'ABS' | 'abs';
MOD : 'MOD' | 'mode';
SIZE: 'SIZE' | 'size';
GROUP: 'GROUP' | 'group';
LIMIT: 'LIMIT' | 'limit';

DATE : YEAR '-' MONTH '-' DAY ('T' HOUR ':' MINUTE ':' SECOND)?;
fragment YEAR : ('1'..'2') DIGIT DIGIT DIGIT;
fragment MONTH: ('0'..'1') DIGIT;
fragment DAY  : ('0'..'3') DIGIT;
fragment HOUR  : ('0'..'2') DIGIT;
fragment MINUTE  : ('0'..'5') DIGIT;
fragment SECOND  : ('0'..'5') DIGIT;

ID  :	('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|DIGIT|'_')*
    ;

IDPATH  :	ID ('.' ID)*;

INT :	DIGIT+
    ;

FLOAT
    :   (DIGIT)+ '.' (DIGIT)* EXPONENT?
    |   '.' (DIGIT)+ EXPONENT?
    |   (DIGIT)+ EXPONENT
    ;

COMMENT
    :   '//' ~('\n'|'\r')* '\r'? '\n' {$channel=HIDDEN;}
    |   '/*' ( options {greedy=false;} : . )* '*/' {$channel=HIDDEN;}
    ;

WS  :   ( ' '
        | '\t'
        | '\r'
        | '\n'
        ) {$channel=HIDDEN;}
    ;

STRING
    :  QUOTE ( ESC_SEQ | ~('\\'|'"') )* QUOTE;
    
fragment DIGIT: '0'..'9';    
fragment QUOTE: '"';

fragment
EXPONENT : ('e'|'E') ('+'|'-')? ('0'..'9')+ ;

fragment
HEX_DIGIT : ('0'..'9'|'a'..'f'|'A'..'F') ;

fragment
ESC_SEQ
    :   '\\' ('b'|'t'|'n'|'f'|'r'|'\"'|'\''|'\\')
    |   UNICODE_ESC
    |   OCTAL_ESC
    ;

fragment
OCTAL_ESC
    :   '\\' ('0'..'3') ('0'..'7') ('0'..'7')
    |   '\\' ('0'..'7') ('0'..'7')
    |   '\\' ('0'..'7')
    ;

fragment
UNICODE_ESC
    :   '\\' 'u' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
    ;
