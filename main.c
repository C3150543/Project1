#include <stdio.h>
#include <string.h>

int main() {
     
    char inputMessage[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    //char outputMessage[];
    int i;
    int key = 1;
    
 
             
            for(i = 0; i < strlen(inputMessage); i++){
                
                if(inputMessage[i] >= 'Z'){
                    
                    inputMessage[i] = (inputMessage[i] + key) - 26;
                    
                    }
                else{
                    
                     inputMessage[i] = inputMessage[i] + key;
                     }
                     
                 }
                 
    printf("%s", inputMessage);

return 0;
}
