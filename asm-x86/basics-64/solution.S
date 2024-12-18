.intel_syntax noprefix

.data

input_mask:
  .string "%d"

input_data:
  .quad 0

output_mask:
  .string "%lld "

.text
.global very_important_function
.extern A

very_important_function:
  mov rcx, rdi
  mov r12, A
  xor r13, r13

  loopa:
    push rcx
    inc r13
    lea rdi, [input_mask]
    lea rsi, [input_data]
    xor rax, rax
    call scanf
    movsxd rax, [input_data]
    movsxd r14, [r12 + r13 * 4 - 4]
    imul r14
    lea rdi, [output_mask]
    mov rsi, rax
    xor rax, rax
    call printf
    pop rcx

  loop loopa
  ret
