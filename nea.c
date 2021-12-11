#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct player {

    int id;
    char name[256];
    int score;
    

} player;


int rollDice() {

    int roll;
    int max_num = 6;
    int min_num = 1;

    srand(time(NULL));

    roll = rand() % (max_num + 1 - min_num) + min_num;
    sleep(rand() % (3 + 1 - 1) + 1);
    return roll;

}

void game(player *player) {

    int i;
    int roll1, roll2, roll3;
    int temp;
    int score = 0;
    printf("%s turn\n", player->name);
    
    for(i=0; i < 5; i++) {
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


void checkScores(player *p1, player *p2) {

    int p1roll = 0, p2roll = 0;


    if(p1->score == p2->score) {

        printf("Tiebreaker\n");

        while(p1roll == p2roll) {
            p1roll = rollDice();
            printf("Player one rolled %d\n", p1roll);
            p2roll = rollDice();
            printf("Player two rolled %d\n", p2roll);
        }

        printf(p1roll > p2roll ? "Player 1 wins!\n" : "Player 2 wins!");
        exit(EXIT_SUCCESS);
    }

    printf(p1->score > p2->score ? "Player 1 wins!\n" : "Player 2 wins!");
    exit(EXIT_SUCCESS);
}



int main() {

    player player1;
    player player2;

    player *p1;
    player *p2;

    p1 = &player1;
    p2 = &player2;

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
    return 0;
}