#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include"card.h"


EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {

	uint8_t name[25];
	uint8_t  length;

	printf("enter the card holder's name:");
	scanf("%s", &name);
	length = strlen(&name);


	if (length < 20 || length > 24 || name == NULL) {


		return WRONG_NAME;

	}

	else {

		strcpy(cardData->cardHolderName, &name);
		return OK;

	}
};









EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {

	uint8_t date[6];
	uint8_t  length;

	printf("enter the card expiration date(in format MM/YY):");
	scanf("%s", &date);

	length = strlen(&date);

	if (length != 5 || date[2] != '/' || date == NULL) {

		
		return WRONG_EXP_DATE;

	}

	else {

		strcpy(cardData->cardExpirationDate, &date);
		return OK;

	}
};











EN_cardError_t getCardPAN(ST_cardData_t* cardData) {

	uint8_t PAN[20];
	uint8_t  length;

	printf("enter the card PAN:");
	scanf("%s", &PAN);

	length = strlen(&PAN);

	if (length < 16 || length > 19 || PAN == NULL) {

		return WRONG_PAN;

	}

	else {

		strcpy(cardData->primaryAccountNumber, &PAN);

		return OK;

	}


}
