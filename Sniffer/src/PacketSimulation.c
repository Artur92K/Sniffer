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
#pragma reverse bitfields; // odwracanie bitow

void pakiet_eth_arp(struct eth_arp *, struct nagl_eth *, struct nagl_arp *,
		unsigned char *, unsigned int);
void pakiet_eth_ip_tcp(struct eth_ip_tcp *, struct nagl_eth *, struct nagl_ip *,
		struct nagl_tcp *, unsigned char *, unsigned int);
void pakiet_eth_ip_icmp(struct eth_ip_icmp *, struct nagl_eth *,
		struct nagl_ip *, struct nagl_icmp *, unsigned char *, unsigned int);
void pakiet_eth_ip_udp(struct eth_ip_udp *, struct nagl_eth *, struct nagl_ip *,
		struct nagl_udp *, unsigned char *, unsigned int);

int main1(void) {

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
	unsigned int eth_ip_icmp = sizeof(struct eth_ip_icmp); // mam
	unsigned int eth_ip_udp = sizeof(struct eth_ip_udp); // robi sie
	unsigned int eth_ip_tcp = sizeof(struct eth_ip_tcp); //
	unsigned int eth_arp = sizeof(struct eth_arp); // mam

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

	pakiet_eth_arp(&pakiet_arp, &naglowek_eth, &naglowek_arp, &buffor_eth_arp,
			eth_arp);

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
	printf("Typ warstwy fizycznej (HTYPE): 0x%x\n", naglowek_arp.hardwaretype);
	printf("Typ protokołu wyzszej warstwy (PTYPE): 0x%x\n",
			naglowek_arp.protokoltype);
	printf("Dlugosc adresu MAC: 0x%x\n", naglowek_arp.hardwaresize);
	printf("Długość protokołu wyższej warstwy (PLEN): 0x%d\n",
			naglowek_arp.protokolsize);
	printf("Kod: 0x%x\n", naglowek_arp.opcodetype);
	printf("Adres zrodlowy MAC: %x %x %x %x %x %x\n", naglowek_arp.senderMAC[0],
			naglowek_arp.senderMAC[1], naglowek_arp.senderMAC[2],
			naglowek_arp.senderMAC[3], naglowek_arp.senderMAC[4],
			naglowek_arp.senderMAC[5]);
	printf("Adres zrodlowy IP: %d %d %d %d \n", naglowek_arp.senderIP[0],
			naglowek_arp.senderIP[1], naglowek_arp.senderIP[2],
			naglowek_arp.senderIP[3]);
	printf("Adres docelowy MAC: %x %x %x %x %x %x\n", naglowek_arp.targetMAC[0],
			naglowek_arp.targetMAC[1], naglowek_arp.targetMAC[2],
			naglowek_arp.targetMAC[3], naglowek_arp.targetMAC[4],
			naglowek_arp.targetMAC[5]);
	printf("Adres docelowy IP: %d %d %d %d \n", naglowek_arp.targetIP[0],
			naglowek_arp.targetIP[1], naglowek_arp.targetIP[2],
			naglowek_arp.targetIP[3]);

//------------------------- ICMP ------------------------------------------
	pakiet_eth_ip_icmp(&pakiet_icmp, &naglowek_eth, &naglowek_ip,
			&naglowek_icmp, &buffor_eth_ip_icmp, eth_ip_icmp);
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
	printf("Adresu zrodlowy IP: %d %d %d %d \n", naglowek_ip.sourceIP[0],
			naglowek_ip.sourceIP[1], naglowek_ip.sourceIP[2],
			naglowek_ip.sourceIP[3]);
	printf("Adres docelowy IP: %d %d %d %d \n", naglowek_ip.destinationIP[0],
			naglowek_ip.destinationIP[1], naglowek_ip.destinationIP[2],
			naglowek_ip.destinationIP[3]);
	printf("\n");
	printf("Naglowek ICMP\n");
	printf("\n");
	printf("Typ: 0x%x\n", naglowek_icmp.type);
	printf("Kod: 0x%x\n", naglowek_icmp.code);
	printf("Suma kontrolna: 0x%x %x\n", naglowek_icmp.crc[0],
			naglowek_icmp.crc[1]);
	printf("Dane ICMP: 0x%x\n", naglowek_icmp.unused);
	printf("\n");
	//------------------------- UDP ------------------------------------------
	pakiet_eth_ip_udp(&pakiet_udp, &naglowek_eth, &naglowek_ip, &naglowek_udp,
			&buffor_eth_ip_udp, eth_ip_udp);
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
	printf("Adresu zrodlowy IP: %d %d %d %d \n", naglowek_ip.sourceIP[0],
			naglowek_ip.sourceIP[1], naglowek_ip.sourceIP[2],
			naglowek_ip.sourceIP[3]);
	printf("Adres docelowy IP: %d %d %d %d \n", naglowek_ip.destinationIP[0],
			naglowek_ip.destinationIP[1], naglowek_ip.destinationIP[2],
			naglowek_ip.destinationIP[3]);
	printf("\n");
	printf("Naglowek User datagram protokol \n");
	printf("\n");
	printf("Port źrodłowy UDP: %d %d \n", naglowek_udp.sourceport[0],
			naglowek_udp.sourceport[1]);
	printf("Port docelowy UDP: %d %d \n", naglowek_udp.destinationport[0],
			naglowek_udp.destinationport[1]);
	printf("Długość UDP: %d %d \n", naglowek_udp.lenght[0],
			naglowek_udp.lenght[1]);
	printf("Suma kontrolna: %d \n", naglowek_udp.crc);
	//------------------------- TCP ------------------------------------------
	pakiet_eth_ip_tcp(&pakiet_tcp, &naglowek_eth, &naglowek_ip, &naglowek_tcp,
			&buffor_eth_ip_tcp, eth_ip_tcp);
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
	printf("Adresu zrodlowy IP: %d %d %d %d \n", naglowek_ip.sourceIP[0],
			naglowek_ip.sourceIP[1], naglowek_ip.sourceIP[2],
			naglowek_ip.sourceIP[3]);
	printf("Adres docelowy IP: %d %d %d %d \n", naglowek_ip.destinationIP[0],
			naglowek_ip.destinationIP[1], naglowek_ip.destinationIP[2],
			naglowek_ip.destinationIP[3]);
	printf("\n");
	printf("Naglowek TCP\n");
	printf("\n");
	printf("Port źródlowy: %d\n", reverseshort(naglowek_tcp.sourceport));
	printf("Port docelowy: %d\n", reverseshort(naglowek_tcp.destinationport));
	printf("Numer sekwencji: %x\n", reverseint(naglowek_tcp.nrsekwencji));
	printf("ACK : %x\n", reverseint(naglowek_tcp.ack));

	printf("Dlugosc naglowka: %d\n", naglowek_tcp.flagi1.dlugoscnaglowka);
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

	if (naglowek_tcp.flagi.urg == 1) {
		printf("Priorytet: 0x%x\n", naglowek_tcp.priorytet);
	}

	printf("Opcje: 0x%x\n", naglowek_tcp.options);

	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++==");

	ETH(&naglowek_eth);

	//return EXIT_SUCCESS;1

}
