#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#define NUM_PLAYERS 14

struct Player{
    pthread_t *thread;
    char team[12];
    char name[20];
    bool playing;
};

// Gryffindor
pthread_t seekerG, keeperG;
pthread_t beaterG_1, beaterG_2;
pthread_t chaserG_1, chaserG_2, chaserG_3;

// Slytherin
pthread_t seekerS, keeperS;
pthread_t beaterS_1, beaterS_2;
pthread_t chaserS_1, chaserS_2, chaserS_3;

// Players
struct Player chaserG_1_s = {.thread = &chaserG_1, .team = "Gryffindor", .name = "Angelina Johnson", .playing = true};
struct Player chaserG_2_s = {.thread = &chaserG_2, .team = "Gryffindor", .name = "Alicia Spinnet", .playing = true};
struct Player chaserG_3_s = {.thread = &chaserG_3, .team = "Gryffindor", .name = "Katie Bell", .playing = true};
struct Player chaserS_1_s = {.thread = &chaserS_1, .team = "Slytherin", .name = "Marcus Flint", .playing = true};
struct Player chaserS_2_s = {.thread = &chaserS_2, .team = "Slytherin", .name = "Graham Montague", .playing = true};
struct Player chaserS_3_s = {.thread = &chaserS_3, .team = "Slytherin", .name = "Cassius Warrington", .playing = true};
struct Player seekerG_s = {.thread = &seekerG, .team = "Gryffindor", .name = "Harry Potter", .playing = true};
struct Player seekerS_s = {.thread = &seekerS, .team = "Slytherin", .name = "Draco Malfoy", .playing = true};
struct Player keeperG_s = {.thread = &keeperG, .team = "Gryffindor", .name = "Oliver Wood", .playing = true};
struct Player keeperS_s = {.thread = &keeperS, .team = "Slytherin", .name = "Miles Bletchley", .playing = true};
struct Player beaterG_1_s = {.thread = &beaterG_1, .team = "Gryffindor", .name = "Fred Weasley", .playing = true};
struct Player beaterG_2_s = {.thread = &beaterG_2, .team = "Gryffindor", .name = "George Weasley", .playing = true};
struct Player beaterS_1_s = {.thread = &beaterS_1, .team = "Slytherin", .name = "Peregrine Derrick", .playing = true};
struct Player beaterS_2_s = {.thread = &beaterS_2, .team = "Slytherin", .name = "Lucian Bole", .playing = true};

struct Player *players[14] = {&chaserG_1_s, &chaserG_2_s, &chaserG_3_s,
                              &chaserS_1_s, &chaserS_2_s, &chaserS_3_s,
                              &seekerG_s, &seekerS_s, &keeperG_s, &keeperS_s,
                              &beaterG_1_s, &beaterG_2_s, &beaterS_1_s, &beaterS_2_s};

pthread_t quaffle;
pthread_t bludger1;
pthread_t bludger2;
pthread_t snitch;
pthread_t gryffindor_goal;
pthread_t slytherin_goal;

static volatile bool caught_snitch = false;
static volatile int gryffindor = 0;
static volatile int slytherin = 0;

//signal handlers
void hitOrScored(int signo){
    for(int i = 0; i < NUM_PLAYERS; ++i){
        if(players[i]->playing && *(players[i]->thread) == pthread_self()){
            players[i]->playing = false;
            printf("%s was hit by a bludger!\n", players[i]->name);
            pthread_exit(0);
        }
    }

    if(pthread_self() == gryffindor_goal){
        slytherin += 10;
        printf("10 points to Slytherin!\n");
    }else{
        gryffindor += 10;
        printf("10 points to Gryffindor!\n");
    }
}

void saved(int signo){
    if(pthread_self() == gryffindor_goal)
        printf("Great save by Oliver Wood!\n");
    else if(pthread_self() == slytherin_goal)
        printf("Great save by Miles Bletchley!\n");
    else
        for(int i = 0; i < NUM_PLAYERS; ++i){
            if(players[i]->playing && *(players[i]->thread) == pthread_self()){
                printf("%s was saved by a beater!\n", players[i]->name);
                return;
            }
        }
}

void caughtQuaffle(int signo){
    for(int i = 0; i < NUM_PLAYERS; ++i){
        if(players[i]->playing && *(players[i]->thread) == pthread_self()){
            printf("%s has the quaffle!\n", players[i]->name);

            if(strcmp(players[i]->team, "Gryffindor") == 0)
                pthread_kill(slytherin_goal, SIGINT);
            else
                pthread_kill(gryffindor_goal, SIGINT);
        }
    }
}

//thread funcs
void *quaffleAct(void *arg){
    for(;;){
        sleep(rand() % 15);
        int index = rand() % 6;
        while(!(players[index]->playing))
            index=rand() % 6;

        pthread_kill(*(players[index]->thread), SIGUSR2);
    }
}

void *bludger(void *arg){
    for(;;){
        sleep(rand() % 20);
        int index=rand() % NUM_PLAYERS;
        while(!(players[index]->playing))
            index = rand() % NUM_PLAYERS;

        pthread_kill(*(players[index]->thread), SIGINT);
    }
}

void *snitchAct(void *arg){
    for(;;){
        sleep(rand() % 5);
        caught_snitch = !caught_snitch;
    }
}

void *goal(void *arg){
    for(;;);
}

void *beater(void *arg){
    for(;;){
        sleep(rand() % 20);
        int index = rand() % NUM_PLAYERS;
        while(!(players[index]->playing))
            index = rand() % NUM_PLAYERS;

        pthread_kill(*(players[index]->thread), SIGUSR1);
    }
}

void *seeker(void *arg){
    for(;;){
        sleep(rand()%10);
        if(caught_snitch){
            for(int i = 0; i < NUM_PLAYERS; ++i) {
                if (players[i]->playing && *(players[i]->thread) == pthread_self()) {
                    if (strcmp(players[i]->team, "Gryffindor") == 0)
                        gryffindor += 150;
                    else
                        slytherin += 150;

                    printf("%s caught the snitch! Game over!\n", players[i]->name);
                    printf("\n*************************\n");
                    printf("\nGryffindor: %d\nSlytherin: %d\n\n", gryffindor, slytherin);
                    exit(0);
                }
            }
        }
        else
            printf("Missed the snitch!\n");
    }
}

void *keeper(void *arg){
    for(;;){
        sleep(rand() % 15);
        for(int i = 0; i < NUM_PLAYERS; ++i){
            if(players[i]->playing && *(players[i]->thread) == pthread_self()){
                if(strcmp(players[i]->team, "Gryffindor") == 0)
                    pthread_kill(gryffindor_goal, SIGUSR1);
                else
                    pthread_kill(slytherin_goal, SIGUSR1);
            }
        }
    }
}

void *chaser(void *arg){
    for(;;);
}

int main() {
    setbuf(stdout, NULL);

    //signal handlers
    struct sigaction sigint_act;
    sigint_act.sa_handler = hitOrScored;
    sigint_act.sa_flags = 0;
    sigemptyset(&sigint_act.sa_mask);
    sigaction(SIGINT, &sigint_act, NULL);

    struct sigaction sigusr1_act;
    sigusr1_act.sa_handler = saved;
    sigusr1_act.sa_flags = 0;
    sigemptyset(&sigusr1_act.sa_mask);
    sigaction(SIGUSR1, &sigusr1_act, NULL);

    struct sigaction sigusr2_act;
    sigusr2_act.sa_handler = caughtQuaffle;
    sigusr2_act.sa_flags = 0;
    sigemptyset(&sigusr2_act.sa_mask);
    sigaction(SIGUSR2, &sigusr2_act, NULL);

    printf("\nMadam Hooch has blown the whistle! Let the game begin!\n");
    printf("\n*************************\n\n");

    //players
    pthread_create(&chaserG_1, NULL, &chaser, NULL);
    pthread_create(&chaserG_2, NULL, &chaser, NULL);
    pthread_create(&chaserG_3, NULL, &chaser, NULL);
    pthread_create(&chaserS_1, NULL, &chaser, NULL);
    pthread_create(&chaserS_2, NULL, &chaser, NULL);
    pthread_create(&chaserS_3, NULL, &chaser, NULL);
    pthread_create(&beaterG_1, NULL, &beater, NULL);
    pthread_create(&beaterG_2, NULL, &beater, NULL);
    pthread_create(&beaterS_1, NULL, &beater, NULL);
    pthread_create(&beaterS_2, NULL, &beater, NULL);
    pthread_create(&keeperG, NULL, &keeper, NULL);
    pthread_create(&keeperS, NULL, &keeper, NULL);
    pthread_create(&seekerG, NULL, &seeker, NULL);
    pthread_create(&seekerS, NULL, &seeker, NULL);

    //balls
    pthread_create(&quaffle, NULL, &quaffleAct, NULL);
    pthread_create(&bludger1, NULL, &bludger, NULL);
    pthread_create(&bludger2, NULL, &bludger, NULL);
    pthread_create(&snitch, NULL, &snitchAct, NULL);

    //goals
    pthread_create(&gryffindor_goal, NULL, &goal, NULL);
    pthread_create(&slytherin_goal, NULL, &goal, NULL);

    for(int i = 0; i < NUM_PLAYERS; ++i)
        pthread_join(*(players[i]->thread), NULL);

    printf("All players out! Game over!\n");
    printf("\n*************************\n");
    printf("\nGryffindor: %d \nSlytherin: %d\n\n", gryffindor, slytherin);

    return 0;
}