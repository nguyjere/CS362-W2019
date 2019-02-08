/* -----------------------------------------------------------------------
 * Unit Test For:
 *	Village
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

	// Add Village to player 0's hand
	gainCard(village, &G, 2, 0);

	// Player 0 plays Village
	res = cardEffect(village, choice1, choice2, choice3, &G, 5, NULL);
	assertEqual(res, 0, "cardEffect did not return 0", &testRes);

	// Count total cards in hand
	finalHandCount = G.handCount[G.whoseTurn];


	// Check player 0 gained 4 new cards, 1 buy, and other players gain 1 card in hand.
	assertEqual((finalHandCount - initialHandCount), 1, "Village did not yield 1 additional card in hand", &testRes);
	assertEqual(G.numActions, 3, "Village did not yield 2 additional actions", &testRes);
	assertNotEqual(G.hand[G.whoseTurn][5], village, "Village was not removed from player's hand", &testRes);
	assertEqual(G.playedCards[G.playedCardCount - 1], village, "Village was not moved to played card", &testRes);

	if (testRes == 0)
	{
		printf("TEST FOR 'Village' PASSED!\n");
	}
	else
	{
		printf("TEST FOR 'Village' FAILED!\n");
	}

	return 0;
}