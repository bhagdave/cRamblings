#include <stdio.h>
#include <time.h>
#define DEBUG
#ifdef DEBUG
#include <assert.h>
#endif
#include "team.h"
#include "league.h"
#include "season.h"
#include "menu.h"

int main(void){
	char* menu_elements[] = {"1.Run Season","2.Manage League","3.Manage Teams","4.Add Results","Q.Quit"};
	print_menu(menu_elements);
	get_menu_option();

	char input;
	int i;
	char *premier[] ={"Man City" , "Man Utd" , "Chelsea" , "Liverpool" , "Spurs" , "Arsenal" , "Burnley" , "Leicester" , "Everton" , "Watford" , "Huddersfield" , "Brighton" , "Newcastle" , "Crystal Palace" , "West Ham" , "Bournemouth" , "Southampton" , "Stoke" , "WBA" , "Swansea"};
	char *championship[] = {"Wolves" , "Derby" , "Cardiff" , "Bristol City" , "Villa" , "Leeds" , "Sheef Utd" , "Middlesborough" , "Preston NE" , "Fulham" , "Brentford" , "Ipswich" , "Norwich" , "Notts Forest" , "Millwall" , "Sheef Wed" , "Qpr" , "Reading" , "Barnsley" , "Bolton" , "Hull" , "Burton" , "Blues" , "Sunderland"};
	char *leagueone[] = {"Wigan" , "Shrewsbury" , "Blackburn" , "Scunthorpe" , "Bradford" , "Portsmouth" , "Rotherham" , "Pterborough" , "Charlton" , "Oxford" , "Doncaster" , "Fleetwood" , "Blackpool" , "Bristol Rovers" , "Gillingham" , "Plymouth Argyle" , "Southend" , "Walsall" , "MK Dons" , "Oldham" , "Wimbledon" , "Northampton" , "Rochdale" , "Bury",};
	char *leaguetwo[] = {"Luton" , "Notts Co" , "Coventry" , "Wycombe" , "Lincoln" , "Mansfield" , "Exeter" , "Colchester" , "Swindon" , "Accrington" , "Newport" , "Cambridge" , "Carlisle" , "Grimsby","Stevange" , "Crawley" , "Cheltenham" , "Port Vale" , "Crewe" , "Yeovil" , "Morecambe" , "Chesterfield" , "Barnet" , "Forest Green"};
	team* temp;
	league prem;
	league champ;
	league league1;
	league league2;
	srand(time(NULL));
	prem = create_league("Premiership", 20);
	prem.relegated = 3;
    prem.promoted_to = NULL;
	for (i = 0; i < 20; i++){
		temp = create_team(premier[i]);
		if (i < 6){
			temp->weighting = 16;
			temp->home_random = 35;
			temp->away_random = 28;
		} else {
			temp->weighting = 8;
			temp->home_random = 32;
		}
		add_to_league(&prem,temp);
	}
	champ = create_league("Championship", 24);
	champ.promoted = 3;
	champ.promoted_to = &prem;
	champ.relegated = 4;
	for (i = 0; i < 24; i++){
		temp = create_team(championship[i]);
		if (i < 7){
			temp->weighting = 8;
		} else {
			temp->weighting = 6;
		}
		add_to_league(&champ,temp);
	}
	league1 = create_league("League One", 24);
	league1.promoted = 4;
	league1.promoted_to = &champ;
	league1.relegated = 4;
	for (i = 0; i < 24; i++){
		temp = create_team(leagueone[i]);
		if (i < 7){
			temp->weighting = 6;
		} else {
			temp->weighting = 4;
		}
		add_to_league(&league1,temp);
	}
	league2 = create_league("League Two", 24);
	league2.promoted = 4;
	league2.promoted_to = &league1;
	league2.relegated = 0;
	for (i = 0; i < 24; i++){
		temp = create_team(leaguetwo[i]);
		if (i < 7){
			temp->weighting = 4;
		} else {
			temp->weighting = 2;
		}
		add_to_league(&league2,temp);
	}
	while(1){
		doseason(&prem);
		scanf("%c",&input);
		doseason(&champ);
		scanf("%c",&input);
		doseason(&league1);
		scanf("%c",&input);
		doseason(&league2);
		scanf("%c",&input);
		// add weighting 
		for (i = 0; i < 20; i++){
			if (i < 5){
				prem.team_array[i]->weighting += 2;
				champ.team_array[i]->weighting += 2;
				league1.team_array[i]->weighting += 2;
				league2.team_array[i]->weighting += 2;
			} else if (i < 12){
				prem.team_array[i]->weighting += 1;
				champ.team_array[i]->weighting += 1;
				league1.team_array[i]->weighting += 1;
				league2.team_array[i]->weighting += 1;
			} else if (i < 18){
				prem.team_array[i]->weighting -= 1;
				champ.team_array[i]->weighting -= 1;
				league1.team_array[i]->weighting -= 1;
				league2.team_array[i]->weighting -= 1;
			} else {
				prem.team_array[i]->weighting -= 2;
				champ.team_array[i]->weighting -= 2;
				league1.team_array[i]->weighting -= 2;
				league2.team_array[i]->weighting -= 2;
			}
		}
		cleanup_teams(&prem);
		cleanup_teams(&champ);
		cleanup_teams(&league1);
		cleanup_teams(&league2);
	}
	free_league(&prem);
	return 0;
}

