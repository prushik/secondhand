#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "host_config.h"
#include "lang_config.h"
#include "tokenizer.h"

struct token *token_array;

int process_operator(int op_n, int len, struct token *token_array);
int process_expression(int len, struct token *token_array);

//This function should find the appropriate args for an operator, perform the operation, and reduce the expression
int process_operator(int op_n, int len, struct token *token_array)
{
	int l,r;
	int result = token_array[op_n].sym;
	int op = token_array[op_n].sym;

	switch (op)
	{
		case OP_ADD:
			r = find_r_arg(op_n, len, token_array);
			l = find_l_arg(op_n, token_array);
			result = token_array[l].sym + token_array[r].sym;
			break;
		case OP_SUB:
			r = find_r_arg(op_n, len, token_array);
			l = find_l_arg(op_n, token_array);
			result = token_array[l].sym - token_array[r].sym;
			break;
		case OP_MUL:
			r = find_r_arg(op_n, len, token_array);
			l = find_l_arg(op_n, token_array);
			result = token_array[l].sym * token_array[r].sym;
			break;
		case OP_DIV:
			r = find_r_arg(op_n, len, token_array);
			l = find_l_arg(op_n, token_array);
			result = token_array[l].sym / token_array[r].sym;
			break;
		case OP_MOD:
			r = find_r_arg(op_n, len, token_array);
			l = find_l_arg(op_n, token_array);
			result = token_array[l].sym % token_array[r].sym;
			break;
		case OP_LSFT:
			r = find_r_arg(op_n, len, token_array);
			l = find_l_arg(op_n, token_array);
			result = token_array[l].sym << token_array[r].sym;
			break;
		case OP_RSFT:
			r = find_r_arg(op_n, len, token_array);
			l = find_l_arg(op_n, token_array);
			result = token_array[l].sym >> token_array[r].sym;
			break;
		case OP_AND:
			r = find_r_arg(op_n, len, token_array);
			l = find_l_arg(op_n, token_array);
			result = token_array[l].sym & token_array[r].sym;
			break;
		case OP_OR:
			r = find_r_arg(op_n, len, token_array);
			l = find_l_arg(op_n, token_array);
			result = token_array[l].sym | token_array[r].sym;
			break;
		case OP_XOR:
			r = find_r_arg(op_n, len, token_array);
			l = find_l_arg(op_n, token_array);
			result = token_array[l].sym ^ token_array[r].sym;
			break;
		case OP_NOT:
			r = find_r_arg(op_n, len, token_array);
			result = ~token_array[r].sym; // This is a special case (single arg operator) and should not require or consume lvalue
			break;
		case OP_COM:
			r = find_r_arg(op_n, len, token_array);
			l = find_l_arg(op_n, token_array);
			result = token_array[r].sym; //This DOES require an lvalue, but it is ignored
			break;
		case OP_EQU:
			r = find_r_arg(op_n, len, token_array);
			l = find_l_arg(op_n, token_array);
			result = token_array[l].sym == token_array[r].sym;
			break;
		case OP_LT:
			r = find_r_arg(op_n, len, token_array);
			l = find_l_arg(op_n, token_array);
			result = token_array[l].sym < token_array[r].sym;
			break;
		case OP_GT:
			r = find_r_arg(op_n, len, token_array);
			l = find_l_arg(op_n, token_array);
			result = token_array[l].sym > token_array[r].sym;
			break;
		case OP_INC:
			l = find_l_arg(op_n, token_array);
			result = token_array[l].sym +1;
			break;
		case OP_DEC:
			l = find_l_arg(op_n, token_array);
			result = token_array[l].sym - 1;
			break;
		default:
			return expr_error("Unknown operator", op_n, token_array);
			break;
	}
	token_array[op_n].sym = result;
	token_array[op_n].type = CHAR_TYPE_NUM;

	return result;
}

int process_expression(int len, struct token *token_array)
{
	int i,max_level=0;
	for (i=0;i<=len;i++)
		if (token_array[i].level>max_level)
			max_level=token_array[i].level;
	for (;max_level>=0;max_level--)
		for (i=0;i<=len;i++)
		{
			if (token_array[i].type == CHAR_TYPE_OPR && token_array[i].level == max_level)
			{
				process_operator(i, len, token_array);
			}
		}

	//print result
	for (i=0;i<=len;i++)
	{
//		write(1,token_array[i].text,token_array[i].text_len);
		if (token_array[i].type == CHAR_TYPE_NUM)
			printf("%ld %lx\n",token_array[i].sym,token_array[i].sym);
	}

	return 0;
}

void interactive()
{
	char buffer[512];

	while (1)
	{
		int len = read(0,buffer,512);
		token_array = malloc(sizeof(struct token) * (count_tokens(buffer,len)+1));
		len = tokenize(buffer, len, token_array);
		process_expression(len, token_array);
		free(token_array);
	}
}

int main(int argc, char **argv)
{
	int n;

	if (argc<2)
		interactive();
	else
	{
		n = tokenize(argv[1], strlen(argv[1]), token_array);
		process_expression(n,token_array);
	}

	return 0;
}
