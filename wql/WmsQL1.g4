grammar WmsQL1;

@header
{
#undef emit
}

options
{
	language=Cpp;
}


// Parser rules

statement : (select_statement | insert_statement | update_statement | delete_statement) EOF;

select_statement: select_clause from_clause where_clause? groupby_clause? orderby_clause? limit_clause?;

insert_statement
	: insert_clause value_clause
	| insert_clause set_clause
	;

update_statement: update_clause set_clause where_clause? orderby_clause? limit_clause?;

delete_statement: delete_clause from_clause where_clause? orderby_clause? limit_clause?;

// select
select_clause: SELECT (select_expression (',' select_expression)*)?;

select_expression
	: aggregate_expression
	| (DISTINCT)? object_ref
	| STAR
	;

aggregate_expression
	: aggFunc=(AVG | MAX | MIN | SUM | COUNT) '(' (DISTINCT)? object_ref ')'
	| aggFunc=COUNT '(' (DISTINCT)? STAR ')'
	;

// insert
insert_clause: INSERT INTO? class_ref ('(' (members+=object_ref (',' members+=object_ref)*)? ')')?;

// update
update_clause: UPDATE class_ref (',' class_ref)*;

// delete
delete_clause: DELETE;

// values
value_clause: VALUES value_list (',' value_list)*;

value_list
	: '(' value_ref (',' value_ref)* ')'
	| '(' ')'
	;

// set
set_clause: SET set_assignment (',' set_assignment)*;

set_assignment: object_ref EQ value_ref;

// from
from_clause: FROM class_ref (',' class_ref)*;

// where
where_clause: WHERE where_expression;

where_expression
	: logical_operator=(OR | AND) '(' where_expression (',' where_expression)* ')'
	| where_expression logical_operator=AND where_expression
	| where_expression logical_operator=OR where_expression
	| (logical_operator=NOT)? '(' where_expression ')'
	| cond_expression
	;

cond_expression
	: in_condition
	| like_condition
	| compare_condition
	;

in_condition
	: object_ref (NOT)? IN '(' in_items ')'
	;

in_items
	: string_expression (',' string_expression)*
	| arithmetic_expression (',' arithmetic_expression)*
	;

like_condition
	: object=object_ref (NOT)? LIKE compareString=string_expression
	| object=object_ref (EQ | NEQ) compareString=string_expression
	;

compare_condition
	: object_ref (EQ | NEQ) (TRUE | FALSE)
	| object_ref IS (NOT)? NULL_REPR
	| object_ref compare_sign arithmetic_expression
	| object_ref compare_sign object_ref
	| arithmetic_expression compare_sign object_ref
	;

compare_sign
	: EQ
	| NEQ
	| LT
	| LEQ
	| GT
	| GEQ
	;

arithmetic_expression
	: arithmetic_expression (STAR | SLASH) arithmetic_expression
	| arithmetic_expression (PLUS | MINUS) arithmetic_expression
	| '(' arithmetic_expression ')'
	| arithmetic_factor
	;

arithmetic_factor
	: (PLUS | MINUS)? type=(INT_TYPE | FLOAT_TYPE | DATE_TYPE)
	| numeric_returning_function
	| string_expression
	;

numeric_returning_function
	: MOD '(' arithmetic_factor ',' arithmetic_factor ')'
	| ABS '(' arithmetic_factor ')'
	| LENGTH '(' string_expression ')'
//	| SIZE '(' arithmetic_factor ')'
	;

// group by
groupby_clause: GROUP BY object_ref (',' object_ref)*;

// order by
orderby_clause: ORDER BY orderby_expression (',' orderby_expression)*;
orderby_expression: object_ref ( ASC | DESC )?;

// limit
limit_clause: LIMIT INT_TYPE (',' INT_TYPE)?;


// ITEMS
value_ref: INT_TYPE | FLOAT_TYPE | DATE_TYPE | STRING_TYPE;

object_ref: ID | IDPATH;

class_ref
	: ID
	| CLASSID
	| STRING_TYPE
	;

string_expression
	: SUBSTRING '(' string_expression ',' string_expression ',' string_expression ')'
	| CONCAT '(' string_expression ',' string_expression ')'
	| (LOWER | UPPER) '(' string_expression ')'
	| STRING_TYPE
	| object_ref
	| aggregate_expression
	;



// Lexer rules

SELECT : 'SELECT' | 'select';
DISTINCT : 'DISTINCT' | 'distinct';
AVG : 'AVG' | 'avg';
MAX : 'MAX' | 'max';
MIN : 'MIN' | 'min';
SUM : 'SUM' | 'sum';
COUNT: 'COUNT' | 'count';

INSERT : 'INSERT' | 'insert';
INTO : 'INTO' | 'into';

UPDATE : 'UPDATE' | 'update';

DELETE : 'DELETE' | 'delete';

VALUES : 'VALUES' | 'values' | 'VALUE' | 'value';
DEFAULT : 'DEFAULT';

SET : 'SET' | 'set';

FROM : 'FROM' | 'from';

WHERE : 'WHERE' | 'where';

AND: 'AND' | 'and';
OR : 'OR' | 'or';
NOT :'NOT' | 'not';

LIKE: 'LIKE' | 'like';
IN: 'IN' | 'in';
IS: 'IS' | 'is';
NULL_REPR: 'NULL' | 'null';

MOD : 'MOD' | 'mode';
LENGTH : 'LENGTH' | 'length';
ABS : 'ABS' | 'abs';
SIZE: 'SIZE' | 'size';
PLUS: '+';
MINUS: '-';
STAR: '*';
SLASH: '/';
EQ: '=';
NEQ: '<>';
LT: '<';
LEQ
	: '<='
	| '=<'
	;
GT: '>';
GEQ
	: '>='
	| '=>'
	;

BY : 'BY' | 'by';
GROUP: 'GROUP' | 'group';

ORDER : 'ORDER' | 'order';
ASC : 'ASC' | 'asc';
DESC : 'DESC' | 'desc';

LIMIT: 'LIMIT' | 'limit';



TRUE: 'TRUE' | 'true';
FALSE: 'FALSE' | 'false';


ID: (LETTER | '_') (LETTER | '_' | DIGIT)*;
CLASSID: ID '.class';
IDPATH: ID ('.' ID)+;
fragment LETTER
	: [A-Z]
	| [a-z]
	| 'ß'
	| 'Ä' | 'ä'
	| 'Ö' | 'ö'
	| 'Ü' | 'ü'
	;

STRING_TYPE: '"' (ESC_SEQ | ~('\\'))*? '"';
fragment ESC_SEQ
	: '\\' ('b' | 't' | 'n' | 'f' | 'r' | '\\"' | '\\')
	| OCTAL_ESC
	| UNICODE_ESC
	;
fragment OCTAL_ESC
	: '\\' [0-3] [0-7] [0-7]
	| '\\' [0-7] [0-7]
	| '\\' [0-7]
	;
fragment UNICODE_ESC
	: '\\' 'u' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
	;
fragment HEX_DIGIT: ([0-9] | [a-f] | [A-F]);

CONCAT: 'CONCAT' | 'concat';
SUBSTRING: 'SUBSTRING' | 'substring';
LOWER: 'LOWER' | 'lower';
UPPER: 'UPPER' | 'upper';

INT_TYPE: (DIGIT)+;
fragment DIGIT: [0-9];

FLOAT_TYPE
	: (DIGIT)+ '.' (DIGIT)* EXPONENT?
	| '.' (DIGIT)+ EXPONENT?
	| (DIGIT)+ EXPONENT
	;
fragment EXPONENT: ('E'|'e') ('+'|'-')? ('0'..'9')+;

DATE_TYPE: YEAR '-' MONTH '-' DAY ('T' HOUR ':' MINUTE ':' SECOND)?;
fragment YEAR: [1-2] DIGIT DIGIT DIGIT;
fragment MONTH: [0-1] DIGIT;
fragment DAY: [0-3] DIGIT;
fragment HOUR: [0-2] DIGIT;
fragment MINUTE: [0-5] DIGIT;
fragment SECOND: [0-5] DIGIT;


BLOCK_COMMENT: '/*' .*? '*/' -> skip;
LINE_COMMENT: '//' ~[\r\n]* ('\r'? '\n')? -> skip;

WS: [ \t\r\n\f]+ -> skip;
