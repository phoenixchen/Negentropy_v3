int locatetransform(char locate);
char locatetransformrevers(int locate);
void printchess(char locate, char * chess, char cursor);
void printfield(char * chess,char cursor,char *message);
void printfieldwithoutcls(char * chess,char cursor);
int initchess(char * chess);
void initchessTEST(char * chess);
char cursormove(char * chess,char cursor,char useroperation);
char* copyfield(char * chess);
