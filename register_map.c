#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct {
    const char *name;
    const char *bnr_rep;
} reg_Map[27] = {
        { "$zero", "00000" },
        { "$at", "00001" },
		{ "$v0", "00010" },
		{ "$v1", "00011" },
		{ "$a0", "00100" },
		{ "$a1", "00101" },
		{ "$a2", "00110" },
		{ "$a3", "00111" },
		{ "$t0", "01000" },
		{ "$t1", "01001" },
		{ "$t2", "01010" },
		{ "$t3", "01011" },
		{ "$t4", "01100" },
		{ "$t5", "01101" },
		{ "$t6", "01110" },
		{ "$t7", "01111" },
		{ "$s0", "10000" },
		{ "$s1", "10001" },
		{ "$s2", "10010" },
		{ "$s3", "10011" },
		{ "$s4", "10100" },
		{ "$s5", "10101" },
		{ "$s6", "10110" },
		{ "$s7", "10111" },
		{ "$t8", "11000" },
		{ "$t9", "11001" },
		{ "NULL" , "0" },
};

struct {
	const char *name;
	const char *funct_code;
} R_instr[8] = {
		{ "add", "100000" },
		{ "sub", "100010" },
		{ "or", "100101" },
		{ "and", "100100" },
		{ "slt", "101010" },
		{ "sll", "000000" },
		{ "jr", "001000" },
		{ "NULL", "0" },
};

struct {
    const char *name;
    const char *op_code;
} I_instr[9] = {
        { "lui", "001111" },
		{ "lw", "100011" },
		{ "sw", "101011" },
		{ "addi", "001000" },
		{ "ori", "001101" },
		{ "andi", "001100" },
		{ "slti", "001001" },
		{ "beq", "000100" },
		{ "NULL", "0" },
};

struct {
	const char *name;
	const char *op_code;
} J_instr[3] = {
		{ "j", "000010" },
		{ "jal", "000011" },
		{ "NULL", "0" },
};







/*
void main(){
    int i;
    char *instruction = "andi";    

   		if(!strcmp(instruction,"la"))
        {   
                i=0;
                while(i<26 && strcmp("lui",instr_Map[i].name)){
                i++;
                }
                printf("\n op code = %s",instr_Map[i].ins_op_code);
                i=0;
                while(i<26 && strcmp("ori",instr_Map[i].name)){
                i++;
                }
                printf("\n op code = %s",instr_Map[i].ins_op_code);        
        }
    else{   
            i=0;
            while(i<26 && strcmp(instruction,instr_Map[i].name)){
            i++;
            }
            if(!strcmp("000000",instr_Map[i].ins_op_code))
                {
                    printf("\n op code = %s \n function_code = %s",instr_Map[i].ins_op_code,instr_Map[i].ins_funct_code);
                }
            else{
                    printf("\n op code = %s",instr_Map[i].ins_op_code);
            }
        }

    return ;
} 
*/