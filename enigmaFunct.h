/* === The Enigma, as a function === */

void enigmaFunct(char input[], char output[], int lRotor, int mRotor, int rRotor, int offset1, int offset2, int offset3, char swap[], int debug);

/* **USAGE**
This can be plugged into other programs merely by including the file and calling the function. The function declaration is at the top of this program.
It takes a string to be translated and runs it through the Enigma.

Other pieces, such as setting the options, are to be done in a separate part of the program; those functions stand alone. Currently, they are not supported in this function except for debugging to the screen.
*/

/* #defines */

#define charDebug(x, y) if (debug == 1) \
                        { \
                            printf("%s %c\n", x, y); \
                        }
#define ctoi(c) i = (c -'0');
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
                        }

/* Functions */
int rotorL(int letter, int lRotor, int debug); //Left-hand rotor
int rotorM(int letter, int mRotor, int debug); //Middle rotor
int rotorR(int letter, int rRotor, int debug); //Right-hand rotor

/* Global Variables */
int timeL; //Whether the value has gone through the left-hand rotor once or not
int timeM; //Whether the value has gone through the middle rotor once or not
int timeR; //Whether the value has gone through the right-hand rotor once or not

/* The main function */
void enigmaFunct(char input[], char output[], int lRotor, int mRotor, int rRotor, int offset1, int offset2, int offset3, char swap[], int debug){
    //ints
    int counter = 0;
    int i;
    int letter;
    int outCounter = 0;
    int stringLen;

    //Check length of swap string and also convert the string to uppercase
    for (stringLen = 0; (stringLen < 26) && (swap[stringLen] != '\0'); stringLen++){
        toUppercase(swap[stringLen]);
    }
    strDebug("Swap after uppercasing: ", swap);
    if (swap[stringLen] != '\0')
    {
        intDebug("DEBUG: Swap string was too long. Length of swap string: ", stringLen);
        return -1; //Swap string too long
    }
    strDebug("Swap string: ", swap);

    //Loop through the string and encipher each letter
    letter = input[counter++];
    charDebug("DEBUG: Next letter from input: ", letter);
    while (letter != '\0'){

        //Convert letter to uppercase
        toUppercase(letter);

        /*Plugboard*/
        for (i = 0; i < 13 && swap[i] != '\0'; i++){
           if (letter == swap[i])
           {
               charDebug("DEBUG: Letter after swapping: ", letter);
               if (i % 2 != 0)
               {
                   letter = swap[i-1];
                   intDebug("DEBUG: i:", i);
                   charDebug("DEBUG: Letter after swap: ", letter);
               }
               else letter = swap[i+1];

               charDebug("DEBUG: Letter after swapping: ", letter);
               break;
           }
       }

       //Increment offset1 if it is less than 25; otherwise, wrap around (subtract 25)
       if (offset1 < 25)
       {
           offset1++;
           intDebug("DEBUG: Offset1 increased by one: ", offset1);
       }
       else
       {
           offset1 -= 25;
           intDebug("DEBUG: Offset1 - 25: ", offset1);
       }

       //Add offset1 to letter
       letter += offset1;
       charDebug("DEBUG: Letter + offset1: ", letter);
       //If that makes the letter greater than 'Z', subtract 26
       fixTooLarge(letter);

       /*Send letter through LH rotor wiring and say it's been through once*/
       letter = rotorL(letter, lRotor, debug);
       charDebug("DEBUG: Letter after going through left-hand rotor: ", letter);
       timeL = 1;

       //Subtract offset1 from the letter, fix letter
       letter -= offset1;
       charDebug("DEBUG: Letter - offset1: ", letter);
       fixTooSmall(letter);

       //Add offset2 to the letter and fix letter
       letter += offset2;
       charDebug("DEBUG: Letter + offset2: ", letter);
       fixTooLarge(letter);

       /*Send letter through M rotor wiring, set marker to 1*/
       letter = rotorM(letter, mRotor, debug);
       timeM = 1;
       charDebug("DEBUG: Letter after going through middle rotor: ", letter);

       //Subtract offset2 from letter, fix letter
       letter -= offset2;
       charDebug("DEBUG: Letter - offset2: ", letter);
       fixTooSmall(letter);

       //Add offset3 to letter, fix letter
       letter += offset3;
       charDebug("DEBUG: Letter + offset3: ", letter);
       fixTooLarge(letter);

       /*Send letter through wiring for RH rotor, set marker to 1*/
       letter = rotorR(letter, rRotor, debug);
       timeR = 1;

       //Subtract offset3 and fix letter
       letter -= offset3;
       charDebug("DEBUG: Letter - offset3: ", letter);
       fixTooSmall(letter);

       /*Send letter through reflector*/
       #include "rB"
       charDebug("DEBUG: Letter after going through reflector: ", letter);

       //Add offset3, fix letter
       letter += offset3;
       charDebug("DEBUG: Letter + offset3: ", letter);
       fixTooLarge(letter);

       /*Back through right-hand rotor*/
       letter = rotorR(letter, rRotor, debug);

       //Subtract offset3, fix, add offset2, fix
       letter -= offset3;
       charDebug("DEBUG: Letter - offset3: ", letter);
       fixTooSmall(letter);
       letter += offset2;
       charDebug("DEBUG: Letter + offset2: ", letter);
       fixTooLarge(letter);

       /*Back through middle rotor*/
       letter = rotorM(letter, mRotor, debug);
       charDebug("DEBUG: Letter after going back through middle rotor: ", letter);

       //Subtract offset2, fix, add offset1, fix
       letter -= offset2;
       charDebug("DEBUG: Letter - offset2: ", letter);
       fixTooSmall(letter);
       letter += offset1;
       charDebug("DEBUG: Letter + offset1: ", letter);
       fixTooLarge(letter);

       /*Back through left-hand rotor*/
       letter = rotorL(letter, lRotor, debug);
       charDebug("DEBUG: Letter after going back through left-hand rotor: ", letter);

       //Subtract offset1, fix letter
       letter -= offset1;
       charDebug("DEBUG: Letter - offset1: ", letter);
       fixTooSmall(letter);

       /*Plugboard*/
       for (i = 0; i < 13 && swap[i] != '\0'; i++){
          if (letter == swap[i])
          {
              charDebug("DEBUG: Letter after swapping: ", letter);
              if (i % 2 != 0)
              {
                  letter = swap[i-1];
                  intDebug("DEBUG: i:", i);
                  charDebug("DEBUG: Letter after swap: ", letter);
              }
              else letter = swap[i+1];

              charDebug("DEBUG: Letter after swapping: ", letter);
              break;
          }
      }

      /*Save output to a string*/

      if (letter != '\n')
      {
          output[outCounter++] = letter;
          charDebug("DEBUG: Letter added to output array: ", letter);
      }

      //Get next letter of input
      letter = input[counter++];

      //Reset rotor counters
      timeL = 0;
      timeM = 0;
      timeR = 0;

      //If a newline, break (EOL, basically); else if space, set to 'X' (traditional way to encode spaces); else nothing
      if (letter == '\n')
      {
          break;
      }
      else if (letter == 32) //Letter is a space
      {
          letter = 'X';
      }
      else ;

    }

    //End array of input, return array
    output[outCounter] = '\0';
}
int rotorL(int letter, int lRotor, int debug){
	if (timeL != 1)
	{
		switch (lRotor){
		case 1:
			#include "r1"
			intDebug("timeL: ", timeL);
            intDebug("lRotor: ", lRotor);
			strDebug("Case 1.", "\n");
			break;
		case 2:
			#include "r2"
			intDebug("timeL: ", timeL);
            intDebug("lRotor: ", lRotor);
			strDebug("Case 2.", "\n");
			break;
		case 3:
			#include "r3"
			intDebug("timeL: ", timeL);
            intDebug("lRotor: ", lRotor);
			strDebug("Case 3.", "\n");
			break;
		default:
			#include "r1"
			intDebug("timeL: ", timeL);
            intDebug("lRotor: ", lRotor);
			strDebug("Case default.", "\n");
			break;
		}
	}
	else {
		switch (lRotor){
		case 1:
			#include "r1Back"
			if (debug == 1)
			intDebug("timeL: ", timeL);
            intDebug("lRotor: ", lRotor);
			strDebug("Case 1.", "\n");
			break;
		case 2:
			#include "r2Back"
			if (debug == 1)
			intDebug("timeL: ", timeL);
            intDebug("lRotor: ", lRotor);
			strDebug("Case 2.", "\n");
			break;
		case 3:
			#include "r3Back"
			intDebug("timeL: ", timeL);
            intDebug("lRotor: ", lRotor);
			strDebug("Case 3.", "\n");
			break;
		default:
			#include "r1Back"
			intDebug("timeL: ", timeL);
            intDebug("lRotor: ", lRotor);
			strDebug("Case default.", "\n");
			break;
		}
	}
	return letter;
}
int rotorM(int letter, int mRotor, int debug){
	if (timeM != 1)
	{
		switch (mRotor){
		case 1:
			#include "r1"
			intDebug("timeM: ", timeM);
            intDebug("mRotor: ", mRotor);
			strDebug("Case 1.", "\n");
			break;
		case 2:
			#include "r2"
			intDebug("timeM: ", timeM);
            intDebug("mRotor: ", mRotor);
			strDebug("Case 2.", "\n");
			break;
		case 3:
			#include "r3"
			intDebug("timeM: ", timeM);
            intDebug("mRotor: ", mRotor);
			strDebug("Case 3.", "\n");
			break;
		default:
			#include "r1"
			intDebug("timeM: ", timeM);
            intDebug("mRotor: ", mRotor);
			strDebug("Case default.", "\n");
			break;
		}
	}
	else {
		switch (mRotor){
		case 1:
			#include "r1Back"
			intDebug("timeM: ", timeM);
            intDebug("mRotor: ", mRotor);
			strDebug("Case 1.", "\n");
			break;
		case 2:
			#include "r2Back"
			intDebug("timeM: ", timeM);
            intDebug("mRotor: ", mRotor);
			strDebug("Case 2.", "\n");
			break;
		case 3:
			#include "r3Back"
			intDebug("timeM: ", timeM);
            intDebug("mRotor: ", mRotor);
			strDebug("Case 3.", "\n");
			break;
		default:
			#include "r1Back"
			intDebug("timeM: ", timeM);
            intDebug("mRotor: ", mRotor);
			strDebug("Case default.", "\n");
			break;
		}
	}
	return letter;
}
int rotorR(int letter, int rRotor, int debug){
	if (timeR != 1)
	{
		switch (rRotor){
		case 1:
			#include "r1"
			intDebug("timeR: ", timeR);
            intDebug("rRotor: ", rRotor);
			strDebug("Case 1.", "\n");
			break;
		case 2:
			#include "r2"
			intDebug("timeR: ", timeR);
            intDebug("rRotor: ", rRotor);
			strDebug("Case 2.", "\n");
			break;
		case 3:
			#include "r3"
			intDebug("timeR: ", timeR);
            intDebug("rRotor: ", rRotor);
			strDebug("Case 3.", "\n");
			break;
		default:
			#include "r1"
			intDebug("timeR: ", timeR);
            intDebug("rRotor: ", rRotor);
			strDebug("Case default.", "\n");
			break;
		}
	}
	else {
		switch (rRotor){
		case 1:
			#include "r1Back"
			intDebug("timeR: ", timeR);
            intDebug("rRotor: ", rRotor);
			strDebug("Case 1.", "\n");
			break;
		case 2:
			#include "r2Back"
			intDebug("timeR: ", timeR);
            intDebug("rRotor: ", rRotor);
			strDebug("Case 2.", "\n");
			break;
		case 3:
			#include "r3Back"
			intDebug("timeR: ", timeR);
            intDebug("rRotor: ", rRotor);
			strDebug("Case 3.", "\n");
			break;
		default:
			#include "r1Back"
			intDebug("timeR: ", timeR);
            intDebug("rRotor: ", rRotor);
			strDebug("Case default.", "\n");
			break;
		}
	}
	return letter;
}
