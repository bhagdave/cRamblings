#include "menu.h"

void print_menu(char *elements[5]){
	system("clear");
	printf("Football Results Analysis and Predictions System - FRAPS v0.0.0\n");
	printf("_______________________________________________________________\n");
	for (int i=0; i<5; i++){
		printf("%s\n",elements[i]);
	}
	printf("_______________________________________________________________\n");
	printf("--------------------Copyright 2018 - Dave Gill-----------------\n");
}

char get_menu_option(){
	char choice;
	printf("\nPlease select a menu option:");
	scanf("%c",&choice);
	return choice;
}

void do_menu_choice(char pick){
	char blank;
	switch(pick){
		case '1':
			printf("Doing season\n");
			scanf("%c",&blank);
			break;
		case 'Q':
			break;
		default:
			printf("\nOption not understood.\n Please hit return\n");
			scanf("%c",&blank);
			break;
	}
}

//void main(void){
//	char* menu_elements[] = {"1.Run Season","2.Does nothing","Q.Quit"};
//	char choice = ' ';
//	while(choice != 'Q'){
//		print_menu(menu_elements);
//		choice = get_menu_option();
//		choice = toupper(choice);
//		do_menu_choice(choice);
//	}
//}
