/*
 ============================================================================
 Name        : Lab_0.c
 Author      : krygier
 Version     : v1
 Copyright   : krygier
 Description : Lab_0
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
	//struct eth_ip_tcp pakiet_tcp;
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
			//pakiet_eth_ip_tcp(&pakiet_tcp, &naglowek_eth, &naglowek_ip,
		//			&naglowek_tcp, buffer, sizeof(pakiet_tcp));
			printf("\n----------==========Ramka TCP==========----------\n");
			printf("\n");
			printf("Naglowek Ethernet II\n");
			printf("\n");
			printf("Broadcast: %d.%d.%d.%d.%d.%d\n", naglowek_eth.destaddr[0],
					naglowek_eth.destaddr[1], naglowek_eth.destaddr[2],
					naglowek_eth.destaddr[3], naglowek_eth.destaddr[4],
					naglowek_eth.destaddr[5]);
			printf("Source: %x:%x:%x:%x:%x:%x\n", naglowek_eth.addrodbriocy[0],
					naglowek_eth.addrodbriocy[1], naglowek_eth.addrodbriocy[2],
					naglowek_eth.addrodbriocy[3], naglowek_eth.addrodbriocy[4],
					naglowek_eth.addrodbriocy[5]);
			printf("Type: 0x0%x  \n", reverseshort(naglowek_eth.typ));
			printf("\n");
			printf("Naglowek Internet Protocol\n");
			printf("\n");
			printf("Wersja: 0x%x\n", naglowek_ip.IP_version);
			printf("Dlugość naglowka: 0x%x\n", naglowek_ip.IP_version.dlugosc);
			printf("Usluga: 0x%x\n", naglowek_ip.klasauslugi);
			printf("Długość pakietu: 0x%x \n", naglowek_ip.calkowitadlugosc);
			printf("Identyfikacja: 0x%x\n", naglowek_ip.identyfikacja);
			printf("Flagi i przesuniecie: 0x%x, MF: 0x%x, DF: 0x%x\n",
					naglowek_ip.flagaIprzesuniecie.przesuniecie);
			printf("Flagi i przesuniecie: 0x%x, MF: 0x%x, DF: 0x%x\n",
					naglowek_ip.flagaIprzesuniecie.flaga);
			printf("Czas życia: %d \n", naglowek_ip.ttl);
			printf("Protokol: 0x%x\n", naglowek_ip.prtokolnizszy);
			printf("Suma kontrolna nagłowka: 0x%x\n", naglowek_ip.crc);
			printf("Adresu zrodlowy IP: %d %d %d %d \n",
					naglowek_ip.sourceIP[0], naglowek_ip.sourceIP[1],
					naglowek_ip.sourceIP[2], naglowek_ip.sourceIP[3]);
			printf("Adres docelowy IP: %d %d %d %d \n",
					naglowek_ip.destinationIP[0], naglowek_ip.destinationIP[1],
					naglowek_ip.destinationIP[2], naglowek_ip.destinationIP[3]);
			printf("\n");
			printf("Naglowek TCP\n");
			printf("\n");
			printf("Port źródlowy: %d\n",
					reverseshort(naglowek_tcp.sourceport));
			printf("Port docelowy: %d\n",
					reverseshort(naglowek_tcp.destinationport));
			printf("Numer sekwencji: %x\n",
					reverseint(naglowek_tcp.nrsekwencji));
			printf("ACK : %x\n", reverseint(naglowek_tcp.ack));

			printf("Dlugosc naglowka: %d\n",
					naglowek_tcp.flagi1.dlugoscnaglowka);
			printf("Zarezerwowane: 0x%x\n", naglowek_tcp.flagi1.zarezerwowane);
			printf("Flaga ns: 0x%x\n", naglowek_tcp.flagi1.ns);
			printf("FLAGI:\n");
			printf("Flaga fin: 0x%x\n", naglowek_tcp.flagi.fin);
			printf("Flaga syn: 0x%x\n", naglowek_tcp.flagi.syn);
			printf("Flaga rst: 0x%x\n", naglowek_tcp.flagi.rst);
			printf("Flaga psh: 0x%x\n", naglowek_tcp.flagi.psh);
			printf("Flaga ack: 0x%x\n", naglowek_tcp.flagi.ack);
			printf("Flaga urg: 0x%x\n", naglowek_tcp.flagi.urg);
			printf("Flaga ece: 0x%x\n", naglowek_tcp.flagi.ece);
			printf("Flaga cwr: 0x%x\n", naglowek_tcp.flagi.cwr);

			printf("KONIEC FLAG:\n");
			printf("Rozmiar okna: %d\n", reverseshort(naglowek_tcp.window));
			printf("CRC: 0x%04x\n", reverseshort(naglowek_tcp.crc));
		}
		if (icmp == 1) {
			pakiet_eth_ip_icmp(&pakiet_icmp, &naglowek_eth, &naglowek_ip,
					&naglowek_icmp, buffer, sizeof(pakiet_icmp));
			printf("\n----------==========Ramka ICMP==========----------\n");
			printf("\n");
			printf("Naglowek Ethernet II\n");
			printf("\n");
			printf("Broadcast: %d.%d.%d.%d.%d.%d\n", naglowek_eth.destaddr[0],
					naglowek_eth.destaddr[1], naglowek_eth.destaddr[2],
					naglowek_eth.destaddr[3], naglowek_eth.destaddr[4],
					naglowek_eth.destaddr[5]);
			printf("Source: %x:%x:%x:%x:%x:%x\n", naglowek_eth.addrodbriocy[0],
					naglowek_eth.addrodbriocy[1], naglowek_eth.addrodbriocy[2],
					naglowek_eth.addrodbriocy[3], naglowek_eth.addrodbriocy[4],
					naglowek_eth.addrodbriocy[5]);
			printf("Type: 0x0%x  \n", reverseshort(naglowek_eth.typ));
			printf("\n");
			printf("Naglowek Internet Protocol\n");
			printf("\n");
			printf("Wersja: 0x%x\n", naglowek_ip.IP_version);
			printf("Dlugość naglowka: 0x%x\n", naglowek_ip.IP_version.dlugosc);
			printf("Usluga: 0x%x\n", naglowek_ip.klasauslugi);
			printf("Długość pakietu: 0x%x \n", naglowek_ip.calkowitadlugosc);
			printf("Identyfikacja: 0x%x\n", naglowek_ip.identyfikacja);
			printf("Flagi i przesuniecie: 0x%x, MF: 0x%x, DF: 0x%x\n",
					naglowek_ip.flagaIprzesuniecie.przesuniecie);
			printf("Flagi i przesuniecie: 0x%x, MF: 0x%x, DF: 0x%x\n",
					naglowek_ip.flagaIprzesuniecie.flaga);
			printf("Czas życia: %d \n", naglowek_ip.ttl);
			printf("Protokol: 0x%x\n", naglowek_ip.prtokolnizszy);
			printf("Suma kontrolna nagłowka: 0x%x\n", naglowek_ip.crc);
			printf("Adresu zrodlowy IP: %d %d %d %d \n",
					naglowek_ip.sourceIP[0], naglowek_ip.sourceIP[1],
					naglowek_ip.sourceIP[2], naglowek_ip.sourceIP[3]);
			printf("Adres docelowy IP: %d %d %d %d \n",
					naglowek_ip.destinationIP[0], naglowek_ip.destinationIP[1],
					naglowek_ip.destinationIP[2], naglowek_ip.destinationIP[3]);
			printf("\n");
			printf("Naglowek ICMP\n");
			printf("\n");
			printf("Typ: 0x%x\n", naglowek_icmp.type);
			printf("Kod: 0x%x\n", naglowek_icmp.code);
			printf("Suma kontrolna: 0x%x %x\n", naglowek_icmp.crc[0],
					naglowek_icmp.crc[1]);
			printf("Dane ICMP: 0x%x\n", naglowek_icmp.unused);
			printf("\n");
		}
		if (udp == 1 && c == 2) {
			pakiet_eth_ip_udp(&pakiet_udp, &naglowek_eth, &naglowek_ip,
					&naglowek_udp, buffer, sizeof(pakiet_udp));
			printf("\n----------==========Ramka UDP==========----------\n");
			printf("\n");
			printf("Naglowek Ethernet II\n");
			printf("\n");
			printf("Broadcast: %d.%d.%d.%d.%d.%d\n", naglowek_eth.destaddr[0],
					naglowek_eth.destaddr[1], naglowek_eth.destaddr[2],
					naglowek_eth.destaddr[3], naglowek_eth.destaddr[4],
					naglowek_eth.destaddr[5]);
			printf("Source: %x:%x:%x:%x:%x:%x\n", naglowek_eth.addrodbriocy[0],
					naglowek_eth.addrodbriocy[1], naglowek_eth.addrodbriocy[2],
					naglowek_eth.addrodbriocy[3], naglowek_eth.addrodbriocy[4],
					naglowek_eth.addrodbriocy[5]);
			printf("Type: 0x0%x  \n", reverseshort(naglowek_eth.typ));
			printf("\n");
			printf("Naglowek Internet Protocol\n");
			printf("\n");
			printf("Wersja: 0x%x\n", naglowek_ip.IP_version);
			printf("Dlugość naglowka: 0x%x\n", naglowek_ip.IP_version.dlugosc);
			printf("Usluga: 0x%x\n", naglowek_ip.klasauslugi);
			printf("Długość pakietu: 0x%x \n", naglowek_ip.calkowitadlugosc);
			printf("Identyfikacja: 0x%x\n", naglowek_ip.identyfikacja);
			printf("Flagi i przesuniecie: 0x%x, MF: 0x%x, DF: 0x%x\n",
					naglowek_ip.flagaIprzesuniecie.przesuniecie);
			printf("Flagi i przesuniecie: 0x%x, MF: 0x%x, DF: 0x%x\n",
					naglowek_ip.flagaIprzesuniecie.flaga);
			printf("Czas życia: %d \n", naglowek_ip.ttl);
			printf("Protokol: 0x%x\n", naglowek_ip.prtokolnizszy);
			printf("Suma kontrolna nagłowka: 0x%x\n", naglowek_ip.crc);
			printf("Adresu zrodlowy IP: %d %d %d %d \n",
					naglowek_ip.sourceIP[0], naglowek_ip.sourceIP[1],
					naglowek_ip.sourceIP[2], naglowek_ip.sourceIP[3]);
			printf("Adres docelowy IP: %d %d %d %d \n",
					naglowek_ip.destinationIP[0], naglowek_ip.destinationIP[1],
					naglowek_ip.destinationIP[2], naglowek_ip.destinationIP[3]);
			printf("\n");
			printf("Naglowek User datagram protokol \n");
			printf("\n");
			printf("Port źrodłowy UDP: %d %d \n", naglowek_udp.sourceport[0],
					naglowek_udp.sourceport[1]);
			printf("Port docelowy UDP: %d %d \n",
					naglowek_udp.destinationport[0],
					naglowek_udp.destinationport[1]);
			printf("Długość UDP: %d %d \n", naglowek_udp.lenght[0],
					naglowek_udp.lenght[1]);
			printf("Suma kontrolna: %d \n", naglowek_udp.crc);
		}
		if (arp == 1) {
			pakiet_eth_arp(&pakiet_arp, &naglowek_eth, &naglowek_arp, buffer,
					sizeof(pakiet_arp));

			printf("\n****************---Ramka ETH_ARP---****************\n");
			printf("\n");
			printf("Naglowek ETHERNET\n");
			printf("\n");
			printf("Broadcast: %d.%d.%d.%d.%d.%d\n", naglowek_eth.destaddr[0],
					naglowek_eth.destaddr[1], naglowek_eth.destaddr[2],
					naglowek_eth.destaddr[3], naglowek_eth.destaddr[4],
					naglowek_eth.destaddr[5]);
			printf("Source: %x:%x:%x:%x:%x:%x\n", naglowek_eth.addrodbriocy[0],
					naglowek_eth.addrodbriocy[1], naglowek_eth.addrodbriocy[2],
					naglowek_eth.addrodbriocy[3], naglowek_eth.addrodbriocy[4],
					naglowek_eth.addrodbriocy[5]);
			printf("Type: 0x0%x  \n", reverseshort(naglowek_eth.typ));
			printf("\n");
			printf("Naglowek ARP\n");
			printf("\n");
			printf("Typ warstwy fizycznej (HTYPE): 0x%x\n",
					naglowek_arp.hardwaretype);
			printf("Typ protokołu wyzszej warstwy (PTYPE): 0x%x\n",
					naglowek_arp.protokoltype);
			printf("Dlugosc adresu MAC: 0x%x\n", naglowek_arp.hardwaresize);
			printf("Długość protokołu wyższej warstwy (PLEN): 0x%d\n",
					naglowek_arp.protokolsize);
			printf("Kod: 0x%x\n", naglowek_arp.opcodetype);
			printf("Adres zrodlowy MAC: %x %x %x %x %x %x\n",
					naglowek_arp.senderMAC[0], naglowek_arp.senderMAC[1],
					naglowek_arp.senderMAC[2], naglowek_arp.senderMAC[3],
					naglowek_arp.senderMAC[4], naglowek_arp.senderMAC[5]);
			printf("Adres zrodlowy IP: %d %d %d %d \n",
					naglowek_arp.senderIP[0], naglowek_arp.senderIP[1],
					naglowek_arp.senderIP[2], naglowek_arp.senderIP[3]);
			printf("Adres docelowy MAC: %x %x %x %x %x %x\n",
					naglowek_arp.targetMAC[0], naglowek_arp.targetMAC[1],
					naglowek_arp.targetMAC[2], naglowek_arp.targetMAC[3],
					naglowek_arp.targetMAC[4], naglowek_arp.targetMAC[5]);
			printf("Adres docelowy IP: %d %d %d %d \n",
					naglowek_arp.targetIP[0], naglowek_arp.targetIP[1],
					naglowek_arp.targetIP[2], naglowek_arp.targetIP[3]);

		}
		// naglowek_eth.typ = 0;
		if (naglowek_eth.typ != 0x0008 && naglowek_eth.typ != 0x0608) {
			printf("\n****************---Ramka ETH---****************\n");
			printf("\n");
			printf("Naglowek ETHERNET\n");
			printf("\n");
			printf("Broadcast: %d.%d.%d.%d.%d.%d\n", naglowek_eth.destaddr[0],
					naglowek_eth.destaddr[1], naglowek_eth.destaddr[2],
					naglowek_eth.destaddr[3], naglowek_eth.destaddr[4],
					naglowek_eth.destaddr[5]);
			printf("Source: %x:%x:%x:%x:%x:%x\n", naglowek_eth.addrodbriocy[0],
					naglowek_eth.addrodbriocy[1], naglowek_eth.addrodbriocy[2],
					naglowek_eth.addrodbriocy[3], naglowek_eth.addrodbriocy[4],
					naglowek_eth.addrodbriocy[5]);
			printf("Type: 0x0%x  \n", reverseshort(naglowek_eth.typ));
			printf("\n");
			printf("Brak protokolu warstwy wyzej = dane !");
		}

#endif
	}

	return EXIT_SUCCESS;
}
