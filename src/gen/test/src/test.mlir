
module {
  func.func @bench() {
       %c0 = arith.constant 0 : index
       %c2 = arith.constant 0 : i1
       %c10 = arith.constant 77 : index
       %c1 = arith.constant 1 : index
       %r0 = arith.constant 0 : i64
       %r1 = arith.constant 0 : i16
       %r2 = arith.constant 0 : i32
       scf.for %r3 = %c0 to %c10 step %c1 {
   %r3_i32 = arith.index_cast %r3 : index to i32
           %r4 = arith.addi %r2, %r3_i32 : i32
       }
       %r5 = arith.subi %r1, %r1 : i16
       %r6 = arith.constant 1 : i16
       %r7 = arith.addi %r1, %r6 : i16
   %r9 = arith.extsi %c2 : i1 to i16
       %r8 = arith.cmpi ne, %r7, %r9 : i16
       %r10 = arith.select %r8, %r6, %r1 : i16
   %0 = arith.trunci %r5 : i16 to i1
   scf.if %0 {
          %r11 = arith.constant 1 : i64
          %r12 = arith.addi %r0, %r11 : i64
      %r14 = arith.extsi %c2 : i1 to i64
          %r13 = arith.cmpi ne, %r11, %r14 : i64
          %r15 = arith.extsi %r10 : i16 to i64
          %r16 = arith.select %r13, %r15, %r12 : i64
   
   } else {
          %r17 = arith.constant 0 : i32
          scf.for %r18 = %c0 to %c10 step %c1 {
      %r18_i32 = arith.index_cast %r18 : index to i32
              %r19 = arith.addi %r17, %r18_i32 : i32
          }
          %r20 = arith.muli %r6, %r6 : i16
          %r21 = arith.constant 1 : i1
          %r22 = arith.addi %r8, %r21 : i1
          %r23 = arith.select %r22, %r6, %r10 : i16
      %1 = arith.trunci %r1 : i16 to i1
      scf.if %1 {
             %r24 = arith.constant 1 : i16
             %r25 = arith.addi %r10, %r24 : i16
         %r27 = arith.extsi %c2 : i1 to i16
             %r26 = arith.cmpi ne, %r1, %r27 : i16
             %r28 = arith.extsi %r8 : i1 to i16
             %r29 = arith.select %r26, %r23, %r28 : i16
      
      } else {
             %r30 = arith.constant 0 : i8
             scf.for %r31 = %c0 to %c10 step %c1 {
         %r31_i8 = arith.index_cast %r31 : index to i8
                 %r32 = arith.addi %r30, %r31_i8 : i8
             }
             %r33 = arith.subi %r5, %r20 : i16
             %r34 = arith.constant 1 : i16
             %r35 = arith.addi %r5, %r34 : i16
         %r37 = arith.extsi %c2 : i1 to i16
             %r36 = arith.cmpi ne, %r1, %r37 : i16
             %r38 = arith.extsi %r8 : i1 to i16
             %r39 = arith.select %r36, %r1, %r38 : i16
         
         scf.if %r36 {
         
         } else {
         }
             %r40 = arith.subi %r7, %r6 : i16
             %r41 = arith.ori %r8, %r8 : i1
             %r42 = arith.constant 1 : i16
             %r43 = arith.subi %r33, %r42 : i16
         %r45 = arith.extsi %c2 : i1 to i16
             %r44 = arith.cmpi ne, %r34, %r45 : i16
             %r46 = arith.extsi %r22 : i1 to i16
             %r47 = arith.select %r44, %r23, %r46 : i16
             %r48 = arith.constant 0 : i16
             scf.for %r49 = %c0 to %c10 step %c1 {
         %r49_i16 = arith.index_cast %r49 : index to i16
                 %r50 = arith.addi %r48, %r49_i16 : i16
             }
      }
          %r51 = arith.subi %r6, %r9 : i16
      %r53 = arith.extsi %c2 : i1 to i16
          %r52 = arith.cmpi ne, %r6, %r53 : i16
          %r54 = arith.ori %r52, %r8 : i1
          %r55 = arith.constant 1 : i16
          %r56 = arith.addi %r51, %r55 : i16
      %r58 = arith.extsi %c2 : i1 to i16
          %r57 = arith.cmpi ne, %r53, %r58 : i16
          %r59 = arith.select %r57, %r10, %r9 : i16
          %r60 = arith.constant 0 : i32
          scf.for %r61 = %c0 to %c10 step %c1 {
      %r61_i32 = arith.index_cast %r61 : index to i32
              %r62 = arith.addi %r60, %r61_i32 : i32
          }
   }
       %r63 = arith.extsi %r6 : i16 to i64
       %r64 = arith.addi %r0, %r63 : i64
   %r66 = arith.extsi %c2 : i1 to i16
       %r65 = arith.cmpi ne, %r7, %r66 : i16
   %r68 = arith.extsi %c2 : i1 to i64
       %r67 = arith.cmpi ne, %r64, %r68 : i64
       %r69 = arith.ori %r65, %r67 : i1
       %r70 = arith.constant 1 : i64
       %r71 = arith.subi %r0, %r70 : i64
   %r73 = arith.extsi %c2 : i1 to i16
       %r72 = arith.cmpi ne, %r5, %r73 : i16
       %r74 = arith.extsi %r65 : i1 to i64
       %r75 = arith.select %r72, %r74, %r0 : i64
       %r76 = arith.constant 0 : i32
       scf.for %r77 = %c0 to %c10 step %c1 {
   %r77_i32 = arith.index_cast %r77 : index to i32
           %r78 = arith.addi %r76, %r77_i32 : i32
       }
       func.return
    }
}

