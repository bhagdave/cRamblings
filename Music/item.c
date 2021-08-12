#include "item.h"

 music_item *create_music_item(){
	music_item *item;

	item = malloc(sizeof( music_item));
    if (item == NULL){
        printf("No more memory for entries");
        return NULL;
    }
    item->next = NULL;
	return item;
}
