GLOBAL initStack
 
section .text
 
; uint64_t * initStack(uint64_t * rsp, void * wrapper, void * func, int argc, char * argv[], int pid)
initStack:
 
   mov rbx, rsp ;hago un backup del sp actual
   mov rsp, rdi ;cambio el sp al del nuevo proceso
 
   push 0x0
   push rdi     ;RBP pasado como param
   push 0x202
   push 0x8
   push rsi     ;main
 
   ; push ; REGS
   push 1
   push 2
 
   push r9
   push r8
 
   push 5
 
   push rdx   ;RDI --> argc
   push rcx   ;RSI --> argv
 
   push 6
   push 7
   push 8
   push 9
   push 10
   push 11
   push 12
   push 13
   ; pusehamos numero ascendentes para debuggear facilmente
 
   mov rax, rsp ;en rax retorno la nueva posicion del rsp
   mov rsp, rbx ;vuelvo el sp al backup hecho al principio
 
   ret
