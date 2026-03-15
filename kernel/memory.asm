; ============================================
; Responsavel por paginas e blocos simples 
; ============================================

init_memory:

    mov ax, 0x2000
    mov [free_mem], ax

    ret

alloc_page:

    mov ax, [free_mem]
    add word [free_mem], 4096

    ret

    free_mem dw 0