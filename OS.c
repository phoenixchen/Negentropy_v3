#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#include "graphic.h"
#include "algorithm.h"
#include "array.h"

    enum keyboard{LEFT,RIGHT,UP,DOWN,ESC,ENTER};
    bool entered = false;

    char input1,input2,input3;
    enum keyboard useroperation=LEFT;
    char cursor = 0;
    char user = 1;

    char start = -127;
    char end = -127;
    char temp = -127;

    char message[70] ;

    char *str ="操作方式:上下左右 確認按ENTER\n";

    char *invalidmsg = "不合法走步\n";


#ifdef linux
    #include <unistd.h>
    #include<termios.h>
    char getch(){
    int i;//判斷是否有read到值
    char ch;
    struct termios _old, _new;

    tcgetattr (0, &_old);
    memcpy (&_new, &_old, sizeof (struct termios));
    _new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr (0, TCSANOW, &_new);
    i = read (0, &ch, 1);
    tcsetattr (0, TCSANOW, &_old);
    if (i == 1)/* ch is the character to use */
        return ch;
    else/* there was some problem; complain, return error, whatever */
        printf("error!n");;
    return 0;
    }
#endif


void WinGaming(void){

    char *chess = (char *)malloc(sizeof(char) * 256 );
    initchessTEST(chess);
    //initchess(chess);
    strcpy(message,str);

    bool AIturn = false;

    while(1){

        printfield(chess,cursor,message);

        if(!AIturn){
            for(input1 = -128; input1<127 ; input1++){  //印自己的棋子
                if(chess[(input1+128)] == 1)
                printf("%4d",locatetransformrevers(input1+128));
            }
            printf("\n");

            for(input1 = -128; input1<127 ; input1++){  //印對手的棋子
                if(chess[(input1+128)] == 2)
                printf("%4d",locatetransformrevers(input1+128));
            }
            printf("\n");

            printf("%5d%5d%5d%5d\n",start,end,locatetransform(end),entered);

            input1=getch();
            if(input1==27)
                useroperation=ESC;
            if(useroperation==ESC)
                break;
            if(input1==13)
                useroperation=ENTER;
            if(useroperation==ENTER){

                if(entered == false)
                        entered = true;
                else{
                    if(entered == true){
                        if(cursor == end | abs(cursor - start)==34 | abs(cursor - start)==20 | abs(cursor - start)==14){
                            if((chess[locatetransform(start + (cursor - start)/2)] != 1) && \
                            (chess[locatetransform(start + (cursor - start)/2)] != 2)){
                                useroperation=LEFT;
                                strcpy(message,invalidmsg);
                                continue;
                            }
                        }
                        else{
                            strcpy(message,invalidmsg);
                            useroperation=LEFT;
                            continue;
                        }
                    }
                }

                if(start==-127){
                    start = cursor;
                    entered = false;
                    if(chess[locatetransform(start)]!=1){
                            start = -127;
                            end = -127;
                            strcpy(message,invalidmsg);
                    }
                }
                else{

                    if(end == cursor){
                        start = -127;
                        end = -127;
                        entered = false;
                        AIturn = true;
                        useroperation=LEFT;
                        continue;
                    }

                    temp = end;
                    end = cursor;

                    if(abs(end - start)==17 | abs(end - start)==10 | abs(end - start)==7){
                        if(chess[locatetransform(end)]==0){
                            if(user == 1)
                                chess[locatetransform(end)] = 1;
                            else
                                chess[locatetransform(end)] = 2;
                            chess[locatetransform(start)] = 0;
                            entered = false;
                            AIturn = true;
                            start = -127;
                            end == -127;
                            useroperation=LEFT;
                            continue;
                        }
                        else{
                            entered = false;
                            start = -127;
                            end == -127;
                            strcpy(message,invalidmsg);
                            useroperation=LEFT;
                            continue;
                        }
                    }

                    //若跳躍的間格正確
                    if(abs(end - start)==34 | abs(end - start)==20 | abs(end - start)==14){
                    //若有旁邊有人可以當跳板
                        if((chess[locatetransform(start + (end - start)/2)] == 1) || \
                           (chess[locatetransform(start + (end - start)/2)] == 2)){
                    //若跳躍的目的地沒有其他人
                               if(chess[locatetransform(end)] == 0){
                                    if(user == 1)
                                        chess[locatetransform(end)] = 1;
                                    else
                                        chess[locatetransform(end)] = 2;
                                    chess[locatetransform(start)] = 0;
                                    if(user == 1)
                                        user = 2;
                                    if(user == 2)
                                        user = 1;
                               }
                                else{
                                    //start = -127;
                                    //end = -127;
                                    //entered = false;
                                    end = temp;
                                    strcpy(message,invalidmsg);
                                    useroperation=LEFT;
                                    continue;
                                }
                        }
                        else{
                            start = -127;
                            entered = false;
                            end = temp;
                            strcpy(message,invalidmsg);
                            useroperation=LEFT;
                            continue;
                        }
                    }
                    else{
                        start = -127;
                        entered = false;
                        end = temp;
                        strcpy(message,invalidmsg);
                        useroperation=LEFT;
                        continue;
                    }
                    start = end;
                    //end = -127;
                }
                useroperation=LEFT;
                continue;
            }
            if(input1!=-32)
                continue;

            input2=getch();
            if(input1==-32){
                 switch(input2){
                 case 72: useroperation=UP;    break;
                 case 80: useroperation=DOWN;  break;
                 case 75: useroperation=LEFT;  break;
                 case 77: useroperation=RIGHT; break;
                }
            strcpy(message,str);
            cursor = cursormove(chess,cursor,(char)useroperation);
            }
        }
        else{
            AIturn = false;
            //Greedy(chess,2);
            Negentropy(chess,2);
/*
/////////////////////////////////////////////////////////////////////
//The code below is for Negentropy_thread_version

            Array *best_solution;
            array_new(&best_solution);

            pthread_t thread[7];
            void *ret;
            for(int i=0;i<7;i++)
                pthread_create(&thread[i], NULL, Negentropy_thread_version, (void*)chess);

            struct MCTS *nodefrom;
            struct MCTS *nodeto;

            pthread_join(thread[0], &ret);

            Array *thread_return_result = (Array *)ret;

            for(int j=0;j<array_size(thread_return_result);j++){
                array_get_at(thread_return_result, j,(void*)&nodefrom);
                nodeto = (struct MCTS*)malloc(sizeof(struct MCTS));
                nodeto->visit_times = nodefrom->visit_times;
                nodeto->win_rate = nodefrom->win_rate;
                nodeto->start = nodefrom->start;
                nodeto->end = nodefrom->end;
                array_add_at(best_solution,(void*)nodeto,j);
            }

            for(int i=1;i<7;i++){
                pthread_join(thread[i], &ret);

                thread_return_result = (Array *)ret;

                for(int j=0;j<array_size(thread_return_result);j++){
                    array_get_at(thread_return_result, j,(void*)&nodefrom);
                    array_remove_at(best_solution, j,(void*)&nodeto);
                    nodeto->visit_times = nodeto->visit_times + nodefrom->visit_times;
                    nodeto->win_rate = nodeto->win_rate + nodefrom->win_rate;
                    array_add_at(best_solution,(void*)nodeto,j);
                }
            }

            double best_ucb = 0;
            int best_move_start;
            int best_move_end;
            int all_of_the_visit_times = 0;
            double node_ucb;

            for(int j=0;j<array_size(best_solution);j++){
                array_get_at(best_solution, j,(void*)&nodeto);
                all_of_the_visit_times = all_of_the_visit_times + nodeto->visit_times;
            }

            for(int j=0;j<array_size(best_solution);j++){
                array_get_at(best_solution, j,(void*)&nodeto);
                node_ucb = ((double)nodeto->win_rate/(double)nodeto->visit_times) + \
                (double)sqrt(2*log((double)all_of_the_visit_times)/(double)nodeto->visit_times);
                if(node_ucb > best_ucb){
                    best_ucb = node_ucb;
                    best_move_start = nodeto->start;
                    best_move_end = nodeto->end;
                }


                //printf("%d->%d,visit_times:%d,win_rate:%d\n",nodeto->start,nodeto->end,nodeto->visit_times,nodeto->win_rate);
            }
            //system("PAUSE");
            chess[locatetransform(best_move_start)] = 0;
            chess[locatetransform(best_move_end)] = 2;
/////////////////////////////////////////////////////////////////////
*/
        }
    }
}

/*                node_ucb = ((double)node->win_rate/(double)node->visit_times) + \
    (double)sqrt(2*log((double)visit_count)/(double)node->visit_times);*/


#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void WinGamingAIvsAI(void){

    char *chess = (char *)malloc(sizeof(char) * 256 );
    initchessTEST(chess);
    strcpy(message,str);

    int my_chess_color = 1;

    while(1){

        printfield(chess,cursor,message);

        if(my_chess_color ==1){
            //Greedy(chess,my_chess_color);
            my_chess_color = 2;
            #ifdef _WIN32
            Sleep(100);
            #else
            usleep(100*1000);
            #endif
        }
        else{
            //Greedy(chess,my_chess_color);
            my_chess_color = 1;
            #ifdef _WIN32
            Sleep(100);
            #else
            usleep(100*1000);
            #endif
        }
    }
}

void LinGaming(void){

    char *chess = (char *)malloc(sizeof(char) * 256 );
    initchess(chess);
    strcpy(message,str);

    while(1){

        printfield(chess,cursor,message);

        for(input1 = -128; input1<127 ; input1++){  //印自己的棋子
        if(chess[(input1+128)] == 1)
        printf("%4d",locatetransformrevers(input1+128));
        }
        printf("\n");
        for(input1 = -128; input1<127 ; input1++){  //印對手的棋子
        if(chess[(input1+128)] == 2)
        printf("%4d",locatetransformrevers(input1+128));
        }
        printf("\n");

        printf("%5d%5d%5d%5d\n",start,end,locatetransform(end),entered);

        input1=getch();

        if(input1==10)
            useroperation=ENTER;
        if(useroperation==ENTER){

            if(entered == false)
                    entered = true;
            else{
                if(entered == true){
                    if(cursor == end | abs(cursor - start)==34 | abs(cursor - start)==20 | abs(cursor - start)==14){
                    }
                    else{
                        strcpy(message,invalidmsg);
                        useroperation=LEFT;
                        continue;
                    }
                }
            }

            if(start==-127){
                start = cursor;
                entered = false;
                if(chess[locatetransform(start)]!=1){
                        start = -127;
                        end = -127;
                        strcpy(message,invalidmsg);
                }
            }
            else{

                if(end == cursor){
                    start = -127;
                    end = -127;
                    entered = false;
                    useroperation=LEFT;
                    continue;
                }

                temp = end;
                end = cursor;


                if(abs(end - start)==17 | abs(end - start)==10 | abs(end - start)==7){
                    if(chess[locatetransform(end)]==0){
                        if(user == 1)
                            chess[locatetransform(end)] = 1;
                        else
                            chess[locatetransform(end)] = 2;
                        chess[locatetransform(start)] = 0;
                        entered = false;
                        start = -127;
                        end = -127;
                        useroperation=LEFT;
                        continue;
                    }
                    else{
                        entered = false;
                        start = -127;
                        end = -127;
                        strcpy(message,invalidmsg);
                        useroperation=LEFT;
                        continue;
                    }
                }

                //若跳躍的間格正確
                if(abs(end - start)==34 | abs(end - start)==20 | abs(end - start)==14){
                //若有旁邊有人可以當跳板
                    if((chess[locatetransform(start + (end - start)/2)] == 1) || \
                       (chess[locatetransform(start + (end - start)/2)] == 2)){
                //若跳躍的目的地沒有其他人
                           if(chess[locatetransform(end)] == 0){
                                if(user == 1)
                                    chess[locatetransform(end)] = 1;
                                else
                                    chess[locatetransform(end)] = 2;
                                chess[locatetransform(start)] = 0;

                                if(user == 1)
                                    user = 2;
                                if(user == 2)
                                    user = 1;
                            }
                            else{
                                //start = -127;
                                //end = -127;
                                //entered = false;
                                end = temp;
                                strcpy(message,invalidmsg);
                                useroperation=LEFT;
                                continue;
                            }
                    }
                    else{
                        start = -127;
                        entered = false;
                        end = temp;
                        strcpy(message,invalidmsg);
                        useroperation=LEFT;
                        continue;
                    }
                }
                else{
                    start = -127;
                    entered = false;
                    end = temp;
                    strcpy(message,invalidmsg);
                    useroperation=LEFT;
                    continue;
                }

                start = end;
            }
            useroperation=LEFT;
            continue;
        }

        if(input1==27){

            input2=getch();
            if(input2 != 91)
            useroperation = ESC;
            if(useroperation==ESC)
            break;

            if(input2==91){

                input3=getch();

                if(input3 > 68 || input3 < 65)
                    continue;

                switch(input3){
                 case 65: useroperation=UP;    break;
                 case 66: useroperation=DOWN;  break;
                 case 68: useroperation=LEFT;  break;
                 case 67: useroperation=RIGHT; break;
                }
                strcpy(message,str);
                cursor = cursormove(chess,cursor,(char)useroperation);
            }
        }
        else
            continue;
    }
}


void OSselect(char *OS){

    if(!strcmp(OS,"Windows")){
        WinGaming();
        //WinGamingAIvsAI();
    }

    if(!strcmp(OS,"Linux"))
        LinGaming();
}
