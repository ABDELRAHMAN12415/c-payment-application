#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>

#include"Card/card.h"
#include"Terminal/terminal.h"
#include"Server/server.h"
#include"Application/app.h"



ST_accountsDB_t clients[255] = {

	{123.5,"asdfghjklzxcvbnm","valid"} , {1345,"aaaaaaaaaaaaaaaa","valid"} , {145.6,"ssssssssssssssss","blocked"}

};

ST_transactionsDB_t transaction[255] = { 0 };

uint32_t transactionSequenceNumber = 0;



void main() {

	appStart();


}