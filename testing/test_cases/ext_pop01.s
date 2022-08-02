mov r11, #2
mov r6, #4
ldr r10, [r0, #8]
mul r12,r11,r6
push {r9-r12}
pop {r0-r3}
