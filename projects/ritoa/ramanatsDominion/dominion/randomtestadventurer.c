/*
Author: Aaron Rito
Date: 10/29/18
Client: CS362 assignment 3
Project: unit test for "adventurer"
Source: CS362 class
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#define TESTCARD "Adventurer"
void my_assert(int result);
int test_passed = 0;
int test_failed = 0;
int main(int argc, char** argv) {
    int seed = MAX_HAND-5;
    SelectStream(1);
    PutSeed(seed);
    int numPlayers = 2;
    int player,h, i, j;
    struct gameState G;
    int temp_k[10];
    int k[10] = {adventurer, salvager, village, minion, steward, cutpurse,
                    sea_hag, tribute, smithy, council_room};
    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    initializeGame(numPlayers, k, seed, &G);
    int num_of_tests = 10000;
    for(h = 0; h < num_of_tests; h++)
    {
        for(player = 0; player < numPlayers; player++)
        {
            /* BOUNDRY GET*/
            // get opp players hand
            int random_hand = Random();
            G.whoseTurn = player;            
            G.handCount[G.whoseTurn] = random_hand;
            int opp_player_cards;
            if (player == 0)
            {
                G.whoseTurn = player +1;            
                G.handCount[G.whoseTurn] = random_hand;
                opp_player_cards = numHandCards(&G);
                G.whoseTurn = player;
            }
            else
            {
                G.whoseTurn = player -1;            
                G.handCount[G.whoseTurn] = random_hand;
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
            /* END BOUNDRY GET*/
            /* START RUN CARD*/ 
            int num_of_cards = numHandCards(&G);
            int money = G.coins;
            rAdventurer(&G);
            my_assert((numHandCards(&G) == num_of_cards + 1 )&& (G.coins <= money));
            /* END RUN CARD CHECK*/
            /* BOUNDRY CHECKS*/
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
                G.handCount[G.whoseTurn] = random_hand;
                opp_player_cards = numHandCards(&G);
            }
            else
            {
                G.whoseTurn = player -1;            
                G.handCount[G.whoseTurn] = random_hand;
                my_assert(opp_player_cards = numHandCards(&G));
            }
        }
    }
    printf("%d tests passed.\n", test_passed);
    printf("%d tests failed.\n", test_failed);
}
void my_assert(int result) {
    if (result) 
        test_passed++;
    else
        test_failed++;         
}
