    !   NAME : Mini Assembler works in specific form of code.txt
    !   The supported instructions : R : add,sub,and,or,slt,sll,jr
    !                                I : la,lw,sw,beq,andi,ori,slti,addi,lui,addui
    !                                J : j , jal
    !   The Authors :
        !- LABADI ABDESSAMIE    star1coach@gmail.com
        !- HAMDI MUSTAPHA
        !- KACEM MOHAMED KARIM BENABDELLAH
    !   The conditions of the code.txt
    !   Register syntax         >>>>>       with their names not their numbers >>>  $t1 (valid) $9 (invalid)
    !   Variable syntax         >>>>>       name : .type value
    !   label syntax            >>>>>       name :
    !   instruction syntax      >>>>>       ins(space)(registers/labels/variables/immediates)
    !                                       between each registers or reg-imm   reg-lab
    !                                       no spaces  just ,  Ex    beq $t1,$t0,end
