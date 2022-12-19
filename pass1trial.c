#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

void main()
{
	char opcd[20], lbl[20], oprnd[20], op[20], otp[20];
	char code[10];
	int locctr, sa, pgmlength;
	FILE *f1, *f2, *f3, *f4;
	f1 = fopen("input.txt", "r");
	f2=fopen("OPTAB.txt","r");
	f4 = fopen("SYMTAB.txt", "w");
	f3 = fopen("output.txt", "w");

	fscanf(f1, "%s %s %s", lbl, opcd, oprnd);

	if (strcmp(opcd, "START") == 0)
	{
		sa = atoi(oprnd);
		locctr = sa;
		fprintf(f3, "%d %s %s %s\n", locctr, lbl, opcd, oprnd);
		fscanf(f1, "%s%s%s", lbl, opcd, oprnd);
	}
	else
	{
		locctr = 0;
	}
	while (strcmp(opcd, "END") != 0)
		{
            fprintf(f3, "%d\t", locctr);
			if (strcmp(lbl, "**") != 0)
				fprintf(f4, "%s\t%d\n", lbl, locctr);
			if (strcmp(opcd, "WORD") == 0)
				locctr += 3;
			else if (strcmp(opcd, "RESW") == 0)
			{
				locctr += 3 * atoi(oprnd);
			}
			else if (strcmp(opcd, "RESB") == 0)
			{
				locctr += atoi(oprnd);
			}
			else if (strcmp(opcd, "BYTE") == 0)
			{
				char ch = oprnd[0];
				if (ch == 'X')
				{
					locctr += 1;
				}
				else
					locctr += (strlen(oprnd) - 3);
			}
			else{
				while (strcmp(code, "END") != 0) {
        			if (strcmp(opcd, code) == 0) {
         				 locctr += 3;
         				 break;
       				 }
       			 fscanf(f2, "%s", code);
    			  }
			}
			//fscanf(f1,"%s%s",lbl,m1);
			fprintf(f3, "%s\t%s\t%s\n", lbl, opcd, oprnd);
    		rewind(f2);
    		fscanf(f1, "%s%s%s", lbl, opcd, oprnd);
		
	}
	pgmlength = locctr - sa;
	if (strcmp(opcd, "END") == 0)
	{
	fprintf(f3, "%d\t%s\t%s\t%s", locctr, lbl, opcd, oprnd);
	}
	fclose(f4);
  fclose(f3);
  fclose(f2);
  fclose(f1);
  printf("\nProgram Length: %d\n\n", pgmlength);


}
