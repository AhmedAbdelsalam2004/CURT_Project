#ifndef STD_MACROS_H_INCLUDED
#define STD_MACROS_H_INCLUDED

#define setbit(Reg,bit) Reg|=(1<<bit)
#define togbit(Reg,bit) Reg^=(1<<bit)
#define clrbit(Reg,bit) Reg&=~(1<<bit)
#define Readbit(Reg,bit) ((Reg>>bit)&1)


#endif // STD_MACROS_H_INCLUDED
