//
// Created by scannell on 4/27/19.
//
#include "threadFunc.h"

//thread funcs
void *quaffleAct(void *arg){
    for(;;){
        sleep(rand()%15);
        int index = rand() % 6;
        while(!(players[index]->playing)){
            index=rand() % 6;
        }
//        printf("\nquaffleAct--signalling\n");
        pthread_kill(*(players[index]->thread), SIGUSR2);
    }
}

void *bludger(void *arg){
    for(;;){
        sleep(rand()%15);
        int index=rand() % NUM_PLAYERS;
        while(!(players[index]->playing)){
            index = rand() % NUM_PLAYERS;
        }
//        printf("\nbludger--signalling\n");
        pthread_kill(*(players[index]->thread), SIGINT);
    }
}

void *snitchAct(void *arg){
    for(;;){
        sleep(rand()%5);
        caught_snitch = !caught_snitch;
    }
}

void *goal(void *arg){
    for(;;);
}

void *beater(void *arg){
    for(;;){
        sleep(rand() % 10);
        int index = rand() % NUM_PLAYERS;
        while(!(players[index]->playing)){
            index = rand() % NUM_PLAYERS;
        }
//        printf("\nbeater--signalling\n");
        pthread_kill(*(players[index]->thread), SIGUSR1);
    }
}

void *seeker(void *arg){
    for(;;){
        sleep(rand()%10);
        if(caught_snitch){
            for(int i = 0; i < NUM_PLAYERS; ++i) {
                if (players[i]->playing && *(players[i]->thread) == pthread_self()) {
                    if (strcmp(players[i]->team, "Gryffindor") == 0) {
                        gryffindor += 150;
                    } else {
                        slytherin += 150;
                    }
                    printf("%s caught the snitch! Game over!\n", players[i]->name);
                    printf("\n*************************\n");
                    printf("\nGryffindor: %d\nSlytherin: %d\n\n", gryffindor, slytherin);
                    exit(0);
                }
            }
        }
        else{
            printf("Missed the snitch!\n");
        }
    }
}

void *keeper(void *arg){
    for(;;){
        sleep(rand() % 15);
        for(int i = 0; i < NUM_PLAYERS; ++i){
            if(players[i]->playing && *(players[i]->thread) == pthread_self()){
                if(strcmp(players[i]->team, "Gryffindor") == 0){
//                    printf("\nkeeper--signalling\n");
                    pthread_kill(gryffindor_goal, SIGUSR1);
                }
                else{
//                    printf("\nkeeper--signalling\n");
                    pthread_kill(slytherin_goal, SIGUSR1);
                }
            }
        }
    }
}

void *chaser(void *arg){
    for(;;);
}