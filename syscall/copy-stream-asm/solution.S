.intel_syntax noprefix
.global _start
.text

_start:
  mov rbx, 0 // read size

read_loop:
  mov rax, 0 // read
  mov rdi, 0
  lea rsi, [buffer]
  mov rdx, 1024
  syscall

  mov rbx, rax
  cmp rbx, -1
  je exit_fail

  cmp rbx, 0
  je exit_success

  mov rax, 1 // write
  mov rdi, 1
  lea rsi, [buffer]
  mov rdx, rbx
  syscall

  cmp rax, -1
  je exit_fail

  jmp read_loop

exit_success:
  mov rax, 60
  mov rdi, 0
  syscall
  jmp end

exit_fail:
  mov rax, 60
  mov rdi, 1
  syscall

end:

.data
buffer:
  .fill 1024, 1, 0