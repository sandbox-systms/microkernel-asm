; =========================================
; KERNEL.INC — MICROKERNEL x86-64
; =========================================

; -----------------------------------------
; MODOS / SEGMENTOS
; -----------------------------------------

KERNEL_LOAD_ADDR    equ 0x100000        ; kernel em 1MB
STACK_TOP           equ 0x80000

; Segment selectors (GDT)
KERNEL_CS           equ 0x08
KERNEL_DS           equ 0x10

; -----------------------------------------
; MEMÓRIA
; -----------------------------------------

PAGE_SIZE           equ 4096
PAGE_SHIFT          equ 12

MEMORY_BASE         equ 0x100000
MEMORY_LIMIT        equ 0x800000        ; 8MB inicial

; Alinhamento
ALIGN_4K            equ 0x1000

; -----------------------------------------
; PAGINAÇÃO (base para x86-64)
; -----------------------------------------

PML4_ENTRIES        equ 512
PDPT_ENTRIES        equ 512
PD_ENTRIES          equ 512
PT_ENTRIES          equ 512

PAGE_PRESENT        equ 1
PAGE_WRITE          equ 2
PAGE_USER           equ 4

; -----------------------------------------
; VGA DEBUG (fallback)
; -----------------------------------------

VGA_BUFFER          equ 0xB8000
VGA_COLS            equ 80
VGA_ROWS            equ 25

VGA_ATTR            equ 0x0F

; -----------------------------------------
; SERIAL DEBUG (essencial em kernel real)
; -----------------------------------------

COM1                equ 0x3F8

; -----------------------------------------
; TAREFAS (64-bit READY)
; -----------------------------------------

MAX_TASKS           equ 16

TASK_READY          equ 0
TASK_RUNNING        equ 1
TASK_BLOCKED        equ 2

struc TCB
    .rsp        resq 1      ; stack pointer 64-bit
    .rip        resq 1      ; instruction pointer
    .rflags     resq 1

    ; registradores gerais
    .rax        resq 1
    .rbx        resq 1
    .rcx        resq 1
    .rdx        resq 1
    .rsi        resq 1
    .rdi        resq 1
    .rbp        resq 1

    .state      resb 1
    .pad        resb 7      ; alinhamento
endstruc

TCB_SIZE equ TCB_size

; -----------------------------------------
; IPC (mensagens reais)
; -----------------------------------------

MSG_MAX_DATA       equ 32

struc MESSAGE
    .src        resb 1
    .dst        resb 1
    .type       resb 1
    .size       resb 1
    .data       resb MSG_MAX_DATA
endstruc

MSG_SIZE equ MESSAGE_size

; -----------------------------------------
; INTERRUPÇÕES
; -----------------------------------------

IDT_ENTRIES        equ 256

; -----------------------------------------
; PORTAS IMPORTANTES
; -----------------------------------------

PIC1_CMD           equ 0x20
PIC1_DATA          equ 0x21

PIC2_CMD           equ 0xA0
PIC2_DATA          equ 0xA1

PIT_CHANNEL0       equ 0x40
PIT_COMMAND        equ 0x43

KEYBOARD_PORT      equ 0x60

; -----------------------------------------
; MACROS CRÍTICAS
; -----------------------------------------

%macro CLI 0
    cli
%endmacro

%macro STI 0
    sti
%endmacro

%macro HLT 0
    hlt
%endmacro

; -----------------------------------------
; CONTEXTO (SAVE / RESTORE)
; -----------------------------------------

%macro SAVE_CONTEXT 0
    push rax
    push rbx
    push rcx
    push rdx
    push rsi
    push rdi
    push rbp
%endmacro

%macro RESTORE_CONTEXT 0
    pop rbp
    pop rdi
    pop rsi
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro

; -----------------------------------------
; SERIAL OUTPUT
; -----------------------------------------

%macro serial_init 0
    mov dx, COM1 + 1
    mov al, 0x00
    out dx, al

    mov dx, COM1 + 3
    mov al, 0x80
    out dx, al

    mov dx, COM1 + 0
    mov al, 0x03
    out dx, al

    mov dx, COM1 + 1
    mov al, 0x00
    out dx, al

    mov dx, COM1 + 3
    mov al, 0x03
    out dx, al
%endmacro

%macro serial_write 1
.wait:
    mov dx, COM1 + 5
    in al, dx
    test al, 0x20
    jz .wait

    mov dx, COM1
    mov al, %1
    out dx, al
%endmacro

; -----------------------------------------
; DEBUG / PANIC
; -----------------------------------------

%macro PANIC 1
    cli
    mov rsi, %1
    call print_string
    
.hang:
    hlt
    jmp .hang
%endmacro