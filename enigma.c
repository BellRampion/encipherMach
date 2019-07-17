#include <stdio.h>

/*THE ENIGMA MACHINE*/

/* COPYRIGHT AND LICENSE
Copyright 2019 by Bailie Livingston.
This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
/*Created by Bailie Livingston.*/

#define charDebug(x, y) if (debug == 1) \
                        { \
                            if (fileDebug != 1) /*This cannot be done as an ifdef because those can't be inside macro definitions*/ \
                            { \
                                printf("%s %c\n", x, y); \
                            } \
                            else \
                            { \
                                fprintf(debuggingFile, "%s %c\n", x, y); \
                            } \
                        }

#define ctoi(c) c = (c -'0');

#define DEBUGGINGFILE debugFile

#define fileLength(fp, i, fileName, s) fp = fopen(fileName, "r"); \
									for (i = 0; fgets(s, MAXLENGTH, fp) != NULL; i++){ \
										; \
									} \
                                    fclose(fp);
#define FILENAME filename
#define getFilename(filename, putNl) printf("Enter the name of the file, including extensions: \n"); \
/*sets it to false*/    putNl = 0; \
                        i = bgetline(filename, putNl); \
                        putNl = 1; //Back to true
#define INPUTSTORED inputStorage
#define intDebug(x, y) if (debug == 1) \
                        { \
                            if (fileDebug != 1) /*This cannot be done as an ifdef because those can't be inside macro definitions*/ \
                            { \
                                printf("%s %i\n", x, y); \
                            } \
                            else \
                            { \
                                fprintf(debuggingFile, "%s %i\n", x, y); \
                            } \
                        }
#define MAXLENGTH 10000
#define OUTPUTFILE outputFile
#define printNl printf("\n")
#define strDebug(x, y) if (debug == 1) \
                        { \
                            if (fileDebug != 1) /*This cannot be done as an ifdef because those can't be inside macro definitions*/ \
                            { \
                                printf("%s %s\n", x, y); \
                            } \
                            else \
                            { \
                                fprintf(debuggingFile, "%s %s\n", x, y); \
                            } \
                        }
#define strCopy(s, s2) while(*s++ = *s2++){ \
                                ; \
                        }
#define toChar(x, y) x = y
#define toUppercase(c) if (c >= 'a' && c <= 'z') \
                        { \
                            c+= ('A' - 'a'); \
                        }

int bgetline(char s[], int putNl);
int fillArray(char options[], char filename[], int numLooped);
int findInArray(char list[], char character);
int isOptionSet(char options[], char *option, FILE *fp, int *numLooped); //Takes the file and actually reads it. Returns 0 if a specific option isn't supposed to be set
int rotorL(int letter, int lRotor, int debug); //Left-hand rotor
int rotorM(int letter, int mRotor, int debug); //Middle rotor
int rotorR(int letter, int rRotor, int debug); //Right-hand rotor
int setOptions(char options[], char *option, int *option1, char debugFile[], int *option2, char filename[], int *setOutputFile, char outputFile[], int *setInputStorage, char inputStorage[]); //Reads file and sets options. Takes the /address/ of option1, etc. instead of the value (shows as a pointer in the declaration). This allows the function to actually modify the variable.

int fileDebug = 0; //To debug into a file or not
int timeL; //Whether the value has gone through the left-hand rotor once or not
int timeM; //Whether the value has gone through the middle rotor once or not
int timeR; //Whether the value has gone through the right-hand rotor once or not
char debugFile[MAXLENGTH]; //Filename to debug into
FILE *debuggingFile; //Pointer to the debugging file. Must be global because of the rotor functions.
char stdAlphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char rotor1Wiring[] = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
char rotor2Wiring[] = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
char rotor3Wiring[] = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
char reflectorBWiring[] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";

int main()
{
    //ints
    int call; //For calling functions
    int countInput = 0; //Counting chars of input
    int debug;
    int filelength = 0;
    int fillOutput = 0; //Filling output[] for printing to a file
    int i, j, k, l, m; //Random vars to do whatever.
    int index = 0;
    int letter; // The ASCII value of the key pressed
    int linesProcessed = 0;
    int lRotor; //Rotor used for the left-hand rotor
    int max = MAXLENGTH;
    int mRotor; //Rotor used for the middle rotor
    int newline; //Catches the newlines
	int offset1; // Offset for the left-hand rotor (or times the rotor has moved one step forward)
    int offset2; //Offset for the middle rotor
    int offset3; //Offset for the right-hand rotor
    int optionsOn = 0;
    int putNl;
    int readFile = 0; //Option to read from file
    int rRotor; //Rotor used for the right-hand rotor
    int setInputStorage = 0;
    int setOutputFile = 0;
    int spaces;
    int turnover1; //For the notches on the rotors
    int turnover2; //For the notches on the rotors

    //chars
    char cha; // A CHAR to convert the ASCII value to a letter
    char swap1; //To get letters to be swapped
    char swap2;
    char fileline[MAXLENGTH];
    char filename[MAXLENGTH];
    char input[MAXLENGTH];
    char inputStorage[MAXLENGTH];
    char output[MAXLENGTH];
    char outputFile[MAXLENGTH];
    char options[MAXLENGTH];
    char swap[26]; //For holding the letters to be swapped
    char *option;

    //FILEs
    FILE *fp;
    FILE *fp2;

    debug = 0;
	offset1 = 0; // offset1 starts at 0
    offset2 = 0;
    offset3 = 0;
	turnover1 = 0;
	turnover2 = 0;
    i = j = k = l = m = 0;


    printf("ENIGMA MACHINE\n");
    printf("Enter h for help or enter to continue: ");
    if ((i = getchar()) != '\n')
    {
        newline = getchar();
        if (i == 'h')
            printf("This program allows you to set options in a profile. To do this, create a file named \".enigmarc\" in the folder containing this program. In it, you can set four different options: \n1. Debugging\n2.Taking input from a file\n3.Piping the output to a file\n4.Recording the input in a file.\nSeparate each option by a ';' and place a ';' after the last option in a line. Up to %i characters on a line are supported.\n\nSome options take parameters. The optional parameters are indicated by square brackets.\n\n1. Debugging: debug[=foo.txt] If you don't want to record to a file, put the ';' immediately after the '=' e.g. \"debug=;\". \n2. Input from a file: input[=foo.txt]\n3. Piping output to a file: output[=foo.txt] No spaces are allowed in the filename. By default, output is stored in output.txt. If you don't want to record to a file at all, put the ';' immediately after the '=' e.g. \"output=; storeInput=input.txt;\".\n" "4. Recording input in a file: storeInput[=foo.txt] No spaces are allowed in the filename. By default, input is stored in input.txt. If you don't want to record to a file at all, put the ';' immediately after the '=' e.g. \"storeInput=; debug;\".\n\n", MAXLENGTH);
    }
    call = setOptions(options, option, &debug, debugFile, &readFile, filename, &setOutputFile, outputFile, &setInputStorage, inputStorage); //Takes an array to get the lines from the config file, a pointer for holding the current option, the address of debug, an array for the debug output filename, the address of readFile, setOutputFile, and setInputstorage, an array for the filename, an array for the output file's name, and an array for the input storage file's name.

    if (debug == 1)
    {
        debuggingFile = fopen("debuggingOutput.txt", "a");
        fprintf(debuggingFile, "==New runthrough==\n");
        fileDebug = 1;
    }
    else if (debug == 2)
    {
        debuggingFile = fopen(DEBUGGINGFILE, "a");
        fprintf(debuggingFile, "==New runthrough==\n");
        fileDebug = 1;
    }
    else if (debug == 3)
    {
        fileDebug = 0;
        debug = 1;
    }
    else ;

	printf("Choose the rotor to put in the right-hand slot: (1, 2, or 3) [1]\n");
	if ((cha = getchar()) != '\n')
        newline = getchar();
    else cha = '1';
	rRotor = ctoi(cha);
	intDebug("The converted rotor number: ", rRotor);

	printf("Choose the rotor to put in the middle slot: (1, 2, or 3) [2]\n");
    if ((cha = getchar()) != '\n')
        newline = getchar();
    else cha = '2';
	mRotor = ctoi(cha);
	intDebug("The converted rotor number: ", mRotor);

	printf("Choose the rotor to put in the left-hand slot: (1, 2, or 3) [3]\n");
    if ((cha = getchar()) != '\n')
        newline = getchar();
    else cha = '3';
	lRotor = ctoi(cha);
	intDebug("The converted rotor number: ", lRotor);

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

    intDebug("l: ", l);
    charDebug("swap1:", swap1);
    charDebug("swap2: ", swap2);


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
    fprintf(fp, "%s\n", swap);

    fclose(fp); //Closes key_settings

    intDebug("Offset1: ", offset1);
    intDebug("Offset2: ", offset2);
    intDebug("Offset3: ", offset3);

	printf("Enter $ to stop the program.\n");

    if (readFile == 1)
    {
        if (filename[0] == '\0')
        {
            getFilename(filename, putNl);
        }
        fileLength(fp2, filelength, filename, fileline);
        intDebug("Length of file:", filelength);
        fp2 = fopen(FILENAME, "r"); //Open the file
        fgets(fileline, max, fp2); //Get a line from the file
        for (m = 0; (fileline[m] != '\0') && m < MAXLENGTH-1; m++) //Copy the line to input
            input[m] = fileline[m];

        input[m] = '\0';
    }
    else
	{
        printf("Enter a letter or phrase. Press the Return key when done: ");
        i = bgetline(input, putNl);
        filelength = 1;
    }

    for (linesProcessed = 0; linesProcessed < filelength; linesProcessed++){ //This lets you do multiple lines of a file in one go instead of rerunning the program each time.

        intDebug("linesProcessed:", linesProcessed);
        if (linesProcessed > 0)
        {
            fgets(fileline, max, fp2); //Get a line from the file
            for (m = 0; (fileline[m] != '\0') && m < MAXLENGTH-1; m++) //Copy the line to input
                input[m] = fileline[m];

            input[m] = '\0';
        }
        strDebug("input[]:", input);
        if (setInputStorage == 1)
        {
            if (inputStorage[0] == '\n') //If the first character is a newline, that means the user wished to specify the filename during runtime
            {
                strDebug("inputStorage:", inputStorage);
                getFilename(inputStorage, putNl); //Get filename from user
            }
            fp = fopen(INPUTSTORED, "a"); //Either way, open the file defined as INPUTSTORED for appending
            if (linesProcessed == 0)
            {
                fprintf(fp, "\n==============================================================\n");
            }
            fprintf(fp, "%s", input);
            fclose(fp);
        }
        else if (setInputStorage == 0)
        {
            if (inputStorage[0] != '\0')
            {
                fp = fopen("input.txt", "a"); //Will record the input from the keyboard
                if (linesProcessed == 0)
                {
                    fprintf(fp, "\n==============================================================\n");
                }
                fprintf(fp, "%s", input);
                fclose(fp);
            }
        }
        else ;

        countInput = 0; //countInput must be reset after each line
        fillOutput = 0; //And fillOutput, too
        letter = input[countInput++]; // "letter" will receive input from the keyboard
        toUppercase(letter);

        while (letter != '$' && letter != '\0') // While input is not equal to $, my EOF character
         {
         	//Resets the markers for if the letter has gone through each rotor once or not
         	timeL = 0;
         	timeM = 0;
         	timeR = 0;

    /*------------------------------------                   --------------------------------------*/
    /*------------------------------------*****Plugboard*****--------------------------------------*/
    /*------------------------------------                   --------------------------------------*/
             for (i = 0; i < 13 && swap[i] != '\0'; i++){
                if (letter == swap[i])
                {
                    charDebug("Letter after swapping: ", letter);
                    if (i % 2 != 0)
                    {
                        letter = swap[i-1];
                        intDebug("i:", i);
                        charDebug("Letter after swap: ", letter);
                    }
                    else letter = swap[i+1];

                    charDebug("Letter after swapping: ", letter);
                    break;
                }
            }


    /*------------------------------------					   ------------------------------------*/
    /*------------------------------------*****Right-hand Rotor*****--------------------------------*/
    /*------------------------------------					   ------------------------------------*/

    		if (letter < 32 && letter != 10) // As long as the ASCII value of the character imputted is less than 32, and not equal to 10,
    	     {
    			letter = 48; // the new ASCII character is the one with the value of 48
    		}

    		if (letter != 32 && letter != 10)
    		{
                if (offset1 < 25)
                {
                    ++offset1; //The rotor advances before enciphering the letter just entered. This is a feature of the real machine.
                }
                else
                {
                    offset1-= 25;
                    intDebug("offset1 after rotating: ", offset1);
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
            cha = letter;
            charDebug("Letter + offset1 ", cha);

            if (letter > 90) // If the new value is greater than 90, take away 26 and tell me
    		{
    		    letter = letter - 26;
                charDebug("Letter - 26: ", letter);
            }
    		if (letter < 65 && letter != 10 && letter != 32)
    		{
    			letter = letter + 26;
                cha = letter;
                charDebug("Letter + 26: ", cha);
            }

    		//Actually sents the letter through the wiring
    		letter = rotorR(letter, rRotor, debug);

            timeR = 1; //Marks going through RH rotor once
            intDebug("timeR after letter has gone through right-hand rotor: ", timeR);

            charDebug("Letter after first time through first rotor: ", letter);

    /*------------------------------------					------------------------------------*/
    /*------------------------------------*****Middle Rotor*****------------------------------------*/
    /*------------------------------------					------------------------------------*/


    		if (letter != 32 && letter != 10) //According to Wikipedia, the Middle rotor was affected by the stepping as well. When the whole left-hand rotor turned, the contacts changed. i.e. If the rotor stepped once, when A was pressed, it would go through the B path and become K. The K would go into the Middle rotor as J.
    		{
                letter-= offset1; // Changes letter based on offset1
                toChar(cha, letter);
                charDebug("Letter - offset1:", cha);
            }

    		if (letter < 65 && letter != 10 && letter != 32)
    		{
    			letter = letter + 26;
                toChar(cha, letter);
                charDebug("Letter + 26: ", cha);
    		}

            if (letter != 32 && letter != 10) //Changing letter based on offset2
    		{
                letter+= offset2; // Changes letter based on offset2
                toChar(cha, letter);
                charDebug("Letter + offset2:", cha);
            }
            if (letter > 90) // If the new value is greater than 90, take away 25 and tell me
    		{
    		     letter = letter - 26;
                 toChar(cha, letter);
                 charDebug("Letter - 26: ", cha);
    		}

    /*		if (turnover1 == 1)
    		{
    			--letter;
    			turnover1 = 0;
    			++turnover2;
    		} */

            //Sends the letter through the wiring
    		letter = rotorM(letter, mRotor, debug);
            timeM = 1;
            toChar(cha, letter);
            charDebug("Letter after first time through middle rotor: ", cha);

    /*------------------------------------				    ------------------------------------*/
    /*------------------------------------*****Left-hand Rotor*****--------------------------------*/
    /*------------------------------------				    ------------------------------------*/

            if (letter != 32 && letter != 10) //Changing letter based on offset2
            {
                letter-= offset2; // Changes letter based on offset2
                toChar(cha, letter);
                charDebug("Letter - offset2:", cha);
            }
            if (letter < 65 && letter != 10 && letter != 32)
            {
                letter = letter + 26;
                toChar(cha, letter);
                charDebug("Letter + 26:", cha);
            }

            if (letter != 32 && letter != 10) //Changing letter based on offset3
            {
                letter += offset3; // Changes letter based on offset3
                toChar(cha, letter);
                charDebug("Letter + offset3:", cha);
            }
            if (letter > 90) // If the new value is greater than 90, take away 25 and tell me
            {
                letter = letter - 26;
                toChar(cha, letter);
                charDebug("Letter - 26: ", cha);
            }

    /*		if (turnover2 == 26)
    		{
    			--letter;
    			turnover2 = 0;
    		} */

            //Sends the letter through the wiring
    		letter = rotorL(letter, lRotor, debug);
            timeL = 1;
            toChar(cha, letter);
            charDebug("Letter after first time through left-hand rotor: ", cha);

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
                toChar(cha, letter);
                charDebug("Letter - offset3:", cha);
            }
            if (letter < 65 && letter != 10 && letter != 32)
            {
                letter = letter + 26;
                charDebug("Letter + 26: ", letter);
            }

            index = findInArray(stdAlphabet, letter);
            letter = reflectorBWiring[index];
            charDebug("\nLetter after going through reflector: ", letter);

    /*------------------------------------							------------------------------------*/
    /*----------------------------*****Back through the Left-hand Rotor*****---------------------------*/
    /*------------------------------------							------------------------------------*/

    /*		if (turnover2 == 26)
    		{
    			++letter;
    			turnover2 = 0;
    		}*/
            if (letter != 32 && letter != 10) //Changing letter based on offset3
            {
                letter+= offset3; // Changes letter based on offset3
                toChar(cha, letter);
                charDebug("Letter + offset3:", cha);
            }
            if (letter > 90) // If the new value is greater than 90, take away 25 and tell me
            {
                 letter = letter - 26;
                 toChar(cha, letter);
                 charDebug("Letter - 26: ", cha);
            }

            //Sends the letter through the wiring
    		letter = rotorL(letter, lRotor, debug);
            toChar(cha, letter);
            charDebug("Letter after second time through right-hand rotor: ", cha);
    /*------------------------------------								       ------------------------------------*/
    /*----------------------------------*****Back through the Middle Rotor*****------------------------------------*/
    /*------------------------------------								       ------------------------------------*/
            if (letter != 32 && letter != 10) //Changing letter based on offset3
            {
                letter-= offset3; // Changes letter based on offset3
                toChar(cha, letter);
                charDebug("Letter - offset3: ", cha);
            }
            if (letter < 65 && letter != 10 && letter != 32) //Makes sure the letter is not less than A
    		{
    			letter = letter + 26;
                toChar(cha, letter);
                charDebug("Letter + 26: ", cha);
    		}

            if (letter != 32 && letter != 10) //Changing letter based on offset2
            {
                letter += offset2; // Changes letter based on offset2
                toChar(cha, letter);
                charDebug("Letter + offset2:", cha);
            }
            if (letter > 90) // If the new value is greater than 90, take away 25 and tell me
            {
                 letter = letter - 26;
                 toChar(cha, letter);
                 charDebug("Letter - 26: ", cha);
            }

            /*if (turnover1 == 1)
            {
                ++letter;
                turnover1 = 0;
                ++turnover2;
            } */
            //Sends the letter through the wiring
    		letter = rotorM(letter, mRotor, debug);

            toChar(cha, letter);
            charDebug("Letter after second time through middle rotor: ", cha);

            if (letter != 32 && letter != 10) //Changing letter based on offset2
            {
                letter-= offset2; // Changes letter based on offset2
                toChar(cha, letter);
                charDebug("Letter - offset2:", cha);
            }
            if (letter < 65 && letter != 10 && letter != 32) //Makes sure the letter is not less than A
    		{
    			letter = letter + 26;
                toChar(cha, letter);
                charDebug("Letter + 26:", cha);
    		}

            if (letter != 32 && letter != 10) //According to Wikipedia, the Middle rotor was affected by the stepping as well. When the whole left-hand rotor turned, the contacts changed. i.e. If the rotor stepped once, when A was pressed, it would go through the B path and become K. The K would go into the Middle rotor as J.
            {
                letter = letter + offset1; // Changes letter based on offset1
                toChar(cha, letter);
                charDebug("Letter + offset1:", cha);
            }

            if (letter > 90) // If the new value is greater than 90, take away 26 and tell me
    		{
    		     letter = letter - 26;
                 toChar(cha, letter);
                 charDebug("Letter - 26:", cha);
    		}

    		if (letter < 65 && letter != 10 && letter != 32)
    		{
    			letter = letter + 26;
                toChar(cha, letter);
                charDebug("Letter + 26:", cha);
    		}

    /*------------------------------------								       ------------------------------------*/
    /*---------------------------------*****Back through the Right-hand Rotor*****---------------------------------*/
    /*------------------------------------								       ------------------------------------*/

    		if (letter < 32 && letter != 10) // As long as the ASCII value of the character imputted is less than 32, and not equal to 10,
    	     {
    			letter = 'Z'; // the new value is that of 'Z'
    		}

    		//Sends the letter through the wiring
    		letter = rotorR(letter, rRotor, debug);

            charDebug("Letter after second time through left-hand rotor: ", letter);

            if (letter < 65 && letter != 32 && letter != 10)
    		{
    			letter = letter + 26;
                charDebug("Letter + 26:", letter);
    		}
            if (letter > 90) // If the new value is greater than 90, take away 26 and tell me
    		{
    		     letter = letter - 26;
                 toChar(cha, letter);
                 charDebug("Letter - 26:", cha);
    		}
    		if (letter != 10)
                letter-= offset1;

    		if (letter < 65 && letter != 10 && letter != 32)
    		{
    			letter = letter + 26;
                toChar(cha, letter);
                charDebug("Letter + 26: ", cha);
    		}
            toChar(cha, letter);
            charDebug("Letter - offset1:", cha);

    /*------------------------------------                   --------------------------------------*/
    /*------------------------------------*****Plugboard*****--------------------------------------*/
    /*------------------------------------                   --------------------------------------*/
             for (i = 0; i < 13 && swap[i] != '\0'; i++){
                if (letter == swap[i])
                {
                    charDebug("Letter before swap: ", letter);
                    if (i % 2 != 0)
                    {
                        letter = swap[i-1];
                        charDebug("Letter after swap (i not an even number): ", letter);
                    }
                    else letter = swap[i+1];

                    charDebug("Letter after swapping: ", letter);

                    break;
                }
            }

    /*------------------------------------				   ------------------------------------*/
    /*------------------------------------*****Printer*****------------------------------------*/
    /*------------------------------------				   ------------------------------------*/

            if (j != 1)
            {
                toChar(cha, letter); // the CHAR is equal to the value of letter, and this converts the ASCII back to a letter
                printf("%c", cha); // Print it
                output[fillOutput++] = cha;
            }
            else printNl;

            strDebug("\n", "");

    		letter = input[countInput++];

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
    	output[fillOutput] = '\0';

        if (setOutputFile == 1)
        {
            if (outputFile[0] == '\n')
            {
                strDebug("outputFile:", outputFile);
                getFilename(outputFile, putNl);
            }
            fp = fopen(OUTPUTFILE, "a");
            if (linesProcessed == 0)
            {
                fprintf(fp, "==========================================================\n");
            }
            fprintf(fp, "%s\n", output);
            fclose(fp);
        }
        else if (outputFile[0] != '\0')
        {
            fp = fopen("output.txt", "a");
            if (linesProcessed == 0)
            {
                fprintf(fp, "==========================================================\n");
            }
            fprintf(fp, "%s\n", output);
            fclose(fp);
        }
        else ;
        strDebug("Output string:", output);
    }

    printf("\nEnter any letter to close the program: \n");
    i = getchar();
    return 0;
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
int rotorL(int letter, int lRotor, int debug){
    int index;
	if (timeL != 1)
	{
		switch (lRotor){
		case 1:
			index = findInArray(stdAlphabet, letter);
            letter = rotor1Wiring[index];
			intDebug("timeL: ", timeL);
            intDebug("lRotor: ", lRotor);
			strDebug("Case 1.", "\n");
			break;
		case 2:
            index = findInArray(stdAlphabet, letter);
            letter = rotor2Wiring[index];
			intDebug("timeL: ", timeL);
            intDebug("lRotor: ", lRotor);
			strDebug("Case 2.", "\n");
			break;
		case 3:
            index = findInArray(stdAlphabet, letter);
            letter = rotor3Wiring[index];
			intDebug("timeL: ", timeL);
            intDebug("lRotor: ", lRotor);
			strDebug("Case 3.", "\n");
			break;
		default:
            index = findInArray(stdAlphabet, letter);
            letter = rotor1Wiring[index];
			intDebug("timeL: ", timeL);
            intDebug("lRotor: ", lRotor);
			strDebug("Case default.", "\n");
			break;
		}
	}
	else {
		switch (lRotor){
		case 1:
            index = findInArray(rotor1Wiring, letter);
            letter = stdAlphabet[index];
			if (debug == 1)
			intDebug("timeL: ", timeL);
            intDebug("lRotor: ", lRotor);
			strDebug("Case 1.", "\n");
			break;
		case 2:
            index = findInArray(rotor2Wiring, letter);
            letter = stdAlphabet[index];
			if (debug == 1)
			intDebug("timeL: ", timeL);
            intDebug("lRotor: ", lRotor);
			strDebug("Case 2.", "\n");
			break;
		case 3:
            index = findInArray(rotor3Wiring, letter);
            letter = stdAlphabet[index];
			intDebug("timeL: ", timeL);
            intDebug("lRotor: ", lRotor);
			strDebug("Case 3.", "\n");
			break;
		default:
            index = findInArray(rotor1Wiring, letter);
            letter = stdAlphabet[index];
			intDebug("timeL: ", timeL);
            intDebug("lRotor: ", lRotor);
			strDebug("Case default.", "\n");
			break;
		}
	}
	return letter;
}
int rotorM(int letter, int mRotor, int debug){
    int index;

	if (timeM != 1)
	{
		switch (mRotor){
		case 1:
            index = findInArray(stdAlphabet, letter);
            letter = rotor1Wiring[index];
			intDebug("timeM: ", timeM);
            intDebug("mRotor: ", mRotor);
			strDebug("Case 1.", "\n");
			break;
		case 2:
            index = findInArray(stdAlphabet, letter);
            letter = rotor2Wiring[index];
			intDebug("timeM: ", timeM);
            intDebug("mRotor: ", mRotor);
			strDebug("Case 2.", "\n");
			break;
		case 3:
            index = findInArray(stdAlphabet, letter);
            letter = rotor3Wiring[index];
			intDebug("timeM: ", timeM);
            intDebug("mRotor: ", mRotor);
			strDebug("Case 3.", "\n");
			break;
		default:
            index = findInArray(stdAlphabet, letter);
            letter = rotor2Wiring[index];
			intDebug("timeM: ", timeM);
            intDebug("mRotor: ", mRotor);
			strDebug("Case default.", "\n");
			break;
		}
	}
	else {
		switch (mRotor){
		case 1:
            index = findInArray(rotor1Wiring, letter);
            letter = stdAlphabet[index];
			intDebug("timeM: ", timeM);
            intDebug("mRotor: ", mRotor);
			strDebug("Case 1.", "\n");
			break;
		case 2:
            index = findInArray(rotor2Wiring, letter);
            letter = stdAlphabet[index];
			intDebug("timeM: ", timeM);
            intDebug("mRotor: ", mRotor);
			strDebug("Case 2.", "\n");
			break;
		case 3:
            index = findInArray(rotor3Wiring, letter);
            letter = stdAlphabet[index];
			intDebug("timeM: ", timeM);
            intDebug("mRotor: ", mRotor);
			strDebug("Case 3.", "\n");
			break;
		default:
            index = findInArray(rotor2Wiring, letter);
            letter = stdAlphabet[index];
			intDebug("timeM: ", timeM);
            intDebug("mRotor: ", mRotor);
			strDebug("Case default.", "\n");
			break;
		}
	}
	return letter;
}
int rotorR(int letter, int rRotor, int debug){
    int index;

	if (timeR != 1)
	{
		switch (rRotor){
		case 1:
            index = findInArray(stdAlphabet, letter);
            letter = rotor1Wiring[index];
			intDebug("timeR: ", timeR);
            intDebug("rRotor: ", rRotor);
			strDebug("Case 1.", "\n");
			break;
		case 2:
            index = findInArray(stdAlphabet, letter);
            letter = rotor2Wiring[index];
			intDebug("timeR: ", timeR);
            intDebug("rRotor: ", rRotor);
			strDebug("Case 2.", "\n");
			break;
		case 3:
            index = findInArray(stdAlphabet, letter);
            letter = rotor3Wiring[index];
			intDebug("timeR: ", timeR);
            intDebug("rRotor: ", rRotor);
			strDebug("Case 3.", "\n");
			break;
		default:
            index = findInArray(stdAlphabet, letter);
            letter = rotor3Wiring[index];
			intDebug("timeR: ", timeR);
            intDebug("rRotor: ", rRotor);
			strDebug("Case default.", "\n");
			break;
		}
	}
	else {
		switch (rRotor){
		case 1:
            index = findInArray(rotor1Wiring, letter);
            letter = stdAlphabet[index];
			intDebug("timeR: ", timeR);
            intDebug("rRotor: ", rRotor);
			strDebug("Case 1.", "\n");
			break;
		case 2:
            index = findInArray(rotor2Wiring, letter);
            letter = stdAlphabet[index];
			intDebug("timeR: ", timeR);
            intDebug("rRotor: ", rRotor);
			strDebug("Case 2.", "\n");
			break;
		case 3:
            index = findInArray(rotor3Wiring, letter);
            letter = stdAlphabet[index];
			intDebug("timeR: ", timeR);
            intDebug("rRotor: ", rRotor);
			strDebug("Case 3.", "\n");
			break;
		default:
            index = findInArray(rotor3Wiring, letter);
            letter = stdAlphabet[index];
			intDebug("timeR: ", timeR);
            intDebug("rRotor: ", rRotor);
			strDebug("Case default.", "\n");
			break;
		}
	}
	return letter;
}
//Handles option setting from the file
int setOptions(char options[], char *option, int *option1, char debugFile[], int *option2, char filename[], int *setOutputFile, char outputFile[], int *setInputStorage, char inputStorage[]){

    int i, numLooped, k;
    i = numLooped = k = 0;

    FILE *fp;

    if ((fp = fopen(".enigmarc", "r")) == NULL)
    {
        fprintf(stderr, "Options file does not exist. Please create a file named \".enigmarc\" in the folder containing this program. Leave it blank if you wish. \n");
        return -1;
    }
    else
    {   //Choose to turn on debugging
        option = "debug";
        i = isOptionSet(options, option, fp, &numLooped);
    //    printf("Got through the next function.\n");
        if (i == 1)
        {
            *option1 = 1;
        }
        else if (i == 2)
        {
            *option1 = 2;
            fillArray(options, debugFile, numLooped); //fills the file, starting where the count left off, to get the filename put by the user
        }
        else if (i == 3)
        {
            debugFile[0] = '\0';
            *option1 = 3;
        }
        else *option1 = 0;
        fclose(fp);

        fp = fopen(".enigmarc", "r");

        //Choose reading from a file
        //Since it already checked to see if .enigmarc exists, it doesn't check again
        option = "input";
        i = isOptionSet(options, option, fp, &numLooped);
    //    printf("Got through the next function.\n");
        if (i == 1)
        {
            *option2 = 1;
            filename[0] = '\0';
        }
        else if (i == 2)
        {
            *option2 = 1;
            fillArray(options, filename, numLooped);
        }
        else *option2 = 0;
        fclose(fp);
        //Choose where to store the output
        fp = fopen(".enigmarc", "r");
        option = "output";
        i = isOptionSet(options, option, fp, &numLooped);
    //    printf("Got through the next function.\n");
        if (i == 1)
        {
            *setOutputFile = 1;
            outputFile[0] = '\n'; //Filename will be given by user when that point is reached
        }
        else if (i == 2)
        {
            *setOutputFile = 1;
            fillArray(options, outputFile, numLooped); //fills the file, starting where the count left off, to get the filename put by the user
        }
        else if (i == 3)
        {
            outputFile[0] = '\0';
        }
        else *setOutputFile = 0;
        fclose(fp);
        //Choose where to store the input string(s)
        fp = fopen(".enigmarc", "r");
        option = "storeInput";
        i = isOptionSet(options, option, fp, &numLooped);
    //    printf("Got through the next function.\n");
        if (i == 1)
        {
            *setInputStorage = 1; //Filename will be given by user when that point is reached
            inputStorage[0] = '\n';
        }
        else if (i == 2)
        {
            *setInputStorage = 1; //Filename already supplied
            fillArray(options, inputStorage, numLooped); //Fills the array for the inputStorage filename
        }
        else if (i == 3)
        {
            inputStorage[0] = '\0'; //Don't store input.
            //setInputStorage will already be 0, so it is not set again.
        }
        else *setInputStorage = 0; //Default. Set again because I had to put something there.
        fclose(fp);
    }
    return 1;
}
int isOptionSet(char options[], char *option, FILE *fp, int *numLooped){
    int i, k, max;

    i = *numLooped = k = 0;
    max = MAXLENGTH;

    char *p; //Pointer to handle the options array
    char *optionStored; //Pointer to remember what the string was so that *option can be reset


    p = options; //p points to the first char of options[]
    optionStored = option; //Both now point to the string *option points to
    //printf("Assigned pointers.\n");

    for (i = 0; fgets(options, max, fp) != NULL; i++){ //Start by opening the file and making sure that there is something in it
    //    printf("Got first line of file.");
        for (*numLooped = 0; *p != '\0'; p++){ //Makes sure the end of the string has not been reached
            if (*p == 32)
            {
                *numLooped += 1; //Increment numLooped to say it looped again.
                continue; //Skip whitespace
            }
            if (*p == *option) //If the current character matches the current char in option,
            {
                //printf("It matches so far.\n");
                if ((*(p +1) != ';') && (*(p +1) != '\n') && (*(option +1) != '\0') && (*(p +1) != '=')) //And if the end of either string hasn't been reached, or the end of an option, or an equals sign
                {
                //    printf("Keep on trying.\n");
                    option++; //Advance to the next character in option. p is advanced at the beginning of the loop.
                    *numLooped += 1; //Increment numLooped to say it looped again
                //    printf("Times looped: %i\n", *numLooped);
                    continue;
                }
                else if (*(p +1) == ';')
                {
                //    printf("Reached the ';'.\n");
                    *numLooped += 1; //Increment numLooped to say it looped again.
                    return 1;
                }
                else if (*(p +1) == '=') //If it reached a '=', something specific is going to follow
                {
                    //printf("Reached the '='.\n");
                    *numLooped += 1; //Increment numLooped to say it looped again.
                    if (*(p +2) == ';')
                    {
                        return 3; //Tell the caller
                    }
                    else return 2; //Tell caller that a name was specified
                }
                else if (*(p +1) == '\n') //If the end of p has been reached, we are out of options on that line, so go back to the parent loop and get the next line. There will be a newline on the end of p right before the '\0', so check for that instead
                {
                    //printf("Reached the end of p.\n");
                    option = optionStored; //Resets *option to keep trying
                    *numLooped += 1; //Increment numLooped to say it looped again
                    break;
                }
                else if (*(option +1) == '\0') //If the end of *option has been reached, we just need to reset option and try again.
                {
                    //printf("Went through all of option. Resetting.\n");
                    option = optionStored; //Resets *option to keep trying
                    continue;
                }
                else return 0; //Should never happen, but this is required.
            }
            else
            {
                //printf("Didn't match at all. Going to next option.\n");
                while ((*p != ';') && (*p != '\0')){ //While the next option hasn't been reached and the end of the string hasn't been reached
                    p++; //Skip ahead to the next option
                    *numLooped += 1; //Increment numLooped to say it looped again.
                    //printf("Times looped: %i\n", *numLooped);
                    //The ';' will be skipped when *p is incremented at the start of the loop.
                }
                *numLooped += 1; //Increment numLooped to say it looped again. numLooped isn't incremented at the start of the loop, so it will get behind p.
            }
        }

    }
    return 0;
}
int fillArray(char options[], char filename[], int numLooped){
    int i = 0;

    numLooped += 1; //numLooped needs to move ahead two in order to skip the '=' and the character preceeding it. Because of the way the loop worked in isOptionSet, it will still be at the ='.
    for (i = 0; (options[numLooped] != '\0') && (options[numLooped] != ';') && (i != MAXLENGTH); i++){
    //printf("numLooped: %i\noptions[numLooped]: %c\n", numLooped, options[numLooped]);
        filename[i] = options[numLooped++];
    }
    return i;

}
int findInArray(char list[], char character){
    int i;

    for (i = 0; i < MAXLENGTH && (list[i] != '\0'); i++){
        if (list[i] == character)
        {
            //Return index of character
            return i;
        }
    }
    //Does not contain character
    return -1;
}
