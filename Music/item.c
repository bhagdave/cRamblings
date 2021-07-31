#include "item.h"

struct music_item *create_music_item(){
	struct music_item *item;

	item = malloc(sizeof(struct music_item));
	item->artist = malloc(sizeof(char) * ARTIST_MAX_LENGTH);
	item->album = malloc(sizeof(char) * ALBUM_MAX_LENGTH);
	return item;
}
