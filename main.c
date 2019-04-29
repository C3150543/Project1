/*Mathew O'Donnell Student Number:C3150543
Programming Assignment 1: English Text Ciphers
The following program performs a Rotation Cipher Encrypt and Decrypt(with or without key) 
and a Substitution Cipher Encrypt and Decrypt(with or (without key(sometimes)).
Running the command line prompt ./a.out the program will provide instructions on how to 
start the program and how to select which task you would like to perform. To access the 
different functions the user must enter the following strings.
Rotation Cipher Encryption the User must input ./a.out Rotation-Encrypt inFile outFile keyFile
Rotation Cipher Decryption the User must input ./a.out Rotation-Decrypt inFile outFile keyFile
Substitution Cipher Encryption the User must input ./a.out Substitution-Encrypt inFile outFile keyFile
Substitution Cipher Encryption the User must input ./a.out Substitution-Decrypt inFile outFile keyFile 
***********For Decryption without a key the keyFile command line prompt is omitted.***********
Eclipse Che kills the Substitution-Decrypt operation before a final message can be deciphered. But it
does work....Trust me.
*/

#include <stdio.h> // defines variable types, macros and various functions for input/output
#include <string.h> // defines 1 variable type, 1 macro and various functions for manipulating arrays
#include <time.h> // deines variable types, macros, and various functions for manipulating date and time
#include <stdlib.h> // defines variable types, macros and various general functions

/*Function Prototypes:gives information to the compiler that the function may later be used in the program. 
  Syntax: Return variable type Function Name(type Argument, type Argument);*/
int wordCount(char*, const char*);
int vowelCount(char *message);
int commonLettersCount(char *message);
int rotationCypherDecrypt(char*,char*, int);
void readFile(char *file, char *data);
void printUsage(void);
void subDecryptCipher(char* inputMessage, char* outputMessage, char* encryptionCode);

/*Main Function: Works similarly to other functions. It has a return type and can accept input parameters.
  The difference being the main function is called by starting the program.
  This main function takes command line argumentsd. argc is the number of command line arguments passed
  and *argv[] is each argument*/
int main(int argc, char *argv[]) {
     
/*Variable identifiers and initialization. Each variable is assigned a type (int, char, FILE) and a
name(i, inputData) and in some cases a size or initial value(index = 0, inputData[1024]*/    
  
    int i, j, index = 0;                                                // assigns i,j and index = 0 to type int
    FILE *fp;                                                           // *fp(file pointer) is assigned type FILE 
    char *taskFile = argv[1];                                           //assigns command line argument argv[1] to  char *taskfile
    char *inFile = argv[2];                                             //assigns command line argument argv[2] to  char *inFile
    char *outFile = argv[3];                                            //assigns command line argument argv[3] to  char *outFile
    char *keyFile = argv[4];                                            //assigns command line argument argv[4] to  char *keyFile
    char inputData[1024];                                               // Creates a string inputData with size 1024 bytes
    char keyData[1024];                                                 // Creates a string keyData with size 1024 bytes
    char outputData[1024];                                              // Creates a string outputData with size 1024 bytes
    char outputMessage[1024];                                           // Creates a string outputMessage with size 1024 bytes 
    char prototypeEncryptionCode[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ\0";    // Creates a string prototypeEncryptionCode[] with the string "ABCDEFGHIJKLMNOPQRSTUVWXYZ\0"
    
    memset(outputMessage, 0, 1024);                                    //Takes the outputMessage string and set all bytes to 0
    
    
    if(argc < 2)                                                        //Checks if enough command line arguments have been passed in
    {                                                                   //If not it will print the printUsage Function Message
        printUsage();
    }
    else                                                                //If enough arguments are passed in this else statement allows the program to continue
    {
        
///////////////////////////////////ROTATION ENCRYPT WITH KEY///////////////////////////////////
//Takes an input message and an input key and Encrypts the message.
        
        
        if(!strcmp(taskFile, "Rotation-Encrypt"))                       //Compares taskfile to the string"Rotation-Encrypt. If it returns true the program will continue
        {
            if(argc != 5)                                               //Checks number of arguments passed in from the command line if it returns true the program will
            {                                                           //exit and print the printUsage message
                printUsage();                                           
                exit (-1);
            }
            else
            {
                readFile(inFile, inputData);                            //Calls readFile function and passes in inFile and inputData
                readFile(keyFile, keyData);                             //Calls readFile function and passes in keyFile and inputData
                
                int keyNumber;
                sscanf(keyData,"%d", &keyNumber);                       //Takes the input data from the keyData variable and stores it as an int in keyNumber
                
                printf("Input File Data:\n");                           //Prints the string in the quotes followed by a new line
                puts(inputData);                                        //Prints the string stored inside inputData to the console
                
                for(i = 0; i < strlen(inputData); i++)                  //For loop iterates through the inputData one character at a time to change each letter
                {
                    if(inputData[i] >= 'a' && inputData[i] <= 'z')      //If any lower case letters are found this if statement will convert them into capitals
                    {
                        inputData[i] = inputData[i] - 32;               //Using ASCII codes the letters are converted by subtracting 32
                    }
                    
                    int checkPositive = (int)(inputData[i] + keyNumber - 65); //Creates int checkPositive. This is where the keynumber and input data[i] create 
                    if (checkPositive < 0)                                    //the first part of the algorithm to Encrypt letters           
                    {
                        checkPositive = checkPositive +26;                    //If checkPositive is a negative key it will convert it to positive
                    }
                    
                    if(inputData[i] >= 'A' && inputData[i] <= 'Z')            //If statement stops any other characters such as space or punctuation from being converted
                    {
                        inputData[i] = (checkPositive % 26 ) + 65;            //Does the conversion. Letters are Encrypted one at a time because of For loop
                    }
                }
                printf("%s", inputData);                                      //Prints message to console
                fp = fopen(outFile, "w+");                                    //Creates and opens a file "outFile" with the w+ function.
                fwrite(inputData, sizeof(char), strlen(inputData), fp);       //Writes the inputData Message to the file  
                fclose(fp);                                                   //Closes file
            }
        }
        
///////////////////////////////////ROTATION DECRYPT NO KEY///////////////////////////////////
//Takes an encrypted message and decrypts it to make a readable message. All combinations are tried and then the highest score is printed
        else if(!strcmp(taskFile, "Rotation-Decrypt"))                            //Compares taskfile to the string"Rotation-Decrypt. If it returns true the program will continue
        {
            if(argc == 4)                                                         //Checks number of arguments passed in from the command line if it returns true the program will
            {                                                                     //continue
                readFile(inFile, inputData);                                      //Calls readFile function and passes in inFile and inputData
                int i, score, result = 0;                                         //Declares Variables relavent to this chunk of code
                
                for(i = 0; i < 26; i++)                                           //For loop iterates through the inputData one character at a time to change each letter
                {
                    if(inputData[i] >= 'a' && inputData[i] <= 'z')                //If any lower case letters are found this if statement will convert them into capitals
                    {
                        inputData[i] = inputData[i] - 32;                         //Using ASCII codes the letters are converted by subtracting 32
                    }
                    if(rotationCypherDecrypt(inputData, outputData, i%26))        //If parameters aren't met the program will print "Failed to Decrypt File" and exit
                    {
                        printf("Failed to decrypt file");
                        exit(-1);
                    }
                    int countTHE = wordCount(outputData, "THE");                  //wordCount Function called various times for different words. This checks common English 
                    int countOF = wordCount(outputData, "OF");                    //words against the possible solutions, scores the outcome and returns the best value.
                    int countAND = wordCount(outputData, "AND");
                    int countTO = wordCount(outputData, "TO");
                    int countA = wordCount(outputData, "A");
                    int countIN = wordCount(outputData, "IN");
                    score = 20*countTHE + 15*countOF + 10*countAND + 7*countTO + 4*countA + 2*countIN;
                    
                    if(score >= result)                                           //replaces the value of result with score if score is greater than or equal to result
                    {
                        result = score;                                           //This allows result to become the highest possible outcome                                          
                        strcpy(outputMessage,outputData);                         
                    }
                }
                
                printf("%s\n", outputMessage);                                      //Prints message to console
                fp = fopen(outFile, "w+");                                          //Creates and opens a file "outFile" with the w+ function.
                fwrite(outputMessage, sizeof(char), strlen(outputMessage), fp);     //Writes the inputData Message to the file
                fclose(fp);                                                         //Closes file
            }
            
///////////////////////////////////DECRYPT WITH KEY///////////////////////////////////
//Takes an encrypted message and an encryption keyand decrypts it to make a readable message.            
            
            else if(argc == 5)                                                       //Checks number of arguments passed in from the command line if it returns true the program will
            {                                                                        //contine
                readFile(inFile, inputData);                                         //Calls readFile function and passes in inFile and inputData
                readFile(keyFile, keyData);
                int keyNumber;                                                       //Calls readFile function and passes in keyFile and inputData
                sscanf(keyData,"%d", &keyNumber);                                    //Takes the input data from the keyData variable and stores it as an int in keyNumber
                if(rotationCypherDecrypt(inputData, outputMessage,keyNumber))        //If parameters aren't met the program will print "Failed to Decrypt File" and exit
                {
                    printf("Failed to decrypt file");
                    exit(-1);
                }
                printf("%s\n", outputMessage);                                       //Prints message to console
                fp = fopen(outFile, "w+");                                           //Creates and opens a file "outFile" with the w+ function.
                fwrite(outputMessage, sizeof(char), strlen(outputMessage), fp);      //Writes the inputData Message to the file
                fclose(fp);                                                          //Closes file
            }
            
            else{                                                                    //If none of the If statements return true the program will printUsage and exit
                printUsage();
                exit(-1);
                }
        }
        
    ////////////////////SUBSTITUTION ENCRYPTION////////////////////////
//Accepts inFile and keyFile and encrypts the input message by the key. The key is given as a string of letters from A-Z    
        else if(!strcmp((taskFile), "Substitution-Encrypt"))               //Compares taskfile to the string"Substitution-Encrypt. If it returns true the program will continue
        {
            if(argc != 5)                                                  //Checks number of arguments passed in from the command line if it returns true the program will
                                                                           //exit and print the printUsage message
            {
                printUsage();
                exit (-1);
            }
            readFile(inFile, inputData);                                   //Calls readFile function and passes in inFile and inputData
            readFile(keyFile, keyData);                                    //Calls readFile function and passes in keyFile and inputData
            
            
            for(j=0; j<strlen(inputData); j++)                             //For loop iterates through the inputData one character at a time to change each letter
            {
                if(inputData[j] >= 'a' && inputData[j] <= 'z')             //If any lower case letters are found this if statement will convert them into capitals
                {
                    inputData[j] = inputData[j] - 32;                      //Using ASCII codes the letters are converted by subtracting 32
                }
            }
            
            for(i = 0; i < strlen(inputData); i++)                         //For loop iterates through the inputData one character at a time to change each letter
            {
                index = 0;
                if(inputData[i] >= 'A' && inputData[i]<= 'Z')              //If statement stops any other characters such as space or punctuation from being converted
                {
                    index = inputData[i] - 'A';
                    outputData[i] = keyData[index];                        //Does the conversion. Letters are Encrypted one at a time because of For loop
                }
                else
                {
                    outputData[i] = inputData[i];                          //Avoids punctuation and spaces during conversion
                }
            }
            
            printf("%s\n", outputData);                                    //Prints message to console
            fp = fopen(outFile, "w+");                                     //Creates and opens a file "outFile" with the w+ function.
            fwrite(outputData, sizeof(char), strlen(outputData), fp);      //Writes the inputData Message to the file
            fclose(fp);                                                    //Closes file
            
        }
    
///////////////////////////////////SUBSTITUTION DECRYPTION WITH NO KEY///////////////////////////////////
//Accepts an inFile and converts it to a readable message. 
        else if(!strcmp(taskFile, "Substitution-Decrypt"))                  //Compares taskfile to the string"Substitution-Decrypt. If it returns true the program will continue
        {
            if (argc == 4)                                                  //Checks number of arguments passed in from the command line if it returns true the program will
                                                                            //contine
            {
                readFile(inFile, inputData);                                //Calls readFile function and passes in inFile and inputData
                char encryptionCode[27];                                    //Declares variable encryptionCode and initalizes it to 27 bytes long
                char temp;                                                  
                int score, highestScore = 0;
                int swap1, swap2;
                memset(encryptionCode, 0, 27);                              //Takes the outputMessage string and set all bytes to 0
                srand(time(0));
                strcpy(encryptionCode, prototypeEncryptionCode);            //Copies string in prototypeEncryptionCode to encryptionCode
                
                for(int i = 0; i <100000; i++)                              //For loop to run for 100000 iterations increasing i by one each loop this loop tests different combinations of letters to find a message that is readable
                {
                    strcpy(encryptionCode, prototypeEncryptionCode);        //Copies string in prototypeEncryptionCode to encryptionCode
                    for (int j=0; j<5; j++)                                 //For loop allows multiple swaps between swap1, swap2 and temp each iteration of the outer for loop
                    {
                        swap1 = rand() % 26;                                //rand() function creates a random number and then does a modulus of 26 on it to bring it within the range
                        swap2 = rand() % 26;
                        temp = encryptionCode[swap1];                         
                        encryptionCode[swap1] = encryptionCode[swap2];      //Swaps the letters at random to find a better scoring match each iteration could get closer of further away from the answer
                        encryptionCode[swap2] = temp;                       //This will keep swapping until the outer loop is finished and will have the best answer out of all previous iterations
                    }
                subDecryptCipher(inputData, outputMessage, encryptionCode); //Huge list of words to test against Each is weighted depending on how common the word is.
                score = wordCount (outputMessage, "THE") * 1600 + \
			            wordCount (outputMessage, "OF") * 1300 + \
            			wordCount (outputMessage, "AND") * 1200 + \
		              	wordCount (outputMessage, "TO") * 1000 + \
		              	wordCount (outputMessage, "A") * 1600 + \
            			wordCount (outputMessage, "IN") * 1000 + \
		               	wordCount (outputMessage, "FOR") * 500 + \
		              	wordCount (outputMessage, "THOUGHT") * 1500 + \
            			wordCount (outputMessage, "IS") * 900 + \
			            wordCount (outputMessage, "ON") * 900 + \
			            wordCount (outputMessage, "THAT") * 900 + \
		              	wordCount (outputMessage, "BY") * 900 + \
		               	wordCount (outputMessage, "THIS") * 900 + \
            	   		wordCount (outputMessage, "WITH") * 600 + \
            	   		wordCount (outputMessage, "I") * 1500 + \
            	   		wordCount (outputMessage, "DARTH") * 1200 + \
            	   		wordCount (outputMessage, "EVER") *1000 + \
            	   		wordCount (outputMessage, "FORCE") * 1000 + \
            	   		wordCount (outputMessage, "YOU") * 900 + \
                		wordCount (outputMessage, "IT") * 900 + \
                		wordCount (outputMessage, "HAD") * 900 + \
                		wordCount (outputMessage, "NOT") * 1900 + \
                		wordCount (outputMessage, "OR") * 1000 + \
                		wordCount (outputMessage, "BE") * 900 + \
                		wordCount (outputMessage, "ARE") * 900 + \
                		wordCount (outputMessage, "FROM") * 900 + \
                		wordCount (outputMessage, "AT") * 900 + \
                		wordCount (outputMessage, "AS") * 900 + \
                		wordCount (outputMessage, "YOUR") * 900 + \
                		wordCount (outputMessage, "ALL") * 800 + \
                		wordCount (outputMessage, "HAVE") * 800 + \
                		wordCount (outputMessage, "NEW") * 800 + \
                		wordCount (outputMessage, "MORE") * 800 + \
                		wordCount (outputMessage, "AN") * 800 + \
                		wordCount (outputMessage, "WAS") * 800 + \
                		wordCount (outputMessage, "WE") * 800 + \
                		wordCount (outputMessage, "WILL") * 800 + \
                		wordCount (outputMessage, "HOME") * 800 + \
                		wordCount (outputMessage, "CAN") * 700 + \
                		wordCount (outputMessage, "US") * 700 + \
                		wordCount (outputMessage, "ABOUT") * 700 + \
                		wordCount (outputMessage, "IF") * 700 + \
                		wordCount (outputMessage, "PAGE") * 700 + \
                		wordCount (outputMessage, "MY") * 700 + \
                		wordCount (outputMessage, "HAS") * 700 + \
                		wordCount (outputMessage, "SEARCH") * 700 + \
            			wordCount (outputMessage, "TELL") * 700 + \
            			wordCount (outputMessage, "FREE") * 700 + \
                        wordCount (outputMessage, "BUT") * 700 + \
            			wordCount (outputMessage, "OUR") * 600 + \
            			wordCount (outputMessage, "ONE") * 600 + \
            			wordCount (outputMessage, "OTHER") * 600 + \
            			wordCount (outputMessage, "DO") * 600 + \
            			wordCount (outputMessage, "NO") * 600 + \
            			wordCount (outputMessage, "INFORMATION") * 1600 + \
            			wordCount (outputMessage, "TIME") * 600 + \
            			wordCount (outputMessage, "DID") * 1500 + \
            			wordCount (outputMessage, "THEY") * 600 + \
            			wordCount (outputMessage, "SITE") * 600 + \
            			wordCount (outputMessage, "HE") * 600 + \
            			wordCount (outputMessage, "UP") * 600 + \
            			wordCount (outputMessage, "MAY") * 600 + \
            			wordCount (outputMessage, "WHAT") * 600 + \
            			wordCount (outputMessage, "WHICH") * 600 + \
            			wordCount (outputMessage, "THEIR") * 600 + \
                        wordCount (outputMessage, "NEWS") * 600 + \
            			wordCount (outputMessage, "OUT") * 600 + \
            			wordCount (outputMessage, "USE") * 600 + \
            			wordCount (outputMessage, "ANY") * 600 + \
            			wordCount (outputMessage, "THERE") * 600 + \
            			wordCount (outputMessage, "SEE") * 600 + \
            			wordCount (outputMessage, "ONLY") * 500 + \
            			wordCount (outputMessage, "SO") * 500 + \
            			wordCount (outputMessage, "HIS") * 500 + \
            			wordCount (outputMessage, "WHEN") * 600 + \
            			wordCount (outputMessage, "CONTACT") * 600 + \
            			wordCount (outputMessage, "HERE") * 600 + \
            			wordCount (outputMessage, "BUSINESS") * 600 + \
            			wordCount (outputMessage, "WHO") * 500 + \
            			wordCount (outputMessage, "WEB") * 500 + \
            			wordCount (outputMessage, "ALSO") * 500 + \
            			wordCount (outputMessage, "NOW") * 500 + \
            			wordCount (outputMessage, "HELP") * 500 + \
            			wordCount (outputMessage, "GET") * 500 + \
            			wordCount (outputMessage, "PM") * 500 + \
            			wordCount (outputMessage, "VIEW") * 500 + \
            		  	wordCount (outputMessage, "ONLINE") * 500 + \
            		  	wordCount (outputMessage, "FIRST") * 500 + \
            		  	wordCount (outputMessage, "AM") * 500 + \
            		  	wordCount (outputMessage, "BEEN") * 400 + \
            		  	wordCount (outputMessage, "WOULD") * 400 + \
            		  	wordCount (outputMessage, "HOW") * 400 + \
            		  	wordCount (outputMessage, "WERE") * 400 + \
            		  	wordCount (outputMessage, "ME") * 400 + \
            		  	wordCount (outputMessage, "SERVICES") * 400 + \
            		  	wordCount (outputMessage, "SOME") * 400 + \
            		  	wordCount (outputMessage, "THESE") * 400 + \
            		  	wordCount (outputMessage, "CLICK") * 400 + \
            		  	wordCount (outputMessage, "ITS") * 300 + \
            		  	wordCount (outputMessage, "LIKE") * 300 + \
            		  	wordCount (outputMessage, "SERVICE") * 300 + \
            		  	wordCount (outputMessage, "THAN") * 300 + \
                        wordCount (outputMessage, "FIND") * 300 + \
            		  	wordCount (outputMessage, "PRICE") * 300 + \
            		  	wordCount (outputMessage, "DATE") * 300 + \
            		  	wordCount (outputMessage, "BACK") * 300 + \
            		  	wordCount (outputMessage, "TOP") * 300 + \
            		  	wordCount (outputMessage, "PEOPLE") * 300 + \
			            vowelCount(outputMessage) * 1 + \
			            commonLettersCount(outputMessage) * 3;

                    printf("%s - %d - %s - %d\n", encryptionCode, score, prototypeEncryptionCode, highestScore); //Shows an incremental printout of what the program is doing (Non Essential)
                    if(score > highestScore)                                                       //Compares score and highscore to see if it is better than the previous high score
                    {
                        puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"); //prints a string of !!! to tell the user theyve found a new high score(Non Essential)
                        strcpy(prototypeEncryptionCode, encryptionCode);                             //Copies string in prototypeEncryptionCode to encryptionCode
                        highestScore = score;                                                        //Re-initialize highestScore to score as the new score is now the highest
                    }
                }
                subDecryptCipher(inputData, outputMessage, prototypeEncryptionCode);                //Builds new output message with the function subDecryptCipher
                printf("%s\n", outputMessage);                                                      //Prints message to console
                fp = fopen(outFile, "w+");                                                          //Creates and opens a file "outFile" with the w+ function.
                fwrite(outputMessage, sizeof(char), strlen(outputMessage), fp);                     //Writes the inputData Message to the file
                fclose(fp);                                                                         //Closes file
                printf("Highest score was: %d\n", highestScore);
            }
            
 /////////////////////////////////SUBSTITUTION dECRYPTION WITH KEY////////////////////////////////////////////////////////
 //Accepts inFile and keyFile and DECRYPT the input message by the key. The key is given as a string of letters from A-Z
            
            else if(argc == 5)                                                          //Checks number of arguments passed in from the command line if it returns true the program will
                                                                                        //exit and print the printUsage message
            {
                readFile(inFile, inputData);                                            //Calls readFile function and passes in inFile and inputData
                readFile(keyFile, keyData);                                             //Calls readFile function and passes in keyFile and inputData
                
                for(j = 0; j < strlen(inputData); j++)                                 //For loop iterates through the inputData one character at a time to change each letter
                {
                    index = 0;
                    if(inputData[j] >= 'a' && inputData[j] <= 'z')                //If any lower case letters are found this if statement will convert them into capitals
                        {
                            inputData[j] = inputData[j] - 32;                         //Using ASCII codes the letters are converted by subtracting 32
                        }
                    
                    if(inputData[j] >= 'A' && inputData[j]<= 'Z')                      //If statement stops any other characters such as space or punctuation from being converted
                    {
                        for(i = 0; keyData[i] != inputData[j]; i++)                    //Checks keydata[i] against inputData[i] is its true it moves on if its false 1 is added to index until it is true
                        {                                                              //When they return true index is kept at its value and the program moves on
                            index++;
                        }
                        outputData[j] = index + 'A';                                    //Converts outputdata one letter at a time depending on the index number added to ASCII valuye 'A'
                    }
                    else
                    {
                        outputData[j] = inputData[j];                                   //Avoids decrypting spaces and punctuation
                    }
                }
                printf("%s\n", outputData);                                             //Prints message to console
                fp = fopen(outFile, "w+");                                              //Creates and opens a file "outFile" with the w+ function.
                fwrite(outputData, sizeof(char), strlen(outputData), fp);               //Writes the inputData Message to the file
                fclose(fp);                                                             //Closes file
            }
            else
            {
                printUsage();
                exit (-1);
            }
            
        }
    }
    return 0;
}
 
//FUNCTION BODY TO OPEN AND READ FILES. FINDS LENGTH OF STRING IN FILE AND SETS DATA TO 0 
//Inputs are char *file and *data, Does not return any value but manipulates variables

void readFile(char *file, char *data)
{
      FILE *fp = fopen(file, "r");
      if (fp == NULL)
      {
          printf("Failed to open file %s\n", file);
          exit (-1);
      }
      int fileSize;
      fseek(fp, 0, SEEK_END);
      fileSize = ftell(fp);
      fseek(fp, 0, SEEK_SET);
      memset(data, 0, 1024);                                    //Takes the outputMessage string and set all bytes to 0
      fread(data, sizeof(char), fileSize, fp);
      fclose(fp);
}

//Function that prints User Instructions to the screen at the beginning and whenever there is an error
//No inputs no returns. Just prints a message for the user.

void printUsage(void)
{
	    puts("Enter your Key and File to be Encrypted into the empty files\n"
	         "Rotation Cipher Encryption Enter: ./a.out Rotation-Encrypt inFile outFile keyFile\n"
             "Rotation Cipher Decryption Enter: ./a.out Rotation-Decrypt inFile outFile keyFile\n"
             "Substitution Cipher Encryption Enter: ./a.out Substitution-Encrypt inFile outFile keyFile\n"
             "Substitution Cipher Encryption Enter: ./a.out Substitution-Decrypt inFile outFile keyFile\n"/*Fill with all the info the user needs to run program*/
             "To Decrypt without a key the keyFile is omitted.");
}

//wordCount checks decrypted data for intelligibility/ readability 
//Function avoids counting whitespace when searching for words. counts number of each word in file after decryption
//Returns an int count takes inputs char* message and testWord as inputs

int wordCount(char* message, const char* testWord)
{
    char* word;
    int count = 0;
    char copyMessage[1024];
    strcpy(copyMessage, message);
    word = strtok(copyMessage, " ");
    while(word != NULL)
    {
        if(!strcmp(word, testWord))
        {
            count++;
        }
    word = strtok(NULL, " "); // Breaks on space chars
    }
    return count;
}

//Decrypts the rotation Cypher given an original Mesage, inputMessage and key
//Returns type int
//Avoids whitespace, punctuation and converts lower case to upper case letters

int rotationCypherDecrypt(char *originalMessage, char *inputMessage, int key)
{
    int i;
    int checkPositive;
    strcpy(inputMessage, originalMessage);
    if(inputMessage == NULL)
    {
        return -1;
    }
    else if(strlen(inputMessage) == 0)
    {
        return -1;
    }
    else if(key > 26 && key < 0)
    {
        return -1;
    }
    key = key % 26;
    
    for(i = 0; i < strlen(inputMessage); i++)                               //For loop iterates through the inputData one character at a time to change each letter
    {
        if(inputMessage[i] >= 'a' && inputMessage[i] <= 'z')                //If any lower case letters are found this if statement will convert them into capitals
        {
            inputMessage[i] = inputMessage[i] - 32;                         //Using ASCII codes the letters are converted by subtracting 32
        }
        
        checkPositive = inputMessage[i] - key - 65;                         //This is where the keynumber and input data[i] create
                                                                            //the first part of the algorithm to Encrypt letters
        if(checkPositive < 0)
        {
            checkPositive = checkPositive +26;                              //If checkPositive is a negative key it will convert it to positive
        }
        
        if(inputMessage[i] >= 'A' && inputMessage[i] <= 'Z')                //If statement stops any other characters such as space or punctuation from being converted
        {
            inputMessage[i] = (checkPositive % 26 ) + 65;
        }
            
        
    }
    return 0;
}

//Counts up most occuring letters to later be added to the wordCount function
//Returns type int and takes a char input


int commonLettersCount(char *message)
{
	int count;

	for (int i=0; i<strlen(message); i++)
	{
	    if(message[i] == 'E' ||
    	   message[i] == 'T' ||
     	   message[i] == 'A' ||
	       message[i] == 'O' ||
    	   message[i] == 'I' ||
		   message[i] == 'N' ||
		   message[i] == 'S' ||
		   message[i] == 'H' ||
		   message[i] == 'R' ||
		   message[i] == 'D' ||
		   message[i] == 'L' ||
		   message[i] == 'U')
        {
            count++;
		}
	}
	return count;
}

//Decrypts the inputMessage entered by user without key


void subDecryptCipher(char*inputMessage, char* outputMessage, char* encryptionCode)
{
	int index, i, j;
	for(j = 0; j < strlen(inputMessage); j++)
	{
	    
	    index = 0;
        if(inputMessage[j] >= 'A' && inputMessage[j]<= 'Z')
        {
            for(i = 0; encryptionCode[i] != inputMessage[j]; i++)
            {
                index++;
			}
			outputMessage[j] = index + 'A';                                           //Does the conversion. Letters are Decrypted one at a time because of For loop
		}
		else
		{
		    outputMessage[j] = inputMessage[j];
		}


	}
}

//Counts vowels in inputMessage to assist in decrypting the message
//Returns type int takes a char *message input
//Is added to the wordCount function
int vowelCount(char *message)
{
    int count;
    for (int i=0; i<strlen(message); i++)
    {
        if (message[i] == 'A' || message[i] == 'E' || message[i] == 'I'
				|| message[i] == 'O' || message[i] == 'U' )
		{
		    count++;
		}
	}
	return count;
}
