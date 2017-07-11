#define HOST_NONE 1
#define HOST_LINUX 0
#define HOST_BITS8 1
#define HOST_BITS16 0
#define HOST_BITS32 0
#define HOST_BITS64 0
#define HOST_BITS128 0

#if (HOST_BITS8)
	typedef unsigned long long qword;
	typedef unsigned long	dword;
	typedef unsigned int	word;
	typedef unsigned char	byte;
#endif
#if (HOST_BITS64)
	typedef unsigned long	qword;
	typedef unsigned int	dword;
	typedef unsigned short	word;
	typedef unsigned char	byte;
#endif
