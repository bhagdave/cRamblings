#include "league.h"

league create_league(char *name, int teams){
	league new;
	new.name = name;
	new.no_of_teams = teams;
	new.cursor = 0;
	new.team_array = calloc(teams,sizeof(team *));
	new.relegated = 4;
	new.promoted = 4;
	return new;
}

void add_to_league(league *destination, team *toadd){
	destination->team_array[destination->cursor] = toadd;
	destination->cursor++;
}

void print_league(league *toprint){
	register int i;
	printf("-----------%s----------\n", toprint->name);
	print_headers();
	for (i = 0 ; i < toprint->no_of_teams; i++){
		print_team(toprint->team_array[i]);
	}
}

void sort_league(league *tosort){
	team *tmp;
	register int i;
	int completed = SORTED;
	do{
		completed = SORTED;
		for (i = 0; i < (tosort->no_of_teams - 1); i++){
			if (tosort->team_array[i]->points < tosort->team_array[i + 1]->points){
				tmp = tosort->team_array[i];
				tosort->team_array[i] = tosort->team_array[i + 1];
				tosort->team_array[i + 1] = tmp;
				completed = UNSORTED;
			} else 	if (tosort->team_array[i]->points == tosort->team_array[i + 1]->points){
				if (tosort->team_array[i]->gd < tosort->team_array[i + 1]->gd){
					tmp = tosort->team_array[i];
					tosort->team_array[i] = tosort->team_array[i + 1];
					tosort->team_array[i + 1] = tmp;
					completed = UNSORTED;
				}
			}
		}
	} while(completed == UNSORTED);
	print_league(tosort);
}

void do_promotions(league *league){
	register int promoted, relegated, i,j;
	team *tmp = NULL;
	if(league->promoted_to != NULL){
		// get the correct number of teams
		promoted  = league->promoted;
        relegated = 0;
        relegated = league->promoted_to->relegated;
		// make sure they match with relegations
		if (promoted != relegated){
			printf("ERROR:Relegations and promotions do not match ");
			return;
		}
		// get starting position for relegations
		j = league->promoted_to->no_of_teams - promoted;
		for (i = 0; i < (promoted - 1); i++, j++){
			tmp = league->team_array[i];
			league->team_array[i] = league->promoted_to->team_array[j];
			league->promoted_to->team_array[j] = tmp;
		}
	}
}

void cleanup_teams(league *league){
	register int i;
	for(i = 0 ; i < league->no_of_teams; i++){
		zero_team(league->team_array[i]);
	}
}

void free_league(league *freeme){
	register int i;
	for(i = 0 ; i < freeme->no_of_teams; i++){
		free(freeme->team_array[i]);
	}
}

