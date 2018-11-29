/*
Author: Aaron Rito
Date: 10/29/18
Client: CS362 assignment 3
Project: unit test for "getCost"
Sources: CS362 class, https://github.com/caperren/Archives
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#define TESTCARD "getCost"
void my_assert(int result);
int main(int argc, char** argv) {
    int seed = 1000;
    int numPlayers = 2;
    int player,i, j;
    struct gameState G;
    int temp_k[10];
    int k[10] = {adventurer, salvager, village, minion, steward, cutpurse,
                    sea_hag, tribute, smithy, council_room};
    printf("----------------- Testing Unit: %s ----------------\n", TESTCARD);
    initializeGame(numPlayers, k, seed, &G);
    for(player = 0; player < numPlayers; player++)
    {
        /* BOUNDRY GET*/
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
        /* END BOUNDRY GET*/
        /* START RUN CARD*/ 
        int cardCost;
        for (int i = 0; i < 27; i++)
        {
            cardCost = getCost(i);           
            switch( i ) 
            {
                case curse:
                  my_assert(cardCost == 0);
                  break;
                case estate:
                  my_assert(cardCost == 2);
                  break;
                case duchy:
                  my_assert(cardCost == 5);
                  break;
                case province:
                  my_assert(cardCost == 8);
                  break;
                case copper:
                  my_assert(cardCost == 0);
                  break;
                case silver:
                  my_assert(cardCost == 3);
                  break;
                case gold:
                  my_assert(cardCost == 6);
                  break;
                case adventurer:   
                  my_assert(cardCost == 6);
                  break;
                case council_room:
                  my_assert(cardCost == 5);
                  break;
                case feast:
                  my_assert(cardCost == 4);
                  break;
                case gardens:
                  my_assert(cardCost == 4);
                  break;
                case mine:
                  my_assert(cardCost == 5);
                  break;
                case remodel:
                  my_assert(cardCost == 4);
                  break;
                case smithy:
                  my_assert(cardCost == 4);
                  break;
                case village:
                  my_assert(cardCost == 3);
                  break;
                case baron:
                  my_assert(cardCost == 4);
                  break;
                case great_hall:
                  my_assert(cardCost == 3);
                  break;
                case minion:
                  my_assert(cardCost == 5);
                  break;
                case steward:
                  my_assert(cardCost == 3);
                  break;
                case tribute:
                  my_assert(cardCost == 5);
                  break;
                case ambassador:
                  my_assert(cardCost == 3);
                  break;
                case cutpurse:
                  my_assert(cardCost == 4);
                  break;
                case embargo: 
                  my_assert(cardCost == 2);
                  break;
                case outpost:
                  my_assert(cardCost == 5);
                  break;
                case salvager:
                  my_assert(cardCost == 4);
                  break;
                case sea_hag:
                  my_assert(cardCost == 4);
                  break;
                case treasure_map:
                  my_assert(cardCost == 4);
                  break;
                default: return -1;
            }
        }
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
void my_assert(int result){
    if (result) 
        printf("TEST PASSED!\n");
    else 
        printf("TEST FAILED!\n");
}