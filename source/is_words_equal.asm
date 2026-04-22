section .text

global is_words_equal_asm

;---------------------------------------------------------------------------------------------------------------------------------
; Checks if the words are the same. Return 1 if yes and 0 if not.
;
; Arguments: 
;   rdi = first word
;   rsi = second word
;
; Return value:
;   eax = 0 or 1 (check result)
;
; Destroy:
;   rdi, rsi
;---------------------------------------------------------------------------------------------------------------------------------

is_words_equal_asm: 

.loop:      mov al, [rdi]   ; AL = current letter in rdi
            mov dl, [rsi]   ; DL = current letter in rsi

            cmp al, dl
            jne .not_equal

            test al, al
            je .equal

            inc rdi
            inc rsi

            jmp .loop

.equal:     mov eax, 1
            ret

.not_equal: xor eax, eax
            ret
