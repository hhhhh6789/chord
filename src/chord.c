#include "util.c"
#include <math.h>

/*
 * the peer we are connected to and the distance to that peer
 */
 typedef struct RoutingTable {
 	struct Peer **Peers;
 } RoutingTable;

/*
 * a peer has a peerID and an array of connections to other peers
 */
 typedef struct Peer {
 	// unsigned char *PeerID;
 	unsigned long PeerID;
 	RoutingTable *Connections;
 } Peer;

/*
 * helper function to generate a new peer
 */
 Peer *newPeer(unsigned int id, RoutingTable *routingTable) {
 	Peer *peer = (Peer*)malloc(sizeof(Peer));
 	peer->PeerID = id;
 	peer->Connections = routingTable;
 	return peer;
 }
 
 /*
 * fill up routing tables for a given peer according to chord algorithm. 
 * this function assumes all peers exist (they are given as the **peers input)
 */
 RoutingTable *getRoutingTableForPeer(unsigned long peerID, Peer **peers, const size_t networkSize) {
 	RoutingTable *table = (RoutingTable*)malloc(sizeof(RoutingTable));
 	table->Peers = (Peer**)malloc(sizeof(Peer*));
 	size_t numConnections = ceil(log2(networkSize));
 	printf("peer %lu is connected to: \n", peerID);
 	for (int i = peerID; i < peerID + numConnections; i++) {
 		unsigned int j = i - peerID;
 		table->Peers[j] = (Peer*)malloc(sizeof(Peer));

 		unsigned long nextPeer;
 		if (j != 0) {
 			nextPeer = table->Peers[j - 1]->PeerID + pow(2, j);
 		} else {
 			nextPeer = peerID + 1;
 		}

		nextPeer = nextPeer % networkSize; // ring wraps around 0 

		table->Peers[j] = peers[nextPeer];
		printf("peer %lu\n", nextPeer);
	}
	return table;
}

/*
 * generate some random data (an array of peers with a random number as PeerID)
 */
 Peer **generateTestNetwork(const size_t networkSize) {
    // srand (clock());
    // OpenSSL_add_all_algorithms();
 	Peer** peers = (Peer**)malloc(sizeof(Peer*) * networkSize);
 	printf("network size is: %zu\n", networkSize);
 	printf("connections per peer: %f\n", ceil(log2(networkSize)));
 	printf("-----------\n");
 	// create peers
 	for (int i = 0; i < networkSize; i++) {
 		peers[i] = newPeer(i, NULL);
 	}

 	// now that peers exist, link then according to chord algorithm
 	for (int i = 0; i < networkSize; i++) {
 		peers[i]->Connections = getRoutingTableForPeer(i, peers, networkSize);
 	}
 	return peers;
 }

/*
 * peer compare function for qsort. use peer PeerID to compare. 
 * in a more realistic scenario, the PeerID would be a GUPeerID, and we would hash the GUPeerID to some number
 * for this comparison
 */
 int peerIDCompare(const void *a, const void *b) {
 	unsigned long a_t = (**(Peer**)a).PeerID;
 	unsigned long b_t = (**(Peer**)b).PeerID;
 	return a_t - b_t;
 }
