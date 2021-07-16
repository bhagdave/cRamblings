#include "season.h"
#ifndef LEAGUE
#include "league.h"
#endif

void doseason(league *leag){
	int i,j;
	for (i = 0; i < leag->cursor; i++){
		for (j =0; j < leag->cursor; j++){
			if (j == i){
				continue;
			} else {
				addresult(leag->team_array[i],leag->team_array[j],
					create_random_score(leag->team_array[i]->home_random + leag->team_array[i]->weighting,leag->team_array[j]->away_random + leag->team_array[j]->weighting));
			}
		}
	}
	sort_league(leag);
	printf("%s Champions:%s\n",leag->name,leag->team_array[0]->name);
	do_promotions(leag);
}
