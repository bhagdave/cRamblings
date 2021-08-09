#include "menu.h"

void show_menu(struct menu_option *option)
{
	if (option != NULL){
		printf("%c:%s\n",option->key, option->desc);
		show_menu(option->next);
	}
}

struct menu_option *add_menu_option(struct menu_option *option,char key, char *desc, void (* menuFunction)())
{
	if (option == NULL){
		option = menu_option_allocate();
		option->key = key;
		option->desc = strdup(desc);
		option->doMenu = menuFunction;
		option->next = NULL;
	} else {
		option->next = add_menu_option(option->next,key, desc, menuFunction);
	}

	return option;
}

struct menu_option *menu_option_allocate(void)
{
	return (struct menu_option *) malloc(sizeof(struct menu_option));
}

char get_menu_option(){
	char choice;
	printf("\nPlease select a menu option:");
	choice = getchar();
	while (getchar() != '\n')
		;
	return choice;
}

void do_menu_choice(char pick, struct menu_option *menu)
{
	while (menu != NULL && pick != 'q'){
		if (pick == menu->key){
			menu->doMenu();
			break;
		} else {
			menu = menu->next;
		}
	}
}

void freeMenu(struct menu_option* head)
{
	struct menu_option* tmp;

	while ( head != NULL){
		tmp = head;
		head = head->next;
		free(tmp->desc);
		free(tmp);
	}
}

