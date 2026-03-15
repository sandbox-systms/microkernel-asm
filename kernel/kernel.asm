; ==========================================
; Responsavel por inicializar o subsistema
; ==========================================

[bits 16]

start;

call int_memory
call int_scheduler
call int_ipc

call start_servers

halt:
jmp halt 