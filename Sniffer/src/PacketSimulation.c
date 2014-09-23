/*
 ============================================================================
 Name        : zadanie1.c
 Author      : AK
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "ProtocolHeaders.h"

int SztucznaRamka(void) {

	struct nagl_eth naglowek_eth;
	struct nagl_arp naglowek_arp;
	struct nagl_tcp naglowek_tcp;
	struct nagl_ip naglowek_ip;
	struct nagl_icmp naglowek_icmp;
	struct nagl_udp naglowek_udp;
	struct eth_ip_icmp pakiet_icmp;
	struct eth_ip_udp pakiet_udp;
	struct eth_ip_tcp pakiet_tcp;
	struct eth_arp pakiet_arp;
	unsigned int eth_ip_icmp = sizeof(struct eth_ip_icmp);
	unsigned int eth_ip_udp = sizeof(struct eth_ip_udp);
	unsigned int eth_ip_tcp = sizeof(struct eth_ip_tcp);
	unsigned int eth_arp = sizeof(struct eth_arp);

	unsigned char buffor_eth_arp[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x94,
			0xce, 0x2c, 0x2b, 0xe8, 0xa1, 0x08, 0x06, 0x00, 0x01, 0x08, 0x00,
			0x06, 0x04, 0x00, 0x01, 0x94, 0xce, 0x2c, 0x2b, 0xe8, 0xa1, 0xc0,
			0xa8, 0x00, 0x0b, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xa8,
			0x00, 0x01 };
	unsigned char buffor_eth_ip_icmp[] = { 0x00, 0x1f, 0x1f, 0x81, 0xfa, 0x1c,
			0x00, 0x18, 0xf3, 0x51, 0xdf, 0x07, 0x08, 0x00, 0x45, 0x00, 0x00,
			0x54, 0xb4, 0xe8, 0x40, 0x00, 0x40, 0x01, 0x15, 0x39, 0xc0, 0xa8,
			0x77, 0x2c, 0xd4, 0x4d, 0x64, 0x65, 0x08, 0x00, 0x31, 0x1f, 0x08,
			0xe7, 0x00, 0x03, 0xef, 0x78, 0x5f, 0x53, 0x7a, 0x27, 0x0a, 0x00 };

	unsigned char buffor_eth_ip_udp[] = { 0x00, 0x1f, 0x1f, 0x81, 0xfa, 0x1c,
			0x00, 0x18, 0xf3, 0x51, 0xdf, 0x07, 0x08, 0x00, 0x45, 0x00, 0x00,
			0x54, 0xb4, 0xe8, 0x40, 0x00, 0x40, 0x01, 0x15, 0x39, 0xc0, 0xa8,
			0x77, 0x2c, 0xd4, 0x4d, 0x64, 0x65,  // od tego miejscia udp
			0x00, 0x7b, 0x00, 0x7b, 0x00, 0x38, 0x22, 0x09 };

	unsigned char buffor_eth_ip_tcp[] = { 0x00, 0x1f, 0x1f, 0x81, 0xfa, 0x1c,
			0x00, 0x18, 0xf3, 0x51, 0xdf, 0x07, 0x08, 0x00, 0x45, 0x00, 0x00,
			0x54, 0xb4, 0xe8, 0x40, 0x00, 0x40, 0x01, 0x15, 0x39, 0xc0, 0xa8,
			0x77, 0x2c, 0xd4, 0x4d, 0x64,
			0x65,  // od tego miejsca TCP
			0x86, 0x61, 0x00, 0x50, 0x55, 0xf6, 0x7f, 0x8f, 0xc4, 0xbb, 0x1b,
			0x5d, 0x80, 0x10, 0x00, 0xe5, 0x0f, 0x26, 0x00, 0x00, 0x01, 0x01,
			0x08, 0x0a, 0xff, 0xff, 0xee, 0x65, 0x4c, 0xda, 0xad, 0x0c };

//printf("Rozmiar nagłówka Ethernet %d Bajtow\n", sizeof(naglowek_eth));
	printf("Rozmiar nagłówka ETHERNET %d Bajtow\n", sizeof(struct nagl_eth));
	printf("Rozmiar nagłówka ARP %d Bajtow\n", sizeof(struct nagl_arp));
	printf("Rozmiar nagłówka IPv4 %d Bajtow\n", sizeof(struct nagl_ip));
	printf("Rozmiar nagłówka ICMP %d Bajtow\n", sizeof(struct nagl_icmp));
	printf("Rozmiar nagłówka TCP %d Bajtow\n", sizeof(struct nagl_tcp));
	printf("Rozmiar nagłówka UDP %d Bajtow\n", sizeof(struct nagl_udp));
	printf("-----------------------------------------------------------\n");
	printf("Rozmiar pakietu ETH + IP + ICMP %d Bajtow\n", eth_ip_icmp);
	printf("Rozmiar pakietu ETH + IP + UDP %d Bajtow\n", eth_ip_udp);
	printf("Rozmiar pakietu ETH + IP + TCP %d Bajtow\n", eth_ip_tcp);
	printf("Rozmiar pakietu ETH + ARP  %d Bajtow\n", eth_arp);

//------------------------- ARP -----------------------------------------
puts ("a");
	pakiet_eth_arp(&pakiet_arp, &naglowek_eth, &naglowek_arp, &buffor_eth_arp,
			eth_arp);

	printf("\n****************---Ramka ETH_ARP---****************\n");
	printf("\n");
	ETHERNET(&naglowek_eth);
	ARP(&naglowek_arp);

//------------------------- ICMP ------------------------------------------
	pakiet_eth_ip_icmp(&pakiet_icmp, &naglowek_eth, &naglowek_ip,
			&naglowek_icmp, &buffor_eth_ip_icmp, eth_ip_icmp);
	printf("\n----------==========Ramka ICMP==========----------\n");
	printf("\n");
	ETHERNET(&naglowek_eth);
	IP(&naglowek_ip);
	ICMP(&naglowek_icmp);

	//------------------------- UDP ------------------------------------------
	pakiet_eth_ip_udp(&pakiet_udp, &naglowek_eth, &naglowek_ip, &naglowek_udp,
			&buffor_eth_ip_udp, eth_ip_udp);
	printf("\n----------==========Ramka UDP==========----------\n");
	printf("\n");
	printf("Naglowek Ethernet II\n");
	ETHERNET(&naglowek_eth);
	IP(&naglowek_ip);
	UDP(&naglowek_udp);

	//------------------------- TCP ------------------------------------------
	pakiet_eth_ip_tcp(&pakiet_tcp, &naglowek_eth, &naglowek_ip, &naglowek_tcp,
			&buffor_eth_ip_tcp, eth_ip_tcp);
	printf("\n----------==========Ramka TCP==========----------\n");
	printf("\n");
	ETHERNET(&naglowek_eth);
	IP(&naglowek_ip);
	TCP(&naglowek_tcp);
	printf("\n");

	printf("\n----------========== Koniec symulacji ==========----------\n");

	return EXIT_SUCCESS;

}
