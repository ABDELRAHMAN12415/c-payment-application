#define _CRT_SECURE_NO_WARNINGS
#include<stdio.H>
#include<string.H>
#include"../Card/card.h"
#include"../Terminal/terminal.h"
#include"server.h"

extern ST_transactionsDB_t transaction[255];
extern uint32_t transactionSequenceNumber;
extern ST_accountsDB_t clients[255];

int x;


EN_serverError_t isValidAccount(ST_cardData_t* cardData) {

	int i;

	for (i = 0; i < 255; i++) {

		if (strcmp(cardData->primaryAccountNumber, &clients[i].primaryAccountNumber) == 0) {
			x = i;
			return OK2;
		}

	}

	return ACCOUNT_NOT_FOUND;

}


EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {


	if (termData->transAmount <= clients[x].balance) {

		return OK2;

	}

	else {

		return LOW_BALANCE;

	}


}


EN_transState_t recieveTransactionData(ST_transaction_t* transData) {

	int server_st1, server_st2;

	if (transactionSequenceNumber >= 255) {

		return INTERNAL_SERVER_ERROR;
	}

	else {

		transData->transactionSequenceNumber = transactionSequenceNumber;

	}

	server_st1 = isValidAccount(&transData->cardHolderData);
	server_st2 = isAmountAvailable(&transData->terminalData);

	if (server_st1 == 3 || strcmp(&clients[x].AccountState, "blocked") == 0) {

		return DECLINED_STOLEN_CARD;

	}
	else if (server_st2 == 4) {

		return DECLINED_INSUFFECIENT_FUND;

	}
	else {

		clients[x].balance = clients[x].balance - transData->terminalData.transAmount;
		return APPROVED;

	}

}








EN_serverError_t AccountControl() {

	int  block =0;

	printf("do you need to block this account?\n(press 1 to block this account ,any other numper to continue with your process):\n");

	scanf("%d", &block);

	if (block == 1) {

		strcpy(clients->AccountState, "blocked" );
		return OK2;

	}

}










EN_serverError_t saveTransaction(ST_transaction_t* transData) {

	transaction[transactionSequenceNumber].cardHolderData = transData->cardHolderData;
	transaction[transactionSequenceNumber].terminalData = transData->terminalData;
	transaction[transactionSequenceNumber].transState = transData->transState;
	transaction[transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber;

	transactionSequenceNumber = transactionSequenceNumber + 1;

	return OK2;
}