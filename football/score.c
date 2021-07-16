#include "score.h"

score create_random_score(int home, int away){
	score new;
	new.home = (rand() % (short)(home/10));
	new.away = (rand() % (short)(away/10));
	return new;
}
