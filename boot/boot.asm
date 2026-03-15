; =======================================================================
; Primeira instrução a ser executada pela CPU/Processador. 
; Ela carrega o endereço do próximo código a ser executado. 
; =======================================================================

org 0x7c000 

mov ah, 0x02 
mov al, 10
mov ch, 0
mov cl, 2
mov dh, 0 
mov bx, 0x1000
int 0x13

jmp 0x00000:0x1000

times 510-($-$$) db 0
dw 0xaa55

; ====================================================================================================================================
; O código acima é um exemplo de um setor de boot (boot sector) para um sistema operacional.
; Ele é carregado pela BIOS quando o computador é ligado. O código realiza as seguintes ações:

; 1. Define a origem do código a ser carregado (0x7c00).
; 2. Usa a interrupção 0x13 para ler o segundo setor do disco (setor 2) para o endereço de memória 0x1000.
; 3. Salta para o endereço 0x1000, onde o próximo código do sistema operacional deve estar localizado.
; 4. Preenche o restante do setor de boot com zeros e adiciona a assinatura de boot (0xaa55) no final, indicando que é um setor de boot válido.
; ====================================================================================================================================
