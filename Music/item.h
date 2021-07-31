#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ARTIST_MAX_LENGTH 75
#define ALBUM_MAX_LENGTH 120

struct music_item *create_music_item();
typedef enum {CD, TAPE, VINYL} MEDIA;

struct music_item{
	char *artist;
	char *album;
	MEDIA media;
    struct music_item *next;
};
