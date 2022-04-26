

// This file was automatically generated by Coco/R; don't modify it.
#if !defined(Ob_COCO_PARSER_H__)
#define Ob_COCO_PARSER_H__

#include <QStack>
#include <Oberon/ObSynTree.h>


#include "ObLexer.h"

namespace Ob {



class Parser {
private:
	enum {
		_EOF=0,
		_T_Literals_=1,
		_T_Hash=2,
		_T_Dlr=3,
		_T_Amp=4,
		_T_Lpar=5,
		_T_Latt=6,
		_T_Rpar=7,
		_T_Star=8,
		_T_Ratt=9,
		_T_StarGt=10,
		_T_Plus=11,
		_T_Comma=12,
		_T_Minus=13,
		_T_Dot=14,
		_T_2Dot=15,
		_T_Slash=16,
		_T_2Slash=17,
		_T_Colon=18,
		_T_ColonEq=19,
		_T_Semi=20,
		_T_Lt=21,
		_T_LtStar=22,
		_T_Leq=23,
		_T_Eq=24,
		_T_Gt=25,
		_T_Geq=26,
		_T_Lbrack=27,
		_T_Rbrack=28,
		_T_Hat=29,
		_T_Lbrace=30,
		_T_Bar=31,
		_T_Rbrace=32,
		_T_Tilde=33,
		_T_Keywords_=34,
		_T_ARRAY=35,
		_T_BEGIN=36,
		_T_BY=37,
		_T_CARRAY=38,
		_T_CASE=39,
		_T_CONST=40,
		_T_CPOINTER=41,
		_T_CSTRUCT=42,
		_T_CUNION=43,
		_T_DEFINITION=44,
		_T_DIV=45,
		_T_DO=46,
		_T_ELSE=47,
		_T_ELSIF=48,
		_T_END=49,
		_T_EXIT=50,
		_T_FALSE=51,
		_T_FOR=52,
		_T_IF=53,
		_T_IMPORT=54,
		_T_IN=55,
		_T_IS=56,
		_T_LOOP=57,
		_T_MOD=58,
		_T_MODULE=59,
		_T_NIL=60,
		_T_OF=61,
		_T_OR=62,
		_T_POINTER=63,
		_T_PROC=64,
		_T_PROCEDURE=65,
		_T_RECORD=66,
		_T_REPEAT=67,
		_T_RETURN=68,
		_T_THEN=69,
		_T_TO=70,
		_T_TRUE=71,
		_T_TYPE=72,
		_T_UNSAFE=73,
		_T_UNTIL=74,
		_T_VAR=75,
		_T_WHILE=76,
		_T_WITH=77,
		_T_Specials_=78,
		_T_ident=79,
		_T_integer=80,
		_T_real=81,
		_T_string=82,
		_T_hexchar=83,
		_T_hexstring=84,
		_T_Comment=85,
		_T_Eof=86,
		_T_MaxToken_=87
	};
	int maxT;

	int errDist;
	int minErrDist;

	void SynErr(int n, const char* ctx = 0);
	void Get();
	void Expect(int n, const char* ctx = 0);
	bool StartOf(int s);
	void ExpectWeak(int n, int follow);
	bool WeakSeparator(int n, int syFol, int repFol);
    void SynErr(const QString& sourcePath, int line, int col, int n, Ob::Errors* err, const char* ctx, const QString& = QString() );

public:
	Ob::Lexer *scanner;
	Ob::Errors  *errors;

	Ob::Token d_cur;
	Ob::Token d_next;
	QList<Ob::Token> d_comments;
	struct TokDummy
	{
		int kind;
	};
	TokDummy d_dummy;
	TokDummy *la;			// lookahead token
	
	int peek( quint8 la = 1 );

    void RunParser();

    
Ob::SynTree d_root;
	QStack<Ob::SynTree*> d_stack;
	void addTerminal() {
		if( d_cur.d_type != Ob::Tok_Semi && d_cur.d_type != Ob::Tok_Comma && d_cur.d_type != Ob::Tok_Dot && d_cur.d_type != Ob::Tok_Colon ){
			Ob::SynTree* n = new Ob::SynTree( d_cur ); d_stack.top()->d_children.append(n);
		}
	}



	Parser(Ob::Lexer *scanner,Ob::Errors*);
	~Parser();
	void SemErr(const char* msg);

	void Oberon();
	void module();
	void definition();
	void number();
	void qualident();
	void identdef();
	void ConstDeclaration();
	void ConstExpression();
	void expression();
	void TypeDeclaration();
	void type();
	void NamedType();
	void enumeration();
	void ArrayType();
	void RecordType();
	void PointerType();
	void ProcedureType();
	void TypeParams();
	void TypeActuals();
	void TypeActual();
	void LengthList();
	void length();
	void vlength();
	void BaseType();
	void FieldListSequence();
	void FieldList();
	void IdentList();
	void FormalParameters();
	void VariableDeclaration();
	void designator();
	void selector();
	void ExpList();
	void SimpleExpression();
	void relation();
	void term();
	void AddOperator();
	void factor();
	void MulOperator();
	void literal();
	void set();
	void variableOrFunctionCall();
	void element();
	void statement();
	void assignmentOrProcedureCall();
	void IfStatement();
	void CaseStatement();
	void WithStatement();
	void LoopStatement();
	void ExitStatement();
	void ReturnStatement();
	void WhileStatement();
	void RepeatStatement();
	void ForStatement();
	void StatementSequence();
	void ElsifStatement();
	void ElseStatement();
	void Case();
	void CaseLabelList();
	void LabelRange();
	void label();
	void ElsifStatement2();
	void Guard();
	void ProcedureDeclaration();
	void Receiver();
	void ProcedureHeading();
	void ProcedureBody();
	void DeclarationSequence();
	void DeclarationSequence2();
	void SystemAttrs();
	void FPSection();
	void ReturnType();
	void FormalType();
	void ImportList();
	void import();
	void SysAttr();

	void Parse();

}; // end Parser

} // namespace


#endif

