void ramka_eth(struct nagl_eth *naglowek_eth, unsigned char *bufor_eth_arp) {

	memcpy(naglowek_eth, bufor_eth_arp, 14);

}
void pakiet_ip(struct nagl_ip *naglowek_ip, unsigned char *bufor_eth_ip) {

	memcpy(naglowek_ip, bufor_eth_ip, 20);

}
unsigned short int ip_sum_calc(unsigned short int len_ip_header,
		unsigned short int buff[]) {
	unsigned short int word16;
	unsigned int sum = 0;
	unsigned short int i;

	// make 16 bit words out of every two adjacent 8 bit words in the packet
	// and add them up
	for (i = 0; i < len_ip_header; i = i + 2) {
		word16 = ((buff[i] << 8) & 0xFF00) + (buff[i + 1] & 0xFF);
		sum = sum + (unsigned int) word16;
	}

	// take only 16 bits out of the 32 bit sum and add up the carries
	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);

	// one's complement the result
	sum = ~sum;

	return ((unsigned short int) sum);
}

void pakowanie_eth(struct nagl_eth *naglowek_eth, unsigned char *buffor_eth,
		struct nagl_ip *naglowek_ip, struct nagl_udp *naglowek_udp) {
	memcpy(buffor_eth, naglowek_eth, 14);
	memcpy(&buffor_eth[14], naglowek_ip, 20);
	memcpy(&buffor_eth[34], naglowek_udp, 8);
	// cel, źródło, rozmiar
}
/*void pakowanie_ip(struct nagl_ip *naglowek_ip, unsigned char *buffor_eth) {
 memcpy(buffor_eth+14, naglowek_ip, 20);
 // cel, źródło, rozmiar
 } */

void pakiet_eth_arp(struct eth_arp *pakiet_arp, struct nagl_eth *naglowek_eth,
		struct nagl_arp *naglowek_arp, unsigned char *bufor_eth_arp,
		unsigned int eth_arp) {
	memcpy(pakiet_arp, bufor_eth_arp, eth_arp);
	memcpy(naglowek_eth, &bufor_eth_arp[0], 14);
	memcpy(naglowek_arp, &bufor_eth_arp[14], 28);
}

void pakiet_eth_ip_icmp(struct eth_ip_icmp *pakiet_icmp,
		struct nagl_eth *naglowek_eth, struct nagl_ip *naglowek_ip,
		struct nagl_icmp *naglowek_icmp, unsigned char *bufor_eth_ip_icmp,
		unsigned int eth_ip_icmp) {
	memcpy(pakiet_icmp, bufor_eth_ip_icmp, eth_ip_icmp);
	memcpy(naglowek_eth, &bufor_eth_ip_icmp[0], 14);
	memcpy(naglowek_ip, &bufor_eth_ip_icmp[14], 20);
	memcpy(naglowek_icmp, &bufor_eth_ip_icmp[34], 8);
}

void pakiet_eth_ip_udp(struct eth_ip_udp *pakiet_udp,
		struct nagl_eth *naglowek_eth, struct nagl_ip *naglowek_ip,
		struct nagl_udp *naglowek_udp, unsigned char *bufor_eth_ip_udp,
		unsigned int eth_ip_udp) {
	memcpy(pakiet_udp, bufor_eth_ip_udp, eth_ip_udp);
	memcpy(naglowek_eth, &bufor_eth_ip_udp[0], 14);
	memcpy(naglowek_ip, &bufor_eth_ip_udp[14], 20);
	memcpy(naglowek_udp, &bufor_eth_ip_udp[34], 8);
}

void pakiet_eth_ip_tcp(struct eth_ip_tcp *pakiet_tcp,
		struct nagl_eth *naglowek_eth, struct nagl_ip *naglowek_ip,
		struct nagl_tcp *naglowek_tcp, unsigned char *bufor_eth_ip_tcp,
		unsigned int eth_ip_tcp) {
	memcpy(pakiet_tcp, bufor_eth_ip_tcp, eth_ip_tcp); // cel źrodło rozmiar
	memcpy(naglowek_eth, &bufor_eth_ip_tcp[0], 14);
	memcpy(naglowek_ip, &bufor_eth_ip_tcp[14], 20);
	memcpy(naglowek_tcp, &bufor_eth_ip_tcp[34], 24);

}
// funkcja odwracająca
void* odrwacajacy(void* cokolwiek, unsigned int rozmiar) {
	unsigned char *tablica = (unsigned char *) cokolwiek;
	unsigned char *wyjsciowy = (unsigned char*) malloc(rozmiar);
	int i = 0;

	for (i = 0; i < rozmiar; i++) {
		wyjsciowy[i] = tablica[rozmiar - 1 - i];
	}
	return (void*) wyjsciowy;
}

unsigned short reverseshort(unsigned short value) {
	return *(unsigned int*) odrwacajacy(&value, sizeof(value));
}
unsigned short reverseint(unsigned int value) {
	return *(unsigned int*) odrwacajacy(&value, sizeof(value));
}
