#define KEY_SIZE_BYTE 2
#define KEY_SIZE_WORD 3
#define KEY_SIZE_DWORD 4
#define KEY_SIZE_QWORD 5
#define KEY_REG_RANGE_BEGIN 24
#define KEY_REG_RANGE_END 39
#define RESERVED_KEYWORDS 40
static const char *reserved[] = {
	"break","case","byte","word",
	"dword","qword","continue","default",
	"do","else","enum","extern",
	"for","jump","if","register",
	"return","signed","struct","switch",
	"typedef","union","unsigned","while",
	"rax","rbx","rcx","rdx",
	"rbp","rsp","rdi","rsi",
	"r8","r9","r10","r11",
	"r12","r13","r14","r15"
};

#define OP_ADD 0
#define OP_SUB 1
#define OP_MUL 2
#define OP_DIV 3
#define OP_MOD 4
#define OP_LSFT 5
#define OP_RSFT 6
#define OP_SET 7
#define OP_EQU 8
#define OP_NEQ 9
#define OP_AND 10
#define OP_OR 11
#define OP_LAND 12
#define OP_LOR 13
#define OP_LNO 14
#define OP_XOR 15
#define OP_NOT 16
#define OP_GT 17
#define OP_LT 18
#define OP_COM 19
#define OP_DOT 20
#define OP_INC 21
#define OP_DEC 22
#define OP_LAB 23

#define OPERATORS 24
static const char *operator[] = {"+","-","*","/","%","<<",">>","=","==","!=","&","|","&&","||","!","^","~",">","<",",",".","++","--",":"};

#define CHAR_TYPE_INV -1
#define CHAR_TYPE_NUM 0
#define CHAR_TYPE_SYM 1
#define CHAR_TYPE_WHT 2
#define CHAR_TYPE_GRP 3
#define CHAR_TYPE_OPR 4
#define CHAR_TYPE_STR 5
#define CHAR_TYPE_SPE 6
#define CHAR_TYPE_NUL 7
#define CHAR_TYPE_COM 16

#define CHARSETS 7
static const char *char_ini[] = {"0123456789",              "_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",           " \r\n\t\0", "([{}])", "+-*/%><=!&|,^~.:`@$", "\"", "#;\\"};
static const char *char_set[] = {"0123456789xabcdefABCDEF", "_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", " \r\n\t\0", "([{}])", "+-*/%><=!&|,^~.:`@$", "",   "#;\\"};
static const char *char_end[] = {"",                        "",                                                                "",          "",       "",                    "\"", ""};
