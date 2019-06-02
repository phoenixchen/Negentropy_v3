#include <stdio.h>
#include <stdlib.h>

#include "utility.h"

void initadjlist(char * chess,struct adjlist * adjlist1,struct adjlist * adjlist2){

    char init1v1[10] = {75,65,55,45,82,72,62,89,79,96};

    adjlist1 = (struct adjlist *)malloc(sizeof(struct adjlist));
}

int compare(void const *e1, void const *e2)
{
    char *i = *((char **) e1);
    char *j = *((char **) e2);

    if (*i < *j)
        return -1;
    if (*i > *j)
        return 1;
    return 0;
}

bool Visited(char new_element, Array *array){

    bool visited = false;

    char *element;
    for(int i=0;i<array_size(array);i++){
        array_get_at(array, i,(void*)&element);
        if(new_element==*element){
            visited = true;
            break;
        }
    }
    return visited;
}

void FindAllSingleMove(char * chess , char start , Array *ends){

    char *element;

    if( chess[locatetransform(start+7)]==0 ){
        element = (char *)malloc(sizeof(char));
        *element = start+7;
        array_add(ends, element);
    }
    if( chess[locatetransform(start+10)]==0 ){
        element = (char *)malloc(sizeof(char));
        *element = start+10;
        array_add(ends, element);
    }
    if( chess[locatetransform(start+17)]==0 ){
        element = (char *)malloc(sizeof(char));
        *element = start+17;
        array_add(ends, element);
    }
    if( chess[locatetransform(start-7)]==0 ){
        element = (char *)malloc(sizeof(char));
        *element = start-7;
        array_add(ends, element);
    }
    if( chess[locatetransform(start-10)]==0 ){
        element = (char *)malloc(sizeof(char));
        *element = start-10;
        array_add(ends, element);
    }
    if( chess[locatetransform(start-17)]==0 ){
        element = (char *)malloc(sizeof(char));
        *element = start-17;
        array_add(ends, element);
    }
}


void FindPartSingleMove(char * chess , char start , Array *ends,int chess_color){

    char *element;

    if(chess_color!=2){
        if( chess[locatetransform(start+7)]==0 ){
            element = (char *)malloc(sizeof(char));
            *element = start+7;
            array_add(ends, element);
        }
        if( chess[locatetransform(start+17)]==0 ){
            element = (char *)malloc(sizeof(char));
            *element = start+17;
            array_add(ends, element);
        }
    }
    if(chess_color!=1){
        if( chess[locatetransform(start-7)]==0 ){
            element = (char *)malloc(sizeof(char));
            *element = start-7;
            array_add(ends, element);
        }
        if( chess[locatetransform(start-17)]==0 ){
            element = (char *)malloc(sizeof(char));
            *element = start-17;
            array_add(ends, element);
        }
    }
    if( chess[locatetransform(start+10)]==0 ){
        element = (char *)malloc(sizeof(char));
        *element = start+10;
        array_add(ends, element);
    }
    if( chess[locatetransform(start-10)]==0 ){
        element = (char *)malloc(sizeof(char));
        *element = start-10;
        array_add(ends, element);
    }
}



void FindPartJump(char * chess , char start , Array *ends ,bool used_backwards,int chess_color){

    char *element;

    if(!Visited(start+14,ends)){
        if(chess_color==2 && used_backwards){
        }
        else{
            if( chess[locatetransform(start+14)]==0 && chess[locatetransform(start+7)]!=0 && chess[locatetransform(start+7)]!=-1){
                element = (char *)malloc(sizeof(char));
                *element = start+14;
                array_add(ends, element);
                if(chess_color==2)
                    FindPartJump(chess,*element,ends,true,chess_color);
                else
                    FindPartJump(chess,*element,ends,false,chess_color);
            }
        }
    }
    if(!Visited(start+34,ends)){
        if(chess_color==2 && used_backwards){
        }
        else{
            if( chess[locatetransform(start+34)]==0 && chess[locatetransform(start+17)]!=0 && chess[locatetransform(start+17)]!=-1){
                element = (char *)malloc(sizeof(char));
                *element = start+34;
                array_add(ends, element);
                if(chess_color==2)
                    FindPartJump(chess,*element,ends,true,chess_color);
                else
                    FindPartJump(chess,*element,ends,false,chess_color);
            }
        }
    }
    if(!Visited(start+20,ends)){
        if( chess[locatetransform(start+20)]==0 && chess[locatetransform(start+10)]!=0 && chess[locatetransform(start+10)]!=-1){
            element = (char *)malloc(sizeof(char));
            *element = start+20;
            array_add(ends, element);
            FindPartJump(chess,*element,ends,used_backwards,chess_color);
        }
    }
    if(!Visited(start-14,ends)){
        if(chess_color==1 && used_backwards){
        }
        else{
            if( chess[locatetransform(start-14)]==0 && chess[locatetransform(start-7)]!=0 && chess[locatetransform(start-7)]!=-1){
                element = (char *)malloc(sizeof(char));
                *element = start-14;
                array_add(ends, element);
                if(chess_color==1)
                    FindPartJump(chess,*element,ends,true,chess_color);
                else
                    FindPartJump(chess,*element,ends,false,chess_color);
            }
        }
    }
    if(!Visited(start-34,ends)){
        if(chess_color==1 && used_backwards){
        }
        else{
            if(chess[locatetransform(start-34)]==0 && chess[locatetransform(start-17)]!=0 && chess[locatetransform(start-17)]!=-1){
                element = (char *)malloc(sizeof(char));
                *element = start-34;
                array_add(ends, element);
                if(chess_color==1)
                    FindPartJump(chess,*element,ends,true,chess_color);
                else
                    FindPartJump(chess,*element,ends,false,chess_color);
            }
        }
    }
    if(!Visited(start-20,ends)){
        if(chess[locatetransform(start-20)]==0 && chess[locatetransform(start-10)]!=0 && chess[locatetransform(start-10)]!=-1){
            element = (char *)malloc(sizeof(char));
            *element = start-20;
            array_add(ends, element);
            FindPartJump(chess,*element,ends,used_backwards,chess_color);
        }
    }
}


void FindAllJump(char * chess , char start , Array *ends){

    char *element;

    if(!Visited(start+14,ends)){
        if( chess[locatetransform(start+14)]==0 && chess[locatetransform(start+7)]!=0 && chess[locatetransform(start+7)]!=-1){
            element = (char *)malloc(sizeof(char));
            *element = start+14;
            array_add(ends, element);
            FindAllJump(chess,*element,ends);
        }
    }
    if(!Visited(start+34,ends)){
        if( chess[locatetransform(start+34)]==0 && chess[locatetransform(start+17)]!=0 && chess[locatetransform(start+17)]!=-1){
            element = (char *)malloc(sizeof(char));
            *element = start+34;
            array_add(ends, element);
            FindAllJump(chess,*element,ends);
        }
    }
    if(!Visited(start+20,ends)){
        if( chess[locatetransform(start+20)]==0 && chess[locatetransform(start+10)]!=0 && chess[locatetransform(start+10)]!=-1){
            element = (char *)malloc(sizeof(char));
            *element = start+20;
            array_add(ends, element);
            FindAllJump(chess,*element,ends);
        }
    }
    if(!Visited(start-14,ends)){
        if( chess[locatetransform(start-14)]==0 && chess[locatetransform(start-7)]!=0 && chess[locatetransform(start-7)]!=-1){
            element = (char *)malloc(sizeof(char));
            *element = start-14;
            array_add(ends, element);
            FindAllJump(chess,*element,ends);
        }
    }
    if(!Visited(start-34,ends)){
        if(chess[locatetransform(start-34)]==0 && chess[locatetransform(start-17)]!=0 && chess[locatetransform(start-17)]!=-1){
            element = (char *)malloc(sizeof(char));
            *element = start-34;
            array_add(ends, element);
            FindAllJump(chess,*element,ends);
        }
    }
    if(!Visited(start-20,ends)){
        if(chess[locatetransform(start-20)]==0 && chess[locatetransform(start-10)]!=0 && chess[locatetransform(start-10)]!=-1){
            element = (char *)malloc(sizeof(char));
            *element = start-20;
            array_add(ends, element);
            FindAllJump(chess,*element,ends);
        }
    }
}


Array * ReturnAllOfTheMove(char * chess , char start){
    Array *ends;
    array_new(&ends);
    FindAllJump(chess,start,ends);
    FindAllSingleMove(chess,start,ends);
    return ends;
}


Array * ReturnPartMoves(char * chess , char start,bool used_backwards){
    Array *ends;
    array_new(&ends);
    int chess_color = chess[locatetransform(start)];
    FindPartJump(chess,start,ends,used_backwards,chess_color);
    FindPartSingleMove(chess,start,ends,chess_color);
    return ends;
}


void FirstScore(char * chess){
    chess[locatetransform(-96)]=1;
    chess[locatetransform(-89)]=3;
    chess[locatetransform(-79)]=3;
    chess[locatetransform(-82)]=5;
    chess[locatetransform(-72)]=6;
    chess[locatetransform(-62)]=5;
    chess[locatetransform(-75)]=7;
    chess[locatetransform(-65)]=8;
    chess[locatetransform(-55)]=8;
    chess[locatetransform(-45)]=7;
    chess[locatetransform(-108)]=5;
    chess[locatetransform(-98)]=6;
    chess[locatetransform(-88)]=7;
    chess[locatetransform(-78)]=8;
    chess[locatetransform(-68)]=9;
    chess[locatetransform(-58)]=10;
    chess[locatetransform(-48)]=11;
    chess[locatetransform(-38)]=10;
    chess[locatetransform(-28)]=9;
    chess[locatetransform(-18)]=8;
    chess[locatetransform(-8)]=7;
    chess[locatetransform(2)]=6;
    chess[locatetransform(12)]=5;
    chess[locatetransform(-91)]=8;
    chess[locatetransform(-81)]=9;
    chess[locatetransform(-71)]=10;
    chess[locatetransform(-61)]=11;
    chess[locatetransform(-51)]=12;
    chess[locatetransform(-41)]=13;
    chess[locatetransform(-31)]=13;
    chess[locatetransform(-21)]=12;
    chess[locatetransform(-11)]=11;
    chess[locatetransform(-1)]=10;
    chess[locatetransform(9)]=9;
    chess[locatetransform(19)]=8;
    chess[locatetransform(-74)]=11;
    chess[locatetransform(-64)]=12;
    chess[locatetransform(-54)]=13;
    chess[locatetransform(-44)]=14;
    chess[locatetransform(-34)]=15;
    chess[locatetransform(-24)]=16;
    chess[locatetransform(-14)]=15;
    chess[locatetransform(-4)]=14;
    chess[locatetransform(6)]=13;
    chess[locatetransform(16)]=12;
    chess[locatetransform(26)]=11;
    chess[locatetransform(-57)]=14;
    chess[locatetransform(-47)]=15;
    chess[locatetransform(-37)]=16;
    chess[locatetransform(-27)]=17;
    chess[locatetransform(-17)]=18;
    chess[locatetransform(-7)]=18;
    chess[locatetransform(3)]=17;
    chess[locatetransform(13)]=16;
    chess[locatetransform(23)]=15;
    chess[locatetransform(33)]=14;
    chess[locatetransform(-40)]=17;
    chess[locatetransform(-30)]=18;
    chess[locatetransform(-20)]=19;
    chess[locatetransform(-10)]=20;
    chess[locatetransform(0)]=21;
    chess[locatetransform(10)]=20;
    chess[locatetransform(20)]=19;
    chess[locatetransform(30)]=18;
    chess[locatetransform(40)]=17;
    chess[locatetransform(-33)]=19;
    chess[locatetransform(-23)]=20;
    chess[locatetransform(-13)]=21;
    chess[locatetransform(-3)]=22;
    chess[locatetransform(7)]=23;
    chess[locatetransform(17)]=23;
    chess[locatetransform(27)]=22;
    chess[locatetransform(37)]=21;
    chess[locatetransform(47)]=20;
    chess[locatetransform(57)]=19;
    chess[locatetransform(-26)]=21;
    chess[locatetransform(-16)]=22;
    chess[locatetransform(-6)]=23;
    chess[locatetransform(4)]=24;
    chess[locatetransform(14)]=25;
    chess[locatetransform(24)]=26;
    chess[locatetransform(34)]=25;
    chess[locatetransform(44)]=24;
    chess[locatetransform(54)]=23;
    chess[locatetransform(64)]=22;
    chess[locatetransform(74)]=21;
    chess[locatetransform(-19)]=23;
    chess[locatetransform(-9)]=24;
    chess[locatetransform(1)]=25;
    chess[locatetransform(11)]=26;
    chess[locatetransform(21)]=27;
    chess[locatetransform(31)]=28;
    chess[locatetransform(41)]=28;
    chess[locatetransform(51)]=27;
    chess[locatetransform(61)]=26;
    chess[locatetransform(71)]=25;
    chess[locatetransform(81)]=24;
    chess[locatetransform(91)]=23;
    chess[locatetransform(-12)]=25;
    chess[locatetransform(-2)]=26;
    chess[locatetransform(8)]=27;
    chess[locatetransform(18)]=28;
    chess[locatetransform(28)]=29;
    chess[locatetransform(38)]=30;
    chess[locatetransform(48)]=31;
    chess[locatetransform(58)]=30;
    chess[locatetransform(68)]=29;
    chess[locatetransform(78)]=28;
    chess[locatetransform(88)]=27;
    chess[locatetransform(98)]=26;
    chess[locatetransform(108)]=25;
    chess[locatetransform(45)]=32;
    chess[locatetransform(55)]=33;
    chess[locatetransform(65)]=33;
    chess[locatetransform(75)]=32;
    chess[locatetransform(62)]=35;
    chess[locatetransform(72)]=36;
    chess[locatetransform(82)]=35;
    chess[locatetransform(79)]=38;
    chess[locatetransform(89)]=38;
    chess[locatetransform(96)]=41;
}

void SecondScore(char * chess){

    chess[locatetransform(-96)]=41;
    chess[locatetransform(-89)]=38;
    chess[locatetransform(-79)]=38;
    chess[locatetransform(-82)]=35;
    chess[locatetransform(-72)]=36;
    chess[locatetransform(-62)]=35;
    chess[locatetransform(-75)]=32;
    chess[locatetransform(-65)]=33;
    chess[locatetransform(-55)]=33;
    chess[locatetransform(-45)]=32;
    chess[locatetransform(-108)]=25;
    chess[locatetransform(-98)]=26;
    chess[locatetransform(-88)]=27;
    chess[locatetransform(-78)]=28;
    chess[locatetransform(-68)]=29;
    chess[locatetransform(-58)]=30;
    chess[locatetransform(-48)]=31;
    chess[locatetransform(-38)]=30;
    chess[locatetransform(-28)]=29;
    chess[locatetransform(-18)]=28;
    chess[locatetransform(-8)]=27;
    chess[locatetransform(2)]=26;
    chess[locatetransform(12)]=25;
    chess[locatetransform(-91)]=23;
    chess[locatetransform(-81)]=24;
    chess[locatetransform(-71)]=25;
    chess[locatetransform(-61)]=26;
    chess[locatetransform(-51)]=27;
    chess[locatetransform(-41)]=28;
    chess[locatetransform(-31)]=28;
    chess[locatetransform(-21)]=27;
    chess[locatetransform(-11)]=26;
    chess[locatetransform(-1)]=25;
    chess[locatetransform(9)]=24;
    chess[locatetransform(19)]=23;
    chess[locatetransform(-74)]=21;
    chess[locatetransform(-64)]=22;
    chess[locatetransform(-54)]=23;
    chess[locatetransform(-44)]=24;
    chess[locatetransform(-34)]=25;
    chess[locatetransform(-24)]=26;
    chess[locatetransform(-14)]=25;
    chess[locatetransform(-4)]=24;
    chess[locatetransform(6)]=23;
    chess[locatetransform(16)]=22;
    chess[locatetransform(26)]=21;
    chess[locatetransform(-57)]=19;
    chess[locatetransform(-47)]=20;
    chess[locatetransform(-37)]=21;
    chess[locatetransform(-27)]=22;
    chess[locatetransform(-17)]=23;
    chess[locatetransform(-7)]=23;
    chess[locatetransform(3)]=22;
    chess[locatetransform(13)]=21;
    chess[locatetransform(23)]=20;
    chess[locatetransform(33)]=19;
    chess[locatetransform(-40)]=17;
    chess[locatetransform(-30)]=18;
    chess[locatetransform(-20)]=19;
    chess[locatetransform(-10)]=20;
    chess[locatetransform(0)]=21;
    chess[locatetransform(10)]=20;
    chess[locatetransform(20)]=19;
    chess[locatetransform(30)]=18;
    chess[locatetransform(40)]=17;
    chess[locatetransform(-33)]=14;
    chess[locatetransform(-23)]=15;
    chess[locatetransform(-13)]=16;
    chess[locatetransform(-3)]=17;
    chess[locatetransform(7)]=18;
    chess[locatetransform(17)]=18;
    chess[locatetransform(27)]=17;
    chess[locatetransform(37)]=16;
    chess[locatetransform(47)]=15;
    chess[locatetransform(57)]=14;
    chess[locatetransform(-26)]=11;
    chess[locatetransform(-16)]=12;
    chess[locatetransform(-6)]=13;
    chess[locatetransform(4)]=14;
    chess[locatetransform(14)]=15;
    chess[locatetransform(24)]=16;
    chess[locatetransform(34)]=15;
    chess[locatetransform(44)]=14;
    chess[locatetransform(54)]=13;
    chess[locatetransform(64)]=12;
    chess[locatetransform(74)]=11;
    chess[locatetransform(-19)]=8;
    chess[locatetransform(-9)]=9;
    chess[locatetransform(1)]=10;
    chess[locatetransform(11)]=11;
    chess[locatetransform(21)]=12;
    chess[locatetransform(31)]=13;
    chess[locatetransform(41)]=13;
    chess[locatetransform(51)]=12;
    chess[locatetransform(61)]=11;
    chess[locatetransform(71)]=10;
    chess[locatetransform(81)]=9;
    chess[locatetransform(91)]=8;
    chess[locatetransform(-12)]=5;
    chess[locatetransform(-2)]=6;
    chess[locatetransform(8)]=7;
    chess[locatetransform(18)]=8;
    chess[locatetransform(28)]=9;
    chess[locatetransform(38)]=10;
    chess[locatetransform(48)]=11;
    chess[locatetransform(58)]=10;
    chess[locatetransform(68)]=9;
    chess[locatetransform(78)]=8;
    chess[locatetransform(88)]=7;
    chess[locatetransform(98)]=6;
    chess[locatetransform(108)]=5;
    chess[locatetransform(45)]=7;
    chess[locatetransform(55)]=8;
    chess[locatetransform(65)]=8;
    chess[locatetransform(75)]=7;
    chess[locatetransform(62)]=5;
    chess[locatetransform(72)]=6;
    chess[locatetransform(82)]=5;
    chess[locatetransform(79)]=3;
    chess[locatetransform(89)]=3;
    chess[locatetransform(96)]=1;
}

char *ScoreINIT(bool is_first){

    char *chess_score = (char *)malloc(sizeof(char)*256);

    for(int i=0;i<256;i++)
        chess_score[i] = 0;

    if(!is_first)
        SecondScore(chess_score);
    else
        FirstScore(chess_score);

    return chess_score;
}


int ScoreCaculate(char *chess_score,char start,char end){

    return chess_score[locatetransform(end)] - chess_score[locatetransform(start)];
}
