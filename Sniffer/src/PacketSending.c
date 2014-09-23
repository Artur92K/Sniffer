#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include <sys/ioctl.h>
#include ".h"

#define INTERFACE	"wlan0"

int main(void) {

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
	int s_out; /*deskryptor gniazda*/
	int j;

	naglowek_eth.destaddr[0] = 0xff;
	naglowek_eth.destaddr[1] = 0xff;
	naglowek_eth.destaddr[2] = 0xff;
	naglowek_eth.destaddr[3] = 0xff;
	naglowek_eth.destaddr[4] = 0xff;
	naglowek_eth.destaddr[5] = 0xff;

	naglowek_eth.addrodbriocy[0] = 0x94;
	naglowek_eth.addrodbriocy[1] = 0xce;
	naglowek_eth.addrodbriocy[2] = 0x2c;
	naglowek_eth.addrodbriocy[3] = 0x2b;
	naglowek_eth.addrodbriocy[4] = 0xe8;
	naglowek_eth.addrodbriocy[5] = 0xa1;
	naglowek_eth.typ = 0x0800;
	reverseshort(naglowek_eth.typ);
	unsigned char zmienna = 0x45;

	memcpy(&naglowek_ip.IP_version, &zmienna, 1);

	naglowek_ip.klasauslugi = 0x00;
	naglowek_ip.calkowitadlugosc = 0x0036;
	naglowek_ip.identyfikacja = 0x0c8d;

	naglowek_ip.flagaIprzesuniecie.przesuniecie = 0x40;

	naglowek_ip.flagaIprzesuniecie.flaga = 0x00;
	naglowek_ip.ttl = 0x2f;
	naglowek_ip.prtokolnizszy = 0x11;


	naglowek_ip.sourceIP[0] = 0xad;
	naglowek_ip.sourceIP[1] = 0xc0;
	naglowek_ip.sourceIP[2] = 0x52;
	naglowek_ip.sourceIP[3] = 0xc4;

	naglowek_ip.destinationIP[0] = 0xc0;
	naglowek_ip.destinationIP[1] = 0xa8;
	naglowek_ip.destinationIP[2] = 0x77;
	naglowek_ip.destinationIP[3] = 0x3b;

	naglowek_ip.crc = 0x0000;

	naglowek_udp.sourceport[0] =0x00;
	naglowek_udp.sourceport[1]=0x7b;
	naglowek_udp.destinationport[0]=0x00;
	naglowek_udp.destinationport[1]=0x7b;
	naglowek_udp.lenght[0] =0x00;
	naglowek_udp.lenght[1]=0x38;
	naglowek_udp.crc =0x2209;

	unsigned char buffor_eth[1500] = { };
	pakowanie_eth(&naglowek_eth, buffor_eth, &naglowek_ip, &naglowek_udp);
	//pakowanie_ip(naglowek_ip,buffor_eth);

	printf("buffor_eth: %d ", buffor_eth[0]);
	void* buffer = (void*) malloc(ETH_FRAME_LEN);
	unsigned char* etherhead = buffer;
	memcpy(buffer, buffor_eth, 42);
	struct ethhdr *eh = (struct ethhdr *) etherhead;
	struct sockaddr_ll socket_address;
	int send_result = 0;
	struct ifreq ifr;
	int ifindex = 0;
	socket_address.sll_halen = ETH_ALEN;

	eh->h_proto = htons(0x0800);
	//**************************wyslij ramke***********************************
#if 1 //tu mozna zablokowac wysylanie
	s_out = socket(AF_PACKET, SOCK_RAW, ETH_P_ALL);
	if (s_out == -1) {
		printf("Nie moge otworzyc gniazda s_out\n");
	}

	strncpy(ifr.ifr_name, INTERFACE, IFNAMSIZ);
	if (ioctl(s_out, SIOCGIFINDEX, &ifr) == -1) {
		perror("SIOCGIFINDEX");
		exit(1);
	}
	ifindex = ifr.ifr_ifindex;
	printf("Pobrano indeks karty NIC: %i\n", ifindex);
	//usatwiono index urzadzenia siecowego
	socket_address.sll_ifindex = ifindex;

	send_result = sendto(s_out, buffer, ETH_FRAME_LEN, 0,
			(struct sockaddr*) &socket_address, sizeof(socket_address));
	if (send_result == -1) {
		printf("Nie moge wyslac danych! \n");
	} else {
		printf("Wyslalem dane do intefejsu: %s \n", INTERFACE);
	}

	//=======wypisz zawartosc bufora do wyslania===========
#if 1
	printf("Dane do wyslania: \n");
	for (j = 0; j < send_result; j++) {
		printf("%02x ", *(etherhead + j));
	}
	printf("\n");
#endif
	//========koniec wypisywania===========================

#endif //konic blokady wysylania
	//*******************************************************************************
}
