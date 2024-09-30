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
	void PrintAccountInfo();
private:
	std::string accountNumber;
	double balance;
	std::string accountHolder;
};

#endif