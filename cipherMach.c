/*Program to illustrate usage of the Enigma as a function*/
/*Enigma function is included as a header and comes with a lot of #defines. */

#include <stdio.h>

#include "enigmaFunct.h"
/*DEFINES INCLUDED WITH enigmaFunct.h:

#define charDebug(x, y) if (debug == 1) \
                        { \
                            printf("%s %c\n", x, y); \
                        }
#define ctoi(c) c = (c -'0');
#define fixTooLarge(letter) if (letter > 'Z') \
                            { \
                                letter -= 26; \
                                charDebug("DEBUG: Letter - 26", letter); \
                            }
#define fixTooSmall(letter) if (letter < 'A') \
                            { \
                                letter += 26; \
                                charDebug("DEBUG: Letter + 26", letter); \
                            }
#define intDebug(x, y) if (debug == 1) \
                        { \
                            printf("%s %i\n", x, y); \
                        }
#define MAXLENGTH 10000
#define printNl printf("\n")
#define strDebug(x, y) if (debug == 1) \
                        { \
                            printf("%s %s\n", x, y); \
                        }
#define strCopy(s, s2) while(*s++ = *s2++){ \
                                ; \
                        }
#define toChar(x, y) x = y
#define toUppercase(c) if (c >= 'a' && c <= 'z') \
                        { \
                            c+= ('A' - 'a'); \
                        }*/

int bgetline(char s[], int putNl);

int main(){

    //ints
    int debug = 0;
    int help;
    int i, m; //Loop counters
    int lRotor, mRotor, rRotor; //Rotor settings
    int newline; //Collects the newline
    int offset1, offset2, offset3; //Offsets for the left, middle, and right-hand rotors
    int putNl;

    //chars
    char output[MAXLENGTH]; //Due to the nature of arrays in C, this has to be passed to the function
    char swap1, swap2, swap[26]; //For the plugboard: the first char, the second char, and the string to hold them
    char userInput[MAXLENGTH]; //MAXLENGTH is defined in enigmaFunct.h
    char yN; //Yes or no

    printf("\n\n\t\tCIPHER MACHINE\n\n");

    printf("Press 'h' for help or Enter to continue: ");
    if ((help = getchar()) == '\n') //They pressed Enter, move on
    {
        printf("Okay!\n\n");
    }
    else //They did anything else: print help
    {
        newline = getchar();
        printf("This is a program that replicates the Engima cipher machine used by the Germans in WWII. The program allows you to select the rotors, the starting positions for the rotors, and set the plugboard. One key feature of the Enigma was that it used the same settings to encipher or decipher. After that, it will ask you for a word, sentence, or phrase to encipher or decipher. Must be less than 10,000 characters. \n");
    }

    printf("Turn debugging on? (y/n): \n");
    if ((yN = getchar()) == 'y')
    {
        debug = 1;
    }
    newline = getchar();

    //Choose rotors
    printf("Which rotor would you like to put in the left-hand slot? (1, 2, or 3) [1]: ");
    if ((lRotor = getchar()) != '\n')
        newline = getchar();
    else lRotor = '1';
    lRotor = ctoi(lRotor); //Convert from char to literal numeral (ASCII to literal)

    printf("Which rotor would you like to put in the middle slot? (1, 2, or 3) [2]: ");
    if ((mRotor = getchar()) != '\n')
        newline = getchar();
    else mRotor = '2';
    mRotor = ctoi(mRotor); //Convert from char to literal numeral (ASCII to literal)

    printf("Which rotor would you like to put in the right-hand slot? (1, 2, or 3) [3]: ");
    if ((rRotor = getchar()) != '\n')
        newline = getchar();
    else rRotor = '3';
    rRotor = ctoi(rRotor); //Convert from char to literal numeral (ASCII to literal)

    //Set rotors
    printf("Please enter the starting letter for left-hand rotor: ");
    if ((offset1 = getchar()) != '\n')
        newline = getchar();
    else offset1 = 'A';
    offset1 -= 'A'; //Convert from letter to numeral
    intDebug("DEBUG: Offset1: ", offset1);

    printf("Please enter the starting letter for middle rotor: ");
    if ((offset2 = getchar()) != '\n')
        newline = getchar();
    else offset2 = 'A';
    offset2 -= 'A';
    intDebug("DEBUG: Offset2: ", offset2);

    printf("Please enter the starting letter for right-hand rotor: ");
    if ((offset3 = getchar()) != '\n')
        newline = getchar();
    else offset3 = 'A';
    offset3 -= 'A';
    intDebug("DEBUG: Offset3: ", offset3);

    //START SETTING PLUGBOARD
    for (i = m = 0; m < 13 && swap1 != '$'; m++){ //m counts the number of times the loop has been run
        printf("Set plugboard: Enter the two letters to be swapped (Enter '$' if you don't want to swap any more letters): ");
        swap1 = getchar();
        if (swap1 == '$')
        {
            strDebug("'$' was entered.", "\n");
            newline = getchar();
            break;
        }
        swap2 = getchar();
        newline = getchar();

        if (newline != 10)
        {
        	printf("ERROR: too many letters were entered. Please rerun the program.\n");
        	return -1;
        }

        if (swap1 > 'a' && swap1 < 'z')
        {
            toUppercase(swap1);
            charDebug("Uppercase now: swap1.", swap1);
        }
        if ((swap2 > 'a') && (swap2 < 'z'))
        {
            toUppercase(swap2);
            charDebug("Uppercase now: swap2.", swap2);
        }

        charDebug("swap1:", swap1);
        charDebug("swap2: ", swap2);

        if ((swap1 < 65) || (swap2 < 65))
        {
            printf("Please reenter both letters without separating them by a space or any other character.\n");
            charDebug("swap1:", swap1);
            charDebug("swap2: ", swap2);
            m--; //To counteract the increase that will happen when the loop is rerun
            continue;
        }
        else if ((swap1 == 10) || (swap2 == 10))
        {
            printf("Try again.\n");
            m--;
            continue;
        }
        else if ((swap1 < 65) || (swap2 < 65) || (swap1 > 90) || (swap2 > 90))
        {
            printf("Sorry, I did not understand that.\n");
            m--; //To counteract the increase that will happen when the loop is rerun
            continue;
        }
        else
        {
            swap[i++] = swap1;
            swap[i++] = swap2;
        }
    }
    //END SETTING PLUGBOARD
    strDebug("Swap list: ", swap);
    charDebug("swap1:", swap1);
    charDebug("swap2: ", swap2);

    swap[i] = '\0';

    printf("Enter a word or phrase less than %i characters: \n", MAXLENGTH);
    putNl = 0;
    i = bgetline(userInput, putNl);
    enigmaFunct(userInput, output, lRotor, mRotor, rRotor, offset1, offset2, offset3, swap, debug);
    printf("\n%s\n", output);
}
int bgetline(char s[], int putNl){
	int i;
	int c;

	for (i=0; i<MAXLENGTH-1 && (c=getchar()) !='$' && c!='\n'; ++i){
		s[i] = c;
    }
	if ((c == '\n') && (putNl == 1))
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
