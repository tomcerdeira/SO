GLOBAL initStack
 
section .text


%macro pushStateNoRAX 0
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
	;push fs
	;;push gs
%endmacro

%macro	popStateNoRAX 0
	;pop gs
	;pop fs
	pop r15 ;0
	pop r14;1
	pop r13;2
	pop r12;3
	pop r11;4
	pop r10;5
	pop r9;6
	pop r8;7
	pop rsi;8
	pop rdi;9
	pop rbp;10
	pop rdx;11
	pop rcx;12
	pop rbx;13
%endmacro
 
; uint64_t * initStack(uint64_t * rsp, void * wrapper, void * func, int argc, char * argv[], int pid)
initStack:
 
   pushStateNoRAX
   
   mov rbp, rsp ;hago un backup del sp actual
   mov rsp, rdi ;cambio el sp al del nuevo proceso
 
   push 0x0
   push rdi     ;RBP pasado como param
   push 0x202
   push 0x8
   push rsi     ;main
 
   
   push 1
   push 2
 
   push r9
   push r8
 
   push 5
 
   push rdx   ;RDI --> argc
   push rcx  ;RSI --> argv
 
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
   mov rsp,rbp ;vuelvo el sp al backup hecho al principio

   popStateNoRAX

   ret


