#include<stdio.h>
#include<stdlib.h>
#define MEMSIZE 100



#define READ 10
#define WRITE 11
#define LOAD 20
#define STORE 21
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43


void execute(signed int mem[MEMSIZE]);
void showMemory(signed int mem[MEMSIZE]);
void enterProgram(signed int mem[MEMSIZE]);

int main()

{

    printf("***Симплетрон приветствует вас!***\n"); 
    signed int memory[MEMSIZE]={0};
    
    enterProgram(memory);
    
    execute(memory);
    
    showMemory(memory);


    return 0;
}

void enterProgram (signed int mem[MEMSIZE])
{
    FILE *progPtr;
    if ((progPtr=fopen("prog.sml","r"))==NULL) 
    {
            
        printf("Файл не найден.\n"); 
        
        exit(EXIT_SUCCESS);
            
    }
    
    int i=0;
    
    while(!feof(progPtr))
    {
        
        fscanf(progPtr,"%d",&mem[i]);
        i++;
    }
    
    fclose(progPtr);
    
    
    
    
}

void showMemory(signed int mem [MEMSIZE])
{
    for(int i = 0;i<MEMSIZE;i++)
    {
        if ((i%10==0)&&(i!=0)) printf("\n");
        printf("%+05d\t",mem[i]);
                
    } 
printf("\n");

}

void execute (signed int mem [MEMSIZE]/*, signed int * InRPtr, signed int * InCPtr*/)
{
    int operationCode;   //код операции
    int operandAddress;   //адрес операнда
    int instructionCounter=0; //адрес следующей инструкции
    int instructionRegister;
    int accumulator=0;
    
    
    do {
        
        instructionRegister=mem[instructionCounter];   
        operationCode = instructionRegister/100;
        operandAddress = instructionRegister%100;
        
        if (operationCode==HALT) 
        {
            printf("*** Симплетрон завершил свою работу ***\n"); 
            printf("accumulator = %d\n",accumulator);
            
            break;
        }

        else if (operationCode==READ) 
        {
            printf("Введите число от -9999 до +9999\n?>");
            scanf("%d",&mem[operandAddress]);
            printf("\n");
            instructionCounter++;
        }

        else if (operationCode==WRITE) 
        {
            printf(">%d\n\n",mem[operandAddress]);
            instructionCounter++;
        }
        else if (operationCode==LOAD) 
        {
            accumulator=mem[operandAddress];
            instructionCounter++;
        }

        else if (operationCode==STORE) 
        {
            mem[operandAddress]=accumulator;
            accumulator=0;
            instructionCounter++;
        }

        else if (operationCode==ADD) 
        {
            accumulator+=mem[operandAddress];
            instructionCounter++;
        }

        else if (operationCode==SUBTRACT) 
        {
            accumulator-=mem[operandAddress];
            instructionCounter++;
        }

        else if (operationCode==MULTIPLY) 
        {
            accumulator*=mem[operandAddress];
            instructionCounter++;
        }

        else if (operationCode==DIVIDE) 
        {
            if (mem[operandAddress]==0) {
                printf("Деление на ноль. Останов.\n");
                break;
            }
            accumulator/=mem[operandAddress];
            instructionCounter++;
        }

        else if (operationCode==BRANCH) 
        {
            instructionCounter=operandAddress;
        }

        else if (operationCode==BRANCHZERO) 
        {
            if (accumulator==0)
            instructionCounter=operandAddress;
            else instructionCounter++;
        }

        else if (operationCode==BRANCHNEG) 
        {
            if (accumulator<0)
            instructionCounter=operandAddress;
            else instructionCounter++;
        }
        else {
            printf("Нераспознанная инструкция!!! Останов.\n");
            break;
            }

    }
    while(1);
    /*               
        printf("%+03d\t",instCode);
        printf("%+03d\n",opAddr);
        */
}
