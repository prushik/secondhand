#define KEY_SIZE_BYTE	0x00
#define KEY_SIZE_WORD	0x01
#define KEY_SIZE_DWORD	0x02
#define KEY_SIZE_QWORD	0x03
#define KEY_INSTR_ADD	0x04
#define KEY_INSTR_ADC	0x05
#define KEY_INSTR_ADIW	0x06
#define KEY_INSTR_SUB	0x07
#define KEY_INSTR_SUBI	0x08
#define KEY_INSTR_SBC	0x09
#define KEY_INSTR_SBCI	0x0a
#define KEY_INSTR_SBIW	0x0b
#define KEY_INSTR_AND	0x0c
#define KEY_INSTR_ANDI	0x0d
#define KEY_INSTR_OR	0x0e
#define KEY_INSTR_ORI	0x0f
#define KEY_INSTR_EOR	0x10
#define KEY_INSTR_COM	0x11
#define KEY_INSTR_NEG	0x12
#define KEY_INSTR_SBR	0x13
#define KEY_INSTR_CBR	0x14
#define KEY_INSTR_INC	0x15
#define KEY_INSTR_DEC	0x16
#define KEY_INSTR_TST	0x17
#define KEY_INSTR_CLR	0x18
#define KEY_INSTR_SER	0x19
#define KEY_INSTR_PUSH	0x1a
#define KEY_INSTR_POP	0x1b
#define KEY_INSTR_JMP	0x1c
#define KEY_INSTR_IJMP	0x1d
#define KEY_INSTR_CALL	0x1e
#define KEY_INSTR_ICALL	0x1f
#define KEY_INSTR_RJMP	0x20
#define KEY_INSTR_RCALL	0x21
#define KEY_INSTR_RET	0x22
#define KEY_INSTR_RETI	0x23
#define KEY_INSTR_CPSE	0x24
#define KEY_INSTR_CP	0x25
#define KEY_INSTR_CPC	0x26
#define KEY_INSTR_CPI	0x27
#define KEY_INSTR_SBRC	0x28
#define KEY_INSTR_SBRS	0x29
#define KEY_INSTR_SBIC	0x2a
#define KEY_INSTR_SBIS	0x2b
#define KEY_INSTR_BRBS	0x2c
#define KEY_INSTR_BRBC	0x2d
#define KEY_INSTR_BREQ	0x2e
#define KEY_INSTR_BRNE	0x2f
#define KEY_INSTR_BRCS	0x30
#define KEY_INSTR_BRCC	0x31
#define KEY_INSTR_BRSH	0x32
#define KEY_INSTR_BRLO	0x33
#define KEY_INSTR_BRMI	0x34
#define KEY_INSTR_BRPL	0x35
#define KEY_INSTR_BRGE	0x36
#define KEY_INSTR_BRLT	0x37
#define KEY_INSTR_BRHS	0x38
#define KEY_INSTR_BRHC	0x39
#define KEY_INSTR_BRTS	0x3a
#define KEY_INSTR_BRTC	0x3b
#define KEY_INSTR_BRVS	0x3c
#define KEY_INSTR_BRVC	0x3d
#define KEY_INSTR_BRIE	0x3e
#define KEY_INSTR_BRID	0x3f
#define KEY_INSTR_LD	0x40
#define KEY_INSTR_ST	0x41
#define KEY_INSTR_MOV	0x42
#define KEY_INSTR_LDI	0x43
#define KEY_INSTR_IN	0x44
#define KEY_INSTR_OUT	0x45
#define KEY_INSTR_LPM	0x46
#define KEY_INSTR_SBI	0x47
#define KEY_INSTR_CBI	0x48
#define KEY_INSTR_LSL	0x49
#define KEY_INSTR_LSR	0x4a
#define KEY_INSTR_ROL	0x4b
#define KEY_INSTR_ROR	0x4c
#define KEY_INSTR_ASR	0x4d
#define KEY_INSTR_SWAP	0x4e
#define KEY_INSTR_BSET	0x4f
#define KEY_INSTR_BCLR	0x50
#define KEY_INSTR_BST	0x51
#define KEY_INSTR_BLD	0x52
#define KEY_INSTR_SEC	0x53
#define KEY_INSTR_CLC	0x54
#define KEY_INSTR_SEN	0x55
#define KEY_INSTR_CLN	0x56
#define KEY_INSTR_SEZ	0x57
#define KEY_INSTR_CLZ	0x58
#define KEY_INSTR_SEI	0x59
#define KEY_INSTR_CLI	0x5a
#define KEY_INSTR_SES	0x5b
#define KEY_INSTR_CLS	0x5c
#define KEY_INSTR_SEV	0x5d
#define KEY_INSTR_CLV	0x5e
#define KEY_INSTR_SET	0x5f
#define KEY_INSTR_CLT	0x60
#define KEY_INSTR_SEH	0x61
#define KEY_INSTR_CLH	0x62
#define KEY_INSTR_NOP	0x63
#define KEY_INSTR_SLEEP	0x64
#define KEY_INSTR_WDR	0x65
#define KEY_INSTR_R0	0x66
#define KEY_INSTR_R1	0x67
#define KEY_INSTR_R2	0x68
#define KEY_INSTR_R3	0x69
#define KEY_INSTR_R4	0x6a
#define KEY_INSTR_R5	0x6b
#define KEY_INSTR_R6	0x6c
#define KEY_INSTR_R7	0x6d
#define KEY_INSTR_R8	0x6e
#define KEY_INSTR_R9	0x6f
#define KEY_INSTR_R10	0x70
#define KEY_INSTR_R11	0x71
#define KEY_INSTR_R12	0x72
#define KEY_INSTR_R13	0x73
#define KEY_INSTR_R14	0x74
#define KEY_INSTR_R15	0x75
#define KEY_INSTR_R16	0x76
#define KEY_INSTR_R17	0x77
#define KEY_INSTR_R18	0x78
#define KEY_INSTR_R19	0x79
#define KEY_INSTR_R20	0x7a
#define KEY_INSTR_R21	0x7b
#define KEY_INSTR_R22	0x7c
#define KEY_INSTR_R23	0x7d
#define KEY_INSTR_R24	0x7e
#define KEY_INSTR_R25	0x7f
#define KEY_INSTR_R26	0x80
#define KEY_INSTR_R27	0x81
#define KEY_INSTR_R28	0x82
#define KEY_INSTR_R29	0x83
#define KEY_INSTR_R30	0x84
#define KEY_INSTR_R31	0x85
#define KEY_INSTR_RAMPX	0x86
#define KEY_INSTR_RAMPY	0x87
#define KEY_INSTR_RAMPZ	0x88
#define KEY_INSTR_RAMPD	0x89
#define KEY_INSTR_EIND	0x8a
#define KEY_INSTR_PC	0x8b
#define KEY_INSTR_SP	0x8c
#define KEY_INSTR_SEG	0x8d
#define KEY_INSTR_X		0x8e
#define KEY_INSTR_Y		0x8f
#define KEY_INSTR_Z		0x90

#define KEY_REG_RANGE_BEGIN 24
#define KEY_REG_RANGE_END 39
#define RESERVED_KEYWORDS 145 
static const char *reserved[RESERVED_KEYWORDS] = {
	"byte","word","dword","qword",
	"add","adc","adiw","sub",
	"subi","sbc","sbci","sbiw",
	"and","andi","or","ori", // combine and/andi and or/ori?
	"eor","com","neg","sbr", // I would also like eor to be called xor
	"cbr","inc","dec","tst",
	"clr","ser","push","pop",
	"jmp","ijmp","call","icall",
	"rjmp","rcall","ret","reti",
	"cpse","cp","cpc","cpi",
	"sbrc","sbrs","sbic","sbis",
	"brbs","brbc","breq","brne",
	"brcs","brcc","brsh","brlo",
	"brmi","brpl","brge","brlt",
	"brhs","brhc","brts","brtc",
	"brvs","brvc","brie","brid",
	"ld","st","mov","ldi",
	"in","out","lpm","sbi",
	"cbi","lsl","lsr","rol",
	"ror","asr","swap","bset",
	"bclr","bst","bld","sec",
	"clc","sen","cln","sez",
	"clz","sei","cli","ses",
	"cls","sev","clv","set",
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
