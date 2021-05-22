GLOBAL _xchg
GLOBAL _xadd

section .text

_xadd:
    mov rax,rdi
    lock xadd [rsi],eax
    ret

_xchg:
    mov rax,rsi
    xchg [rdi],eax
    ret

