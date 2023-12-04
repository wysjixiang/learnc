#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ex19.h"


int Monster_attack(void *self, int damage){

    Monster *monster = self;

    printf("you attack %s\n", monster->_(description));

    monster->hit_points -= damage;
    if(monster->hit_points > 0){
        printf("It is still alive.\n");
        printf("Nonster HP: %d\n", monster->hit_points);
        return 0;
    } else{
        printf("It is dead!\n");
        printf("Finally you defeated the Monster!\n");
        return 1;
    }
}

int Monster_init(void *self){
    Monster *monster = self;
    monster->hit_points = 10;
    return 1;
}

Object MonsterProto = {
    .init = Monster_init,
    .attack = Monster_attack
};


void *Room_move(void *self, Direction direction){
    Room *room = self;
    Room *next = NULL;

    if(direction == NORTH && room->north){
        printf("you go north, into:\n");
        next = room->north;
    } else if(direction == SOUTH && room->south){
        printf("you go south, into:\n");
        next = room->south;
    } else if(direction == WEST && room->west){
        printf("you go west, into:\n");
        next = room->west;
    } else{
        printf("you go east, into:\n");
        next = room->east;
    }

    if(next){
        next->_(describe)(next);
    } else{
        printf("stand still");
    }

    return next;
}


int Room_attack(void *self, int damage){
    Room *room = self;
    Monster *monster = room->room_monster;

    if(monster){
        monster->_(attack)(monster,damage);
        return 1;
    } else{
        printf("no monster in this room\n");
        return 0;
    }
}

Object RoomProto = {
    .move = Room_move,
    .attack = Room_attack
};


void *Map_move(void *self, Direction direction){
    Map *map = self;
    Room *location = map->location;
    Room *next = NULL;

    next = location->_(move)(location,direction);
    if(next){
        map->location = next;
        return next;
    } else{
        printf("you can't go that direction\n");
        return location;
    }
}

int Map_attack(void *self, int damage){
    Map *map = self;
    Room *location = map->location;

    return location->_(attack)(location,damage);
}

int Map_init(void *self){

    Map *map = self;

    Room *hall = NEW(Room,"The great Hall");
    Room *throne = NEW(Room,"The throne room");
    Room *arena = NEW(Room, "The arena, with the minotaur");
    Room *kitchen = NEW(Room, "Kitchen, you have the knife now");

    arena->room_monster = NEW(Monster, "The evil monster");

        // setup the map rooms
    hall->north = throne;

    throne->west = arena;
    throne->east = kitchen;
    throne->south = hall;

    arena->east = throne;
    kitchen->west = throne;

    // start the map and the character off in the hall
    map->start = hall;
    map->location = hall;

    return 1;

}

Object MapProto = {
    .init = Map_init,
    .move = Map_move,
    .attack = Map_attack
};

int process_input(Map *game){

    printf("\n> ");
    char ch = getchar();
    // since getchar will read 'enter' key, so need to handle this
    if(ch == '\n') return 1;

    int damage = rand() % 4 + 1;
    printf("This round the damage is %d\n",damage);

        switch(ch) {

        case 'g':
            printf("Giving up? You suck.\n");
            return 0;
            break;

        case 'n':
            game->_(move)(game, NORTH);
            break;

        case 's':
            game->_(move)(game, SOUTH);
            break;

        case 'e':
            game->_(move)(game, EAST);
            break;

        case 'w':
            game->_(move)(game, WEST);
            break;

        case 'a':

            game->_(attack)(game, damage);
            break;
        case 'l':
            printf("You can go:\n");
            if(game->location->north) {
                printf("NORTH:    ");
                game->location->north->_(describe)(game->location->north);
            } 
            if(game->location->south) {
                printf("SOUTH:    ");
                game->location->south->_(describe)(game->location->south);
            } 
            if(game->location->east) {
                printf("EAST:    ");
                game->location->east->_(describe)(game->location->east);
            } 
            if(game->location->west) {
                printf("WEST:    ");
                game->location->west->_(describe)(game->location->west);
            } 
            break;

        default:
            printf("What?: %d\n", ch);
    }

    return 1;

}

int main(int argc, char **argv){
    srand(time(NULL));

    Map *game = NEW(Map, "The Hall of the Minotaur");

    printf("You enter the ");
    game->location->_(describe)(game->location);

    while(process_input(game));

    return 0;
}