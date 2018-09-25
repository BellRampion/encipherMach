#include <stdio.h>

#define MAXLENGTH 1000
#define toUppercase(c) if (c >= 'a' && c <= 'z') \
                            { \
                                c+= ('A' - 'a'); \
                            }

//main() will take arguments this time
int main(int argc, char *argv[]){ //These are conventional names for a) the number of arguments and b) a pointer to an array of character strings
	FILE *fp;
	FILE *fp2;
	FILE *fp3;

	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;
	int debug = 0;
	int max = MAXLENGTH;

	char filename[MAXLENGTH];
	char fileLine[MAXLENGTH]; //Stores line retrieved from file
	char line[MAXLENGTH]; //Stores altered line to be written to file
	char c;

	printf("Would you like to turn debugging on? (y/n): ");
	c = getchar();
	debug = (c == 'y') ? 1 : 0;

	if (argc != 2)
		printf("Usage: prepForEnigma filename\n");

	else {
		fp = fopen(argv[1], "r");
		if (debug == 1)
		{
			printf("Filename: %s\n", argv[1]);
		}
		fp2 = fopen("temp", "w");

		for (i = 1; fgets(fileLine, max, fp) != NULL; i++){ //Set i (num of lines) to 1; if EOF hasn't been reached; increment i by 1
			k = 0; //Reset k each time
			if (debug == 1)
			{
				printf("Line %i of original file: %s\n", i, fileLine);
				printf("K: %i\n", k);
			}
			for (j = 0; (c = fileLine[j]) != '\0'; j++){

				if (c > '@' && c < 97)
				{
					line[k++] = c;
					if (debug == 1)
					{
						printf("%c", line[k]);
					}
				}
				else if (c > 96 && c < 123) //97 == lowercase A; 122 == lowercase Z
				{
					toUppercase(c);
					line[k++] = c;
					if (debug == 1)
					{
						printf("Now in uppercase: %c\n", line[k]);
					}
				}
				else if (c < 65)
				{
					switch (c){
					case ' ': //Space is replaced by a double X
						line[k++] = 'X';
						line[k++] = 'X';
						break;
					case '!':
						line[k++] = 'Z'; //! is replaced by double Z
						line[k++] = 'Z';
						break;
					case ',':
						line[k++] = 'C'; //k is incremented after the value is read
						line[k++] = 'O';
						line[k++] = 'M';
						line[k++] = 'M';
						line[k++] = 'A';
						break;
					case '.':
						line[k++] = 'S';
						line[k++] = 'T';
						line[k++] = 'O';
						line[k++] = 'P';
						break;
					case '1':
						line[k++] = 'O';
						line[k++] = 'N';
						line[k++] = 'E';
						break;
					case '2':
						line[k++] = 'T';
						line[k++] = 'W';
						line[k++] = 'O';
						break;
					case '3':
						line[k++] = 'T';
						line[k++] = 'H';
						line[k++] = 'R';
						line[k++] = 'E';
						line[k++] = 'E';
						break;
					case '4':
						line[k++] = 'F';
						line[k++] = 'O';
						line[k++] = 'U';
						line[k++] = 'R';
						break;
					case '5':
						line[k++] = 'F';
						line[k++] = 'I';
						line[k++] = 'V';
						line[k++] = 'E';
						break;
					case '6':
						line[k++] = 'S';
						line[k++] = 'I';
						line[k++] = 'X';
						break;
					case '7':
						line[k++] = 'S';
						line[k++] = 'E';
						line[k++] = 'V';
						line[k++] = 'E';
						line[k++] = 'N';
						break;
					case '8':
						line[k++] = 'E';
						line[k++] = 'I';
						line[k++] = 'G';
						line[k++] = 'T';
						break;
					case '9':
						line[k++] = 'N';
						line[k++] = 'I';
						line[k++] = 'N';
						line[k++] = 'E';
						break;
					case '0':
						line[k++] = 'Z';
						line[k++] = 'E';
						line[k++] = 'R';
						line[k++] = 'O';
						break;
					case '/':
						line[k++] = 'S';
						line[k++] = 'L';
						line[k++] = 'A';
						line[k++] = 'S';
						line[k++] = 'H';
						break;
					case '&':
						line[k++] = 'A';
						line[k++] = 'N';
						line[k++] = 'D';
						break;
					case '#':
						line[k++] = 'P';
						line[k++] = 'O';
						line[k++] = 'U';
						line[k++] = 'N';
						line[k++] = 'D';
						break;
					case '%':
						line[k++] = 'P';
						line[k++] = 'E';
						line[k++] = 'R';
						line[k++] = 'C';
						line[k++] = 'E';
						line[k++] = 'N';
						line[k++] = 'T';
						break;
					case '@':
						line[k++] = 'A';
						line[k++] = 'T';
						break;
					case '*':
						line[k++] = 'S';
						line[k++] = 'T';
						line[k++] = 'A';
						line[k++] = 'R';
						break;
					case '-':
						line[k++] = 'D';
						line[k++] = 'A';
						line[k++] = 'S';
						line[k++] = 'H';
						break;
					case '+':
						line[k++] = 'P';
						line[k++] = 'L';
						line[k++] = 'U';
						line[k++] = 'S';
						break;
					case '=':
						line[k++] = 'E';
						line[k++] = 'Q';
						line[k++] = 'U';
						line[k++] = 'A';
						line[k++] = 'L';
						line[k++] = 'S';
						break;
					case 39: //' is 39 in ASCII
						line[k++] = 'Z';
						line[k++] = 'Q';
						break;
					case '"':
						line[k++] = 'Q';
						line[k++] = 'Z';
						break;
					case ':':
						line[k++] = 'C';
						line[k++] = 'O';
						line[k++] = 'L';
						line[k++] = 'O';
						line[k++] = 'N';
						break;
					case ';':
						line[k++] = 'S';
						line[k++] = 'C';
						line[k++] = 'O';
						line[k++] = 'L';
						line[k++] = 'O';
						line[k++] = 'N';
						break;
					case '?':
						line[k++] = 'Q'; //? is replaced by double Q
						line[k++] = 'Q';
						break;
					case 10: //Includes the newline instead of dropping it.
						line[k++] = 10; //10 is the newline in ASCII
						break;
					case '(':
					    line[k++] = 'X';
					    line[k++] = 'Q';
					    break;
					case ')':
					    line[k++] = 'Q';
					    line[k++] = 'X';
					    break;
					default:
						printf("prepForEngima: file contains unallowable character %i (%c). Please remove it from your file and run this program again.\n", c, c);
						break;
					}
				}
				else printf("prepForEngima: file contains illegal character %i (%c). Please remove it from your file and run this program again.\n", c, c);

			}
            line[k] = '\0';
            if (debug == 1)
            {
                printf("\nLine ended with NULL: %c\n", line[k]);
            }
			fprintf(fp2, "%s", line); //Print the line to the temp file
			if (debug == 1)
			{
				printf("Line %i: %s\n", i, line);
			}
		}

		fclose(fp);
		fclose(fp2);

		fp = fopen(argv[1], "w");
		fp2 = fopen("temp", "r");
		if (debug == 1)
		{
			printf("Number of lines in temp file: %i\n", j);
			printf("Number of lines in original file: %i\n", i);
		}
		for (l = 1; fgets(line, max, fp2) != NULL && (l < i || l == i); l++){
			fprintf(fp, "%s", line);
			if (debug == 1)
			{
				printf("Line %i of temp file: %s\n", l, line);
				printf("l == %i\n", l);
			}
		}
		if (debug == 1)
			{
				printf("Line %i of temp file: %s\n", l, line);
				printf("l == %i\n", l);
			}
		printf("Prepping finished. File is now ready to be enciphered on the Engima Machine.\n");
	}
}
