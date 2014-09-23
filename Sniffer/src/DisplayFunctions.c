#include <stdio.h>
#include <stdlib.h>
#include "ProtocolHeaders.h"


	struct nagl_eth naglowek_eth;
	struct nagl_arp naglowek_arp;
	struct nagl_tcp naglowek_tcp;
	struct nagl_ip naglowek_ip;
	struct nagl_icmp naglowek_icmp;
	struct nagl_udp naglowek_udp;
	struct eth_ip_icmp pakiet_icmp;
	struct eth_ip_udp pakiet_udp;
//	struct eth_ip_tcp pakiet_tcp;
	struct eth_arp pakiet_arp;
	unsigned int eth_ip_icmp = sizeof(struct eth_ip_icmp); // mam
	unsigned int eth_ip_udp = sizeof(struct eth_ip_udp); // robi sie
	//unsigned int eth_ip_tcp = sizeof(struct eth_ip_tcp); //
	//unsigned int eth_arp = sizeof(struct eth_arp); // mam

void ETH(struct nagl_eth *naglowek_eth) {
	printf("\n");
	printf("Naglowek ETHERNET\n");
	printf("\n");
	printf("%d", nagl_eth.destaddr[1]);
	//naglowek_eth.destaddr[1]);

	/*
	printf("Broadcast: %d.%d.%d.%d.%d.%d\n", naglowek_eth.destaddr[0],
			naglowek_eth.destaddr[1], naglowek_eth.destaddr[2],
			naglowek_eth.destaddr[3], naglowek_eth.destaddr[4],
			naglowek_eth.destaddr[5]);
	printf("Source: %x:%x:%x:%x:%x:%x\n", naglowek_eth.addrodbriocy[0],
			naglowek_eth.addrodbriocy[1], naglowek_eth.addrodbriocy[2],
			naglowek_eth.addrodbriocy[3], naglowek_eth.addrodbriocy[4],
			naglowek_eth.addrodbriocy[5]);
	printf("Type: 0x0%x  \n", reverseshort(naglowek_eth.typ));
	*/
}
