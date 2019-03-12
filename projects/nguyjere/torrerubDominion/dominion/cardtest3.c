/* -----------------------------------------------------------------------
 * Unit Test For:
 *	Council Room
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
	int initialHandCount0, finalHandCount0;
	int initialHandCount1, finalHandCount1;
	int res;
	int testRes = 0;
	int seed = 1000;
	int numPlayer = 2;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
				remodel, smithy, village, baron, great_hall };
	struct gameState G;

	initializeGame(numPlayer, k, seed, &G);
	initialHandCount0 = G.handCount[G.whoseTurn];
	initialHandCount1 = G.handCount[G.whoseTurn + 1];

	// Add Council Room to player 0's hand
	gainCard(council_room, &G, 2, 0);

	// Player 0 plays Council Room
	res = cardEffect(council_room, choice1, choice2, choice3, &G, 5, NULL);
	assertEqual(res, 0, "cardEffect did not return 0", &testRes);

	// Count total cards in hand
	finalHandCount0 = G.handCount[G.whoseTurn];
	finalHandCount1 = G.handCount[G.whoseTurn + 1];

	// Check player 0 gained 4 new cards, 1 buy, and other players gain 1 card in hand.
	assertEqual((finalHandCount0 - initialHandCount0), 4, "Council Room did not yield 4 additional cards in hand", &testRes);
	assertEqual((finalHandCount1 - initialHandCount1), 1, "Council Room did not yield 1 additional card in hand for other player", &testRes);
	assertEqual(G.numBuys, 2, "Council Room did not yield 1 additional buy", &testRes);
	assertNotEqual(G.hand[G.whoseTurn][5], council_room, "Council Room was not removed from player's hand", &testRes);
	assertEqual(G.playedCards[G.playedCardCount - 1], council_room, "Council Room was not moved to played card", &testRes);

	if (testRes == 0)
	{
		printf("TEST FOR 'Council Room' PASSED!\n");
	}
	else
	{
		printf("TEST FOR 'Council Room' FAILED!\n");
	}

	return 0;
}