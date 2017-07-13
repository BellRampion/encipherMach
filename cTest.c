#include <stdio.h>


/*Each section of code, that for each rotor and the reflector, is separated by a long comment that informs the programmer which section they are about to enter.*/

/*The right-hand rotor is currently Rotor I; the middle rotor, Rotor II; and the left-hand rotor, Rotor III. The Reflector is Reflector B, since that was the standard reflector.*/

#define MAXLENGTH 10000
#define printAsChar(expr, x, y) x = y; printf(#expr " %c\n", x);
#define printNl printf("\n")
#define toUppercase(c) if (c >= 'a' && c <= 'z') \
                            { \
                                c+= ('A' - 'a'); \
                            }
int bgetline(char s[]);

int main()
{
	int letter; // The ASCII value of the key pressed
	int timesStepped; // The number of times the loop has been run, up to 26 (then it starts over)
    int newline; //Catches the newlines
    int debug;
    int i, j, k;
    int spaces;
    int deftSet;

	timesStepped = 0; // timesStepped starts at 0
	int turnover1 = 0;
	int turnover2 = 0;
    debug = 0;
    i = j = k = 0;

    char cha; // A CHAR to convert the ASCII value to a letter
    char input[MAXLENGTH];

    printf("Would you like to turn debugging on? (y/n):\n ");
    debug = getchar();
    newline = getchar();
    if (debug == 'y')
    {
        debug = 1;
    }
    else debug = 0;

//    printf("Which rotor would you like as the right-hand rotor? (1, 2, or 3): ");
//    i = getchar();
//    printNl;

    printf("Set rotor one: (enter an uppercase letter from A-Z): \n");
    i = getchar();
    newline = getchar();
    toUppercase(i);
    timesStepped = i - 'A'; //Entering A will produce a timesStepped of 0, entering B gives 1, and so on
	printf("Enter $ to stop the program.\n");
    printf("Enter a letter or phrase. Press the Return key when done: ");

    i = bgetline(input);

    letter = input[k]; // "letter" will receive input from the keyboard
    k++;
    toUppercase(letter);
//    printAsChar(,cha, letter);

	while (letter != '$' && letter != '\0') // While input is not equal to $, my EOF character
     {

/*------------------------------------					   ------------------------------------*/
/*------------------------------------*****Right-hand rotor*****-----------------------------------*/
/*------------------------------------					   ------------------------------------*/


		if (letter < 32 && letter != 10) // As long as the ASCII value of the character imputted is less than 32, and not equal to 10,
	     {
			letter = 48; // the new ASCII character is the one with the value of 48
		}


//		printf("letter %i ", letter); // Value of letter is printed. This is for error checking.
		if (letter != 32 && letter != 10)
		{
            if (timesStepped < 25)
            {
                ++timesStepped; //The rotor advances before enciphering the letter just entered. This is a feature of the real machine.
                //printf("\nIncreased timesStepped by one: %i\n", timesStepped);
            }
            else
            {
                timesStepped-= 25;
                if (debug == 1)
                {
                    printf("timesStepped after rotating: %i\n", timesStepped);
                }
        //        ++timesStepped;
        //        printf("timesStepped: %i\n", timesStepped);
            }
            if (letter != 10)
            {
                letter = letter + timesStepped; // Changes letter based on timesStepped
            }
/*          	if (timesStepped == 17)
          	{
          		++turnover1; //Notch to turn next rotor
          	}*/
		}
        if (debug == 1)
        {
            printAsChar(letter + timesStepped: , cha, letter); // More error checking
        }

        if (letter > 90) // If the new value is greater than 90, take away 26 and tell me
		{
		    letter = letter - 26;
            if (debug == 1)
            {
                printAsChar(Letter - 26: , cha, letter);
            }
        }
		if (letter < 65 && letter != 10 && letter != 32)
		{
			letter = letter + 26;
            if (debug == 1)
            {
                printAsChar(Letter + 26: , cha, letter);
            }
        }

		switch (letter) {
		case 'A':
			letter = 'E';
			break;
		case 'B':
			letter = 'K';
			break;
		case 'C':
			letter = 'M';
			break;
		case 'D':
			letter = 'F';
			break;
		case 'E':
			letter = 'L';
			break;
		case 'F':
			letter = 'G';
			break;
		case 'G':
			letter = 'D';
			break;
		case 'H':
			letter = 'Q';
			break;
		case 'I':
			letter = 'V';
			break;
		case 'J':
			letter = 'Z';
			break;
		case 'K':
			letter = 'N';
			break;
		case 'L':
			letter = 'T';
			break;
		case 'M':
			letter = 'O';
			break;
		case 'N':
			letter = 'W';
			break;
		case 'O':
			letter = 'Y';
			break;
		case 'P':
			letter = 'H';
			break;
		case 'Q':
			letter = 'X';
			break;
		case 'R':
			letter = 'U';
			break;
		case 'S':
			letter = 'S';
			break;
		case 'T':
			letter = 'P';
			break;
		case 'U':
			letter = 'A';
			break;
		case 'V':
			letter = 'I';
			break;
		case 'W':
			letter = 'B';
			break;
		case 'X':
			letter = 'R';
			break;
		case 'Y':
			letter = 'C';
			break;
		case 'Z':
			letter = 'J';
			break;
		default:
			break;
		}
        if (debug == 1)
        {
            printAsChar(Letter after first time through first rotor: , cha, letter);
        }

/*------------------------------------					------------------------------------*/
/*------------------------------------*****Middle rotor*****------------------------------------*/
/*------------------------------------					------------------------------------*/


		if (letter != 32 && letter != 10) //According to Wikipedia, the Middle rotor was affected by the stepping as well. When the whole Right-hand rotor turned, the contacts changed. i.e. If the rotor stepped once, when A was pressed, it would go through the B path and become K. The K would go into the Middle rotor as J.
		{
            letter-= timesStepped; // Changes letter based on timesStepped
            if (debug == 1)
            {
                printAsChar(Letter - timesStepped: , cha, letter); // More error checking
            }
        }

		if (letter > 90) // If the new value is greater than 90, take away 25 and tell me
		{
		     letter = letter - 26;
             if (debug == 1)
             {
                 printAsChar(Letter - 26: , cha, letter); // More error checking
             }
		}

		if (letter < 65 && letter != 10 && letter != 32)
		{
			letter = letter + 26;
            if (debug == 1)
            {
                printAsChar(Letter + 26: , cha, letter); // More error checking
            }
		}
/*		if (turnover1 == 1)
		{
			--letter;
			turnover1 = 0;
			++turnover2;
		} */

		switch (letter) {
		case 'A':
			letter = 'A';
			break;
		case 'B':
			letter = 'J';
			break;
		case 'C':
			letter = 'D';
			break;
		case 'D':
			letter = 'K';
			break;
		case 'E':
			letter = 'S';
			break;
		case 'F':
			letter = 'I';
			break;
		case 'G':
			letter = 'R';
			break;
		case 'H':
			letter = 'U';
			break;
		case 'I':
			letter = 'X';
			break;
		case 'J':
			letter = 'B';
			break;
		case 'K':
			letter = 'L';
			break;
		case 'L':
			letter = 'H';
			break;
		case 'M':
			letter = 'W';
			break;
		case 'N':
			letter = 'T';
			break;
		case 'O':
			letter = 'M';
			break;
		case 'P':
			letter = 'C';
			break;
		case 'Q':
			letter = 'Q';
			break;
		case 'R':
			letter = 'G';
			break;
		case 'S':
			letter = 'Z';
			break;
		case 'T':
			letter = 'N';
			break;
		case 'U':
			letter = 'P';
			break;
		case 'V':
			letter = 'Y';
			break;
		case 'W':
			letter = 'F';
			break;
		case 'X':
			letter = 'V';
			break;
		case 'Y':
			letter = 'O';
			break;
		case 'Z':
			letter = 'E';
			break;
		default:
			break;

		}
        if (debug == 1)
        {
            printAsChar(Letter after first time through middle rotor: , cha, letter);
        }

/*------------------------------------				    ------------------------------------*/
/*------------------------------------*****Left-hand rotor*****--------------------------------*/
/*------------------------------------				    ------------------------------------*/

/*		if (turnover2 == 26)
		{
			--letter;
			turnover2 = 0;
		} */

		switch (letter) {
		case 'A':
			letter = 'B';
			break;
		case 'B':
			letter = 'D';
			break;
		case 'C':
			letter = 'F';
			break;
		case 'D':
			letter = 'H';
			break;
		case 'E':
			letter = 'J';
			break;
		case 'F':
			letter = 'L';
			break;
		case 'G':
			letter = 'C';
			break;
		case 'H':
			letter = 'P';
			break;
		case 'I':
			letter = 'R';
			break;
		case 'J':
			letter = 'T';
			break;
		case 'K':
			letter = 'X';
			break;
		case 'L':
			letter = 'V';
			break;
		case 'M':
			letter = 'Z';
			break;
		case 'N':
			letter = 'N';
			break;
		case 'O':
			letter = 'Y';
			break;
		case 'P':
			letter = 'E';
			break;
		case 'Q':
			letter = 'I';
			break;
		case 'R':
			letter = 'W';
			break;
		case 'S':
			letter = 'G';
			break;
		case 'T':
			letter = 'A';
			break;
		case 'U':
			letter = 'K';
			break;
		case 'V':
			letter = 'M';
			break;
		case 'W':
			letter = 'U';
			break;
		case 'X':
			letter = 'S';
			break;
		case 'Y':
			letter = 'Q';
			break;
		case 'Z':
			letter = 'O';
			break;
		default:
			break;

		}
        if (debug == 1)
        {
            printAsChar(Letter after first time through left-hand rotor: , cha, letter);
        }

/*------------------------------------				  ------------------------------------*/
/*------------------------------------*****Reflector*****------------------------------------*/
/*------------------------------------				  ------------------------------------*/

/*This part of the code sends the letter back through the rotors a second time, so that the path it takes looks sort of like this:
---|
   | Imagine a sideways U.
---|  */
		switch (letter) {
		case 'A':
			letter = 'Y';
			break;
		case 'B':
			letter = 'R';
			break;
		case 'C':
			letter = 'U';
			break;
		case 'D':
			letter = 'H';
			break;
		case 'E':
			letter = 'Q';
			break;
		case 'F':
			letter = 'S';
			break;
		case 'G':
			letter = 'L';
			break;
		case 'H':
			letter = 'D';
			break;
		case 'I':
			letter = 'P';
			break;
		case 'J':
			letter = 'X';
			break;
		case 'K':
			letter = 'N';
			break;
		case 'L':
			letter = 'G';
			break;
		case 'M':
			letter = 'O';
			break;
		case 'N':
			letter = 'K';
			break;
		case 'O':
			letter = 'M';
			break;
		case 'P':
			letter = 'I';
			break;
		case 'Q':
			letter = 'E';
			break;
		case 'R':
			letter = 'B';
			break;
		case 'S':
			letter = 'F';
			break;
		case 'T':
			letter = 'Z';
			break;
		case 'U':
			letter = 'C';
			break;
		case 'V':
			letter = 'W';
			break;
		case 'W':
			letter = 'V';
			break;
		case 'X':
			letter = 'J';
			break;
		case 'Y':
			letter = 'A';
			break;
		case 'Z':
			letter = 'T';
			break;
		default:
			break;

		}
        if (debug == 1)
        {
            printAsChar(Letter after going through reflector: , cha, letter);
        }

/*------------------------------------								 ------------------------------------*/
/*------------------------------------*****Back through the Left-hand rotor*****--------------------------------*/
/*------------------------------------								 ------------------------------------*/

/*		if (turnover2 == 26)
		{
			++letter;
			turnover2 = 0;
		}*/

		switch (letter) {
		case 'A':
			letter = 'T';
			break;
		case 'B':
			letter = 'A';
			break;
		case 'C':
			letter = 'G';
			break;
		case 'D':
			letter = 'B';
			break;
		case 'E':
			letter = 'P';
			break;
		case 'F':
			letter = 'C';
			break;
		case 'G':
			letter = 'S';
			break;
		case 'H':
			letter = 'D';
			break;
		case 'I':
			letter = 'Q';
			break;
		case 'J':
			letter = 'E';
			break;
		case 'K':
			letter = 'U';
			break;
		case 'L':
			letter = 'F';
			break;
		case 'M':
			letter = 'V';
			break;
		case 'N':
			letter = 'N';
			break;
		case 'O':
			letter = 'Z';
			break;
		case 'P':
			letter = 'H';
			break;
		case 'Q':
			letter = 'Y';
			break;
		case 'R':
			letter = 'I';
			break;
		case 'S':
			letter = 'X';
			break;
		case 'T':
			letter = 'J';
			break;
		case 'U':
			letter = 'W';
			break;
		case 'V':
			letter = 'L';
			break;
		case 'W':
			letter = 'R';
			break;
		case 'X':
			letter = 'K';
			break;
		case 'Y':
			letter = 'O';
			break;
		case 'Z':
			letter = 'M';
			break;
		default:
			break;

		}
        if (debug == 1)
        {
            printAsChar(Letter after second time through left-hand rotor: , cha, letter);
        }

/*------------------------------------								  ------------------------------------*/
/*------------------------------------*****Back through the Middle rotor*****------------------------------------*/
/*------------------------------------								  ------------------------------------*/


/*		if (turnover1 == 1)
		{
			++letter;
			turnover1 = 0;
			++turnover2;
		} */

		switch (letter) {
		case 'A':
			letter = 'A';
			break;
		case 'B':
			letter = 'J';
			break;
		case 'C':
			letter = 'P';
			break;
		case 'D':
			letter = 'C';
			break;
		case 'E':
			letter = 'Z';
			break;
		case 'F':
			letter = 'W';
			break;
		case 'G':
			letter = 'R';
			break;
		case 'H':
			letter = 'L';
			break;
		case 'I':
			letter = 'F';
			break;
		case 'J':
			letter = 'B';
			break;
		case 'K':
			letter = 'D';
			break;
		case 'L':
			letter = 'K';
			break;
		case 'M':
			letter = 'O';
			break;
		case 'N':
			letter = 'T';
			break;
		case 'O':
			letter = 'Y';
			break;
		case 'P':
			letter = 'U';
			break;
		case 'Q':
			letter = 'Q';
			break;
		case 'R':
			letter = 'G';
			break;
		case 'S':
			letter = 'E';
			break;
		case 'T':
			letter = 'N';
			break;
		case 'U':
			letter = 'H';
			break;
		case 'V':
			letter = 'X';
			break;
		case 'W':
			letter = 'M';
			break;
		case 'X':
			letter = 'I';
			break;
		case 'Y':
			letter = 'V';
			break;
		case 'Z':
			letter = 'S';
			break;
		default:
			break;
		}
        if (debug == 1)
        {
            printAsChar(Letter after second time through middle rotor: , cha, letter);
        }

		if (letter != 32 && letter != 10) //According to Wikipedia, the Middle rotor was affected by the stepping as well. When the whole Right-hand rotor turned, the contacts changed. i.e. If the rotor stepped once, when A was pressed, it would go through the B path and become K. The K would go into the Middle rotor as J.
		{
         		letter = letter + timesStepped; // Changes letter based on timesStepped
                if (debug == 1)
                {
                    printAsChar(Letter + timesStepped: , cha, letter); // More error checking
                }
		}

		if (letter > 90) // If the new value is greater than 90, take away 26 and tell me
		{
		     letter = letter - 26;
             if (debug == 1)
             {
                 printAsChar(Letter - 26: , cha, letter); // More error checking
             }
		}

		if (letter < 65 && letter != 10 && letter != 32)
		{
			letter = letter + 26;
            if (debug == 1)
            {
                printAsChar(Letter + 26: , cha, letter); // More error checking
            }
		}

/*------------------------------------								 ------------------------------------*/
/*------------------------------------*****Back through the Right-hand rotor*****-------------------------------*/
/*------------------------------------								 ------------------------------------*/

		if (letter < 32 && letter != 10) // As long as the ASCII value of the character imputted is less than 32, and not equal to 10,
	     {
			letter = 48; // the new ASCII character is the one with the value of 48
		}

//		printf("letter %i", letter); // Value of letter is printed. This is for error checking.

		switch (letter) {
		case 'A':
			letter = 'U';
			break;
		case 'B':
			letter = 'W';
			break;
		case 'C':
			letter = 'Y';
			break;
		case 'D':
			letter = 'G';
			break;
		case 'E':
			letter = 'A';
			break;
		case 'F':
			letter = 'D';
			break;
		case 'G':
			letter = 'F';
			break;
		case 'H':
			letter = 'P';
			break;
		case 'I':
			letter = 'V';
			break;
		case 'J':
			letter = 'Z';
			break;
		case 'K':
			letter = 'B';
			break;
		case 'L':
			letter = 'E';
			break;
		case 'M':
			letter = 'C';
			break;
		case 'N':
			letter = 'K';
			break;
		case 'O':
			letter = 'M';
			break;
		case 'P':
			letter = 'T';
			break;
		case 'Q':
			letter = 'H';
			break;
		case 'R':
			letter = 'X';
			break;
		case 'S':
			letter = 'S';
			break;
		case 'T':
			letter = 'L';
			break;
		case 'U':
			letter = 'R';
			break;
		case 'V':
			letter = 'I';
			break;
		case 'W':
			letter = 'N';
			break;
		case 'X':
			letter = 'Q';
			break;
		case 'Y':
			letter = 'O';
			break;
		case 'Z':
			letter = 'J';
			break;
		default:
			break;
		}
        if (debug == 1)
        {
            printAsChar(Letter after second time through right-hand rotor: , cha, letter);
        }

/*------------------------------------				------------------------------------*/
/*------------------------------------*****Printer*****------------------------------------*/
/*------------------------------------				------------------------------------*/



		if (letter > 90) // If the new value is greater than 90, take away 25 and tell me
		{
		     letter = letter - 26;
             if (debug == 1)
             {
                 printAsChar(Letter - 26: , cha, letter); // More error checking
             }
		}

		if (letter < 65 && letter != 32 && letter != 10)
		{
			letter = letter + 26;
            if (debug == 1)
            {
                printAsChar(Letter + 26: , cha, letter); // More error checking
            }
		}
        if (letter > 90) // If the new value is greater than 90, take away 26 and tell me
		{
		     letter = letter - 26;
             if (debug == 1)
             {
                 printAsChar(Letter - 26: , cha, letter); // More error checking
             }
		}

        if (letter != 10)
        {
            letter-= timesStepped;
        }
		if (letter < 65 && letter != 10 && letter != 32)
		{
			letter = letter + 26;
            if (debug == 1)
            {
                printAsChar(Letter + 26: , cha, letter); // More error checking
            }
		}
        if (debug == 1)
        {
            printAsChar(Letter - timesStepped:, cha, letter);
        }
        if (j != 1)
        {
            cha = letter; // the CHAR is equal to the value of letter, and this converts the ASCII back to a letter
            printf("%c", cha); // Print it
        }
        else printNl;

        if (debug == 1)
        {
            printNl;
        }

		letter = input[k];
        k++;
        if (letter == 10)
		{
			newline = letter;
            j = 1;
			//letter = input[k];
		}
        else if (letter == 32)
        {
            spaces = letter;
            letter = 'X';
        }
        else j = 0;

        toUppercase(letter);

	}
    return 0;

}
int bgetline(char s[]){
	int i;
	int c;

	for (i=0; i<MAXLENGTH-1 && (c=getchar()) !='$' && c!='\n'; ++i){
		s[i] = c;
        if (c == 32)
        {
            i++;
            s[i] = c;
        }
    }
	if (c == '\n')
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
