#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "OS.h"
#include "array.h"

enum keyboard{LEFT,RIGHT,UP,DOWN,ESC,ENTER};

char OSstring[10];

char *Windows ="Windows";
char *Linux ="Linux";

int main(){
    /*
    char *chess = (char *)malloc(sizeof(char) * 256 );
    initchessTEST(chess);
    chess[locatetransform(-38)] = 0;
    chess[locatetransform(-28)] = 1;
    chess[locatetransform(-82)] = 0;
    chess[locatetransform(-75)] = 1;

    printfield(chess,-127,"");

    int mychess[10];
    int enemychess[10];
    char *element;

    int j=0,k=0;
    for(int i =0;i<256;i++){
        if(chess[i] == 1){
            mychess[j] = (int)locatetransformrevers(i);
            j++;
        }
        if(chess[i] == 2){
            enemychess[k] = (int)locatetransformrevers(i);
            k++;
        }
    }

    char * my_chess_score = ScoreINIT(true);
    char * enemy_chess_score = ScoreINIT(false);
    
    printf("parts:\n");

    for(int i =0;i<10;i++){
        Array *parts;
        array_new(&parts);
        FindPartJump(chess , mychess[i] ,parts , false ,1);
        for(int j=0;j<array_size(parts);j++){
                array_get_at(parts, j,(void*)&element);
                printf("%d ",*element);
        }
        printf("\n");
        array_remove_all_free(parts);
        array_remove_all(parts);
        array_destroy(parts);
    }

    system("PAUSE");
    return 0;*/

    #ifdef WIN32
    strcpy(OSstring,Windows);
    #endif

    #ifdef linux
    strcpy(OSstring,Linux);
    #endif

    OSselect(OSstring);
    return 0;
}
