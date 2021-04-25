GLOBAL _cli
GLOBAL _sti
GLOBAL _hlt
GLOBAL _picMasterMask
GLOBAL _picSlaveMask
GLOBAL _irq0Handler
GLOBAL _irq80Handler
GLOBAL _irq1Handler
GLOBAL _excp0Handler
GLOBAL _excp6Handler

EXTERN sysHandler
EXTERN irqDispatcher
EXTERN exceptionDispatcher

section .text

_sti:
	sti
	ret

_cli:
	cli
	ret

_hlt:
	sti
	hlt
	ret

_picMasterMask:
	push rbp
	mov rbp,rsp

	mov ax,di
	out 21h,al

	mov rsp,rbp
	pop rbp
	retn
	
_picSlaveMask:
	push rbp
	mov rbp,rsp

	mov ax,di
	out 0A1h,al

	mov rsp,rbp
	pop rbp
	retn
%macro pushState 0
	push rax
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

%macro	popState 0
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
	pop rax;14
%endmacro


%macro irqHandlerMaster 1
	pushState
	push rbp
	mov rbp,rsp

	mov rdi, %1 ; pasaje de parametro
	mov rsi, rsp ;pasaje del Stack Frame
	
	call irqDispatcher
	mov rsp, rax

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro

%macro sysHandlerMaster 0
	pushState
	push rbp
	mov rbp,rsp
	push r8  ;se recibe le 6to parametro por stack
	mov r8,rbp

	call sysHandler

	; mov al,20h
	; out 20h,al
	pop r8
	mov rsp,rbp
	pop rbp
	popState
	iretq

%endmacro

%macro exceptionHandlerMaster 1

	pushState
	;push rbp
	;mov rbp,rsp

	mov rdi, %1 ; pasaje de parametro del numero de la excepcion
	mov rsi, rsp ; pasaje de parametro del puntero al stack
	
	
	call exceptionDispatcher
	
	; ; signal pic EOI (End of Interrupt)
	; mov al, 20h
	; out 20h, al
	
	;mov rsp,rbp
	;pop rbp
	popState
	iretq
	
%endmacro



_irq0Handler:
    irqHandlerMaster 0 ;Timer Tick

_irq1Handler:
	irqHandlerMaster 1 ;Teclado

; Las syscalls van a recibir por el registro 
; Rcx --> int que indique la syscall a ejecutar
;
_irq80Handler:
	 sysHandlerMaster

;;; EXCEPCIONES

_excp0Handler:
	exceptionHandlerMaster 0 ;Dividir por cero

_excp6Handler:
	exceptionHandlerMaster 6 ;Operacion invalida
