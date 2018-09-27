#include <stdio.h>

/*This is a program to translate human-readable text into something the Enigma program can read and vice versa. Created by Bailie Livingston.*/

#define FILENAME filename
#define MAXLENGTH 10000
#define toUppercase(c) if (c >= 'a' && c <= 'z') \
                            { \
                                c+= ('A' - 'a'); \
                            }


int main(int argc, char *argv[]){ //main() takes two argments: the number of arguments and a pointer to an array of char strings. This allows for multiple command-line arguments.
    //ints
    int i, l, linePlace, fLPlace;
    int tempFileLines = 0;
    int debug = 1;

    //chars
    char c;
    char fileline[MAXLENGTH];
    char line[MAXLENGTH];
    char *enigmaMode = "e";
    char *humanMode = "h";

    //FILEs
    FILE *mainFile;
    FILE *tempFile;

    if (argc != 3)
    {
        printf("Usage: transEnigma.c filename mode\n");
        printf("Mode is \"h\" for human-readable text and \"e\" for Enigma-readable text.\n");
    }
    else
    {
        mainFile = fopen(argv[1], "r"); //Opens the file that needs translating
        tempFile = fopen("temp", "w");

        if (debug == 1)
            printf("Filename: %s\nMode: %s\n", argv[1], argv[2]);

        if (*argv[2] == *enigmaMode)
        {
            for (i = 1; (fgets(fileline, MAXLENGTH, mainFile)) != NULL; i++){
                linePlace = 0; //Start over for the place on the line to be written to the file
                if (debug == 1)
                {
                    printf("Fileline: %s\n", fileline);
                }
                for (fLPlace = 0; (c = fileline[fLPlace]) != '\0'; fLPlace++){
                    if (c >= 'a' && c <= 'z')
                    {
                        c+= ('A' - 'a');
                        line[linePlace++] = c;
                    }
                    else if (c >= 'A' && c <= 'Z')
                    {
                        line[linePlace++] = c;
                        if (debug == 1)
    					{
    						printf("%c\n", line[linePlace]);
    					}
                    }
                    /*Numbers are written out. Punctuation is assigned a value arbitrarily. Here is a list:
                        And symbol: written out
                        Asterisk: written out as "star"
                        At symbol: written out
                        Backslash: LQ
                        Close Parenthesis: QX
                        Colon: QZ
                        Comma: YY
                        Dash: YZ
                        Double quote: XZ
                        Equals: written out
                        Exclaimation point: ZY
                        Open Parenthesis: XQ
                        Percent symbol: PQ
                        Period: ZZ
                        Plus: written out
                        Pound sign: QP
                        Semicolon: ZQ
                        Single quote: ZX
                        Slash: QL
                        Space: XX
                        Question mark: QQ
                        */
                    else if ((c < 65) || ((c >= 91) && (c <= 96))) //If it's not an alphabetic character,
                    {
                        switch(c){
                        //In alphebetical order: first the ones with letter combos, then the written-out ones.
                        case '\\': //I had to escape the backslash. It only looks for and replaces one.
                            line[linePlace++] = 'L';
                            line[linePlace++] = 'Q';
                            break;
                        case ')':
                            line[linePlace++] = 'Q';
                            line[linePlace++] = 'X';
                            break;
                        case ':':
                            line[linePlace++] = 'Q';
                            line[linePlace++] = 'Z';
                            break;
                        case ',':
                            line[linePlace++] = 'Y';
                            line[linePlace++] = 'Y';
                            break;
                        case '-':
                            line[linePlace++] = 'Y';
                            line[linePlace++] = 'Z';
                            break;
                        case '"':
                            line[linePlace++] = 'X';
                            line[linePlace++] = 'Z';
                            break;
                        case '!':
                            line[linePlace++] = 'Z';
                            line[linePlace++] = 'Y';
                            break;
                        case '(':
                            line[linePlace++] = 'X';
                            line[linePlace++] = 'Q';
                            break;
                        case '%':
                            line[linePlace++] = 'P';
                            line[linePlace++] = 'Q';
                            break;
                        case '.':
                            line[linePlace++] = 'Z';
                            line[linePlace++] = 'Z';
                            break;
                        case '#':
                            line[linePlace++] = 'Q';
                            line[linePlace++] = 'P';
                            break;
                        case ';':
                            line[linePlace++] = 'Z';
                            line[linePlace++] = 'Q';
                            break;
                        case '\'': //Escaped the single quote.
                            line[linePlace++] = 'Z';
                            line[linePlace++] = 'X';
                            break;
                        case '/':
                            line[linePlace++] = 'Q';
                            line[linePlace++] = 'L';
                            break;
                        case 32: //Space
                            line[linePlace++] = 'X';
                            line[linePlace++] = 'X';
                            break;
                        case '?':
                            line[linePlace++] = 'Q';
                            line[linePlace++] = 'Q';
                            break;
                        case '1':
    						line[linePlace++] = 'O';
    						line[linePlace++] = 'N';
    						line[linePlace++] = 'E';
    						break;
    					case '2':
    						line[linePlace++] = 'T';
    						line[linePlace++] = 'W';
    						line[linePlace++] = 'O';
    						break;
    					case '3':
    						line[linePlace++] = 'T';
    						line[linePlace++] = 'H';
    						line[linePlace++] = 'R';
    						line[linePlace++] = 'E';
    						line[linePlace++] = 'E';
    						break;
    					case '4':
    						line[linePlace++] = 'F';
    						line[linePlace++] = 'O';
    						line[linePlace++] = 'U';
    						line[linePlace++] = 'R';
    						break;
    					case '5':
    						line[linePlace++] = 'F';
    						line[linePlace++] = 'I';
    						line[linePlace++] = 'V';
    						line[linePlace++] = 'E';
    						break;
    					case '6':
    						line[linePlace++] = 'S';
    						line[linePlace++] = 'I';
    						line[linePlace++] = 'X';
    						break;
    					case '7':
    						line[linePlace++] = 'S';
    						line[linePlace++] = 'E';
    						line[linePlace++] = 'V';
    						line[linePlace++] = 'E';
    						line[linePlace++] = 'N';
    						break;
    					case '8':
    						line[linePlace++] = 'E';
    						line[linePlace++] = 'I';
    						line[linePlace++] = 'G';
    						line[linePlace++] = 'T';
    						break;
    					case '9':
    						line[linePlace++] = 'N';
    						line[linePlace++] = 'I';
    						line[linePlace++] = 'N';
    						line[linePlace++] = 'E';
    						break;
    					case '0':
    						line[linePlace++] = 'Z';
    						line[linePlace++] = 'E';
    						line[linePlace++] = 'R';
    						line[linePlace++] = 'O';
    						break;
                        case '&':
    						line[linePlace++] = 'A';
    						line[linePlace++] = 'N';
    						line[linePlace++] = 'D';
    						break;
                        case '@':
    						line[linePlace++] = 'A';
    						line[linePlace++] = 'T';
    						break;
                        case '=':
    						line[linePlace++] = 'E';
    						line[linePlace++] = 'Q';
    						line[linePlace++] = 'U';
    						line[linePlace++] = 'A';
    						line[linePlace++] = 'L';
    						line[linePlace++] = 'S';
    						break;
                        case '+':
    						line[linePlace++] = 'P';
    						line[linePlace++] = 'L';
    						line[linePlace++] = 'U';
    						line[linePlace++] = 'S';
    						break;
    					case '*':
    						line[linePlace++] = 'S';
    						line[linePlace++] = 'T';
    						line[linePlace++] = 'A';
    						line[linePlace++] = 'R';
    						break;
                        case 10: //Leaves the newline
                            line[linePlace++] = 10;
                            break;
                        default:
                            printf("Sorry, %c is not permitted. Please remove it from your file and rerun the program.\n", c);
                            return -1;
                        }
                    }
                    else
                    {
                        printf("%c is not able to be translated. Please remove it from your file and try again.\n", c);
                    }
                }
                line[linePlace] = '\0';
                if (debug == 1)
                {
                    printf("Line: %s\n", line);
                }
                fprintf(tempFile, "%s", line);
            }
            fclose(tempFile);
            fclose(mainFile);
        }
        else if (*argv[2] == *humanMode)
        {
            for (i = 1; (fgets(fileline, MAXLENGTH, mainFile)) != NULL; i++){
                linePlace = 0; //Start over for the place on the line to be written to the file
                if (debug == 1)
                {
                    printf("Fileline: %s\n", fileline);
                }
                for (fLPlace = 0; (c = fileline[fLPlace]) != '\0'; fLPlace++){
                    toUppercase(c); //Should already be uppercase, so this is redundant and unnecessary, but whatever
                    //Since everything is uppercase anyway, the program will just go through and find patterns.
                    if (debug == 1)
                        printf("Place on fileline: %i\nCharacter: %c\n", fLPlace, fileline[fLPlace]);
                    switch (c){
                    case 'L':
                        if (fileline[fLPlace+1] == 'Q')
                        {
                            line[linePlace++] = '\\'; //Escaped the backslash
                            fLPlace++;
                        }
                        else
                        {
                            line[linePlace++] = c;
                            if (debug == 1)
                            {
                                printf("It was a letter.\n");
                            }
                        }
                        break;
                    case 'P':
                        if (fileline[fLPlace+1] == 'Q')
                        {
                            line[linePlace++] = '%';
                            fLPlace++;
                        }
                        else
                        {
                            line[linePlace++] = c;
                            if (debug == 1)
                            {
                                printf("It was a letter.\n");
                            }
                        }
                        break;
                    case 'Q':
                        if (fileline[fLPlace+1] == 'L')
                        {
                            line[linePlace++] = '/';
                            fLPlace++;
                        }
                        else if (fileline[fLPlace+1] == 'P')
                        {
                            line[linePlace++] = '#';
                            fLPlace++;
                        }
                        else if (fileline[fLPlace+1] == 'Q')
                        {
                            line[linePlace++] = '?';
                            fLPlace++;
                        }
                        else if (fileline[fLPlace+1] == 'X')
                        {
                            line[linePlace++] = ')';
                            fLPlace++;
                        }
                        else if (fileline[fLPlace+1] == 'Z')
                        {
                            line[linePlace++] = ':';
                            fLPlace++;
                        }
                        else
                        {
                            line[linePlace++] = c;
                            if (debug == 1)
                            {
                                printf("It was a letter.\n");
                            }
                        }
                        break;
                    case 'X':
                        if (fileline[fLPlace+1] == 'Q')
                        {
                            line[linePlace++] = '(';
                            fLPlace++;
                        }
                        else if (fileline[fLPlace+1] == 'X')
                        {
                            line[linePlace++] = ' '; //Space
                            fLPlace++;
                        }
                        else if (fileline[fLPlace+1] == 'Z')
                        {
                            line[linePlace++] = '"';
                            fLPlace++;
                        }
                        else
                        {
                            line[linePlace++] = c;
                            if (debug == 1)
                            {
                                printf("It was a letter.\n");
                            }
                        }
                        break;
                    case 'Y':
                        if (fileline[fLPlace+1] == 'Y')
                        {
                            line[linePlace++] = ',';
                            fLPlace++;
                        }
                        else if (fileline[fLPlace+1] == 'Z')
                        {
                            line[linePlace++] = '-';
                            fLPlace++;
                        }
                        else
                        {
                            line[linePlace++] = c;
                            if (debug == 1)
                            {
                                printf("It was a letter.\n");
                            }
                        }
                        break;
                    case 'Z':
                        if (fileline[fLPlace+1] == 'Q')
                        {
                            line[linePlace++] = ';';
                            fLPlace++;
                        }
                        else if (fileline[fLPlace+1] == 'X')
                        {
                            line[linePlace++] = '\''; //Escaped single quote
                            fLPlace++;
                        }
                        else if (fileline[fLPlace+1] == 'Y')
                        {
                            line[linePlace++] = '!';
                            fLPlace++;
                        }
                        else if (fileline[fLPlace+1] == 'Z')
                        {
                            line[linePlace++] = '.';
                            fLPlace++;
                        }
                        else
                        {
                            line[linePlace++] = c;
                            if (debug == 1)
                            {
                                printf("It was a letter.\n");
                            }
                        }
                        break;
                    default:
                        line[linePlace++] = c;
                        break;
                    }
                }
                line[linePlace] = '\0';
                if (debug == 1)
                {
                    printf("Line: %s\n", line);
                }
                fprintf(tempFile, "%s", line);
                tempFileLines++;
            }
            fclose(tempFile);
            fclose(mainFile);
        }
        else printf("The mode you specified was not either 'e' or 'h'. Please make sure you were using lowercase letters and that you specified one of those two modes.\n");

        mainFile = fopen(argv[1], "w");
		tempFile = fopen("temp", "r");
		if (debug == 1)
		{
			printf("Number of lines in temp file: %i\n", tempFileLines);
			printf("Number of lines in original file: %i\n", i);
		}
		for (l = 1; fgets(line, MAXLENGTH, tempFile) != NULL && (l < i || l == i); l++){
			fprintf(mainFile, "%s", line);
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
		printf("File was translated successfully.\n");
        return 1;
    }

}
