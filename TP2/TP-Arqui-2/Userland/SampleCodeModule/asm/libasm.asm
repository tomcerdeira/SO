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
 
   push rcx
   push r9
   push r10
   mov r9,rdx
   mov r10, rcx
 
   mov rcx,14
   int 80h
 
   pop r10
   pop r9
   pop rcx
 
   mov rsp,rbp
   pop rbp
   ret
