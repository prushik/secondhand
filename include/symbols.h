#define SYM_TYPE_LABEL 1
#define SYM_TYPE_REGISTER 2
#define SYM_TYPE_FUNCTION 3
#define SYM_TYPE_VARIABLE 4
#define SYM_TYPE_KEYWORD 5
#define SYM_TYPE_UNKNOWN 6

struct symbol
{
	int token_num;
	const char *text;
	int text_len;
	int size;
	int type;
	int reg;
};


int keyword_index(struct token *tok);
int count_symbols(struct token *tokens, int n_tok);
