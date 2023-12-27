#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stddef.h>
#include<ctype.h>

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
		{ "$ra", "11111" }
};

struct {
	const char *name;
	const char *funct_code;
} R_instr[7] = {
		{ "add", "100000" },
		{ "sub", "100010" },
		{ "or", "100101" },
		{ "and", "100100" },
		{ "slt", "101010" },
		{ "sll", "000000" }, 
		{ "jr", "001000" },  
};

struct {
    const char *name;
    const char *op_code;
} I_instr[8] = {
		{ "lw", "100011" },		
		{ "sw", "101011" },
		{ "beq", "000100" },
    	{ "lui", "001111" },
		{ "addi", "001000" },
		{ "slti", "001010" },
		{ "ori", "001101" },
		{ "andi", "001100" },
};

struct {
	const char *name;
	const char *op_code;
} J_instr[2] = {
		{ "j", "000010" },
		{ "jal", "000011" },
};

const char* R_search(const char * instruction){
    for(int i=0;i<7;i++){
        if(strcmp(instruction,R_instr[i].name)==0) return R_instr[i].funct_code;
    }
    return "null";
}

const char* I_search(const char * instruction){
    for(int i=0;i<8;i++){
        if(strcmp(instruction,I_instr[i].name)==0) return I_instr[i].op_code;
    }
    return "null";
}

const char* J_search(const char * instruction){
	for(int i=0;i<2;i++){
        if(strcmp(instruction,J_instr[i].name)==0) return J_instr[i].op_code;
    }
    return "null";
}

const char* reg_search(const char* reg){
	for(int i=0;i<27;i++){
        if(strcmp(reg,reg_Map[i].name)==0) return reg_Map[i].bnr_rep;
    }
    return "null";
}