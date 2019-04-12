#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 

int rotationCypherEncrypt(char *, int);

 

int main() {

    char inputMessage[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcde";

 

              if(rotationCypherEncrypt(inputMessage, 15) < 0) {

                             printf("Failed to encrypt file");

                             exit(-1);

              }

       

    printf("%s", inputMessage);

   

    return 0;   

}

 

int rotationCypherEncrypt(char *inputMessage, int key)

{

      int i;

      int checkPositive;

 

                key = key % 26;

 

                for(i = 0; i < strlen(inputMessage); i++){

        if(inputMessage[i] >= 'a' && inputMessage[i] <= 'z')

        {

            inputMessage[i] = inputMessage[i] - 32;           

        }

       

        checkPositive = inputMessage[i] + key - 65;

       

        if (checkPositive < 0){

           

            checkPositive = checkPositive +26;

        }

       

        if(inputMessage[i] >= 'A' && inputMessage[i] <= 'Z') //Excluding all characters

        {                                                    //that are not Capitals  

            inputMessage[i] = (checkPositive % 26 ) + 65;

        }     

      }

 

              return 0;

}