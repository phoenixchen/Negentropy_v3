#include "array.h"

struct adjlist{
    char locate;
    struct adjlist *next;
};

struct headadjlist{
    char head;
    struct headadjlist *next;
    struct adjlist *canjumpto;
};

void initadjlist(char * chess,struct adjlist * adjlist1,struct adjlist * adjlist2);

int compare(void const *e1, void const *e2);

bool Visited(char new_element, Array *ends);

void FindAllSingleMove(char * chess , char start , Array *ends);

void FindPartSingleMove(char * chess , char start , Array *ends,int chess_color);

void FindPartJump(char * chess , char start , Array *ends ,bool used_backwards,int chess_color);

void FindAllJump(char * chess , char start , Array *ends);

Array *ReturnAllOfTheMove(char * chess , char start);

Array *ReturnPartMoves(char * chess , char start,bool used_backwards);

void FirstScore(char * chess);

void SecondScore(char * chess);

char *ScoreINIT(bool is_first);

int ScoreCaculate(char *chess_score,char start,char end);
