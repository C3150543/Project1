#include <stdio.h>
#include <string.h>

int main() {
     
    char inputMessage[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcde";
    int i;
    int key = 1;
    int checkPositive;
    

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
        
    printf("%s", inputMessage);
    
    return 0;
    
    }
