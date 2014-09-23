/*
 ============================================================================
 Reading packet using socket;
 ============================================================================
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include "ProtocolHeaders.h"

#define ETH_FRAME_LEN 1518

int main2(void) {
	puts("Lab_0"); /* prints Lab_0 */
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
	//definicja zmiennych
	int s; /*deskryptor gniazda*/
	int j;
	int i = 0;
	int length = 0;

	//bufor dla ramek z Ethernetu
	void* buffer = (void*) malloc(ETH_FRAME_LEN);
	//wskaznik do naglowka Eth
	unsigned char* etherhead = buffer;
	//wskaznik do miejsca rozpoczecia danych
	unsigned char* data = buffer + 14;

	printf("Program do odbierania ramek Ethernet z NIC!\n");

	//otworz gniazdo
	s = socket(AF_INET, SOCK_PACKET, htons(ETH_P_ALL));
	if (s == -1) {
		printf("Nie moge otworzyc gniazda\n");
	}

	while (i < 1) {
		//odbierz ramke Eth
		length = recvfrom(s, buffer, ETH_FRAME_LEN, 0, NULL, NULL);
		if (length == -1)

			printf("Problem z odbiorem ramki \n");
		else {
			i++;
			printf("Ramka: %d, dlugosc: %d [B]\n", i, length);
		}
		printf("LENTH SDASDASDASDSAD %d", length);
#if 1

		int arp, ip, icmp, udp, tcp, c;

		ramka_eth(&naglowek_eth, buffer);
		printf("Type: 0x0%x  \n", reverseshort(naglowek_eth.typ));
		if (naglowek_eth.typ == 0x0008) {
			printf("Nastepny naglowek to IPv4\n");
			ip = 1;
		}
		if (naglowek_eth.typ == 0x0608) {
			printf("Nastepny naglowek to ARP\n");
			arp = 1;
		}

		pakiet_ip(&naglowek_ip, data); // buffor +14
		printf("Protokol: 0x%x\n", naglowek_ip.prtokolnizszy);
		if (naglowek_ip.prtokolnizszy == 0x06) {
			printf("Nastepny naglowek to TCP\n");
			tcp = 1;
		}
		if (naglowek_ip.prtokolnizszy == 0x01) {
			printf("Nastepny naglowek to ICMP\n");
			icmp = 1;
		}
		if (naglowek_ip.prtokolnizszy == 0x11) {
			printf("Nastepny naglowek to UDP\n");
			udp = 1;
			c = 2; // nie wiem czemu nie działalo sprawdzanie warunku ale z tym dziala
		}

		//=======================PAKOWANIE====================
		if (tcp == 1) {
			pakiet_eth_ip_tcp(&pakiet_tcp, &naglowek_eth, &naglowek_ip,
					&naglowek_tcp, buffer, sizeof(pakiet_tcp));
			printf("\n----------==========Ramka TCP==========----------\n");
			printf("\n");
			ETHERNET(&naglowek_eth);
			IP(&naglowek_ip);
			TCP(&naglowek_tcp);
		}
		if (icmp == 1) {
			pakiet_eth_ip_icmp(&pakiet_icmp, &naglowek_eth, &naglowek_ip,
					&naglowek_icmp, buffer, sizeof(pakiet_icmp));
			printf("\n----------==========Ramka ICMP==========----------\n");
			printf("\n");
			ETHERNET(&naglowek_eth);
			IP(&naglowek_ip);
			ICMP(&naglowek_icmp);
		}
		if (udp == 1 && c == 2) {
			pakiet_eth_ip_udp(&pakiet_udp, &naglowek_eth, &naglowek_ip,
					&naglowek_udp, buffer, sizeof(pakiet_udp));
			printf("\n----------==========Ramka UDP==========----------\n");
			printf("\n");
			ETHERNET(&naglowek_eth);
			IP(&naglowek_ip);
			UDP(&naglowek_udp);
		}
		if (arp == 1) {
			pakiet_eth_arp(&pakiet_arp, &naglowek_eth, &naglowek_arp, buffer,
					sizeof(pakiet_arp));

			printf("\n****************---Ramka ETH_ARP---****************\n");
			printf("\n");
			ETHERNET(&naglowek_eth);
			ARP(&naglowek_arp);

		}
		// naglowek_eth.typ = 0;
		if (naglowek_eth.typ != 0x0008 && naglowek_eth.typ != 0x0608) {
			printf("\n****************---Ramka ETH---****************\n");
			printf("\n");
			ETHERNET(&naglowek_eth);
		}

#endif
	}

	return EXIT_SUCCESS;
}

