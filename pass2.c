#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main()
{
	char lbl[20], locctr[20], oprnd[20], opcd[20], code[20], value[20], symbl[20], addr[20], ab[20];
	int len = 20, slen, i, start;
	FILE *f1, *f2, *f3, *f4, *f5;

	f1 = fopen("output.txt", "r");
	f2 = fopen("symtab.txt", "r");
	f3 = fopen("file.txt", "w");
	f4 = fopen("objcode.txt", "w");
	f5 = fopen("OPTAB.txt", "r");

	fscanf(f1, "%s%s%s%s", locctr, lbl, opcd, oprnd);

	if (strcmp(opcd, "START") == 0)
	{
		start = atoi(oprnd);
		fprintf(f3, "%s\t%s\t%s", lbl, opcd, oprnd);
		fprintf(f4, "H^%s^00%s^%d\n", lbl, oprnd, len);
		fscanf(f1, "%s%s%s%s", locctr, lbl, opcd, oprnd);
		fprintf(f4, "T^00%d^%d", atoi(locctr), len);
	}

	while (strcmp(opcd, "END") != 0)
	{
		if (strcmp(opcd, "BYTE") == 0)
		{
			if (oprnd[0] == 'C')
			{
				slen = strlen(oprnd) - 3;
				fprintf(f3, "\n%s\t%s\t%s\t%s", locctr, lbl, opcd, oprnd);
				fprintf(f4, "^");
				for (i = 2; i < (slen + 2); i++)
				{
					sprintf(ab, "%x", oprnd[i]);
					fprintf(f3, "%s", ab);
					fprintf(f4, "%s", ab);
				}
				fprintf(f3, "\n");
			}
			else if (oprnd[0] == 'X')
			{
				slen = strlen(oprnd) - 3;
				fprintf(f3, "\n%s\t%s\t%s", lbl, opcd, oprnd);
				fprintf(f4, "^");
				for (i = 2; i < (slen + 2); i++)
				{
					fprintf(f3, "%s", oprnd[i]);
					fprintf(f4, "%s", oprnd[i]);
				}
				fprintf(f3, "\n");
			}
		}

		else if (strcmp(opcd, "WORD") == 0)
		{
			fprintf(f3, "\n%s\t%s\t%s\t%s\t0000%s", locctr, lbl, opcd, oprnd, oprnd);
			fprintf(f4, "^0000%s", oprnd);
		}
		else if ((strcmp(opcd, "RESB") == 0) || (strcmp(opcd, "RESW") == 0))
		{
			fprintf(f3, "\n%s\t%s\t%s\t%s", locctr, lbl, opcd, oprnd);
		}
		else
		{
			fscanf(f5, "%s%s", code, value);
			while (strcmp(code, "END") != 0)
			{
				if (strcmp(code, opcd) == 0)
					break;
				fscanf(f5, "%s%s", code, value);
			}
			fscanf(f2, "%s%s", symbl, addr);
			while (!feof(f2))
			{
				if (strcmp(oprnd, symbl) == 0)
					break;
				fscanf(f2, "%s%s", symbl, addr);
			}
			fprintf(f3, "\n%d\t%s\t%s\t%s\t%d%d\n", atoi(locctr), lbl, opcd, oprnd, atoi(value), atoi(addr));
            fprintf(f4, "^%d%d", atoi(value), atoi(addr));
		}
		rewind(f5);
		rewind(f2);
		fscanf(f1, "%s%s%s%s", locctr, lbl, opcd, oprnd);
	}
	fprintf(f4, "\n");
	if (strcmp(opcd, "END") == 0)
	{
		fprintf(f4, "\nE^00%d", start);
		fprintf(f3, "\n%s\t%s\t%s\t%s", locctr, lbl, opcd, oprnd);
	}
	printf("Object Program produced");
}