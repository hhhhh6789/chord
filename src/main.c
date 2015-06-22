#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "chord.c"

#define VERSION "0.0.1"

/*
 * aim: given n nodes, distribute a file across some of the nodes. we must be able to get that file later
 * from the set of nodes. 
 *
 * flow: 
 *	1. generate set of n nodes
 *	2. distribute a file amongst nodes
 *	3. restore the file from the nodes
 *
 */

 size_t getNetworkSize(int argc, char const *argv[]) {
 	int n = 0;
 	if (argc == 2) {
 		n = atoi(argv[1]);
 		if (n <= 0) {
 			printf("usage: chord <n> (n > 0)\n");
 		}
 	} else {
 		printf("usage: chord <n>\n");
 	}
 	return n;
 }


 void printNetwork(Peer** peers, const size_t n) {
 	for (int i = 0; i < n; i++) {
 		printf("peerID: %lu\n", peers[i]->PeerID);
 		size_t conn = (size_t)log2(n);
 		for (int j = 0; i < conn; j++) {
 			printf("---> %d - peer %lu\n", j, peers[i]->Connections->Peers[j]->PeerID);
 		}
 	}
 }

 int main(int argc, char const *argv[]) {
 	const size_t n = getNetworkSize(argc, argv);
 	if (n == 0) {
 		return 1;
 	}
	// create sample data, peers with a random number as ID
 	Peer **peers = generateTestNetwork(n);

 	// printNetwork(peers, NETWORK_SIZE);
	// in the ring, peers are ordered by a numeric (the ID in this case) in ascending order
 	// qsort(peers, n, sizeof(Peer*), peerIDCompare);

 	// for (int i = 0; i < n; i++) {
 	// 	printf("peer %d:\n", i);
 	// 	printHash((*peers[i]).PeerID);
 	// }

 	return 0;
 }