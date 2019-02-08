/* -----------------------------------------------------------------------
 * Unit Test For:
 *	Smithy
 *	int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void assertEqual(int x, int y, char* message, int* testResult)
{
	if (x != y)
	{
		printf("Assertion Failed: %s\n", message);
		*testResult = -1;
	}
}

void assertNotEqual(int x, int y, char* message, int* testResult)
{
	if (x == y)
	{
		printf("Assertion Failed: %s\n", message);
		*testResult = -1;
	}
}


int main() {
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int initialHandCount, finalHandCount;
	int res;
	int testRes = 0;
	int seed = 1000;
	int numPlayer = 2;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
				remodel, smithy, village, baron, great_hall };
	struct gameState G;

	initializeGame(numPlayer, k, seed, &G);
	initialHandCount = G.handCount[G.whoseTurn];

	// Add smithy to player 0's hand
	gainCard(smithy, &G, 2, 0);

	// Player 0 plays smithy
	res = cardEffect(smithy, choice1, choice2, choice3, &G, G.handCount[0]-1, NULL);
	assertEqual(res, 0, "cardEffect did not return 0", &testRes);
	finalHandCount = G.handCount[G.whoseTurn];

	// Check player 0 gained 3 new cards to the hand, and discarded Smithy
	assertEqual((finalHandCount - initialHandCount), 3, "Smithy did not yield 3 new cards to player's hand", &testRes);
	assertNotEqual(G.hand[G.whoseTurn][5], smithy, "Smithy was not removed from player's hand", &testRes);
	assertEqual(G.playedCards[G.playedCardCount - 1], smithy, "Smithy was not move to played card", &testRes);

	if (testRes == 0)
	{
		printf("TEST FOR 'Smithy' PASSED!\n");
	}
	else 
	{
		printf("TEST FOR 'Smithy' FAILED!\n");
	}
	
	return 0;
}