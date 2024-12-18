.text
.global sum

sum:
  ldr x3, [x2]
  add x2, x2, #4
  sub x1, x1, #1
  add x0, x0, x3
  cmp x1, #0
  bgt sum
  ret
