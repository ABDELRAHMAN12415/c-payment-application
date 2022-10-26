#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.H>
#include"../Card/card.h"
#include"terminal.h"







EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {

	uint8_t  length;

	printf("enter the trasaction date(in format DD/MM/YYYY):");
	scanf("%s", termData->transactionDate);

	length = strlen(termData->transactionDate);

	if (length != 10 || termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/') {

		return WRONG_DATE;

	}

	else {

		
		return OK1;

	}


}







EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {

	int y10, y01, m10, m01;

	y10 = strncmp(&(termData.transactionDate[8]), &(cardData.cardExpirationDate[3]), 1);
	y01 = strncmp(&(termData.transactionDate[9]), &(cardData.cardExpirationDate[4]), 1);
	m10 = strncmp(&(termData.transactionDate[3]), &(cardData.cardExpirationDate[0]), 1);
	m01 = strncmp(&(termData.transactionDate[4]), &(cardData.cardExpirationDate[1]), 1);

	if (y10 < 0) {

		return OK1;

	}
	else if (y10 == 0 && y01 < 0) {

		return OK1;

	}
	else if (y10 == 0 && y01 == 0 && m10 < 0) {

		return OK1;

	}
	else if (y10 == 0 && y01 == 0 && m10 == 0 && m01 < 0) {

		return OK1;

	}
	else {

		return EXPIRED_CARD;

	};

}



EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {

	float amount;

	printf("enter the transaction amount:");
	scanf("%f", &amount);


	if (amount <= 0) {

		return INVALID_AMOUNT;

	}

	else {

		termData->transAmount = amount;

		return OK1;

	};

}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {

	if (termData->maxTransAmount > termData->transAmount) {

		return OK1;

	}

	else {

		return EXCEED_MAX_AMOUNT;

	};

}



EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {

	float maxamount;

	printf("enter the maximum amount:");
	scanf("%f", &maxamount);

	if (maxamount <= 0) {

		return INVALID_MAX_AMOUNT;

	}

	else {

		termData->maxTransAmount = maxamount;

		return OK1;

	}

}