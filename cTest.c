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
    //ints
    int letter; // The ASCII value of the key pressed
    int offset1; // Offset for the first rotor (or times the rotor has moved one step forward)
    int newline; //Catches the newlines
    int debug;
    int i, j, k, l, m;
    int spaces;
    int deftSet;
    int turnover1; //For the notches on the rotors
    int turnover2; //For the notches on the rotors
    int offset2; //Offset for the second rotor
    int offset3; //Offset for the third rotor

    //chars
    char cha; // A CHAR to convert the ASCII value to a letter
    char swap1; //To get letters to be swapped
    char swap2;
    char swap[26]; //For holding the letters to be swapped
    char input[MAXLENGTH];
    char output[MAXLENGTH];

    //FILEs
    FILE *fp;

	offset1 = 0; // offset1 starts at 0
	turnover1 = 0;
	turnover2 = 0;
	offset2 = 0;
	offset3 = 0;
    debug = 0;
    i = j = k = l = m = 0;

    printf("Would you like to turn debugging on? (y/n):\n ");
    debug = getchar();
    newline = getchar();
    if (debug == 'y')
    {
        debug = 1;
    }
    else debug = 0;

    fp = fopen("key_settings.txt", "a"); //Opens a file for appending to add the key settings for this message

    printf("Set right-hand rotor: (enter an uppercase letter from A-Z): \n");
    i = getchar();
    newline = getchar();
    toUppercase(i);
    cha = i;
    fprintf(fp, "\n%c", cha);
    offset1 = i - 'A'; //Entering A will produce a offset1 of 0, entering B gives 1, and so on

    printf("Set middle rotor: (enter an uppercase letter from A-Z): \n");
    i = getchar();
    newline = getchar();
    toUppercase(i);
    cha = i;
    fprintf(fp, "%c", cha);
    offset2 = i - 'A'; //Entering A will produce an offset of 0, entering B gives 1, and so on

    printf("Set left-hand rotor: (enter an uppercase letter from A-Z): \n");
    i = getchar();
    newline = getchar();
    toUppercase(i);
    cha = i;
    fprintf(fp, "%c", cha);
    offset3 = i - 'A'; //Entering A will produce a offset1 of 0, entering B gives 1, and so on
    
    if (debug == 1)
    {
        printf("l: %i\n", l);
        printf("swap1: %c\nswap2: %c\n", swap1, swap2);
    }
    //START SETTING PLUGBOARD
    for (i = m = 0; m < 13 && swap1 != '$'; m++){ //m counts the number of times the loop has been run
        printf("Set plugboard: Enter the two letters to be swapped (Enter '$' if you don't want to swap any more letters): ");
        swap1 = getchar();
        if (swap1 == '$')
        {
            if (debug == 1)
                printf("'$' was entered.\n");
            newline = getchar();
            break;
        }
        swap2 = getchar();
        newline = getchar();
        
        if (swap1 > 'a' && swap1 < 'z')
        {
            toUppercase(swap1);
            if (debug == 1)
            {
                printf("Uppercase now: swap1. %c\n", swap1);
            }
        }
        if (swap2 > 'a' && swap2 < 'z')
        {
            toUppercase(swap2);
            if (debug == 1)
            {
                printf("Uppercase now: swap2. %c\n", swap2);
            }
        }
        
        if (debug == 1)
        {
            printf("swap1: %c\nswap2: %c\n", swap1, swap2);
        }   
        
        if ((swap1 < 65) || (swap2 < 65))
        {
            printf("Please reenter both letters without separating them by a space or any other character.\n");
            if (debug == 1)
            {
                printf("Swap1: %c\nSwap2: %c\n", swap1, swap2);
            }
            m--; //To counteract the increase that will happen when the loop is rerun
            continue;
            if (debug == 1)
            {
                printf("Swap list: %s\n", swap);
                printf("Swap1: %c\nSwap2: %c\n", swap1, swap2);
            }
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
        /*if (debug == 1)
        {
            printf("Swap list: %s\n", swap);
            printf("Swap1: %c\nSwap2: %c\n", swap1, swap2);
        }*/
    }
    //END SETTING PLUGBOARD
    if (debug == 1)
    {
        printf("Swap list: %s\n", swap);
        printf("Swap1: %c\nSwap2: %c\n", swap1, swap2);
    }
    swap[i] = '\0';
    fprintf(fp, "%s\n", swap);
    fclose(fp); //Closes key_settings

    if (debug == 1)
    {
        printf("Offset1: %i\nOffset2: %i\nOffset3: %i\n", offset1, offset2, offset3);
        printf("Swapped letters: %s\n", swap);
    }

	printf("Enter $ to stop the program.\n");
    printf("Enter a letter or phrase. Press the Return key when done: ");

    i = bgetline(input);
    fp = fopen("input.txt", "a"); //Will record the input from the keyboard
    fprintf(fp, "\n==============================================================\n");
    fprintf(fp, "%s", input);
    fclose(fp);

    letter = input[k]; // "letter" will receive input from the keyboard
    k++;
    toUppercase(letter);
//    printAsChar(,cha, letter);

	while (letter != '$' && letter != '\0') // While input is not equal to $, my EOF character
     {

/*------------------------------------                   --------------------------------------*/
/*------------------------------------*****Plugboard*****--------------------------------------*/     
/*------------------------------------                   --------------------------------------*/
         for (i = 0; i < 13 && swap[i] != '\0'; i++){
            if (letter == swap[i])
            {
                if (debug == 1)
                {
                    printf("Letter before swap: %c\n", letter);
                }
                if (i % 2 != 0)
                {
                    letter = swap[i-1];
                    if (debug == 1)
                    {
                        printf("i: %i\nLetter after swap: %c\n", i, letter);
                    }
                }
                else letter = swap[i+1];
                
                if (debug == 1)
                {
                    printf("Letter after swapping: %c\n", letter);
                }
                break;
            }
        }


/*------------------------------------					   ------------------------------------*/
/*------------------------------------*****Right-hand rotor*****-----------------------------------*/
/*------------------------------------					   ------------------------------------*/


		/*if (letter < 32 && letter != 10) // As long as the ASCII value of the character imputted is less than 32, and not equal to 10,
	     {
			letter = 48; // the new ASCII character is the one with the value of 48
		}*/


//		printf("letter %i ", letter); // Value of letter is printed. This is for error checking.
		if (letter != 32 && letter != 10)
		{
            if (offset1 < 25)
            {
                ++offset1; //The rotor advances before enciphering the letter just entered. This is a feature of the real machine.
                //printf("\nIncreased offset1 by one: %i\n", offset1);
            }
            else
            {
                offset1-= 25;
                if (debug == 1)
                {
                    printf("offset1 after rotating: %i\n", offset1);
                }
            }
            if (letter != 10)
            {
                letter = letter + offset1; // Changes letter based on offset1
            }
/*          	if (offset1 == 17)
          	{
          		++turnover1; //Notch to turn next rotor
          	}*/
		}
        if (debug == 1)
        {
            printAsChar(letter + offset1: , cha, letter); // More error checking
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

	    #include "r1" //Includes wiring for first rotor
        
        if (debug == 1)
        {
            printAsChar(Letter after first time through first rotor: , cha, letter);
        }

/*------------------------------------					------------------------------------*/
/*------------------------------------*****Middle rotor*****------------------------------------*/
/*------------------------------------					------------------------------------*/


		if (letter != 32 && letter != 10) //According to Wikipedia, the Middle rotor was affected by the stepping as well. When the whole Right-hand rotor turned, the contacts changed. i.e. If the rotor stepped once, when A was pressed, it would go through the B path and become K. The K would go into the Middle rotor as J.
		{
            letter-= offset1; // Changes letter based on offset1
            if (debug == 1)
            {
                printAsChar(Letter - offset1: , cha, letter); // More error checking
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

        if (letter != 32 && letter != 10) //Changing letter based on offset2
		{
            letter+= offset2; // Changes letter based on offset2
            if (debug == 1)
            {
                printAsChar(Letter + offset2: , cha, letter); // More error checking
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

/*		if (turnover1 == 1)
		{
			--letter;
			turnover1 = 0;
			++turnover2;
		} */

		#include "r2" //Includes the wiring for the 2nd rotor
        if (debug == 1)
        {
            printAsChar(Letter after first time through middle rotor: , cha, letter);
        }

/*------------------------------------				    ------------------------------------*/
/*------------------------------------*****Left-hand rotor*****--------------------------------*/
/*------------------------------------				    ------------------------------------*/

        if (letter != 32 && letter != 10) //Changing letter based on offset2
        {
            letter-= offset2; // Changes letter based on offset2
            if (debug == 1)
            {
                printAsChar(Letter - offset2: , cha, letter); // More error checking
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

        if (letter != 32 && letter != 10) //Changing letter based on offset2
        {
            letter+= offset3; // Changes letter based on offset2
            if (debug == 1)
            {
                printAsChar(Letter + offset3: , cha, letter); // More error checking
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

/*		if (turnover2 == 26)
		{
			--letter;
			turnover2 = 0;
		} */

		#include "r3"

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

        if (letter != 32 && letter != 10) //Changing letter based on offset3
        {
            letter-= offset3; // Changes letter based on offset3
            if (debug == 1)
            {
                printAsChar(Letter - offset3: , cha, letter); // More error checking
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

        #include "reflector"
        if (debug == 1)
        {
            printAsChar(Letter after going through reflector: , cha, letter);
        }

/*------------------------------------							------------------------------------*/
/*------------------------------------*****Back through the Left-hand rotor*****--------------------*/
/*------------------------------------							------------------------------------*/

/*		if (turnover2 == 26)
		{
			++letter;
			turnover2 = 0;
		}*/
        if (letter != 32 && letter != 10) //Changing letter based on offset3
        {
            letter+= offset3; // Changes letter based on offset3
            if (debug == 1)
            {
                printAsChar(Letter + offset3: , cha, letter); // More error checking
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

		#include "r3Back"
        if (debug == 1)
        {
            printAsChar(Letter after second time through left-hand rotor: , cha, letter);
        }
/*------------------------------------								         ------------------------------------*/
/*------------------------------------*****Back through the Middle rotor*****------------------------------------*/
/*------------------------------------								         ------------------------------------*/
        if (letter != 32 && letter != 10) //Changing letter based on offset3
        {
            letter-= offset3; // Changes letter based on offset3
            if (debug == 1)
            {
                printAsChar(Letter - offset3: , cha, letter); // More error checking
            }
        }
        if (letter < 65 && letter != 10 && letter != 32) //Makes sure the letter is not less than A
		{
			letter = letter + 26;
            if (debug == 1)
            {
                printAsChar(Letter + 26: , cha, letter); // More error checking
            }
		}

        if (letter != 32 && letter != 10) //Changing letter based on offset2
        {
            letter+= offset2; // Changes letter based on offset2
            if (debug == 1)
            {
                printAsChar(Letter + offset2: , cha, letter); // More error checking
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

        /*if (turnover1 == 1)
        {
            ++letter;
            turnover1 = 0;
            ++turnover2;
        } */
        #include "r2Back"


        if (debug == 1)
        {
            printAsChar(Letter after second time through middle rotor: , cha, letter);
        }

        if (letter != 32 && letter != 10) //Changing letter based on offset2
        {
            letter-= offset2; // Changes letter based on offset2
            if (debug == 1)
            {
                printAsChar(Letter - offset2: , cha, letter); // More error checking
            }
        }
        if (letter < 65 && letter != 10 && letter != 32) //Makes sure the letter is not less than A
		{
			letter = letter + 26;
            if (debug == 1)
            {
                printAsChar(Letter + 26: , cha, letter); // More error checking
            }
		}

        if (letter != 32 && letter != 10) //According to Wikipedia, the Middle rotor was affected by the stepping as well. When the whole Right-hand rotor turned, the contacts changed. i.e. If the rotor stepped once, when A was pressed, it would go through the B path and become K. The K would go into the Middle rotor as J.
        {
            letter = letter + offset1; // Changes letter based on offset1
            if (debug == 1)
            {
                printAsChar(Letter + offset1: , cha, letter); // More error checking
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

/*------------------------------------								        ------------------------------------*/
/*------------------------------------*****Back through the Right-hand rotor*****-------------------------------*/
/*------------------------------------								        ------------------------------------*/

		if (letter < 32 && letter != 10) // As long as the ASCII value of the character imputted is less than 32, and not equal to 10,
	     {
			letter = 48; // the new ASCII character is the one with the value of 48
		}

//		printf("letter %i", letter); // Value of letter is printed. This is for error checking.

	#include "r1Back"
        if (debug == 1)
        {
            printAsChar(Letter after second time through right-hand rotor: , cha, letter);
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
            letter-= offset1;
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
            printAsChar(Letter - offset1:, cha, letter);
        }

/*------------------------------------                   --------------------------------------*/
/*------------------------------------*****Plugboard*****--------------------------------------*/     
/*------------------------------------                   --------------------------------------*/
         for (i = m = 0; m < 13 && swap1 != '$'; m++){ //m counts the number of times the loop has been run
        printf("Set plugboard: Enter the two letters to be swapped (Enter '$' if you don't want to swap any more letters): ");
        swap1 = getchar();
        if (swap1 == '$')
        {
            if (debug == 1)
                printf("'$' was entered.\n");
            newline = getchar();
            break;
        }
        swap2 = getchar();
        newline = getchar();
        
        if (swap1 > 'a' && swap1 < 'z')
        {
            toUppercase(swap1);
            if (debug == 1)
            {
                printf("Uppercase now: swap1. %c\n", swap1);
            }
        }
        if (swap2 > 'a' && swap2 < 'z')
        {
            toUppercase(swap2);
            if (debug == 1)
            {
                printf("Uppercase now: swap2. %c\n", swap2);
            }
        }
        
        if (debug == 1)
        {
            printf("swap1: %c\nswap2: %c\n", swap1, swap2);
        }   
        
        if ((swap1 < 65) || (swap2 < 65))
        {
            printf("Please reenter both letters without separating them by a space or any other character.\n");
            if (debug == 1)
            {
                printf("Swap1: %c\nSwap2: %c\n", swap1, swap2);
            }
            m--; //To counteract the increase that will happen when the loop is rerun
            continue;
            if (debug == 1)
            {
                printf("Swap list: %s\n", swap);
                printf("Swap1: %c\nSwap2: %c\n", swap1, swap2);
            }
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
        /*if (debug == 1)
        {
            printf("Swap list: %s\n", swap);
            printf("Swap1: %c\nSwap2: %c\n", swap1, swap2);
        }*/
    }

/*------------------------------------				   ------------------------------------*/
/*------------------------------------*****Printer*****------------------------------------*/
/*------------------------------------				   ------------------------------------*/
		
        if (j != 1)
        {
            cha = letter; // the CHAR is equal to the value of letter, and this converts the ASCII back to a letter
            printf("%c", cha); // Print it
            output[l] = cha;
            ++l;
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
	}
        else if (letter == 32)
        {
            spaces = letter;
            letter = 'X';
        }
        else j = 0;

        toUppercase(letter);

    }

    fp = fopen("output.txt", "a");
    fprintf(fp, "\n==========================================================\n");
    if (debug == 1)
    {
        printf("Output[]: %s\n", output);
    }
    fprintf(fp, "%s", output);
    fclose(fp);

    /*printf("WARNING: All input and output will be deleted when you next run this program. Copy the file to a different location to save your data.\n"); */


    printf("Enter any letter to close the program: \n");
    i = getchar();
    return 0;

}
int bgetline(char s[]){
	int i;
	int c;

	for (i=0; i<MAXLENGTH-1 && (c=getchar()) !='$' && c!='\n'; ++i){
	    s[i] = c;
        }
	if (c == '\n')
	{
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
