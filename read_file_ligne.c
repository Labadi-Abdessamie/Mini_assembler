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

    while (fgets(buffer, 256, ptr_file) != NULL)
    {
        if (buffer[0] == '.')
        {
            if (buffer[1] == 't')
            {
                                
                //! initialiser le PC = 0x00400000
                Program_counter=00400000.;
                
                //! ignore the line and go to the first instruction
                continue;

            }
            if (buffer[1] == 'd')
            {
                break;
                //! save all the variables names and theire adrress 
                //! their adress means like a PC but for the data he has his own way to move +3 or +4
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
                    //printf("%s   %s\n", instruction, I_search(instruction));
                    if (sscanf(buffer, "%s %s ", instruction,registers) == 2){
                        printf("ins = %s  regs=%s    \n", instruction,registers);    
                    }

                    Program_counter+=4;
            }
            else if (strcmp(J_search(instruction), "null"))
            {
                    //printf("%s   %s\n", instruction, J_search(instruction));
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
            printf("%lf",Program_counter);
    fclose(ptr_file);

    return 0;
}
