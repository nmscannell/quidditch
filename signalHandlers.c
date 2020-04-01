//
// Created by scannell on 4/27/19.
//
#include "signalHandlers.h"

void hitOrScored(int signo){
//    printf("\nBeginning of hitOrScored\n");
    for(int i = 0; i < NUM_PLAYERS; ++i){
        if(players[i]->playing && *(players[i]->thread) == pthread_self()){
            players[i]->playing = false;
            printf("%s hit by a bludger!\n", players[i]->name);
            pthread_exit(0);
        }
    }
    if(pthread_self() == gryffindor_goal){
        slytherin += 10;
        printf("10 points to Slytherin!\n");
    }
    else{
        gryffindor += 10;
        printf("10 points to Gryffindor!\n");
    }
}

void saved(int signo){
//    printf("\nBeginning of saved\n");
    for(int i = 0; i < NUM_PLAYERS; ++i){
        if(players[i]->playing && *(players[i]->thread) == pthread_self()){
            printf("%s saved by beater!\n", players[i]->name);
            return;
        }
    }
    if(pthread_self() == gryffindor_goal){
        printf("Great save by Oliver Wood!\n");
    }
    else{
        printf("Great save by Miles Bletchley!\n");
    }
}

void caughtQuaffle(int signo){
//    printf("\nBeginning of caughtQuaffle\n");
    for(int i = 0; i < NUM_PLAYERS; ++i){
        if(players[i]->playing && *(players[i]->thread) == pthread_self()){
            printf("%s has the quaffle!\n", players[i]->name);
            if(strcmp(players[i]->team, "Gryffindor") == 0){
//                printf("\ncaughtQuaffle--signalling\n");
                pthread_kill(slytherin_goal, SIGINT);
            }
            else{
//                printf("\ncaughtQuaffle--signalling\n");
                pthread_kill(gryffindor_goal, SIGINT);
            }
        }
    }
}
