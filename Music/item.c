#include "item.h"

 music_item *create_music_item(){
	music_item *item;

	item = malloc(sizeof( music_item));
    if (item == NULL){
        printf("No more memory for entries");
        return NULL;
    }
	item->artist = malloc(sizeof(char) * ARTIST_MAX_LENGTH);
    if (item->artist == NULL){
        printf("No more memory for entries");
        free(item);
        return NULL;
    }
	item->album = malloc(sizeof(char) * ALBUM_MAX_LENGTH);
    if (item->album == NULL){
        printf("No more memory for entries");
        free(item);
        return NULL;
    }
    item->next = NULL;
	return item;
}
