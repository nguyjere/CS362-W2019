/* -----------------------------------------------------------------------
 * Unit Test For:
 *	Adventurer
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

int countTreasureInHand(int currentPlayer, struct gameState *state)
{
	int res = 0;
	for (int i = 0; i < state->handCount[currentPlayer]; i++)
	{
		if (state->hand[currentPlayer][i] == copper || state->hand[currentPlayer][i] == silver || state->hand[currentPlayer][i] == gold)
		{
			res++;
		}
	}
	return res;
}


int main() {
	int choice1 = 0, choice2 = 0, choice3 = 0;
	int initialHandCount, finalHandCount;
	int initialTreasureCount, finalTreasureCount;
	int res;
	int testRes = 0;
	int seed = 1000;
	int numPlayer = 2;
	int k[10] = { adventurer, council_room, feast, gardens, mine,
				remodel, smithy, village, baron, great_hall };
	struct gameState G;

	initializeGame(numPlayer, k, seed, &G);
	initialHandCount = G.handCount[G.whoseTurn];

	//Count treasure card in hand
	initialTreasureCount = countTreasureInHand(G.whoseTurn, &G);
	initialHandCount = G.handCount[G.whoseTurn];

	// Add adventurer to player 0's hand
	gainCard(adventurer, &G, 2, 0);

	// Player 0 plays adventurer
	res = cardEffect(adventurer, choice1, choice2, choice3, &G, 5, NULL);
	assertEqual(res, 0, "cardEffect did not return 0", &testRes);
	
	// Count treasure cards in hand and total cards in hand
	finalTreasureCount = countTreasureInHand(G.whoseTurn, &G);
	finalHandCount = G.handCount[G.whoseTurn];

	// Check player 0 gained 2 new treasure cards and adventurer moved to played cards
	assertEqual((finalTreasureCount - initialTreasureCount), 2, "Adventurer did not yield exactly 2 new treasure cards in hand", &testRes);
	assertEqual((finalHandCount - initialHandCount), 2, "Adventurer did not yield exactly 2 new cards in hand", &testRes);
	assertNotEqual(G.hand[G.whoseTurn][5], adventurer, "Adventurer was not removed from player's hand", &testRes);
	assertEqual(G.playedCards[G.playedCardCount - 1], adventurer, "Adventurer was not moved to played card", &testRes);

	if (testRes == 0)
	{
		printf("TEST FOR 'Adventurer' PASSED!\n");
	}
	else
	{
		printf("TEST FOR 'Adventurer' FAILED!\n");
	}

	return 0;
}