//
// Created by scannell on 4/27/19.
//

#ifndef UNTITLED_PLAYER_H
#define UNTITLED_PLAYER_H
#include <pthread.h>
#include <stdbool.h>
#define NUM_PLAYERS 14

struct Player
{
    pthread_t *thread;
    char team[12];
    char name[20];
    bool playing;
};

#endif //UNTITLED_PLAYER_H
