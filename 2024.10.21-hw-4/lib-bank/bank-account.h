#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include<iostream>

class BankAccount
{
public:
	BankAccount(std::string accNumber, double bal, std::string accHolder);
	void Deposit(double amount);
	void Withdraw(double amount);
	double GetBalance();
	std::string GetAccountHolder();
	std::string GetAccountNumber();
	std::string PrintAccountInfo();
private:
	std::string accountNumber;
	double balance;
	std::string accountHolder;
};

#endif