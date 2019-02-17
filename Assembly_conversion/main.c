/*
Rounak Parihar: 170101056
*/
//Including useful libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int mem=0; //globally declared variable used to assign the memory address
char *ReadOpCode[12];  //global character array to store the operator codes (opcode)
void Decimal_To_Binary(int Number,FILE *file_point) // function to convert decimal number to binary i.e, 0 ad 1
{
  int Binary_Number[100]={0}; //an integer aray initalizing all the values as 0
  int index = 0,j;
  while (Number > 0)
  {
      Binary_Number[index++] = Number % 2;
      Number/=2;
  }
  for (j = 4; j >= 0; j--)
  {
      fprintf(file_point,"%d",Binary_Number[j]);
  }
}
void Hexadecimal_To_Binary(FILE *file_point,char c)  //Function to convert hexadecimal number to binary number
{
    	if(c=='0')       //considering the hexadecimal number and printing the corresponding binary number.
    		fprintf(file_point,"0000 ");
    	if(c=='1')
    		fprintf(file_point,"0001 ");
    	if(c=='2')
    		fprintf(file_point,"0010 ");
    	if(c=='3')
    		fprintf(file_point,"0011 ");
    	if(c=='4')
    		fprintf(file_point,"0100 ");
    	if(c=='5')
    		fprintf(file_point,"0101 ");
    	if(c=='6')
    		fprintf(file_point,"0110 ");
    	if(c=='7')
    		fprintf(file_point,"0111 ");
    	if(c=='8')
    		fprintf(file_point,"1000 ");
    	if(c=='9')
    		fprintf(file_point,"1001 ");
    	if(c=='A')
    		fprintf(file_point,"1010 ");
    	if(c=='B')
    		fprintf(file_point,"1011 ");
    	if(c=='C')
    		fprintf(file_point,"1100 ");
    	if(c=='D')
    		fprintf(file_point,"1101 ");
    	if(c=='E')
    		fprintf(file_point,"1110 ");
    	if(c=='F')
    		fprintf(file_point,"1111 ");
}
bool containsLabel(char *Content)    //function to check whether the line of input contains any label i.e, L1 /L2 or any other....
{
	for(int j=0;j<strlen(Content);j++)
    	{
    		if(Content[j]==':') return true;
    	}
    	return false;
}
void matching(FILE *file_point)       //fuction to take opcode from the file opcode.txt
{
    for(int i=0;i<12;i++)
    {
        ReadOpCode[i]=(char *)malloc((sizeof(char))*4);
    }
    char input[1000];
    int i=0;
    while(fgets(input, 1000 ,file_point))
    {
        char *str[2];
        int head=0;
        bool Marker=false;
        str[head] = strtok(input," ,\n:\t");
        while(str[head]!=NULL)
        {
            if (Marker==true)
            {
                strcpy(ReadOpCode[i],str[head]);
                i++;
            }
            head++;
            str[head]=strtok(NULL," ,\n");
            Marker=!Marker;
        }
    }
}
int labelLength(char *Content)
{
	int count=0;
	for(int j=0;j<strlen(Content);j++)
	{
		if(Content[j]!=':')
			count++;
		else break;
	}
	return count;
}
void Loop_Condition_Change(int Number,FILE *file_point)  //function to change deciml to binary using hexadecimal for loop purpose
{
    char Hexadecimal_Number[100];
    int index = 0;
    while(Number!=0)
    {
        int temp  = 0;
        temp = Number % 16;
        if(temp < 10)
        {
            Hexadecimal_Number[index++] = temp + 48;  // Ascii value for integers
        }
        else
        {
            Hexadecimal_Number[index++] = temp + 55;  //Ascii value for Capital letters
        }
        Number/=16;
    }
    //Conditions to assign the last bundled 4 bit of hexadecimal number to convert it into binary number
    if(index==0)
        fprintf(file_point,"0000 0000 0000 0000");
    if(index==1)
    {
        fprintf(file_point,"0000 0000 0000 ");
        Hexadecimal_To_Binary(file_point,Hexadecimal_Number[0]);
    }
    if(index==2)
    {
        fprintf(file_point,"0000 0000 ");
        Hexadecimal_To_Binary(file_point,Hexadecimal_Number[1]);
        Hexadecimal_To_Binary(file_point,Hexadecimal_Number[0]);
    }
    if(index==3)
    {
        fprintf(file_point,"0000 ");
        Hexadecimal_To_Binary(file_point,Hexadecimal_Number[2]);
        Hexadecimal_To_Binary(file_point,Hexadecimal_Number[1]);
        Hexadecimal_To_Binary(file_point,Hexadecimal_Number[0]);
    }
    if(index>3)
    {
    	Hexadecimal_To_Binary(file_point,Hexadecimal_Number[2]);
        Hexadecimal_To_Binary(file_point,Hexadecimal_Number[2]);
        Hexadecimal_To_Binary(file_point,Hexadecimal_Number[1]);
        Hexadecimal_To_Binary(file_point,Hexadecimal_Number[0]);
    }
}
void Memory_Condition(char *str[1000])   // if both operands are Registers then mem added will be 2 byte otherwise it will be 4 byte
{
    if(str[1][0]=='R'&&str[2][0]=='R')
        mem+=2;
    else
        mem+=4;
}
void Memory_Address_MOV(char *str[1000])
{
    Memory_Condition(str);
}
void Memory_Address_ADD(char *str[1000])
{
    Memory_Condition(str);
}
void Memory_Address_SUB(char *str[1000])
{
    Memory_Condition(str);
}
void Memory_Address_MUL(char *str[1000])
{
    if(str[1][0]=='R')
        mem+=2;
    else
        mem+=4;
}
void Memory_Address_CMP(char *str[1000])
{
    Memory_Condition(str);
}
void Memory_Address_AND(char *str[1000])
{
    Memory_Condition(str);
}
void Memory_Address_OR(char *str[1000])
{
    Memory_Condition(str);
}
void Memory_Address_NOT(char *str[1000])
{
    mem+=2;

}
// special conditions in the assembly language Took reference from google
void Memory_Address_JMP(char *str[1000])
{
    mem+=3;
}
void Memory_Address_HLT(char *str[1000])
{
    mem+=1;
}
void Memory_Address_JNZ(char *str[1000])
{
    mem+=3;
}
void Memory_Address_LOOP(char *str[1000])
{
    mem+=7;
}
void Mem_Address_MOV(char *str[1000],FILE *file_point)
{
	  fprintf(file_point,"%04X",mem);
    fprintf(file_point,"           %s ",ReadOpCode[0]);
    if(strlen(str[1])==2)
    {
        int tempk=(int)str[1][1]-48;
        Decimal_To_Binary(tempk,file_point);
        fprintf(file_point," ");
    }
    if(strlen(str[1])==3)
    {
        int tempk=0;
        tempk+=(int)str[1][2]-48;
        tempk+=(10*((int)str[1][1]-48));
        Decimal_To_Binary(tempk,file_point);
        fprintf(file_point," ");
    }
	  if(str[2][0]=='R')
    {
        if(strlen(str[2])==2)
        {
            int tempk=(int)str[2][1]-48;
            Decimal_To_Binary(tempk,file_point);
            fprintf(file_point," ");
        }
        if(strlen(str[2])==3)
        {
            int tempk=0;
            tempk+=(int)str[2][2]-48;
            tempk+=(10*((int)str[2][1]-48));
            Decimal_To_Binary(tempk,file_point);
            fprintf(file_point," ");
        }
        mem+=2;
    }
    else
    {
        Hexadecimal_To_Binary(file_point,str[2][0]);
        Hexadecimal_To_Binary(file_point,str[2][1]);
        Hexadecimal_To_Binary(file_point,str[2][2]);
        Hexadecimal_To_Binary(file_point,str[2][3]);

        mem+=4;
    }
    fprintf(file_point,"\n");
}

void Mem_Address_ADD(char *str[1000],FILE *file_point)
{
  fprintf(file_point,"%04X",mem);
  fprintf(file_point,"           %s ",ReadOpCode[0]);
  if(strlen(str[1])==2)
  {
      int tempk=(int)str[1][1]-48;
      Decimal_To_Binary(tempk,file_point);
      fprintf(file_point," ");
  }
  if(strlen(str[1])==3)
  {
      int tempk=0;
      tempk+=(int)str[1][2]-48;
      tempk+=(10*((int)str[1][1]-48));
      Decimal_To_Binary(tempk,file_point);
      fprintf(file_point," ");
  }
  if(str[2][0]=='R')
  {
      if(strlen(str[2])==2)
      {
          int tempk=(int)str[2][1]-48;
          Decimal_To_Binary(tempk,file_point);
          fprintf(file_point," ");
      }
      if(strlen(str[2])==3)
      {
          int tempk=0;
          tempk+=(int)str[2][2]-48;
          tempk+=(10*((int)str[2][1]-48));
          Decimal_To_Binary(tempk,file_point);
          fprintf(file_point," ");
      }
      mem+=2;
  }
  else
  {
      Hexadecimal_To_Binary(file_point,str[2][0]);
      Hexadecimal_To_Binary(file_point,str[2][1]);
      Hexadecimal_To_Binary(file_point,str[2][2]);
      Hexadecimal_To_Binary(file_point,str[2][3]);

      mem+=4;
  }
  fprintf(file_point,"\n");
}

void Mem_Address_SUB(char *str[1000],FILE *file_point)
{
  fprintf(file_point,"%04X",mem);
  fprintf(file_point,"           %s ",ReadOpCode[0]);
  if(strlen(str[1])==2)
  {
      int tempk=(int)str[1][1]-48;
      Decimal_To_Binary(tempk,file_point);
      fprintf(file_point," ");
  }
  if(strlen(str[1])==3)
  {
      int tempk=0;
      tempk+=(int)str[1][2]-48;
      tempk+=(10*((int)str[1][1]-48));
      Decimal_To_Binary(tempk,file_point);
      fprintf(file_point," ");
  }
  if(str[2][0]=='R')
  {
      if(strlen(str[2])==2)
      {
          int tempk=(int)str[2][1]-48;
          Decimal_To_Binary(tempk,file_point);
          fprintf(file_point," ");
      }
      if(strlen(str[2])==3)
      {
          int tempk=0;
          tempk+=(int)str[2][2]-48;
          tempk+=(10*((int)str[2][1]-48));
          Decimal_To_Binary(tempk,file_point);
          fprintf(file_point," ");
      }
      mem+=2;
  }
  else
  {
      Hexadecimal_To_Binary(file_point,str[2][0]);
      Hexadecimal_To_Binary(file_point,str[2][1]);
      Hexadecimal_To_Binary(file_point,str[2][2]);
      Hexadecimal_To_Binary(file_point,str[2][3]);

      mem+=4;
  }
  fprintf(file_point,"\n");
}

void Mem_Address_MUL(char *str[1000],FILE *file_point)
{
	fprintf(file_point,"%04X",mem);
    fprintf(file_point,"           %s 00001 ",ReadOpCode[3]);
    if(str[1][0]=='R')
    {
        if(strlen(str[1])==2)
        {
            int tempk=(int)str[1][1]-48;
            Decimal_To_Binary(tempk,file_point);
            fprintf(file_point," ");
        }
        if(strlen(str[1])==3)
        {
            int tempk=0;
            tempk+=(int)str[1][2]-48;
            tempk+=(10*((int)str[1][1]-48));
            Decimal_To_Binary(tempk,file_point);
            fprintf(file_point," ");
        }
        mem+=2;
    }
    else
    {
    	Hexadecimal_To_Binary(file_point,str[1][0]);
        Hexadecimal_To_Binary(file_point,str[1][1]);
        Hexadecimal_To_Binary(file_point,str[1][2]);
        Hexadecimal_To_Binary(file_point,str[1][3]);
        mem+=4;
    }
    fprintf(file_point,"\n");
}
void Mem_Address_CMP(char *str[1000],FILE *file_point)
{
  fprintf(file_point,"%04X",mem);
  fprintf(file_point,"           %s ",ReadOpCode[0]);
  if(strlen(str[1])==2)
  {
      int tempk=(int)str[1][1]-48;
      Decimal_To_Binary(tempk,file_point);
      fprintf(file_point," ");
  }
  if(strlen(str[1])==3)
  {
      int tempk=0;
      tempk+=(int)str[1][2]-48;
      tempk+=(10*((int)str[1][1]-48));
      Decimal_To_Binary(tempk,file_point);
      fprintf(file_point," ");
  }
  if(str[2][0]=='R')
  {
      if(strlen(str[2])==2)
      {
          int tempk=(int)str[2][1]-48;
          Decimal_To_Binary(tempk,file_point);
          fprintf(file_point," ");
      }
      if(strlen(str[2])==3)
      {
          int tempk=0;
          tempk+=(int)str[2][2]-48;
          tempk+=(10*((int)str[2][1]-48));
          Decimal_To_Binary(tempk,file_point);
          fprintf(file_point," ");
      }
      mem+=2;
  }
  else
  {
      Hexadecimal_To_Binary(file_point,str[2][0]);
      Hexadecimal_To_Binary(file_point,str[2][1]);
      Hexadecimal_To_Binary(file_point,str[2][2]);
      Hexadecimal_To_Binary(file_point,str[2][3]);

      mem+=4;
  }
  fprintf(file_point,"\n");
}
void Mem_Address_AND(char *str[1000],FILE *file_point)
{
  fprintf(file_point,"%04X",mem);
  fprintf(file_point,"           %s ",ReadOpCode[0]);
  if(strlen(str[1])==2)
  {
      int tempk=(int)str[1][1]-48;
      Decimal_To_Binary(tempk,file_point);
      fprintf(file_point," ");
  }
  if(strlen(str[1])==3)
  {
      int tempk=0;
      tempk+=(int)str[1][2]-48;
      tempk+=(10*((int)str[1][1]-48));
      Decimal_To_Binary(tempk,file_point);
      fprintf(file_point," ");
  }
  if(str[2][0]=='R')
  {
      if(strlen(str[2])==2)
      {
          int tempk=(int)str[2][1]-48;
          Decimal_To_Binary(tempk,file_point);
          fprintf(file_point," ");
      }
      if(strlen(str[2])==3)
      {
          int tempk=0;
          tempk+=(int)str[2][2]-48;
          tempk+=(10*((int)str[2][1]-48));
          Decimal_To_Binary(tempk,file_point);
          fprintf(file_point," ");
      }
      mem+=2;
  }
  else
  {
      Hexadecimal_To_Binary(file_point,str[2][0]);
      Hexadecimal_To_Binary(file_point,str[2][1]);
      Hexadecimal_To_Binary(file_point,str[2][2]);
      Hexadecimal_To_Binary(file_point,str[2][3]);

      mem+=4;
  }
  fprintf(file_point,"\n");
}
void Mem_Address_JMP(char *str[1000],char *Lbl[1000],int *Lbl_Add,FILE *file_point)
{
	fprintf(file_point,"%04X",mem);
    fprintf(file_point,"           %s ",ReadOpCode[8]);
	int index=0;
	while(strcmp(str[1],Lbl[index])!=0)
	{
		index++;
	}
	Loop_Condition_Change(Lbl_Add[index],file_point);
    mem+=3;
    fprintf(file_point,"\n");
}
void Mem_Address_OR(char *str[1000],FILE *file_point)
{
  fprintf(file_point,"%04X",mem);
  fprintf(file_point,"           %s ",ReadOpCode[0]);
  if(strlen(str[1])==2)
  {
      int tempk=(int)str[1][1]-48;
      Decimal_To_Binary(tempk,file_point);
      fprintf(file_point," ");
  }
  if(strlen(str[1])==3)
  {
      int tempk=0;
      tempk+=(int)str[1][2]-48;
      tempk+=(10*((int)str[1][1]-48));
      Decimal_To_Binary(tempk,file_point);
      fprintf(file_point," ");
  }
  if(str[2][0]=='R')
  {
      if(strlen(str[2])==2)
      {
          int tempk=(int)str[2][1]-48;
          Decimal_To_Binary(tempk,file_point);
          fprintf(file_point," ");
      }
      if(strlen(str[2])==3)
      {
          int tempk=0;
          tempk+=(int)str[2][2]-48;
          tempk+=(10*((int)str[2][1]-48));
          Decimal_To_Binary(tempk,file_point);
          fprintf(file_point," ");
      }
      mem+=2;
  }
  else
  {
      Hexadecimal_To_Binary(file_point,str[2][0]);
      Hexadecimal_To_Binary(file_point,str[2][1]);
      Hexadecimal_To_Binary(file_point,str[2][2]);
      Hexadecimal_To_Binary(file_point,str[2][3]);

      mem+=4;
  }
  fprintf(file_point,"\n");
}
void Mem_Address_HLT(char *str[1000],FILE *file_point)
{
	fprintf(file_point,"%04X",mem);
    fprintf(file_point,"           %s\n",ReadOpCode[10]);
    mem+=1;
}
void Mem_Address_NOT(char *str[1000],FILE *file_point)
{
	fprintf(file_point,"%04X",mem);
    fprintf(file_point,"           %s ",ReadOpCode[7]);
	if(strlen(str[1])==2)
    {
        int tempk=(int)str[1][1]-48;
        Decimal_To_Binary(tempk,file_point);
        fprintf(file_point," ");
    }
    else if(strlen(str[1])==3)
    {
        int tempk=0;
        tempk+=(int)str[1][2]-48;
        tempk+=(10*((int)str[1][1]-48));
        Decimal_To_Binary(tempk,file_point);
        fprintf(file_point," ");
    }
    mem+=2;
    fprintf(file_point,"\n");
}

void Mem_Address_JNZ(char *str[1000],char *Lbl[1000],int *Lbl_Add,FILE *file_point)
{
	fprintf(file_point,"%04X",mem);
    fprintf(file_point,"           %s ",ReadOpCode[11]);
	int index=0;
	while(strcmp(str[1],Lbl[index])!=0)
	{
		index++;
	}
	Loop_Condition_Change(Lbl_Add[index],file_point);
    mem+=3;
    fprintf(file_point,"\n");
}

void Mem_Address_LOOP(char *str[1000],char *Lbl[1000],int *Lbl_Add,FILE *file_point)
{
	fprintf(file_point,"%04X",mem);
    fprintf(file_point,"           %s 11111 0000 0000 0000 0001 ",ReadOpCode[2]);
    mem+=4;
    fprintf(file_point,"\n");
    Mem_Address_JNZ(str,Lbl,Lbl_Add,file_point);
}
int main()
{
    FILE* Input;
    Input=fopen("input.asm","r");
    FILE* opcode;
    opcode=fopen("Op_Table.txt","w");
    FILE* SymbolTable;                                //file opening in different formats
    SymbolTable=fopen("Symbol_Table.txt","w");
    FILE* opcode_Match;
    opcode_Match=fopen("opcode.txt","r");
    FILE* Output;
    Output=fopen("output.txt","w");

    matching(opcode_Match);
	  char * Content = NULL;
    size_t len = 0;
    ssize_t read;

	  bool islabel[1000];
    int Lbl_Add[1000];
  	char *Lbl[1000];
    int count=0;
    int nlabels=0;
  	while ((read = getline(&Content, &len, Input)) != -1)
    {
        islabel[count++]=containsLabel(Content);
        if(islabel[count-1])
        {
        	Lbl[nlabels++]=(char *)malloc((sizeof(char))*labelLength(Content));
   		}
    }
    rewind(Input);
//pass 1 opcode
    nlabels=0;
    char input[1000];
    int Instuction[12]={0};
    int head;
    while(fgets(input, 1000 ,Input))
    {
        char *str[1000];
        head=0;
        int Marker=-1;
        str[head] = strtok(input," ,\n:\t");
        while(str[head]!=NULL)
        {
            if(str[head][0]==';') break;
            if(strcmp(str[head],"START")==0)
                mem=0;
           else if(strcmp(str[head],"ADD")==0)
           {
                Marker=1;
                if(Instuction[1]==0)
                {
                    fprintf(opcode,"ADD %s\n",ReadOpCode[1]);
                    Instuction[1]=1;
                }
            }
            else if(strcmp(str[head],"MOV")==0)
            {
                Marker=0;
                if(Instuction[0]==0)
                {
                    fprintf(opcode,"MOV %s\n",ReadOpCode[0]);
                    Instuction[0]=1;
                }
            }
            else if (strcmp(str[head],"END")==0)
            {

            }

            else if(strcmp(str[head],"SUB")==0)
            {
                Marker=2;
                if(Instuction[2]==0)
                {
                    fprintf(opcode,"SUB %s\n",ReadOpCode[2]);
                    Instuction[2]=1;
                }
            }
            else if(strcmp(str[head],"CMP")==0)
            {
                Marker=4;
                if(Instuction[4]==0)
                {
                    fprintf(opcode,"CMP %s\n",ReadOpCode[4]);
                    Instuction[4]=1;
                }
            }
            else if(strcmp(str[head],"MUL")==0)
            {
                Marker=3;
                if(Instuction[3]==0)
                {
                    fprintf(opcode,"MUL %s\n",ReadOpCode[3]);
                    Instuction[3]=1;
                }
            }

            else if(strcmp(str[head],"AND")==0)
            {
                Marker=5;
                if(Instuction[5]==0)
                {
                    fprintf(opcode,"AND %s\n",ReadOpCode[5]);
                    Instuction[5]=1;
                }
            }
            else if(strcmp(str[head],"OR")==0)
            {
                Marker=6;
                if(Instuction[6]==0)
                {
                    fprintf(opcode,"OR  %s\n",ReadOpCode[6]);
                    Instuction[6]=1;
                }
            }
            else if(strcmp(str[head],"NOT")==0)
            {
                Marker=7;
                if(Instuction[7]==0)
                {
                    fprintf(opcode,"NOT %s\n",ReadOpCode[7]);
                    Instuction[7]=1;
                }
            }
            else if(strcmp(str[head],"JMP")==0)
            {
                Marker=8;
                if(Instuction[8]==0)
                {
                    fprintf(opcode,"JMP %s\n",ReadOpCode[8]);
                    Instuction[8]=1;
                }
            }
            else if(strcmp(str[head],"LOOP")==0)
            {
                Marker=9;
                if(Instuction[2]==0)
                {
                    fprintf(opcode,"SUB %s\n",ReadOpCode[2]);
                    Instuction[2]=1;
                }
                if(Instuction[11]==0)
                {
                    fprintf(opcode,"JNZ %s\n",ReadOpCode[11]);
                    Instuction[11]=1;
                }
            }
            else if(strcmp(str[head],"JNZ")==0)
            {
                Marker=11;
                if(Instuction[11]==0)
                {
                    fprintf(opcode,"JNZ %s\n",ReadOpCode[11]);
                    Instuction[11]=1;
                }
            }
            else if(strcmp(str[head],"HLT")==0)
            {
                Marker=10;
                if(Instuction[10]==0)
                {
                    fprintf(opcode,"HLT %s\n",ReadOpCode[10]);
                    Instuction[10]=1;
                }
            }
    //pass1 symbol tabe
            else if(head==0)
            {
            	strcpy(Lbl[nlabels],str[head]);
            	Lbl_Add[nlabels++]=mem;
                fprintf(SymbolTable,"%s: %04XH\n",str[head],mem);
            }
            head++;
            str[head]=strtok(NULL," ,\n");
        }
        if(Marker==0)
            Memory_Address_MOV(str);
        else if(Marker==1)
            Memory_Address_ADD(str);
        else if(Marker==2)
            Memory_Address_SUB(str);
        else if(Marker==3)
            Memory_Address_MUL(str);
        else if(Marker==4)
            Memory_Address_CMP(str);
        else if(Marker==5)
            Memory_Address_AND(str);
        else if(Marker==6)
            Memory_Address_OR(str);
        else if(Marker==7)
            Memory_Address_NOT(str);
        else if(Marker==8)
            Memory_Address_JMP(str);
        else if(Marker==9)
             Memory_Address_LOOP(str);
        else if(Marker==10)
            Memory_Address_HLT(str);
        else if(Marker==11)
            Memory_Address_JNZ(str);
    }
    rewind(Input);
// pass 2
    nlabels=0;
    char input1[1000];
    int Op_Coder_check[12]={0};
    int Start;
    fprintf(Output,"ADDRESS           INSTRUCTION\n\n");
    while(fgets(input1, 1000 ,Input))
    {
        char *str1[1000];
        Start=0;
        int Marker1=-1;
        str1[Start] = strtok(input1," ,\n:\t");
        while(str1[Start]!=NULL)
        {
            if(strcmp(str1[Start],"START")==0)
                mem=0;
            else if (strcmp(str1[Start],"END")==0)
            {

            }
            else if(strcmp(str1[Start],"MOV")==0)
            {
                Marker1=0;
                if(Op_Coder_check[0]==0)
                {
                    Op_Coder_check[0]=1;
                }
            }
            else if(strcmp(str1[Start],"ADD")==0)
            {
                Marker1=1;
                if(Op_Coder_check[1]==0)
                {
                    Op_Coder_check[1]=1;
                }
            }
            else if(strcmp(str1[Start],"SUB")==0)
            {
                Marker1=2;
                if(Op_Coder_check[2]==0)
                {
                    Op_Coder_check[2]=1;
                }
            }
            else if(strcmp(str1[Start],"AND")==0)
            {
                Marker1=5;
                if(Op_Coder_check[5]==0)
                {
                    Op_Coder_check[5]=1;
                }
            }
            else if(strcmp(str1[Start],"NOT")==0)
            {
                Marker1=7;
                if(Op_Coder_check[7]==0)
                {
                    Op_Coder_check[7]=1;
                }
            }
            else if(strcmp(str1[Start],"MUL")==0)
            {
                Marker1=3;
                if(Op_Coder_check[3]==0)
                {
                    Op_Coder_check[3]=1;
                }
            }
            else if(strcmp(str1[Start],"CMP")==0)
            {
                Marker1=4;
                if(Op_Coder_check[4]==0)
                {
                    Op_Coder_check[4]=1;
                }
            }

            else if(strcmp(str1[Start],"OR")==0)
            {
                Marker1=6;
                if(Op_Coder_check[6]==0)
                {
                    Op_Coder_check[6]=1;
                }
            }

            else if(strcmp(str1[Start],"JMP")==0)
            {
                Marker1=8;
                if(Op_Coder_check[8]==0)
                {
                    Op_Coder_check[8]=1;
                }
            }
            else if(strcmp(str1[Start],"LOOP")==0)
            {
                Marker1=9;
                if(Op_Coder_check[2]==0)
                {
                    Op_Coder_check[2]=1;
                }
                if(Op_Coder_check[11]==0)
                {
                    Op_Coder_check[11]=1;
                }
            }
            else if(strcmp(str1[Start],"HLT")==0)
            {
                Marker1=10;
                if(Op_Coder_check[10]==0)
                {
                    Op_Coder_check[10]=1;
                }
            }
            else if(strcmp(str1[Start],"JNZ")==0)
            {
                Marker1=11;
                if(Op_Coder_check[11]==0)
                {
                    Op_Coder_check[11]=1;
                }
            }
            else if(Start==0)
            {
            	Start--;
            }
            Start++;
            str1[Start]=strtok(NULL," ,\n");
        }
        if(Marker1==0)
            Mem_Address_MOV(str1,Output);
        else if(Marker1==1)
            Mem_Address_ADD(str1,Output);
        else if(Marker1==2)
            Mem_Address_SUB(str1,Output);
        else if(Marker1==3)
            Mem_Address_MUL(str1,Output);
        else if(Marker1==4)
            Mem_Address_CMP(str1,Output);
        else if(Marker1==5)
            Mem_Address_AND(str1,Output);
        else if(Marker1==6)
            Mem_Address_OR(str1,Output);
        else if(Marker1==7)
            Mem_Address_NOT(str1,Output);
        else if(Marker1==8)
            Mem_Address_JMP(str1,Lbl,Lbl_Add,Output);
        else if(Marker1==9)
            Mem_Address_LOOP(str1,Lbl,Lbl_Add,Output);
        else if(Marker1==10)
            Mem_Address_HLT(str1,Output);
        else if(Marker1==11)
            Mem_Address_JNZ(str1,Lbl,Lbl_Add,Output);
    }
    fclose(Input);
    fclose(opcode);             //closing the files
    fclose(SymbolTable);
    fclose(opcode_Match);
    fclose(Output);
    return 0;
}
