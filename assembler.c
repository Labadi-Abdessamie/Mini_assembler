#include <conio.h>
#include "register_map.c"
#include "fonctions.c"
#include "compile.c"
//yes
/*  
    !   NAME : Mini Assembler works in specific form of code.txt
    !   The supported instructions : R : add,sub,and,or,slt,sll,jr
    !                                I : la,lw,sw,beq,andi,ori,slti,addi,lui,addui
    !                                J : j , jal
    !   The Authors :
        !- LABADI ABDESSAMIE
        !- HAMDI MUSTAPHA
        !- KACEM MOHAMED KARIM BENABDELLAH
        !- MENDJOUR LOUNIS 
    !   The conditions of the code.txt
    !   Register syntax         >>>>>       with their names not their numbers >>>  $t1 (valid) $9 (invalid)
    !   Variable syntax         >>>>>       name : .type value
    !   label syntax            >>>>>       name :
    !   instruction syntax      >>>>>       ins(space)(registers/labels/variables/immediates)
    !                                       between each registers or reg-imm   reg-lab
    !                                       no spaces  just ,  Ex    beq $t1,$t0,end
*/           
int main()
{
    if(compile()==-1) exit(EXIT_FAILURE);

    FILE *ptr_file;
    FILE *out_file;

    //! open the files
    ptr_file = fopen("code.txt", "r");
    out_file = fopen("out.txt", "w");

    if (ptr_file == NULL)
    {
        printf("Problem to open the file");
        return -1;
    }
    if (out_file == NULL)
    {
        printf("Problem to open the out_file");
        return -1;
    }

    char buffer[257];
    double Program_counter;
    double data_counter=268500992;

    while (fgets(buffer, 256, ptr_file) != NULL)
    {
        if (buffer[0] == '.')
        {
            if (buffer[1] == 't')
            {
                text :                
                //! initialiser le PC = 0x00400000
                Program_counter=4194304;
                continue;
            }
            if (buffer[1] == 'd')
            {   
                while(fgets(buffer, 256, ptr_file) != NULL ){
                if(buffer[0]=='.' && buffer[1]=='t') goto text;
                }
                continue;
            }
        }
        char instr_reg[33];
        char registers[20];
        char instruction[20];

        if (sscanf(buffer, "%s", instruction) == 1)
        {
            if(strcmp(R_search(instruction), "null"))
            {   
                    if (sscanf(buffer, "%s %s ", instruction,registers) == 2){
                        
                        strcpy(instr_reg,R_format(instruction,registers));
                        Out(hexa(instr_reg),Program_counter,out_file);
                    }
                    Program_counter+=4;
            }
            else if (strcmp(I_search(instruction), "null") || strcmp(instruction,"la")==0)
            {
                    if (sscanf(buffer, "%s %s ", instruction,registers) == 2){
                        char des[10],src[15],imm[15];
                        char *regdes= des;
                        char *regsrc= src;
                        char *immed= imm;
                        sscanf(registers,"%3[^,],%14[^,],%s",regdes,regsrc,immed); 
                        
                        if(strcmp(instruction,"andi")==0 || strcmp(instruction,"ori")==0){
                            if(immed[0]=='-'){
                                strcpy(instr_reg,I_format("lui","$at","-1",immed));
                                Out(hexa(instr_reg),Program_counter,out_file);    
                                Program_counter+=4;
                                strcpy(instr_reg,I_format("ori","$at","$at",immed));
                                Out(hexa(instr_reg),Program_counter,out_file);    
                                Program_counter+=4;
                                strcat(regdes,",");
                                strcat(regdes,regsrc);
                                char* temp=(char*)malloc(4*sizeof(char));
                                temp = (strcmp(instruction,"andi")==0) ? "and" : "or";
                                strcpy(instr_reg,R_format(temp,strcat(regdes,",$at")));
                                Out(hexa(instr_reg),Program_counter,out_file);
                                Program_counter+=4;
                            }
                            else{
                                strcpy(instr_reg,I_format(instruction,regdes,regsrc,immed));
                                Out(hexa(instr_reg),Program_counter,out_file);    
                                Program_counter+=4;
                            }
                        }
                        else if(strcmp(instruction,"lw")==0 || strcmp(instruction,"sw")==0){
                            if(regsrc[0]=='-' || regsrc[0]=='(' || isdigit(regsrc[0]))
                            {   
                                if(regsrc[0]=='('){
                                sscanf(registers,"%3[^,],(%3[^)]",regdes,regsrc);
                                immed="0";
                                }
                                else 
                                sscanf(registers,"%3[^,],%9[^(](%3[^)]",regdes,immed,regsrc);
                                strcpy(instr_reg,I_format(instruction,regdes,regsrc,immed));
                                Out(hexa(instr_reg),Program_counter,out_file);
                                Program_counter+=4;
                            }
                            else{
                                char temp[10];
                                if(Var_search(regsrc)==-1){
                                    printf("Variable does not exist");
                                    exit(EXIT_FAILURE);
                                }
                                sprintf(temp, "%d", hexToDecimal(upper_bits(Var_search(regsrc))));
                                strcpy(instr_reg,I_format("lui","$at",temp,"-1"));
                                Out(hexa(instr_reg),Program_counter,out_file);
                                Program_counter+=4;
                                sprintf(temp, "%d", hexToDecimal(lower_bits(Var_search(regsrc))));
                                strcpy(instr_reg,I_format(instruction,regdes,"$at",temp));
                                Out(hexa(instr_reg),Program_counter,out_file);
                                Program_counter+=4;
                            }
                        }
                        else if(strcmp(instruction,"beq")==0){
                                char temp[10];
                                if(label_search(immed)==-1){
                                    printf("label does not exist");
                                    exit(EXIT_FAILURE);
                                }
                                signed int i =(label_search(immed)-(Program_counter+4))/4;
                                sprintf(temp, "%d", i );
                                strcpy(instr_reg,I_format(instruction,regdes,regsrc,temp));
                                Out(hexa(instr_reg),Program_counter,out_file);
                                Program_counter+=4;
                        }
                        else if(strcmp(instruction,"la")==0){
                                if(regsrc[0]=='-' || regsrc[0]=='(' || isdigit(regsrc[0])){
                                    if(regsrc[0]=='('){
                                        sscanf(registers,"%3[^,],(%3[^)]",regdes,regsrc);
                                        immed="0";
                                        strcpy(instr_reg,I_format("addi",regdes,regsrc,immed));
                                        Out(hexa(instr_reg),Program_counter,out_file);
                                        Program_counter+=4;      
                                    }        
                                    else{
                                        sscanf(registers,"%3[^,],%9[^(](%3[^)]",regdes,immed,regsrc);
                                        if(strcmp(regsrc,immed)==0){
                                        strcpy(instr_reg,I_format("addiu",regdes,"$zero",regsrc));
                                        Out(hexa(instr_reg),Program_counter,out_file);
                                        Program_counter+=4;  
                                        }
                                        else{
                                        strcpy(instr_reg,I_format("ori","$at","$zero",immed));
                                        Out(hexa(instr_reg),Program_counter,out_file);
                                        Program_counter+=4;
                                        strcat(regdes,",");
                                        strcat(regdes,regsrc);
                                        strcat(regdes,",$at");
                                        strcpy(instr_reg,R_format("add",regdes));
                                        Out(hexa(instr_reg),Program_counter,out_file);
                                        Program_counter+=4;
                                        }
                                    }
                                }
                                else{
                                    char temp[10];
                                    if(Var_search(regsrc)==-1){
                                    printf("Variable does not exist");
                                    exit(EXIT_FAILURE);
                                    }
                                    sprintf(temp, "%d", hexToDecimal(upper_bits(Var_search(regsrc))));
                                    strcpy(instr_reg,I_format("lui","$at",temp,"$zero"));    
                                    Out(hexa(instr_reg),Program_counter,out_file);    
                                    Program_counter+=4;
                                    sprintf(temp, "%d", hexToDecimal(lower_bits(Var_search(regsrc))));
                                    strcpy(instr_reg,I_format("ori",regdes,"$at",temp));
                                    Out(hexa(instr_reg),Program_counter,out_file);
                                    Program_counter+=4;
                                }
                        }
                        else if(strcmp(instruction,"addi")==0 || strcmp(instruction,"slti")==0){
                            strcpy(instr_reg,I_format(instruction,regdes,regsrc,immed));    
                            Out(hexa(instr_reg),Program_counter,out_file);
                            Program_counter+=4;
                        }
                        else 
                        {      
                            strcpy(instr_reg,I_format(instruction,regdes,regsrc,immed));    
                            Out(hexa(instr_reg),Program_counter,out_file);    
                            Program_counter+=4;
                        }
                    }
            }
            else if (strcmp(J_search(instruction), "null"))
            {
                    if (sscanf(buffer, "%s %s ", instruction,registers) == 2){
                        if(label_search(registers)==-1){
                        printf("label does not exist");
                        exit(EXIT_FAILURE);
                        }
                        strcpy(instr_reg,J_format(instruction,decimalToBinary26Bits(label_search(registers)/4)));
                        Out(hexa(instr_reg),Program_counter,out_file);
                        Program_counter+=4;
                    }
            }
            else if (!strcmp(instruction, "syscall"))
            {
                    strcpy(instr_reg,"00000000000000000000000000001100");
                    Out(hexa(instr_reg),Program_counter,out_file);
                    Program_counter+=4;
            }
        }
    }
    fclose(ptr_file);
    fclose(out_file);
    
     
    printf(" DONE \n");
    char answer;
    printf("Do you want more information (the adress of labels and the adress of varibles ) (Y/N)\n");
    answer=getch();
    if(answer=='Y' || answer=='y'){
        printf("The variables : \n");
        while (data!=NULL)
        {
        char hexadecimal_result[10];
        sprintf(hexadecimal_result, "0x%lX",(unsigned long) data->adress);
        printf("%s  =  %s \n",data->nom,hexadecimal_result);
        data=data->suiv;
        }
        printf("The labels : \n");
        while (labels!=NULL)
        {
        char hexadecimal_result[10];
        sprintf(hexadecimal_result, "0x%08lX",(unsigned long) labels->adress);
        printf("%s  =  %s \n",labels->nom,hexadecimal_result);
        labels=labels->suiv;
        }
    }
    system("pause");
    return 0;
}