#include <stdio.h>
#include <string.h>

int main() {
     
    char inputMessage[] = "ATTAcK AT SUNRISE";
    int i;
    int key = 1;
    int checkPositive;
    

    for(i = 0; i < strlen(inputMessage); i++){
        
        checkPositive = inputMessage[i] + key - 65;
        
        if (checkPositive < 0){
            
            checkPositive = checkPositive +26;
        }
        
        if(inputMessage[i] != ' '){
            
            inputMessage[i] = (checkPositive % 26 ) + 65;
            }
            
        }
        
    printf("%s", inputMessage);
    
    return 0;
    
    }
