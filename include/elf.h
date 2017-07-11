#define ELF_CLASS_32 0x01
#define ELF_CLASS_64 0x02

#define ELF_ENDIAN_LITTLE 0x01
#define ELF_ENDIAN_BIG 0x02

#define	ELF_ABI_SYSV	0x00 
#define	ELF_ABI_HPUX	0x01 
#define	ELF_ABI_NETBSD	0x02 
#define	ELF_ABI_LINUX	0x03 
#define	ELF_ABI_HURD	0x04 
#define	ELF_ABI_SOLARIS	0x06 
#define	ELF_ABI_AIX		0x07 
#define	ELF_ABI_IRIX	0x08 
#define	ELF_ABI_FREEBSD	0x09 
#define	ELF_ABI_TRU64	0x0A 
#define	ELF_ABI_MODESTO	0x0B 
#define	ELF_ABI_OPENBSD	0x0C 
#define	ELF_ABI_OPENVMS	0x0D 
#define	ELF_ABI_NONSTOP	0x0E 
#define	ELF_ABI_AROS	0x0F 
#define	ELF_ABI_FENIX	0x10 
#define	ELF_ABI_CLOUD	0x11 
#define	ELF_ABI_SORTIX	0x53 

#define ELF_TYPE_RELOCATABLE 1
#define ELF_TYPE_EXECUTABLE 2
#define ELF_TYPE_SHARED 3
#define ELF_TYPE_CORE 4

#define	ELF_ISA_NONE	0x00 
#define	ELF_ISA_SPARC	0x02 
#define	ELF_ISA_X86		0x03 
#define	ELF_ISA_MIPS	0x08 
#define	ELF_ISA_PPC		0x14 
#define	ELF_ISA_ARM		0x28 
#define	ELF_ISA_SUPERH	0x2A 
#define	ELF_ISA_IA64	0x32 
#define	ELF_ISA_X86_64	0x3E 
#define	ELF_ISA_ARM64	0xB7 
#define	ELF_ISA_RISCV	0xF3 

struct elf_header
{
	int		magic;
	char	class;
	char	endian;
	char	version;
	char	abi; // OS
	char	abi_version; // unused in Linux
	char	pad[7];
	short	type;
	short	isa; //instruction set
	int		lversion; // same as version
	long	entry; // entry point
	long	ph_offset; // program header offset
	long	sh_offset; // section header offset
	int		flags;
	short	eh_size; // size of this header - 64 or 52
	short	ph_entry_size;
	short	ph_number;
	short	sh_entry_size;
	short	sh_number;
	short	sh_sect_index; // index of section header entry containing names
};

#define	ELF_PROG_TYPE_NULL
#define	ELF_PROG_TYPE_LOAD
#define	ELF_PROG_TYPE_DYNAMIC
#define	ELF_PROG_TYPE_INTERP
#define	ELF_PROG_TYPE_NOTE
#define	ELF_PROG_TYPE_SHLIB
#define	ELF_PROG_TYPE_PHDR
#define	ELF_PROG_TYPE_LOOS
#define	ELF_PROG_TYPE_HIOS
#define	ELF_PROG_TYPE_LOPROC
#define	ELF_PROG_TYPE_HIPROC

struct elf_program_header
{
	int		type; //	0-3 	Type of segment (see below)
	int		flags; //	4-7 	Flags (see below)
	long	offset; //	8-15 	The offset in the file that the data for this segment can be found (p_offset)
	long	vaddr; //	16-23 	Where you should start to put this segment in virtual memory (p_vaddr)
	long	paddr; //	24-31 	Undefined for the System V ABI
	long	fsize; //	32-39 	Size of the segment in the file (p_filesz)
	long	msize; //	40-47 	Size of the segment in memory (p_memsz)
	long	align; //	48-55 	The required alignment for this section (must be a power of 2) 
};

#define	ELF_SECT_FLAG_EXEC 1
#define	ELF_SECT_FLAG_WRIT 2
#define	ELF_SECT_FLAG_READ 4

#define	ELF_SECT_TYPE_
#define ELF_SECT_TYPE_NULL			0x00	// Section header table entry unused
#define ELF_SECT_TYPE_PROGBITS		0x01	// Program data
#define ELF_SECT_TYPE_SYMTAB		0x02	// Symbol table
#define ELF_SECT_TYPE_STRTAB		0x03	// String table
#define ELF_SECT_TYPE_RELA			0x04	// Relocation entries with addends
#define ELF_SECT_TYPE_HASH			0x05	// Symbol hash table
#define ELF_SECT_TYPE_DYNAMIC		0x06	// Dynamic linking information
#define ELF_SECT_TYPE_NOTE			0x07	// Notes
#define ELF_SECT_TYPE_NOBITS		0x08	// Program space with no data (bss)
#define ELF_SECT_TYPE_REL			0x09	// Relocation entries, no addends
#define ELF_SECT_TYPE_SHLIB			0x0A	// Reserved
#define ELF_SECT_TYPE_DYNSYM		0x0B	// Dynamic linker symbol table
#define ELF_SECT_TYPE_INIT_ARRAY	0x0E	// Array of constructors
#define ELF_SECT_TYPE_FINI_ARRAY	0x0F	// Array of destructors
#define ELF_SECT_TYPE_PREINIT_ARRAY	0x10	// Array of pre-constructors
#define ELF_SECT_TYPE_GROUP			0x11	// Section group
#define ELF_SECT_TYPE_SYMTAB_SHNDX	0x12	// Extended section indeces
#define ELF_SECT_TYPE_NUM			0x13	// Number of defined types.

struct elf_section_header
{
	int		name;
	int		type;
	long	flags;
	long	vaddr;
	long	offset;
	long	size;
	int		link;
	int		info;
	long	align;
	long	ent_size;
};
