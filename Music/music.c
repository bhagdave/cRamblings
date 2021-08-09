#include <string.h>
#include <stdio.h>
#include "menu.h"
#include "item.h"

music_item *music_db = NULL;

void addItem()
{
	music_item *new_item;;
	char media;

	new_item = create_music_item(); 
    if (new_item == NULL)
        return;

	printf("Adding Music\n");
	printf("------------\n");

	printf("Artist:");
	fgets(new_item->artist, ARTIST_MAX_LENGTH, stdin);
    // get rid of \n in response
    new_item->artist[strcspn(new_item->artist, "\n")] = 0;

	printf("\nAlbum:");
	fgets(new_item->album, ALBUM_MAX_LENGTH, stdin);
    // get rid of \n in response
    new_item->album[strcspn(new_item->album, "\n")] = 0;

	printf("\nCD(c), Tape(t) or Vinyl(v)");
	media = getchar();
    while (getchar() != '\n')
        ;
	switch (media) {
		case 'c':
			new_item->media = CD;
			break;
		case 't':
			new_item->media = TAPE;
			break;
		case 'v':
			new_item->media = VINYL;
			break;
	}

    if (music_db == NULL)
        music_db = new_item;
    else {
        new_item->next = music_db;
        music_db = new_item;
    }

}

void printItems()
{
    music_item *item;
    char * media;
    // print table header
    printf("%-25.25s%25.25s%10.10s\n", "Artist", "Album", "Media");
    for (item = music_db; item != NULL; item = item->next){
        switch (item->media) {
            case CD:
                media = "CD";
                break;
            case TAPE:
                media = "Cassette";
                break;
            case VINYL:
                media = "Vinyl";
                break;
            default:
                media = "";
        }
        printf("%-25.25s%25.25s%10.10s", item->artist, item->album, media);
    }
}

void findItem(){
    char searchFor;
    char searchTerm[ALBUM_MAX_LENGTH];

    printf("\nA:Artist or B:Album?");
    searchFor = getchar();
    while (getchar() != '\n')
        ;
    if (searchFor == 'A'){
        printf("Album:");
    } else {
        printf("Artist::");
    }
    scanf(" %s", searchTerm);
    while (getchar() != '\n')
        ;
    printf("Searching for %s\n", searchTerm);
}

int main(int argc, char** argv)
{

	char input = ' ';

	struct menu_option *root_menu;

	root_menu = add_menu_option(NULL, 'A', "Add Music",addItem);
	root_menu = add_menu_option(root_menu, 'F', "Find Music",findItem);
	root_menu = add_menu_option(root_menu, 'P', "Print Items",printItems);
	root_menu = add_menu_option(root_menu, 'q', "Quit",NULL);

    while (input != 'q'){
        show_menu(root_menu);
        input=get_menu_option();
        do_menu_choice(input, root_menu);
    }
	freeMenu(root_menu);
	return 0;
}
