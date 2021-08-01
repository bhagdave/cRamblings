#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct menu_option{
	char key;
	char *desc;
	struct menu_option *next;
	void (* doMenu)();
};

void show_menu(struct menu_option *option);
char get_menu_option();
struct menu_option *menu_option_allocate(void); 
void do_menu_choice(char pick, struct menu_option *menu);
struct menu_option *add_menu_option(struct menu_option *option,char key, char desc[25], void (* menuFunction)());
void freeMenu(struct menu_option* head);
