ldr r0,=0x20200028
mov r1,#50331648
add r2,r0,r1
stmed r5,{r0-r2}
andeq r0,r0,r0
