/* -----------------------------------------------------------------------
 * Unit Test For: 
 *	int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main() {
	int i;
	int res;
	int seed = 1000;
	int numPlayer = 2;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
				remodel, smithy, village, baron, great_hall };
	struct gameState G;

	//printf("TESTING gainCard():\n");

	initializeGame(numPlayer, k, seed, &G);

	for (i = 0; i <= 2; i++) // Add card to discard pile, deck, and hand for player 0
	{
		res = gainCard(adventurer, &G, i, 0);
		assert(res == 0);
	}

	// Adventurer pile starts with 10 card then ends with 7
	assert(G.supplyCount[adventurer] == 7);
	
	// There should be 6 cards in player 0's hand and deck, and 1 in discard.
	assert(G.handCount[0] == 6);
	assert(G.deckCount[0] == 6);
	assert(G.discardCount[0] == 1);
	assert(G.hand[0][G.handCount[0]-1] == adventurer); //The last card in the hand should be adventurer
	assert(G.deck[0][G.deckCount[0]-1] == adventurer); //Top card of the deck should be adventurer
	assert(G.discard[0][G.discardCount[0]-1] == adventurer); //Their discard pile should only have adventurer

	printf("TEST FOR gainCard() PASSED!\n");

	return 0;
}