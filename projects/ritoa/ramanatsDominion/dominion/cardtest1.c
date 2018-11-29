/*
Author: Aaron Rito
Date: 10/29/18
Client: CS362 assignment 3
Project: unit test for "smithy"
Source: CS362 class
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#define TESTCARD "Smithy"
void my_assert(int result);
int main(int argc, char** argv) {
    int seed = 1000;
    int numPlayers = 2;
    int player,i, j;
    struct gameState G;
    int temp_k[10];
    int k[10] = {adventurer, salvager, village, minion, steward, cutpurse,
                    sea_hag, tribute, smithy, council_room};
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    initializeGame(numPlayers, k, seed, &G);
    for(player = 0; player < numPlayers; player++)
    {
        // get opp players hand
        G.whoseTurn = player;            
        G.handCount[G.whoseTurn] = 5;
        int opp_player_cards;
        if (player == 0)
        {
            G.whoseTurn = player +1;            
            G.handCount[G.whoseTurn] = 5;
            opp_player_cards = numHandCards(&G);
            G.whoseTurn = player;
        }
        else
        {
            G.whoseTurn = player -1;            
            G.handCount[G.whoseTurn] = 5;
            opp_player_cards = numHandCards(&G);
            G.whoseTurn = player;
        }           
        // get kingdom supply
        for(i = 0; i < 10; i++)    
            temp_k[i] = supplyCount(k[i], &G);
        // get victory supply
        int estates = supplyCount(estate, &G);
        int duchys = supplyCount(duchy, &G);
        int provinces = supplyCount(province, &G);
        // run the card  
        int num_of_cards = numHandCards(&G);
        rSmithy(&G, 0);
        // ensure number of cards is correct
        my_assert(numHandCards(&G) == num_of_cards + 2); 
        // ensure kingdom and victory piles the same
        for(j = 0; j < 10; j++)    
            my_assert(temp_k[j] == supplyCount(k[j], &G));
        my_assert(estates == supplyCount(estate, &G));
        my_assert(duchys == supplyCount(duchy, &G));
        my_assert(provinces == supplyCount(province, &G)); 
        // check player state
        if (player == 0)
        {
            G.whoseTurn = player +1;            
            G.handCount[G.whoseTurn] = 5;
            opp_player_cards = numHandCards(&G);
        }
        else
        {
            G.whoseTurn = player -1;            
            G.handCount[G.whoseTurn] = 5;
            my_assert(opp_player_cards = numHandCards(&G));
        }
    }
}
void my_assert(int result) {
    if (result) 
        printf("TEST PASSED!\n");
    else 
        printf("TEST FAILED!\n");
}
