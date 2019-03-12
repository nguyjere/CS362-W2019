/* -----------------------------------------------------------------------
 * Unit Test For:
 *	int initializeGame(int numPlayers, int kingdomCards[10], int randomSeed, struct gameState *state)
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

	//printf("Testing initializeGame() with 2 players...\n");
	res = initializeGame(2, k, seed, &G);
	assert(res == 0);
	assert(G.numPlayers == 2);

	// Check for curse and victory cards
	assert(G.supplyCount[curse] == 10);
	assert(G.supplyCount[estate] == 8);
	assert(G.supplyCount[duchy] == 8);
	assert(G.supplyCount[province] == 8);

	// Check if all of the kingdom cards are initialized with the right amount
	assert(G.supplyCount[adventurer] == 10);
	assert(G.supplyCount[council_room] == 10);
	assert(G.supplyCount[feast] == 10);
	assert(G.supplyCount[gardens] == 8);
	assert(G.supplyCount[mine] == 10);
	assert(G.supplyCount[remodel] == 10);
	assert(G.supplyCount[smithy] == 10);
	assert(G.supplyCount[village] == 10);
	assert(G.supplyCount[baron] == 10);
	assert(G.supplyCount[great_hall] == 8);

	// Check amount for treasure cards
	assert(G.supplyCount[copper] == 46);
	assert(G.supplyCount[silver] == 40);
	assert(G.supplyCount[gold] == 30);


	memset(&G, 23, sizeof(struct gameState)); //Clear gameState

	//printf("Testing initializeGame() with 3 players...\n");
	res = initializeGame(3, k, seed, &G);
	assert(res == 0);
	assert(G.numPlayers == 3);

	// Check for curse and victory cards
	assert(G.supplyCount[curse] == 20);
	assert(G.supplyCount[estate] == 12);
	assert(G.supplyCount[duchy] == 12);
	assert(G.supplyCount[province] == 12);

	// Check if all of the kingdom cards are initialized with the right amount
	assert(G.supplyCount[adventurer] == 10);
	assert(G.supplyCount[council_room] == 10);
	assert(G.supplyCount[feast] == 10);
	assert(G.supplyCount[gardens] == 12);
	assert(G.supplyCount[mine] == 10);
	assert(G.supplyCount[remodel] == 10);
	assert(G.supplyCount[smithy] == 10);
	assert(G.supplyCount[village] == 10);
	assert(G.supplyCount[baron] == 10);
	assert(G.supplyCount[great_hall] == 12);

	// Check amount for treasure cards
	assert(G.supplyCount[copper] == 39);
	assert(G.supplyCount[silver] == 40);
	assert(G.supplyCount[gold] == 30);

	memset(&G, 23, sizeof(struct gameState)); //Clear gameState

	//printf("Testing initializeGame() with 4 players...\n");
	res = initializeGame(4, k, seed, &G);
	assert(res == 0);
	assert(G.numPlayers == 4);

	// Check for curse and victory cards
	assert(G.supplyCount[curse] == 30);
	assert(G.supplyCount[estate] == 12);
	assert(G.supplyCount[duchy] == 12);
	assert(G.supplyCount[province] == 12);

	// Check if all of the kingdom cards are initialized with the right amount
	assert(G.supplyCount[adventurer] == 10);
	assert(G.supplyCount[council_room] == 10);
	assert(G.supplyCount[feast] == 10);
	assert(G.supplyCount[gardens] == 12);
	assert(G.supplyCount[mine] == 10);
	assert(G.supplyCount[remodel] == 10);
	assert(G.supplyCount[smithy] == 10);
	assert(G.supplyCount[village] == 10);
	assert(G.supplyCount[baron] == 10);
	assert(G.supplyCount[great_hall] == 12);

	// Check amount for treasure cards
	assert(G.supplyCount[copper] == 32);
	assert(G.supplyCount[silver] == 40);
	assert(G.supplyCount[gold] == 30);

	printf("TEST FOR initializeGame() PASSED!\n");

	return 0;
}