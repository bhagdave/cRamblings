#include <stdio.h>
#ifndef SCORE
#include "score.h"
#endif
#define TEAM
#define HOME_RANDOM 30
#define AWAY_RANDOM 25
#define PTSFORWIN 3
#define PTSFORDRAW 1
#define PTSFOR3GOALS 0
#define WIN 3
#define DRAW 2
#define LOSS 1
typedef enum{true,false} boolean;
struct team_stats{
	short played;
	short won;
	short drawn;
	short lost;
	short goals_for;
	short goals_against;
	short winning_streak;
	short losing_streak;
	unsigned short form;
};
typedef struct team_stats team_stats;
struct team {
	char * name;
	team_stats home;
	team_stats away;
	short home_random;
	short away_random;
	short gd;
	short points;
	short bonus_points;
	int weighting;
};
typedef struct team team;

void record_home_win(team *team, score result);
void record_home_loss(team *home, score result);
void record_away_win(team *away, score result);
void record_away_loss(team *team, score result);
void record_home_draw(team *home, score result);
void record_away_draw(team *away, score result);
void calculate_points(team *calc);
void calculate_gd(team *calc);
void addresult(team *home, team *away, score result);
void print_headers(void);
void print_team(team *print);
void zero_team(team *team);
team* create_team(char *name);
score predict_score(team *home, team *away);
