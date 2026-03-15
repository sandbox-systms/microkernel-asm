; =========================================
; Definição de qual tarefa será executada:
; Modelo simple round-robin 
; =========================================

init_scheduler: 

    mov byte [current_task], 0
    ret 

scheduler:

    inc byte [current_task]
    cmp byte [current_task], MAX_TASKS 
    jl done 

    mov byte [current_tasks], 0

done:
    ret 

    MAX_TASKS equ 4
    current_tasks db 0 