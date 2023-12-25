#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <C:\Users\user\Desktop\inf\2LMD-INF\TP\Archi\Mini_assembler\register_map.c>

#define MAX_LENGTH_LINE 256;



int main()
{
    FILE *ptr_file;

    //! open the file
    ptr_file = fopen("code.txt", "r");

    if (ptr_file == NULL)
    {
        printf("Problem to open the file");
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
                
                //! ignore the line and go to the first instruction
                continue;

            }
            if (buffer[1] == 'd')
            {   

                while(fgets(buffer, 256, ptr_file) != NULL ){
                
                if(buffer[0]=='.') goto text;
                
                char* nom=(char*)malloc(10*sizeof(char));
                char* type=(char*)malloc(10*sizeof(char));
                    //! the variable syntax must be var_name : .type 
                if(sscanf(buffer,"%s : .%s",nom,type)==2){
                    data=Insertion_variable(data,nom,data_counter);
                    
                    if(strcmp(type,"word")==0) data_counter+=4;
                    
                    else if(strcmp(type,"asciiz")==0) data_counter+=3;
                
                }

                //! calcule l'address de variable w  le inserer dans la liste
                
                }
                //! save all the variables names and theire adrress 
                //! their adress means like a PC but for the data he has his own way to move +3 or +4
                
                continue;
            }
        }
        char Instr_reg[33];
        char *instr_reg=Instr_reg;
        char Registers[10];
        char *registers = Registers;
        
        char inst[5];
        char *instruction = inst;
        if (sscanf(buffer, "%s", instruction) == 1)
        {
            if(strcmp(instruction,"la")==0){
                    //!handle two instruction lui  and ori    lui i think it is a fixed statement 
                    //!  but the ori is a little complicated because you must know the place of your label
                    //! to  know the place of the label or the variable you must do something like the 
                    //! program counter begin from the .data and increase (but how to increase )
                    //! each type increase a different amount .
            }
            else if(strcmp(R_search(instruction), "null"))
            {   
                    if (sscanf(buffer, "%s %s ", instruction,registers) == 2){
                           
                        strcpy(instr_reg,R_format(instruction,registers));
                        printf(" %s\n",instr_reg);
                    }
                    Program_counter+=4;
            }
            
            else if (strcmp(I_search(instruction), "null"))
            {
                    
                    if (sscanf(buffer, "%s %s ", instruction,registers) == 2){
                        printf("ins = %s  regs=%s    \n", instruction,registers);    
                    }

                    Program_counter+=4;
            }
            else if (strcmp(J_search(instruction), "null"))
            {
                    
                    if (sscanf(buffer, "%s %s ", instruction,registers) == 2){
                        printf("ins = %s  regs=%s    \n", instruction,registers);    
                    }
                    Program_counter+=4;
            }
            else if (!strcmp(instruction, "syscall"))
            {
                    strcpy(instr_reg,"00000000000000000000000000001100");
                    printf(" %s\n",instr_reg);
                    Program_counter+=4;
            }
            else
            {
                    printf("%s   %s\n", instruction, "label"); //! label
                    //! here we may have to create a global linked list to add the label and his adress
            }
        }
    }
    
    while (data!=NULL)
    {   
        char hexadecimal_result[8];
        sprintf(hexadecimal_result, "%lX",(unsigned long) data->adress);
        printf("\n%s = %s\n",data->nom,hexadecimal_result);
        data=data->suiv;  
    }
            char hexadecimal_result[10];
            sprintf(hexadecimal_result, "%lX",(unsigned long) Program_counter);
            printf("%s",hexadecimal_result);
    fclose(ptr_file);

    return 0;
}
