#include <string.h>
#include "host_config.h"
#include "lang_config.h"
#include "tokenizer.h"
#include "symbols.h"

int keyword_index(struct token *tok)
{
	int i,j;
	for (i = 0; i < RESERVED_KEYWORDS; i++)
	{
		int len = strlen(reserved[i]);
		if (tok->text_len != len)
			continue;
		
		for (j = 0; j < len; j++)
			if (reserved[i][j] != tok->text[j])
				break;
		if (j == len)
			return i; // return index of matching reserved keyword
	}
	return -1; // not a keyword, return error
}

int count_symbols(struct token *tokens, int n_tok)
{
	int i;
	for (i = 0; i < n_tok; i++)
	{
		//I guess this is where the finite state machine is needed, to 
		//figure out when a given keyword means what.
	}
}

int add_symbol(struct token *tokens, struct symbol table, int active, int tok_n)
{
	int i,j;
	for (i = 0; i < active; i++)
	{
		
	}
}
