#include <stdio.h>
#include <string.h>

int main() {
     
    char inputMessage[] = "ATTACK AT SUNRISE";
    //char outputMessage[];
    int i;
    int key = 1;
    

    for(i = 0; i < strlen(inputMessage); i++){
        
        if(inputMessage[i] != ' '){
            
            inputMessage[i] = ((inputMessage[i] + key - 65 ) % 26 ) + 65;
            
        }
        
        else{
            
            inputMessage[i] = inputMessage[i];
            
            
        }
        

        
    }
    
    printf("%s", inputMessage);
    
    return 0;
    
    }
