GLOBAL _xchg
GLOBAL _xadd

section .text

; enter_region:
;     push rbp
; 	mov rbp,rsp

;     push rax

;     mov rax, 1
;     xchg rax, LOCK
;     cmp rax, 0
;     jne enter_renter_region
;     ret

; leave_region:
;     mov LOCK, 0
;     ret

_xadd:
    mov rax,rdi
    lock xadd [rsi],eax
    ret

_xchg:
    mov rax,rsi
    xchg [rdi],eax
    ret

; section .data
; LOCK db 0


;Fuente: https://codebytez.blogspot.com/2005/08/semaphores-in-assembler-and-java.html
;acquire semaphore
;    xor     ax, ax      ; set AX to zero
;L1:
;    xchg    ax, sema    ; atomic test and set. sema = 0, ax = sema
;    or      ax, ax      ; is the value we obtained from sema 0?
;    jz      L1          ; yes, wait for someone to release semaphore
;    dec     ax          ; no, we got the semaphore.
;    xchg    ax, sema    ; decrease by one and store
;
;process stuff
;
; release semaphore
;    xchg    ax, sema    ; sema value may have been changed by other threads
;    inc     ax          ; bump to notify we have released it
;    xchg    ax, sema    ; atomic store