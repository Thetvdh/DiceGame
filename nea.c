#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define DRUM_ROLL 3
#define MAX_ROUNDS 5

typedef struct Player {
    int id;
    char name[256];
    int score;
} Player;

int rollDice() {

    int roll = 1;

    srand(time(NULL));

    roll = (rand() % 6) + 1;
    sleep((rand() % DRUM_ROLL) + 1);

    return roll;
}

void game(Player *player) {

    int i;
    int roll1, roll2, roll3;
    int temp;
    int score = 0;

    printf("%s turn\n", player->name);
    
    for(i=0; i < MAX_ROUNDS; i++) {
        if (score < 0)
            score = 0;

        roll1 = rollDice();
        printf("You rolled %d\n", roll1);
        roll2 = rollDice();
        printf("You rolled %d\n", roll2);
        roll3 = roll1 == roll2 ? rollDice() : 0;

        if(roll3 != 0)
            printf("You rolled a double, your third dice is %d\n", roll3);
        
        temp = roll1 + roll2 + roll3;
        score += temp;

        if(temp % 2 == 0) {
            printf("Your total is even! +10\n");
            score += 10;
        }

        else {
            printf("Your total is odd! -5\n");
            score -= 5;
        }
    }

    player->score = score;

    printf("%s score is %d\n", player->name, player->score);
}

void checkScores(Player *p1, Player *p2) {

    int p1Roll = 0, p2Roll = 0;
	char *winnerName = NULL;

	p1->score = 10;
	p2->score = 10;
    if(p1->score == p2->score) {

        printf("Tiebreaker\n");

        while(p1Roll == p2Roll) {
            p1Roll = rollDice();
            printf("Player one rolled %d\n", p1Roll);
            p2Roll = rollDice();
            printf("Player two rolled %d\n", p2Roll);
        }

		winnerName = p1Roll > p2Roll ? p1->name : p2->name;
		printf( "%s wins!\n", winnerName);

		return;
    }

	winnerName = p1->score > p2->score ? p1->name : p2->name;
    printf( "%s wins!\n", winnerName);
}

int main() {

    Player player1;
    Player player2;


    Player *p1 = &player1;
    Player *p2 = &player2;

    player1.id = 1;
    player2.id = 2;
    player1.score = 0;
    player2.score = 0;

    printf("Enter player 1 name: ");
    scanf("%s", player1.name);
    printf("Enter player 2 name: ");
    scanf("%s", player2.name);

    game(p1);
    game(p2);

    checkScores(p1, p2);

    return EXIT_SUCCESS;
}

