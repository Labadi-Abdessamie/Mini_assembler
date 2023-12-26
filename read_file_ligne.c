#include "register_map.c"
#include "fonctions.c"

#define MAX_LENGTH_LINE 256;


int main()
{
    FILE *ptr_file;

    //! open the files
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
                
                if(buffer[0]=='.' && buffer[1]=='t') goto text;
                
                char* nom=(char*)malloc(10*sizeof(char));
                char* type=(char*)malloc(10*sizeof(char));
                    //! the variable syntax must be var_name : .type 
                if(sscanf(buffer,"%s : .%s",nom,type)==2){
                    data=Insertion_variable(data,nom,data_counter);
                    
                    if(strcmp(type,"word")==0) data_counter+=4;
                    else if(strcmp(type,"half")==0) data_counter+=2;
                    else if(strcmp(type,"byte")==0) data_counter+=1;
                    else if(strcmp(type,"asciiz")==0) {
                        char* value=(char*)malloc(20*sizeof(char));
                        sscanf(buffer,"%*s : .%*s %s", value);
                        int len=strlen(value)-1;
                        data_counter+=len;
                    }
                    else if(strcmp(type,"space")==0) {
                        char* value=(char*)malloc(20*sizeof(char));
                        sscanf(buffer,"%*s : .%*s %s", value);
                        int len=atoi(value);
                        data_counter+=len;
                    }
                    
                }
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
                        hexa(instr_reg);
                    }
                    Program_counter+=4;
            }
            
            else if (strcmp(I_search(instruction), "null") || strcmp(instruction,"la")==0)
            {
                    if (sscanf(buffer, "%s %s ", instruction,registers) == 2){
                        char des[10],src[10],imm[10];
                        char *regdes= des;
                        char *regsrc= src;
                        char *immed= imm;
                        sscanf(registers,"%3[^,],%3[^,],%s",regdes,regsrc,immed);
                        
                        if(strcmp(instruction,"andi")==0 || strcmp(instruction,"ori")==0){
                            if(immed[0]=='-'){
                                strcpy(instr_reg,I_format("lui","$at","-1",immed));
                                hexa(instr_reg);    
                                Program_counter+=4;
                                strcpy(instr_reg,I_format("ori","$at","$at",immed));
                                hexa(instr_reg);    
                                Program_counter+=4;
                                strcat(regdes,",");
                                strcat(regdes,regsrc);
                                char* temp=(char*)malloc(4*sizeof(char));
                                temp = (strcmp(instruction,"andi")==0) ? "and" : "or";
                                strcpy(instr_reg,R_format(temp,strcat(regdes,",$at")));
                                hexa(instr_reg);    
                                Program_counter+=4;
                            }
                            else{
                                strcpy(instr_reg,I_format(instruction,regdes,regsrc,immed));
                                hexa(instr_reg);    Program_counter+=4;
                            }
                        }
                        else if(strcmp(instruction,"lw")==0 || strcmp(instruction,"sw")==0){
                        
                        
                        }
                        else if(strcmp(instruction,"beq")==0){
                        
                        
                        }
                        else {
                                strcpy(instr_reg,I_format(instruction,regdes,regsrc,immed));    
                                hexa(instr_reg);    Program_counter+=4;
                        }
                    }
                    
            }
            else if (strcmp(J_search(instruction), "null"))
            {
                    
                    if (sscanf(buffer, "%s %s ", instruction,registers) == 2){
                        printf("ins = %s  regs=%s    \n",instruction,registers);    
                    }
                    Program_counter+=4;
            }
            else if (!strcmp(instruction, "syscall"))
            {
                    strcpy(instr_reg,"00000000000000000000000000001100");
                    hexa(instr_reg);
                    Program_counter+=4;
            }
            else
            {       //! the label must write like label_name :
                    labels=insertion_label(labels,instruction,Program_counter);
            }
        }
    }
    
            while (data!=NULL)
            {
                char hexadecimal_result[10];
            sprintf(hexadecimal_result, "%lX",(unsigned long) data->adress);
            printf("%s  =  %s \n",data->nom,hexadecimal_result);
            data=data->suiv;
            }
            
            while (labels!=NULL)
            {
                char hexadecimal_result[10];
            sprintf(hexadecimal_result, "%lX",(unsigned long) labels->adress);
            printf("%s  =  %s \n",labels->nom,hexadecimal_result);
            labels=labels->suiv;
            }
            char hexadecimal_result[10];
            sprintf(hexadecimal_result, "%lX",(unsigned long) Program_counter);
            printf("%s",hexadecimal_result);

    fclose(ptr_file);

    return 0;
}
