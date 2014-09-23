/*
 ============================================================================
 Name        : Sniffer.c
 Author      : A.K
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "ProtocolHeaders.h"
#pragma reverse bitfields; // odwracanie bitow
/*
 void pakiet_eth_arp(struct eth_arp *, struct nagl_eth *, struct nagl_arp *,
 unsigned char *, unsigned int);
 void pakiet_eth_ip_tcp(struct eth_ip_tcp *, struct nagl_eth *, struct nagl_ip *,
 struct nagl_tcp *, unsigned char *, unsigned int);
 void pakiet_eth_ip_icmp(struct eth_ip_icmp *, struct nagl_eth *,
 struct nagl_ip *, struct nagl_icmp *, unsigned char *, unsigned int);
 void pakiet_eth_ip_udp(struct eth_ip_udp *, struct nagl_eth *, struct nagl_ip *,
 struct nagl_udp *, unsigned char *, unsigned int);
 */
int main(void) {
	int wybor;
	scanf("%d", &wybor);

	switch (wybor) {
		case 1:
			main1();
			break;
		case 2:
			main2();
			break;
		case 3:
			main3();
			break;
		default:
			printf("Brak wyboru");
			puts("TEST");
//
	}
	return EXIT_SUCCESS;
}
