#include "team.h"

static void team_update(char flag,team *team, score result){
	if (flag='a'){
		team->away.goals_for += result.away;
		team->away.goals_against += result.home;
		if (team->away.winning_streak > 2){
			team->away.winning_streak = 0;
			team->home.winning_streak++;
			team->away_random++;
			team->home_random++;
		}
		if (result.away > 2){
			team->bonus_points += (short) PTSFOR3GOALS;
		}

	} else if(flag='h'){
		team->home.goals_for += result.home;
		team->home.goals_against += result.away;
		if (team->home.winning_streak > 2){
			team->home.winning_streak = 0;
			team->home_random++;
			team->away_random++;
		}
		if (result.home > 2){
			team->bonus_points += (short) PTSFOR3GOALS;
		}
	}
}

void record_home_win(team *home, score result){
	home->home.played++;
	home->home.won++;
	home->home.losing_streak = 0;
	home->home.winning_streak++;
	home->home.form = home->home.form << 2;
	home->home.form += WIN;
	team_update('h',home,result);
}

void record_home_loss(team *home, score result){
	home->home.played++;
	home->home.lost++;
	home->home.winning_streak = 0;
	home->home.losing_streak++;
	home->home.form = home->home.form << 2;
	home->home.form += LOSS;
	team_update('h',home,result);
}

void record_away_win(team *away, score result){
	away->away.played++;
	away->away.winning_streak++;
	away->away.losing_streak = 0;
	away->away.won++;
	away->away.form = away->away.form << 2;
	away->away.form += WIN;
	team_update('a',away,result);
}

void record_away_loss(team *away, score result){
	away->away.played++;
	away->away.lost++;
	away->away.losing_streak++;
	away->away.winning_streak = 0;
	away->away.form = away->away.form << 2;
	away->away.form += LOSS;
	team_update('a',away,result);
}

void record_home_draw(team *home, score result){
	home->home.played++;
	home->home.drawn++;
	home->home.winning_streak = 0;
	home->home.losing_streak = 0;
	home->home.form = home->home.form << 2;
	home->home.form += DRAW;
	team_update('h',home,result);
}
void record_away_draw(team *away, score result){
	away->away.played++;
	away->away.drawn++;
	away->away.winning_streak = 0;
	away->away.losing_streak = 0;
	away->away.form = away->away.form << 2;
	away->away.form += DRAW;
	team_update('a',away,result);
}

void calculate_points(team *calc){
	calc->points = calc->bonus_points + (calc->home.drawn * PTSFORDRAW) + (calc->away.drawn * PTSFORDRAW) + (calc->home.won * PTSFORWIN) + (calc->away.won * PTSFORWIN);
}

void calculate_gd(team *calc){
	calc->gd = calc->home.goals_for - calc->home.goals_against + calc->away.goals_for - calc->away.goals_against;
}


void addresult(team *home, team *away, score result){
#ifdef DEBUG
//	printf("%s %hd - %hd %s\n",home->name, result.home, result.away, away->name);
#endif
	if (result.home > result.away){
		record_home_win(home, result);
		record_away_loss(away, result);
	}
	if (result.home < result.away){
		record_home_loss(home, result);
		record_away_win(away, result);
	}
	if (result.home == result.away){
		record_home_draw(home, result);
		record_away_draw(away, result);
	}
	calculate_points(home);
	calculate_gd(home);
	calculate_points(away);
	calculate_gd(away);
}


void print_headers(void){
	printf("%-25s %3s %3s %3s %3s %3s %3s %3s %3s %3s %3s\n",
		"Team", "PL","W","D","L","PL","W","D","L","PTS","wgt"	);
}


void print_team(team *print){
	printf("%-25s %3d %3d %3d %3d %3d %3d %3d %3d %3d %3d\n",
		print->name,
		print->home.played,
		print->home.won,
		print->home.drawn,
		print->home.lost,
		print->away.played,
		print->away.won,
		print->away.drawn,
		print->away.lost,
		print->points,
		print->weighting
	);
}
void zero_team(team *team){
	team->gd = 0;
	team->points = 0;
	team->home.played = 0;
	team->home.won = 0;
	team->home.drawn = 0;
	team->home.lost = 0;
	team->home.goals_for = 0;
	team->home.goals_against = 0;
	team->home.form =0;
	team->away.played = 0;
	team->away.won = 0;
	team->away.drawn = 0;
	team->away.lost = 0;
	team->away.goals_for = 0;
	team->away.goals_against = 0;
	team->away.form = 0;
	team->bonus_points = 0;
	if (team->home_random > (HOME_RANDOM * 2)){
		team->home_random -= 10;
	} else {
		team->home_random = HOME_RANDOM;
	}
	if (team->away_random > (AWAY_RANDOM * 2)){
		team->away_random -= 10;
	} else {
		team->away_random = AWAY_RANDOM;
	}

	// correct for any negative weihtin
	if (team->weighting < 0){
		team->weighting = 10;
	}
	if (team->weighting > 100){
		team->weighting -= 21;
	}
}

team* create_team(char *name){
	team* new;
	new = malloc(sizeof(team));
	new->name = name;
	new->home_random = HOME_RANDOM;
	new->away_random = AWAY_RANDOM;
	zero_team(new);
	return new;
}

score predict_score(team *home, team *away){
	score result;
	result.home = 0;
	result.away = 0;
	return result;
}
