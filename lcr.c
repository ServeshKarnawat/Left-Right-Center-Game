#include "cse13s_random.h"
#include "names.h"

#include <stdio.h>

typedef enum { DOT, LEFT, CENTER, RIGHT } Position;

const Position die[6] = {
    DOT,
    DOT,
    DOT,
    LEFT,
    CENTER,
    RIGHT,
};

int main() {
    int num_players = 3;
    printf("Number of players (3 to 11)? ");
    int scanf_result = scanf("%d", &num_players);

    if (scanf_result < 1 || num_players < 3 || num_players > MAX_PLAYERS) {

        fprintf(stderr, "Invalid number of players. Using 3 instead.\n");
        num_players = 3;
    }

    unsigned seed = 4823;
    printf("Random-number seed? ");
    scanf_result = scanf("%u", &seed);

    if (scanf_result < 1) {
        fprintf(stderr, "Invalid seed. Using 4823 instead.\n");
    }

    int dots[num_players];
    int i;
    for (i = 0; i < num_players; i++) {
        dots[i] = 3;
    }

    int dice1 = 0;
    int dice2 = 0;
    int dice3 = 0;

    int currentP = 0;
    //Game loop
    int loop = 1;

    int random = 0;
    int players_in = 0;
    cse13s_random_seed(seed);
    while (loop == 1) {
        if (dots[currentP] > 0) {

            printf("%s:", player_name[currentP]);

            dice1 = 0;
            dice2 = 0;
            dice3 = 0;

            if (dots[currentP] > 0) {
                random = cse13s_random();
                random = random % 6;
                dice1 = random;
            }

            if (dots[currentP] > 1) {
                random = cse13s_random() % 6;
                dice2 = random;
            }

            if (dots[currentP] > 2) {
                random = cse13s_random() % 6;
                dice3 = random;
            }

            //3 is pass left

            if (dice1 == 3) {
                dots[currentP] = dots[currentP] - 1;
                if (currentP == num_players - 1) {
                    dots[0] = dots[0] + 1;

                } else {
                    dots[currentP + 1] = dots[currentP + 1] + 1;
                }
            }

            if (dice2 == 3) {
                dots[currentP] = dots[currentP] - 1;
                if (currentP == num_players - 1) {
                    dots[0] = dots[0] + 1;
                } else {
                    dots[currentP + 1] = dots[currentP + 1] + 1;
                }
            }

            if (dice3 == 3) {
                dots[currentP] = dots[currentP] - 1;
                if (currentP == num_players - 1) {
                    dots[0] = dots[0] + 1;
                } else {
                    dots[currentP + 1] = dots[currentP + 1] + 1;
                }
            }

            //4 is center, put one in the middle

            if (dice1 == 4) {
                dots[currentP] = dots[currentP] - 1;
            }

            if (dice2 == 4) {
                dots[currentP] = dots[currentP] - 1;
            }
            if (dice3 == 4) {
                dots[currentP] = dots[currentP] - 1;
            }

            //5 is pass right
            if (dice1 == 5) {
                dots[currentP] = dots[currentP] - 1;
                if (currentP == 0) {
                    dots[num_players - 1] = dots[num_players - 1] + 1;

                } else {
                    dots[currentP - 1] = dots[currentP - 1] + 1;
                }
            }
            if (dice2 == 5) {
                dots[currentP] = dots[currentP] - 1;
                if (currentP == 0) {
                    dots[num_players - 1] = dots[num_players - 1] + 1;

                } else {
                    dots[currentP - 1] = dots[currentP - 1] + 1;
                }
            }
            if (dice3 == 5) {
                dots[currentP] = dots[currentP] - 1;
                if (currentP == 0) {
                    dots[num_players - 1] = dots[num_players - 1] + 1;

                } else {
                    dots[currentP - 1] = dots[currentP - 1] + 1;
                }
            }

            printf(" ends her turn with %d\n", dots[currentP]);
        }

        //move onto next player
        if (currentP >= num_players - 1) {
            currentP = 0;
        } else {
            currentP = currentP + 1;
        }

        //check if one person has all the chips
        players_in = 0;
        for (i = 0; i < num_players; i++) {
            if (dots[i] > 0) {
                players_in = players_in + 1;
            }
        }

        if (players_in > 1) {
            loop = 1;
        } else {
            loop = 2;
        }
    }

    for (i = 0; i < num_players; i++) {

        if (dots[i] != 0) {
            printf("%s won!\n", player_name[i]);
        }
    }
}
