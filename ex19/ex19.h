
#ifndef _EX19_H_
#define _EX19_H_

#include "object.h"

struct Monster {
    Object proto;
    int hit_points;
};


typedef struct Monster Monster;

int Monster_attack(void *self, int damage);
int Monster_init(void *self);

struct Room {
    Object proto;

    Monster *room_monster;

    struct Room *north;
    struct Room *south;
    struct Room *west;
    struct Room *east;
};

typedef struct Room Room;

void *Room_move(void *self, Direction direction);
int Room_attack(void *self, int damage);
int Room_init(void *self);

struct Map{
    Object proto;
    Room *start;
    Room *location;
};

typedef struct Map Map;
 
void *Map_move(void *self, Direction direction);
int Map_attack(void *self, int damage);
int Map_init(void *self);

#endif