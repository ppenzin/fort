! RUN: %fort -emit-llvm -o - %s | FileCheck %s
PROGRAM gototest

1000 CONTINUE   ! CHECK: 0:
     GOTO 1000  ! CHECK: br label %0

     GOTO 2000
2000 CONTINUE

END
