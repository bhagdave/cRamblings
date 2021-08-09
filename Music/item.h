#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ARTIST_MAX_LENGTH 75
#define ALBUM_MAX_LENGTH 120

typedef enum {CD, TAPE, VINYL} MEDIA;
typedef struct music_item music_item;

struct music_item{
	char *artist;
	char *album;
	MEDIA media;
    music_item *next;
};

music_item *create_music_item();
