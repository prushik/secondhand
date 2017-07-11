//#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <time.h>
#include "host_config.h"
#include "lang_config.h"
#include "tokenizer.h"

struct token *token_array;

static inline int is_keyword(struct token *tok)
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
			return 1;
	}
	return 0;
}

static int cursor_x=0, frame_v=0, token_n=0;

static char *disp_buffer;
static int disp_buffer_pos, disp_buffer_size;

void buffer_clear()
{
	disp_buffer_pos=0;
	disp_buffer_size=0;
}

void buffer_init(int x, int y)
{
	disp_buffer = (char*)malloc(x*y*2);
	buffer_clear();
}

// This probably only works on 64 bit systems. basically its a 64 bit
// memcpy with an implied destination
void buffer_write(const char *data, int size)
{
	int qwordsize = (size >> 3);
	int i;
	for (i=0; i <= qwordsize; i++)
	{
		((qword*)(disp_buffer+disp_buffer_pos))[i] = ((qword*)data)[i];
	}
	disp_buffer_pos += size;
	disp_buffer_size += size;
}

void buffer_present()
{
	(void)write(1, disp_buffer, disp_buffer_size);
}

void move_cursor(struct token *tokens, int n_tok, int x, int y)
{
	cursor_x += x;

	if (cursor_x < 0)
	{
		token_n += -1;
		cursor_x = tokens[token_n].text_len-1;
	}
	else if (cursor_x >= tokens[token_n].text_len)
	{
		cursor_x += (-tokens[token_n].text_len);
		token_n += 1;
	}

	if (y > 0)
	{
		int i,j;
		for (i=token_n;i<n_tok;i++)
		{
			if (tokens[i].type == CHAR_TYPE_WHT)
			{
				for (j=0;j<tokens[i].text_len;j++)
					if (tokens[i].text[j] == '\n')
					{
						token_n = i;
						cursor_x=0;
						return;
					}
			}
		}
	}
}

// tokens = token array ; n_tokens = size of array ; sel = selected token ; y = start of page to display
// w = window width ; h = window height
void display_page(struct token *tokens, int n_tokens, int sel, int y, int w, int h)
{
	int i,j;
	int vframe = 0, xpos = 0;
	int fgcolor, bgcolor;
	for (i = 0; i < n_tokens; i++)
	{
		bgcolor=9;
		fgcolor=9;

		if (tokens[i].type == CHAR_TYPE_NUM)
		fgcolor=1;
		if (tokens[i].type == CHAR_TYPE_STR)
		fgcolor=2;
		if (tokens[i].type == CHAR_TYPE_OPR)
		fgcolor=3;
		if (tokens[i].type == CHAR_TYPE_GRP)
		fgcolor=6;
		if (tokens[i].type == CHAR_TYPE_COM)
		fgcolor=4;
		if (tokens[i].type == CHAR_TYPE_SYM)
		if (is_keyword(&tokens[i]))
		fgcolor=5;
		else
		fgcolor=7;

		// track the current x and y position
		if (tokens[i].type == CHAR_TYPE_WHT)
			for (j = 0; j < tokens[i].text_len; j++)
				if (tokens[i].text[j] == '\n')
					vframe++,xpos=0;
				else
					xpos++;
			else
				xpos += tokens[i].text_len;

		if (vframe >= y && vframe < y+h)
		{
			char esc[] = "\x1b[30m";
			esc[3]+=fgcolor;
			// esc[6]+=bgcolor;

			buffer_write(esc, 5);
			if (i != token_n)
			{
				buffer_write(tokens[i].text, tokens[i].text_len);
			} else {
				buffer_write("\x1b[4m", 4);
				buffer_write(tokens[i].text, cursor_x);
				buffer_write("\x1b[7m", 4);
				buffer_write(&tokens[i].text[cursor_x], 1);
				buffer_write("\x1b[27m", 5);
				buffer_write(&tokens[i].text[cursor_x+1], tokens[i].text_len - (cursor_x+1));
			}
			buffer_write("\x1b[0m", 4);
		}
	}

	buffer_present();
}

void clear()
{
	buffer_clear();
	buffer_write("\x1b[H\x1b[J",6);
}



static struct termios orig_term_attr;
static struct termios new_term_attr;

void disable_canon()
{
	/* set the terminal to raw mode */
	tcgetattr(fileno(stdin), &orig_term_attr);
	memcpy(&new_term_attr, &orig_term_attr, sizeof(struct termios));
	new_term_attr.c_lflag &= ~(ECHO|ICANON);
	//    new_term_attr.c_cc[VTIME] = 0;
	//    new_term_attr.c_cc[VMIN] = 0;
	tcsetattr(fileno(stdin), TCSANOW, &new_term_attr);
	(void)write(1,"\x1b[?25l",6);
}

void enable_canon()
{
	(int)write(1,"\x1b[?25h",6);

	/* restore the original terminal attributes */
	tcsetattr(fileno(stdin), TCSANOW, &orig_term_attr);
}

int get_key()
{
	int character;

	//blocks until char is ready
	character = fgetc(stdin);

	return character;
}

void get_size(int *w, int *h)
{
	struct winsize win;
	ioctl(1, TIOCGWINSZ, &win);

	*h = win.ws_row;
	*w = win.ws_col;

	return;
}

int main(int argc, char **argv)
{
	int key;
	int w,h,n, sel = 0, cursor=0, y = 0;
	int fd;
	struct stat status;

	stat(argv[1], &status);

	if (!(fd = open(argv[1], O_RDONLY, 0)))
	exit(0);

	char *src_code = (char*)mmap(NULL, status.st_size+4096, PROT_READ, MAP_SHARED, fd, 0);

	token_array = malloc(sizeof(struct token) * (count_tokens(src_code, status.st_size)+1));

	n = tokenize(src_code, status.st_size, token_array);

	n = tokenize_fixup(token_array, n+1);

	disable_canon();

	get_size(&w,&h);
	
	buffer_init(w,h);

	clear();
	display_page(token_array, n+1, sel, y, w, h);

	while ((key = get_key()) != 0x04)
	{
		/* terminate loop on ESC (0x1B) or Ctrl-D (0x04) on STDIN */
		if (key == 0x1b)
		{
			key = get_key();
			if (key == 0x1b)
				break;
			if (key == '[')
			{
				key = get_key();
				if (key == 'A')
					y--;
				else if (key == 'B')
					move_cursor(token_array, n+1, 0, 1);
				else if (key == 'C')
					move_cursor(token_array, n+1, 1, 0);
				else if (key == 'D')
					move_cursor(token_array, n+1, -1, 0);
			}
		}
		else
		{
		//user is trying to edit shit
		}

		clear();
		display_page(token_array, n+1, sel, y, w, h);
	}

	enable_canon();

	return 0;
}
