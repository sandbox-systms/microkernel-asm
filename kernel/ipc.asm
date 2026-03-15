; ==============================================
; Comunicação entre processos - elemento central
; ==============================================

inc_send:

    mov [msg_buffer], ax
    ret

ipc_receive:

    mov ax, [msg_buffer]
    ret 

    msg_buffer dw 0