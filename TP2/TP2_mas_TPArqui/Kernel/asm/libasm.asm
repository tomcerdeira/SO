GLOBAL cpuVendor
GLOBAL getDay
GLOBAL getMonth
GLOBAL getYear
GLOBAL getHour
GLOBAL getMins
GLOBAL getSeconds
GLOBAL readKeyboard
GLOBAL getMemory
GLOBAL getSP
GLOBAL snapShotRegister
GLOBAL timerTickInterrupt

EXTERN saveSnapShotRegister
section .text
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
	;push gs
%endmacro

%macro	popState 0
	;;pop gs;0
	;;pop fs;1
	pop r15;2
	pop r14;3
	pop r13;4
	pop r12;5
	pop r11;6
	pop r10;7
	pop r9;8
	pop r8;9
	pop rsi;10
	pop rdi;11
	pop rbp;12
	pop rdx;13
	pop rcx;14
	pop rbx;15
	pop rax;16
%endmacro
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret

;; Funcion que devuelve el puntero a la siguiente instruccion ("get stack pointer")
getSP:
	mov rax,rsp
	ret

snapShotRegister:
	pushState
	mov rdi,rsp
	call saveSnapShotRegister

	popState
	ret






;; FUNCIONES PARA EL CLOCK (Dia - Mes - Ano / Hora - Minutos - Segundos) ;;
;; http://helppc.netcore2k.net/hardware/cmos-clock

getDay:
	push rbp
	mov rbp,rsp
	
	mov rax,0
	mov al,6
	out 70h,al
	mov rax,0
	in al,71h

	mov rsp,rbp
	pop rbp
	ret

getMonth:
	push rbp
	mov rbp,rsp
	
	mov rax,0
	mov al,8
	out 70h,al
	mov rax,0
	in al,71h

	mov rsp,rbp
	pop rbp
	ret

getYear:
	push rbp
	mov rbp,rsp
	
	mov rax,0
	mov al,9
	out 70h,al
	mov rax,0
	in al,71h

	mov rsp,rbp
	pop rbp
	ret

getHour: ; recordar que clock me devuelve la hora en formato BCD de 8 bits, los primeros 4 bits son las decena y el resto las u
	push rbp
	mov rbp,rsp
	
	mov rax,0
	mov al,4
	out 70h,al
	mov rax,0
	in al,71h

	mov rsp,rbp
	pop rbp
	ret

getMins:
	push rbp
	mov rbp,rsp
	
	mov rax,0
	mov al,2
	out 70h,al
	mov rax,0
	in al,71h

	mov rsp,rbp
	pop rbp
	ret

getSeconds:
	push rbp
	mov rbp,rsp
	
	mov rax,0
	mov al,0
	out 70h,al
	mov rax,0
	in al,71h

	mov rsp,rbp
	pop rbp
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


readKeyboard:
	xor rax, rax
	in al, 64h
	and al, 1 ;Me quedo con el ultimo bit
	test al, al
	jz .end
	in al, 60h
	.end:
	ret


getMemory:
	mov rax,rsi
	ret

timerTickInterrupt:
  int 0x20
  ret


