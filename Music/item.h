#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ARTIST_MAX_LENGTH 75
#define ALBUM_MAX_LENGTH 120

typedef enum {CD, TAPE, VINYL} MEDIA;

typedef struct{
	char *artist;
	char *album;
	MEDIA media;
    struct music_item *next;
} music_item;

music_item *create_music_item();
