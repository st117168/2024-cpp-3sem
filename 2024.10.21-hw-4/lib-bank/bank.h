#ifndef BANK_H
#define BANK_H

#include"bank-account.h"
#include<vector>

class Bank
{
public:
	void AddAccount(BankAccount* account);
	double GetTotalBalance();
	std::string PrintAllAccounts();

	size_t AccountsCount();
private:
	std::vector<BankAccount*> accounts;
};

#endif