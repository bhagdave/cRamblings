#include <stdio.h>
#define LEAGUE
#ifndef TEAM
#include "team.h"
#endif
#define SORTED 1
#define UNSORTED 0
struct league{
	int no_of_teams;
	int cursor;
	char *name;
	team  **team_array;
	short relegated;
	short promoted;
	struct league *promoted_to;
	struct league *relegated_to;
};
typedef struct league league;

league create_league(char *name, int teams);
void add_to_league(league *destination, team *toadd);
void print_league(league *toprint);
void sort_league(league *tosort);
void do_promotions(league *league);
void cleanup_teams(league *league);
void free_league(league *freeme);
