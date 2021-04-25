GLOBAL initStack

section .text

; uint64_t * initStack(int argc, char * argv[], uint64_t * rsp, void * main)
initStack:

    mov rbx, rsp ;hago un backup del sp actual
    mov rsp, rdx ;cambio el sp al del nuevo proceso

    push 0x0
    push rdx     ;RBP pasado como param
    push 0x202
    push 0x8
    push rcx     ;main

    ; push ; REGS
    push 1
	push 2
	push 3
	push 4
	push 5

    push rdi   ;RDI --> argc
    push rsi   ;RSI --> argv

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
