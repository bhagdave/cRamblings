#include <stdlib.h>
#define SCORE
struct score{
	unsigned home;
	unsigned away;
};

typedef struct score score;
score create_random_score(int home, int away);
