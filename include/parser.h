#define PARSE_STATE_OPEN 0
#define PARSE_STATE_ENTERING_DIRECTIVE 1
#define PARSE_STATE_ENTERING_SECTION 2
#define PARSE_STATE_IN_BLOCK 3
#define PARSE_STATE_IN_EXPRESSION 4
#define PARSE_STATE_DECLARATION 5
#define PARSE_STATE_IDENTIFIER 6

struct state
{
	qword current_state;
	qword previous_state;
	dword block_level;
	dword group_level;
	qword token_num;
};
