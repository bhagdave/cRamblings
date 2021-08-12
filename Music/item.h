#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ARTIST_MAX_LENGTH 75
#define ALBUM_MAX_LENGTH 120

typedef enum {CD = 10, TAPE, VINYL} MEDIA;
typedef struct music_item music_item;

struct music_item{
	char artist[ARTIST_MAX_LENGTH];
	char album[ALBUM_MAX_LENGTH];
	MEDIA media;
    music_item *next;
};

music_item *create_music_item();
