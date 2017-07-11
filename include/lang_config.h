#define LANG_MAINSPRING 0
#define LANG_MAINSPRING_PREPROCESSOR 1
#define LANG_MAINSPRING_ASSEMBLER 2

#ifndef LANG
	#define LANG LANG_MAINSPRING_ASSEMBLER
#endif

#if LANG == LANG_MAINSPRING
	#include "mainspring_lang.h"
#endif

#if LANG == LANG_MAINSPRING_PREPROCESSOR
	#include "preprocessor_lang.h"
#endif

#if LANG == LANG_MAINSPRING_ASSEMBLER
	#include "assembler_lang.h"
#endif
