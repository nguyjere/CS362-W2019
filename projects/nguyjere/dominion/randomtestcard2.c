
/* -----------------------------------------------------------------------
 * Random Test For:
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
#include <time.h>
#include <stdlib.h>

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
	int numOfTests = 1000;
	int numOfFails = 0;
	srand(time(NULL));

	for (int i = 0; i < numOfTests; i++)
	{
		int initialHandCount, finalHandCount;
		int res;
		int testRes = 0;

		// Random number of players between 2 and 4
		int numOfPlayers = rand() % (MAX_PLAYERS - 1) + 2;
		int k[10] = { adventurer, council_room, feast, gardens, mine,
				remodel, smithy, village, baron, great_hall };
		int seed = rand();
		struct gameState G;

		initializeGame(numOfPlayers, k, seed, &G);

		// Switch to random player
		while (G.whoseTurn != rand() % numOfPlayers)
		{
			endTurn(&G);
		}

		//Count cards in hand
		initialHandCount = G.handCount[G.whoseTurn];

		// Add village to player's hand
		gainCard(village, &G, 2, G.whoseTurn);

		// Randomize Parameters
		int bonus = rand() % 4;
		int max = G.handCount[G.whoseTurn] - 1;
		int choice1 = rand() % max;
		int choice2 = rand() % max;
		int choice3 = rand() % max;

		// Player plays village
		res = cardEffect(village, choice1, choice2, choice3, &G, G.handCount[G.whoseTurn] - 1, &bonus);
		assertEqual(res, 0, "cardEffect did not return 0", &testRes);

		// Count total cards in hand
		finalHandCount = G.handCount[G.whoseTurn];

		// Check player gained 4 new cards, 1 buy, and other players gain 1 card in hand.
		assertEqual((finalHandCount - initialHandCount), 1, "Village did not yield exactly 1 new cards in hand", &testRes);
		assertEqual(G.numActions, 3, "Village did not yield 2 additional actions", &testRes);
		assertNotEqual(G.hand[G.whoseTurn][5], village, "Village was not removed from player's hand", &testRes);
		assertEqual(G.playedCards[G.playedCardCount - 1], village, "Village was not moved to played pile", &testRes);

		if (testRes != 0)
		{
			numOfFails++;
		}
	}
	printf("PASSED: %d\nFAILED:%d\n", (numOfTests - numOfFails), numOfFails);
}