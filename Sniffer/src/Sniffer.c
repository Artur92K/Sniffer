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
#pragma reverse bitfields;

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

	}
	return EXIT_SUCCESS;
}
