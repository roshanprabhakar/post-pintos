.section ".text.throwaway"

.global practice_writing_assembly

/*
  int fn(arg1, arg2, arg3)
  {
    if (arg1 > arg2)
    {
      arg1 -= arg2
      return arg1 & arg3;
    }
    else
    {
      return (arg1 & arg2) & 0x300;
    }
  }
 */
practice_writing_assembly:
  cmp x0, x1
  b.le else 
  sub x0, x0, x1
  and x0, x0, x2
  b end
else:  
  and x0, x1, x2
  ldr x3, =0x300
  orr x0, x0, x3
end:
  ret
