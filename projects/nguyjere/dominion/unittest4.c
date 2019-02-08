/* -----------------------------------------------------------------------
 * Unit Test For:
 *	endTurn(struct gameState *state)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


int main() {
	int res;
	int seed = 1000;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
				remodel, smithy, village, baron, great_hall };
	struct gameState G;

	initializeGame(2, k, seed, &G);

	res = endTurn(&G); // Ends player 0's turn
	assert(res == 0);
	assert(G.whoseTurn == 1);
	assert(G.handCount[0] == 0);
	assert(G.handCount[1] == 5);
	
	res = endTurn(&G); // Ends player 1's turn
	assert(res == 0);
	assert(G.whoseTurn == 0);
	assert(G.handCount[0] == 5);
	assert(G.handCount[1] == 0);

	res = endTurn(&G); // Ends player 0's turn
	assert(res == 0);
	assert(G.whoseTurn == 1);
	assert(G.handCount[0] == 0);
	assert(G.handCount[1] == 5);

	printf("TEST FOR endTurn() PASSED!\n");

	return 0;
}