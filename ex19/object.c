#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "object.h"
#include <assert.h>

int Object_init(void *self){
    //
    printf("Defaut initialization!\n");
    return 1;
}

void Object_describe(void *self){
    Object *obj = self;
    if(obj->description){
        printf("%s.\n",obj->description);
    } else{
        printf("No description!\n");
    }
}

void Object_destroy(void *self){
    Object *obj = self;
    if(self){
        if(obj->description) free(obj->description);
        free(obj);
    }
}

void *Object_move(void *self, Direction direction){
    //
    printf("No object move function!\n");
    return NULL;
}

int Object_attack(void *self, int damage){
    printf("you can not attack\n");
    return 0;
};

void *Object_new(size_t size, Object proto, char *description){
    // setup the default functions
    if(!proto.init) proto.init = Object_init;
    if(!proto.describe) proto.describe = Object_describe;
    if(!proto.destroy) proto.destroy = Object_destroy;
    if(!proto.attack) proto.attack = Object_attack;
    if(!proto.move) proto.move = Object_move;

    Object *el = calloc(1,size); // use calloc is good! it will set all
    // elements to zero!

    /*
    why we need to recreate a new object as el?
    since Object proto is also an object in form. proto provides
    general functions, But we need a entity.
    In a way that easily understood, the proto is like a class( a room class),
    and the el entity is the real one, a roon, a dark room, bright room?
    */
    

    *el = proto; // attention! proto is not a pointer.
    el->description = strdup(description);// attention strdup function
    // you need to free description after use! or mem leak

    // make sure it is initializaed accurately
    if(!el->init(el)){
        el->destroy(el);
        return NULL;
    } else{
        return el;
    }
}