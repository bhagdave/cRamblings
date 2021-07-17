#include<stdio.h>

struct testing {
    unsigned int flag_1 : 1;
    unsigned int flag_2 : 1;
    unsigned int flag_3 : 1;
    unsigned int flag_4 : 1;
    unsigned int flag_5 : 1;
    unsigned int flag_6 : 1;
    unsigned int flag_7 : 1;
    unsigned int flag_8 : 1;
    unsigned int flag_9 : 1;
    unsigned int flag_10 : 1;
    unsigned int flag_0 : 1;
    unsigned int flag_11 : 1;
    unsigned int flag_12 : 1;
    unsigned int flag_13 : 1;
    unsigned int flag_14 : 1;
    unsigned int flag_15 : 1;
    unsigned int flag_16 : 1;
    unsigned int flag_17 : 1;
    unsigned int flag_18 : 1;
    unsigned int flag_19 : 1;
    unsigned int flag_20 : 1;
    unsigned int flag_21 : 1;
};


int main(void){

    struct testing y;
    int x;

    y.flag_1 = 1;
    y.flag_20 = 1;
    y.flag_3 = 0;
    y.flag_10 = 0;

    if (y.flag_1)
        y.flag_16 = 1;
    if (y.flag_20)
        y.flag_21 = 1;

    if (y.flag_21)
        x = y.flag_1 + y.flag_20 + y.flag_16 + y.flag_21;

    printf("testing structure has a size of %lu\n", sizeof(y));
    printf("X is %d\n", x);
	return 1;
}
