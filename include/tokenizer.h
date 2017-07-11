struct token
{
	int type;			//type of token
	int level;			//
	int group_id;		//id of current group
	int group_parent_id;//id of parent group
	int group_depth;	//depth of group nesting
	long sym;			//symbolic representation of token (machine readable)
	int text_len;		//length of token text
	const char *text;	//pointer to text of token
	int argc;			//number of operands
	int argv[6];		//token numbers of operands to this token
	long custom_flags;	//reserved for application use
};

#ifndef RESERVED_KEYWORDS
	#define RESERVED_KEYWORDS 24
	static const char *reserved[] = {"auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if","int","long","register","return","short","signed","static","struct","switch","typedef","union","unsigned","void","volitile","while","_Packed"};
#endif

#ifndef OPERATORS
	#define OPERATORS 23
	static const char *operator[] = {"+","-","*","/","%","<<",">>","=","==","!=","&","|","&&","||","!","^","~",">","<",",",".","++","--"};
#endif

#ifndef OP_COM
	#define OP_COM 19
#endif
#ifndef OP_ADD
	#define OP_ADD OP_COM
#endif
#ifndef OP_SUB
	#define OP_SUB OP_COM
#endif
#ifndef OP_MUL
	#define OP_MUL OP_COM
#endif
#ifndef OP_DIV
	#define OP_DIV OP_COM
#endif
#ifndef OP_MOD
	#define OP_MOD OP_COM
#endif
#ifndef OP_LSFT
	#define OP_LSFT OP_COM
#endif
#ifndef OP_RSFT
	#define OP_RSFT OP_COM
#endif
#ifndef OP_SET
	#define OP_SET OP_COM
#endif
#ifndef OP_EQU
	#define OP_EQU OP_COM
#endif
#ifndef OP_NEQ
	#define OP_NEQ OP_COM
#endif
#ifndef OP_AND
	#define OP_AND OP_COM
#endif
#ifndef OP_OR
	#define OP_OR OP_COM
#endif
#ifndef OP_LAND
	#define OP_LAND OP_COM
#endif
#ifndef OP_LOR
	#define OP_LOR OP_COM
#endif
#ifndef OP_LNO
	#define OP_LNO OP_COM
#endif
#ifndef OP_XOR
	#define OP_XOR OP_COM
#endif
#ifndef OP_NOT
	#define OP_NOT OP_COM
#endif
#ifndef OP_GT
	#define OP_GT OP_COM
#endif
#ifndef OP_LT
	#define OP_LT OP_COM
#endif
#ifndef OP_DOT
	#define OP_DOT OP_COM
#endif
#ifndef OP_INC
	#define OP_INC OP_COM
#endif
#ifndef OP_DEC
	#define OP_DEC OP_COM
#endif

#ifndef CHARSETS
	#define CHARSETS 7
	static const char *char_ini[] = {"0123456789",              "_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",           " \r\n\t\0", "([{}])", "+-*/%><=!&|,^~.", "\"", "#;\\"};
	static const char *char_set[] = {"0123456789xabcdefABCDEF", "_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", " \r\n\t\0", "([{}])", "+-*/%><=!&|,^~.", "",   "#;\\"};
	static const char *char_end[] = {"",                        "",                                                                "",          "",       "",                "\"", ""};
#endif

#ifndef CHAR_TYPE_INV
	#define CHAR_TYPE_INV -1
#endif
#ifndef CHAR_TYPE_NUM
	#define CHAR_TYPE_NUM CHAR_TYPE_INV
#endif
#ifndef CHAR_TYPE_SYM
	#define CHAR_TYPE_SYM CHAR_TYPE_INV
#endif
#ifndef CHAR_TYPE_WHT
	#define CHAR_TYPE_WHT CHAR_TYPE_INV
#endif
#ifndef CHAR_TYPE_GRP
	#define CHAR_TYPE_GRP CHAR_TYPE_INV
#endif
#ifndef CHAR_TYPE_OPR
	#define CHAR_TYPE_OPR CHAR_TYPE_INV
#endif
#ifndef CHAR_TYPE_STR
	#define CHAR_TYPE_STR CHAR_TYPE_INV
#endif
#ifndef CHAR_TYPE_SPE
	#define CHAR_TYPE_STR CHAR_TYPE_INV
#endif
#ifndef CHAR_TYPE_NUL
	#define CHAR_TYPE_NUL CHAR_TYPE_INV
#endif

int id_token_str(const char *token);
int id_operator(const char *op_str, int len);
int count_tokens(const char *expr, unsigned int len);
int tokenize(const char *expr, unsigned int len, struct token *token_array);
int expr_error(const char *msg, int tok_n, struct token *token_array);
int find_l_arg(int op_n, struct token *token_array);
int find_r_arg(int op_n, int len, struct token *token_array);
