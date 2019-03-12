/* -----------------------------------------------------------------------
 * Unit Test For:
 *	int fullDeckCount(int player, int card, struct gameState *state)
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
	
	res = fullDeckCount(0, copper, &G);

	assert(res == 7); // Players starts with 7 copper in a deck

	gainCard(copper, &G, 0, 0); // Add copper to discard
	gainCard(copper, &G, 1, 0); // Add copper to deck
	gainCard(copper, &G, 2, 0); // Add copper to hand

	res = fullDeckCount(0, copper, &G);

	assert(res == 10); // There should be 10 copper in player 0's deck

	printf("TEST FOR fullDeckCount() PASSED!\n");

	return 0;
}