/*
Author: Aaron Rito
Date: 10/29/18
Client: CS362 assignment 3
Project: unit test for "getCost"
Sources: CS362 class
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

void my_assert(int result);
int main() {
    int i;
    int seed = 1000;
    int numPlayer = 2;
    int maxBonus = 10;
    int player, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }
    for (player = 0; player < numPlayer; player++)
    {
        for (handCount = 1; handCount <= maxHandCount; handCount++)
        {
            for (bonus = 0; bonus <= maxBonus; bonus++)
            {
                initializeGame(numPlayer, k, seed, &G); // initialize a new game
                G.handCount[player] = handCount;                 // set the number of cards on hand
                memcpy(G.hand[player], coppers, sizeof(int) * handCount); // set all the cards to copper
                updateCoins(player, &G, bonus);
                my_assert(G.coins == handCount * 1 + bonus); // check if the number of coins is correct
                memcpy(G.hand[player], silvers, sizeof(int) * handCount); // set all the cards to silver
                updateCoins(player, &G, bonus);
                my_assert(G.coins == handCount * 2 + bonus); // check if the number of coins is correct
                memcpy(G.hand[player], golds, sizeof(int) * handCount); // set all the cards to gold
                updateCoins(player, &G, bonus);
                my_assert(G.coins == handCount * 3 + bonus); // check if the number of coins is correct
            }
        }
    }

    return 0;
}
void my_assert(int result) {
    if (result) 
        printf("TEST PASSED!\n");
    else 
        printf("TEST FAILED!\n");
}