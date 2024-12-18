.intel_syntax noprefix
.text
.global sum

sum:
  mov r8d, ecx // В r8d указатель на массив R
  mov ecx, edi // В ecx итератор цикла (изначально это у нас N)


loopa:
  mov eax, [esi + ecx * 4 - 4]
  add eax, [edx + ecx * 4 - 4]
  mov [r8d + ecx * 4 - 4], eax

loop loopa
ret
