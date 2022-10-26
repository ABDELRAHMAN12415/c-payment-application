#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.H>
#include"app.h"
#include"../Card/card.h"
#include"../Server/server.h"
#include"../Terminal/terminal.h"

extern ST_accountsDB_t clients[255];

extern  x;

void appStart(void) {

	ST_cardData_t tempdata1 ;
	ST_terminalData_t tempdata2 ;
	ST_transaction_t tempdata3 ;



	ST_cardData_t* ptempdata1 = &tempdata1;
	ST_terminalData_t* ptempdata2 = &tempdata2;
	ST_transaction_t* ptempdata3 = &tempdata3;

	uint8_t  block, block_state, state, transaction_state;




	state = getCardHolderName(ptempdata1);

	if (state != 0) {
		printf("Invalid Name!");
		return;
	};

	state = getCardExpiryDate(ptempdata1);

	if (state != 0) {
		printf("Invalid Date Format!");
		return;
	};

	state = getCardPAN(ptempdata1);

	if (state != 0) {
		printf("Invalid Pan!");
		return;
	};

	state = getTransactionDate(ptempdata2);

	if (state != 0) {
		printf("Invalid Date Format!");
		return;
	};

	state = isCardExpired(tempdata1, tempdata2);

	if (state != 0) {
		printf("Expired Card!");
		return;
	};




	if (isValidAccount(ptempdata1) == 0)
	{

		block_state = AccountControl();

		if (block_state == 0) {

			printf("account blocked");
			return;

		}

	};





	state = getTransactionAmount(ptempdata2);

	if (state != 0) {
		printf("Invalid Amount!");
		return;
	};

	state = setMaxAmount(ptempdata2);

	if (state != 0) {
		printf("Invalid Amount!");
		return;
	};

	state = isBelowMaxAmount(ptempdata2);

	if (state != 0) {
		printf("Exceeded Max Amount!");
		return;
	};


	tempdata3.cardHolderData = tempdata1;
	tempdata3.terminalData = tempdata2;

	transaction_state = recieveTransactionData(ptempdata3);

	if (transaction_state == 3) {

		printf("Saving Failed!");
		return;

	}

	else {

		ptempdata3->transState = transaction_state;

		saveTransaction(ptempdata3);

		const char* arr[] = { "APPROVED", "DECLINED_INSUFFECIENT_FUND" , "DECLINED_STOLEN_CARD", "INTERNAL_SERVER_ERROR" };

		printf("%s", arr[transaction_state]);

		return;
	}

}