GLOBAL readKeyBuff
GLOBAL writeScreen
GLOBAL getTime
GLOBAL getRegisterState
GLOBAL getMemoryState
GLOBAL printFigure
GLOBAL deleteN
GLOBAL clearConsoleIn
GLOBAL getSecondsCronometro
GLOBAL setCronometro
GLOBAL disableCursor
GLOBAL setCursorUser
GLOBAL printRectangle
GLOBAL createP
GLOBAL getProcessPid
GLOBAL halt
GLOBAL nice
GLOBAL block
GLOBAL ps
GLOBAL test_sync
GLOBAL test_no_sync

;  par1 --> buffer donde esta lo que quiero escribir
;  par2 --> fileDescrpitor
;  par3 --> long del buffer
writeScreen:
    push rbp
    mov rbp,rsp
    push rcx
    mov rcx,0

    int 80h

    pop rcx
    mov rsp,rbp
    pop rbp

    ret

;par1 --> buffer donde escribir lo leido
;par2 --> long del buffer
readKeyBuff:
    push rbp
mov rbp,rsp
    push rcx
    mov rcx,1
    int 80h

    pop rcx
    mov rsp,rbp
    pop rbp
    ret


; par1 --> int * donde se copia lo pedido
; par 2 -->  si es 0 --> devuelve la hora, si es 1 --> devuelve los mins
; si es 2 --> devuelve los seconds
getTime:
    push rbp
    mov rbp,rsp
    push rcx
    mov rcx,2

    int 80h
    
    pop rcx
    mov rsp,rbp
    pop rbp
    ret


;par1 --> int * donde se copia el estado de los registros, debe tener al menos CANT_REGISTER espacio  
getRegisterState:
    push rbp
    mov rbp,rsp
    push rcx
    mov rcx,3

    int 80h
    pop rcx
    mov rsp,rbp
    pop rbp
    ret

;par1 --> int * de entrada salida
;par2 --> int que indica el principio del lugar de memoria pedido
getMemoryState:
    push rbp
    mov rbp,rsp
    push rcx
    mov rcx,4

    int 80h
    pop rcx
    mov rsp,rbp
    pop rbp
    ret



printFigure:
;     push rbp
;     mov rbp,rsp
;     ;push rcx
;     ;push r8
;     mov r8,rcx
;     mov rcx,6 ; syscall del printFigure

;     int 80h

;    ; pop r8
;    ; pop rcx
;     mov rsp,rbp
;     pop rbp
;     ret
    push rbp
    mov rbp,rsp
    push rcx
    push r8
    mov r8,rcx
    mov rcx,6 ; syscall del printFigure

    int 80h


    
    pop r8
     pop rcx
    mov rsp,rbp
    pop rbp
    ret

deleteN:

    push rbp
    mov rbp,rsp
    push rcx
    push rsi
    mov rcx,7
    mov rsi,rdi


    int 80h
    pop rcx
     pop rsi
    mov rsp,rbp
   
    pop rbp
    ret

clearConsoleIn:
     push rbp
    mov rbp,rsp
    push rcx
    push rsi
    mov rsi,rdi
    mov rcx,8

    int 80h
    
    pop rsi
    pop rcx
    mov rsp,rbp
    pop rbp
    ret

setCronometro:
    push rbp
    mov rbp,rsp
    push rcx
   ; push rsi
    ;mov rsi,rdi
    mov rcx,9

    int 80h

  ;  pop rsi
    pop rcx
    mov rsp,rbp
    pop rbp
    ret

getSecondsCronometro:
    push rbp
    mov rbp,rsp
    push rcx
    mov rcx,10

    int 80h

    pop rcx
    mov rsp,rbp
    pop rbp
    ret
setCursorUser:
    push rbp
    mov rbp,rsp
    push rcx
    push rdx
    
    mov rdx,rsi
    mov rsi,rdi

    mov rcx,11

    int 80h

    pop rdx
    pop rcx
    mov rsp,rbp
    pop rbp
    ret

disableCursor:
    push rbp
    mov rbp,rsp
    push rcx
    mov rcx,12

    int 80h

    pop rcx
    mov rsp,rbp
    pop rbp
    ret


 printRectangle:
    push rbp
    mov rbp,rsp
    push rcx
    push r9
    mov r9,rdx
    mov rcx,13

    int 80h

    pop r9
    pop rcx
    mov rsp,rbp
    pop rbp
    ret

; REVISARRR!!!!!!!!!!!!!!!!!!!!!!!!!!
createP:
   push rbp
   mov rbp,rsp

   push r8
   push r9
 
   mov r8, rsi
   mov r9, rcx
   mov rsi, rdx

   mov rcx, 14
   int 80h

   pop r9
   pop r8
 
   mov rsp,rbp
   pop rbp
   ret


getProcessPid:
    push rbp
    mov rbp,rsp

    push rcx

    mov rcx,15
    int 80h
    
    pop rcx

    mov rsp,rbp
    pop rbp
    ret


halt:
    push rbp
    mov rbp,rsp
    push rcx
    mov rcx, 16

    int 80h

    pop rcx
    mov rsp,rbp
    pop rbp
    ret

nice:
    push rbp
    mov rbp,rsp

    push rdx
    push rcx

    mov rdx, rdi
    mov rcx, 17

    int 80h

    pop rcx
    mov rsp,rbp
    pop rbp
    ret

block:
    push rbp
    mov rbp,rsp

    push rsi
    push rcx

    mov rsi, rdi
    mov rcx, 18

    int 80h

    pop rcx
    mov rsp,rbp
    pop rbp
    ret

ps:
    push rbp
    mov rbp,rsp

   
    push rcx

   
    mov rcx, 19

    int 80h

    pop rcx
    mov rsp,rbp
    pop rbp
    ret

test_sync:
    push rbp
    mov rbp,rsp

    push rcx

    mov rcx, 20

    int 80h

    pop rcx
    mov rsp,rbp
    pop rbp
    ret

test_no_sync:
    push rbp
    mov rbp,rsp

    push rcx

    mov rcx, 21

    int 80h

    pop rcx
    mov rsp,rbp
    pop rbp
    ret
