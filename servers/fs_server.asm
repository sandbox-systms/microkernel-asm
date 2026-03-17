; ==========================================
; Drivers e sistemas rodando fora do kernel 
; ==========================================

fs_server: 
    call wait_message 
    call process_request

    jmp fs_main 

