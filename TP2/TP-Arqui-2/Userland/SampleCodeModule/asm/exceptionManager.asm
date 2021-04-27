GLOBAL _opCodeException

section .text 

; https://www.felixcloutier.com/x86/ud
_opCodeException:
    UD2
    ret