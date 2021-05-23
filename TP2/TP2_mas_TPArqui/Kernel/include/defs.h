#ifndef _defs_
#define _defs_

#define ACS_PRESENT 0x80 // segmento presente en memoria
#define ACS_CSEG    0x18 // segmento de codigo
#define ACS_DSEG    0x10
#define ACS_READ    0X02
#define ACS_IDT     ACS_DSEG
#define ACS_INT_386  0X0E
#define ACS_INT (ACS_PRESENT | ACS_INT_386)

#define ACS_CODE (ACS_PRESENT | ACS_CSEG | ACS_READ)
#define ACS_DATA (ACS_PRESENT | ACS_CSEG | ACS_WRITE)
#define ACS_STACK (ACS_PRESENT | ACS_CSEG | ACS_WRITE)

#define PIT_FREQUENCY 100

#endif