/*
 ============================================================================
 Name        : Sniffer.c
 Author      : A.K
 Version     : 1.1
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "ProtocolHeaders.h"

int main(void) {
	int wybor;
	scanf("%d", &wybor);

	switch (wybor) {
		case 1:
			SztucznaRamka();
			break;
		case 2:
			OdczytanieZKarty();
			break;
		case 3:
			WyslaniePrzezKarte();
			break;
		default:
			printf("Brak wyboru");

	}
	return EXIT_SUCCESS;
}
