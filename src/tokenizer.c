#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "host_config.h"
#include "lang_config.h"
#include "tokenizer.h"

static inline int token_boundary(const char *expr, int pos, int type, int start_pos)
{
	int i;

	if (char_set[type][0])
	{
		for (i = 0; i < strlen(char_set[type]); i++)
			if (char_set[type][i] == expr[pos])
				return 0; // then this is still part of the same token, do nothing.
		return 1; // This is not part of the current token's charset
	}

	if ((pos-1) > start_pos)
	{
		for (i = 0; i < strlen(char_end[type]); i++)
			if (char_end[type][i] == expr[pos-1])
				return 1; // we just passed an end character
		return 0; // We did not pass an end character
	}
	return 0; // Only happens if this is the first character
}

int id_token_str(const char *token)
{
	int i,j;
	for (i = 0; i < CHARSETS; i++)
	{
		for (j = 0; j < strlen(char_ini[i]); j++)
		{
			if (token[0] == char_ini[i][j])
				return i;
		}
	}
	return CHAR_TYPE_INV;
}

int id_operator(const char *op_str, int len)
{
	int i;
	for (i = 0; i < OPERATORS; i++)
	{
		if (strlen(operator[i]) == len && strncmp(operator[i], op_str, len) == 0)
			return i;
	}
	return OP_COM; // ? I needed something to use for invalid operators
}

int count_tokens(const char *expr, unsigned int len)
{
	int cur_tok, n_tok=0, tok_start_pos=0;
	int i,j;
	//Figure out what the first token is
	cur_tok = id_token_str(expr);

	//Step through the string, locate token boundaries, and count tokens
	for (i = 0; i < len; i++)
	{
		if (token_boundary(expr, i, cur_tok, tok_start_pos))
		{
//			// start next token
			cur_tok = id_token_str(&expr[i]);
			n_tok++;
			tok_start_pos = i;
		}
	}

	return n_tok;
}

int tokenize(const char *expr, unsigned int len, struct token *token_array)
{
	int cur_tok, n_tok, tok_start_pos;
	int i;

	//We figured out how many tokens there are, now lets figure out what they are and how to handle them
	n_tok = 0;
	int level = 0;
	cur_tok = id_token_str(expr);
	token_array[n_tok].type = cur_tok;
	token_array[n_tok].text = expr;
	token_array[n_tok].level = level;
	for (i=0; i < len; i++)
	{
		if (token_boundary(expr, i, cur_tok, tok_start_pos))
		{
			token_array[n_tok].text_len = (&expr[i]) - token_array[n_tok].text;

			// Interpret the token to get it into a more usable form
			if (cur_tok == CHAR_TYPE_NUM)
			{
				token_array[n_tok].sym = strtol(token_array[n_tok].text, NULL, 0);
			}
			if (cur_tok == CHAR_TYPE_GRP)
			{
				int k;
				for (k=0;k<token_array[n_tok].text_len;k++)
					if (token_array[n_tok].text[k] == '(')
						level++;
					else
						level--;
			}
			if (cur_tok == CHAR_TYPE_OPR)
			{
				token_array[n_tok].sym = id_operator(token_array[n_tok].text, token_array[n_tok].text_len);
			}
			cur_tok = id_token_str(&expr[i]); // learn what the next token is
			n_tok++;
			tok_start_pos = i;
			token_array[n_tok].type = cur_tok;
			token_array[n_tok].text = &expr[i];
			token_array[n_tok].level = level;
		}
	}

	token_array[n_tok].text_len = (&expr[i]) - token_array[n_tok].text;

	// Interpret the token to get it into a more usable form
	if (cur_tok == CHAR_TYPE_NUM)
	{
		token_array[n_tok].sym = strtol(token_array[n_tok].text, NULL,0);
	}
	if (cur_tok == CHAR_TYPE_GRP)
	{
		int k;
		for (k=0;k<token_array[n_tok].text_len;k++)
			if (token_array[n_tok].text[k] == '(')
				level++;
			else
				level--;
	}
	if (cur_tok == CHAR_TYPE_OPR)
	{
		token_array[n_tok].sym = id_operator(token_array[n_tok].text, token_array[n_tok].text_len);
	}

	return n_tok;
}

// This function will cleanup the tokenization, catching any type of
// tokenization which can not be handled in one pass.
// Ideally, this should not be needed if preprocessing is already
// completed. This handles: comments
int tokenize_fixup(struct token *tokens, int tok_len)
{
	int i,j,k,l;
	for (i=0; i<tok_len ; i++)
	{
		if (tokens[i].type == CHAR_TYPE_OPR)
		{
			//check if this is a comment
			if (tokens[i].text_len > 1 && tokens[i].text[0] == '/' && tokens[i].text[1] == '/')
			{
				for (j = i; j < tok_len; j++)
				{
					if (tokens[j].type == CHAR_TYPE_WHT)
					{
						for (k = 0; k < tokens[j].text_len; k++)
							if (tokens[j].text[k] == '\n')
								break;
						if (tokens[j].text[k] == '\n')
						{
							// then we need to merge i-j into i and mark i as a comment
							for (k = i; k < j; k++)
								tokens[i].text_len += tokens[k].text_len;
							for (k = i+1; k < j; k++)
							{
								for (l = i+1; l < tok_len-1; l++)
									memcpy(&tokens[l], &tokens[l+1], sizeof(struct token));
								tok_len += -1;
							}
							tokens[i].type = CHAR_TYPE_COM;
							break;
						}
					}
				}
			}
		}
	}
	return tok_len;
}

//This function will print an error message and nullify an invalid expression to prevent it from processing
//since it prints to the screen, it should be removed or moved elsewhere. Currently used by calc
int expr_error(const char *msg, int tok_n, struct token *token_array)
{
	printf("Error related to token #%d (\"",tok_n);
	int i;
	for (i = 0; i < token_array[tok_n].text_len; i++)
		printf("%c", token_array[tok_n].text[i]);
	printf("\"): %s\n", msg);
	return -1;
}

// This function should find the "l arg" for an operation
int find_l_arg(int op_n, struct token *token_array)
{
	int i,op_level = token_array[op_n].level;
	for (i=op_n-1; i>=0; i--)
	{
		if (token_array[i].level < op_level)
			return expr_error("Missing lvalue operand", op_n, token_array);

		if (token_array[i].type == CHAR_TYPE_NUM)
		{
			token_array[i].type = CHAR_TYPE_NUL;
			return i;
		}
	}
	return expr_error("Missing lvalue operand", op_n, token_array);
}

// This function should find the "r arg" for an operation
int find_r_arg(int op_n, int len, struct token *token_array)
{
	int i,op_level = token_array[op_n].level;
	for (i=op_n+1; i<=len; i++)
	{
		if (token_array[i].level < op_level)
			return expr_error("Missing rvalue operand", op_n, token_array);

		if (token_array[i].type == CHAR_TYPE_NUM)
		{
			token_array[i].type = CHAR_TYPE_NUL;
			return i;
		}
	}
	return expr_error("Missing rvalue operand", op_n, token_array);
}
