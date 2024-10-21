#include "bank-account.h"

BankAccount::BankAccount(std::string accNumber, double bal, std::string accHolder)
	: accountNumber(accNumber), balance(bal), accountHolder(accHolder) {}

void BankAccount::Deposit(double amount)
{
	balance += amount;
	printf("Added to account %s: %.2lf\n", accountNumber.c_str(), amount);
}

void BankAccount::Withdraw(double amount)
{
	if (amount > balance)
	{
		std::cout << "Not enough money in the account.\n";
	}
	else
	{
		balance -= amount;
		printf("Withdrawn from account %s: %.2lf\n", accountNumber.c_str(), amount);
	}
}

double BankAccount::GetBalance()
{
	return balance;
}

std::string BankAccount::GetAccountHolder()
{
	return accountHolder;
}

std::string BankAccount::GetAccountNumber()
{
	return accountNumber;
}

std::string BankAccount::PrintAccountInfo()
{
	std::string outstr = "";
	outstr = "Account number: " + accountNumber + "\nOwner: " + accountHolder + "\nBalance: " + std::to_string(balance) + "\n";
	std::cout << outstr;
	return outstr;
}
