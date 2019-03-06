# encipherMach

# NOTES: 
Program now handles spaces, but must be rerun after each newline is entered. Up to 9,098 characters may be entered at once. Spaces  are replaced by XX. (That is how spaces were entered on the Enigma.) 
Now taking file input! Please make sure your file is compatible before feeding it to the program to avoid errors. No punctuation marks or other non-alphabet symbols are supported. 
Latest update added a profile called ".enigmarc" that allows you to set options: debugging (which can be sent to a file), filename to read from, and files to write to. Press 'h' when prompted after running the program for details. The Windows .exe does support this.

Double-click the engima.exe file to run on Windows. "enigma.c" is the C code file. "enigma" is the Linux executable. On Linux, you may have to run "chmod +x enigma" in the folder where the file is in order to have executing permissions for the file. 

"cTest.c", "cTest", and "cTest.exe" are the C code file and the Linux and Windows executables, respectively, for an Enigma with the rotors hard-coded to certain positions. 

Input, output, and key settings are, by default (if those options are enabled), stored in files called input.txt, output.txt, and key_settings.txt. 
The full Enigma no longer requires r1, r2, etc.

# LIST OF FILES:

AboutEnigmaMach.txt - text file listing references that explain how the Enigma works

README.md - what you are currently reading

cipherMach - Linux executable for program illustrating the Enigma-as-a-function

cipherMach.c - Code for program illustrating the Enigma-as-a-function

cTest - Linux executable for an Enigma with the rotors hard-coded to certain posotions

cTest.c - Code for the hard-coded Enigma

cTest.exe - Windows executable for the hard-coded Enigma

enigma - Linux executable for the full Enigma 

enigma.c - Code for the full Enigma 

enigma.exe - Windows exectuable for the full Enigma (may be several features behind)

enigmaFunct.h - The Enigma as a function / header file for use in other programs

enigmaMach2Psuedocode - Psuedocode for the full Enigma

r1 - Rotor I for the Enigma

r1Back - Rotor I for the Enigma, wiring reversed 

r2 - Rotor II for the Enigma

r2Back - Rotor II for the Enigma, wiring reversed

r3 - Rotor III for the Enigma

r3Back - Rotor III for the Enigma, wiring reversed

rB - Reflector B for the Enigma

reflector - Same as Reflector B, but more generic name; used in cTest

transEnigma - Linux executable for a program that translates from Human-readable text to Enigma-readable text

transEnigma.c - Code for program that translates between human-readable and Enigma-readable




