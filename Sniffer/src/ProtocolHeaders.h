#ifndef NAGLOWKI_H_
#define NAGLOWKI_H_

#endif /* NAGLOWKI_H_ */

// Naglowek Ethernet II typu 14 bajtów

struct nagl_eth { 						// 14B
	unsigned char destaddr[6]; 			// 6B // nadawca !!
	unsigned char addrodbriocy[6]; 		// 6B
	unsigned short typ; 				// 16b - 2b

} nagl_eth;
// Nagłowek ARP 28 bajtów
struct nagl_arp { // 28B

	unsigned short int hardwaretype;	// 16b
	unsigned short int protokoltype; 	// 16b
	unsigned char hardwaresize; 		// 8b
	unsigned char protokolsize; 		// 8b
	unsigned short int opcodetype; 		// 16b
	unsigned char senderMAC[6]; 		// 48b
	unsigned char senderIP[4]; 			// 48 b
	unsigned char targetMAC[6];			// 48 b
	unsigned char targetIP[4]; 			// 48 b

};

struct nagl_ip {
	struct IP_version {
		unsigned char dlugosc :4, version :4; // długosc naglowka i wersja 8b = 1B
	} IP_version;

	unsigned char klasauslugi; 					// 8b Klasa usługi
	unsigned short int calkowitadlugosc;		// 16b Całkowita długość
	unsigned short int identyfikacja; 			// 16b Numer identyfikayjny

	struct flagaIprzesuniecie { 				// flagaIprzesuniecie 3+13
		unsigned short int przesuniecie :13, flaga :3;

	} flagaIprzesuniecie;

	unsigned char ttl; 							// 8b  Czas zycia
	unsigned char prtokolnizszy; 				// 8b  Protokół warstwy wyższej
	unsigned short int crc;						// 16b Suma kontrona
	unsigned char sourceIP[4]; 					// 32b Adres źródłowy
	unsigned char destinationIP[4];				// 32b Adres docelowy
};
// Nagłowek ICMP 8 bajtów

struct nagl_icmp {
	unsigned char type; 	// 8b
	unsigned char code; 	// 8b
	unsigned char crc[2]; 	// 16b
	unsigned int unused; 	// 32b
};

// Nagłowek UDP 8 bajtów
struct nagl_udp {
	unsigned char sourceport[2];		// 16b
	unsigned char destinationport[2];	// 16b
	unsigned char lenght[2]; 			// 16b
	unsigned short int crc; 			// 16b

};

// Nagłowek TCP 24 bajty
struct nagl_tcp {
	unsigned short int sourceport;				 // 16b Port źródłowy 2B
	unsigned short int destinationport; 		 // 16b Port docelowy 2B
	unsigned int nrsekwencji; 					 // 32b Numer sekwencyjny 4B
	unsigned int ack; 							 // 32b Numer potwierdzenia 4B
	struct flagi1 {
		unsigned char ns :1, zarezerwowane :3, dlugoscnaglowka :4;
	} flagi1;
	struct flagi {								// 16b Flagi 2B LITTLE ENDIAN !
		unsigned char fin :1, syn :1, rst :1, psh :1, ack :1, urg :1, ece :1,
				cwr :1;

	} flagi;

	unsigned short int window; 					// 16b Rozmiar okna 2B
	unsigned short int crc; 					// 16b Suma kontrolna 2B
	unsigned short int priorytet; 				// 16b Wskaźnik priorytetu 2B
	unsigned short int options;
}__attribute__ ((packed));

/* Spis nazw naglowkow:
 nagl_arp
 nagl_eth
 nagl_icmp
 nagl_tcp
 nagl_udp
 nagl_ip
 */

struct eth_arp {
	struct nagl_eth eth;
	struct nagl_arp arp;

} eth_arp;

struct eth_ip_icmp {
	struct nagl_eth eth;
	struct nagl_ip ip;
	struct nagl_icmp icmp;
	unsigned char bufor_danych[1500];
}__attribute__ ((packed));

struct eth_ip_udp {
	struct nagl_eth eth;
	struct nagl_ip ip;
	struct nagl_udp udp;
	unsigned char bufor_danych[1500];
}__attribute__ ((packed));

struct eth_ip_tcp {
	struct nagl_eth eth;
	struct nagl_ip ip;
	struct nagl_tcp tcp;
	unsigned char bufor_danych[1500];
}__attribute__ ((packed));

