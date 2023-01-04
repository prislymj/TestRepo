#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main(){
int locctr, start, length;
FILE *f1, *f2, *f3, *f4, *f5;
char label[20], opcd[20], oprnd[20], code[20];

f1=fopen("input.txt", "r");
f2=fopen("optab.txt", "r");
f3=fopen("output.txt", "w");
f4=fopen("symtab.txt", "w");

fscanf(f1, "%s%s%s", label, opcd, oprnd);

if(strcmp(opcd,"START")==0){
locctr=atoi(oprnd);
start=locctr;
fprintf(f3,"%d\t%s\t%s\t%s",locctr, label, opcd, oprnd);
fscanf(f1, "%s%s%s", label, opcd, oprnd);
}
else{
locctr=0;
}
while(strcmp(opcd,"END")!=0){
fprintf(f3,"\n%d\t",locctr);
if(strcmp(label,"**")!=0){
fprintf(f4,"\n%s\t%d", label, locctr);
}
if(strcmp(opcd,"WORD")==0)
locctr+=3;
else if(strcmp(opcd,"RESW")==0)
locctr+=3*atoi(oprnd);
else if(strcmp(opcd,"RESB")==0)
locctr+=atoi(oprnd);
else if(strcmp(opcd,"BYTE")==0)
{
if(oprnd[0]=='C')
locctr+=strlen(oprnd)-3;
else
locctr+=1;
}
else{
while(strcmp(code,"END")!=0){
if(strcmp(opcd,code)==0){
locctr+=3;
break;
}
fscanf(f2,"%s",code);
}
}
rewind(f2);
fprintf(f3,"%s\t%s\t%s",label, opcd, oprnd);
fscanf(f1, "%s%s%s", label, opcd, oprnd);
}
length=locctr-start;
if(strcmp(opcd,"END")==0)
fprintf(f3,"\n%d\t%s\t%s\t%s",locctr, label, opcd, oprnd);
printf("\nProgram length=%d", length);
}