#ifndef BANK_H
#define BANK_H

#include"bank-account.h"
#include<vector>

class Bank
{
public:
	void AddAccount(BankAccount* account);
	double GetTotalBalance();
	void PrintAllAccounts();
private:
	std::vector<BankAccount*> accounts;
};

#endif