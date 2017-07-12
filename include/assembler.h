#define KEY_SIZE_BYTE 0
#define KEY_SIZE_WORD 1
#define KEY_SIZE_DWORD 2
#define KEY_SIZE_QWORD 3
#define KEY_REG_RANGE_BEGIN 24
#define KEY_REG_RANGE_END 39
#define RESERVED_KEYWORDS 40
static const char *reserved[] = {
	"byte","word","dword","qword",
	"add","adc","adiw","sub",
	"subi","sbc","sbci","sbiw",
	"and","andi","or","ori", // combine and/andi and or/ori?
	"eor","com","neg","sbr", // I would also like eor to be called xor
	"cbr","inc","dec","tst",
	"clr","ser","","",
	"rjmp","rcall","ret","reti",
	"cpse","cp","cpc","cpi",
	"sbrc","sbrs","sbic","sbis",
	"brbs","brbc","breq","brne",
	"brcs","brcc","brsh","brlo",
	"brmi","bpl","brge","brlt",
	"brhs","brhc","brts","brtc",
	"brvs","brvc","brie","brid",
	"ld","st","mov","ldi",
	"in","out","lpm","sbi",
	"cbi","lsl","lsr","rol",
	"ror","asr","swap","bset",
	"bclr","bst","bld","sec",
	"clc","sen","cln","sez",
	"clz","sei","cli","ses",
	"cls","sev","slv","set",
	"clt","seh","clh","nop",
	"sleep","wdr",
	"r0","r1","r2","r3",
	"r4","r5","r6","r7",
	"r8","r9","r10","r11",
	"r12","r13","r14","r15",
	"r16","r17","r18","r19",
	"r20","r21","r22","r23",
	"r24","r25","r26","r27",
	"r28","r29","r30","r31",
	"rampx","rampy","rampz","rampd",
	"eind","pc","sp","sreg",
	"x","y","z"
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
static const char *char_set[] = {"0123456789xabcdefABCDEF", "_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789", " \r\n\t\0", "([{}])", "+-*/%><=!&|,^~.:`@$", "",   ""};
static const char *char_end[] = {"",                        "",                                                                "",          "",       "",                    "\"", "\n"};
