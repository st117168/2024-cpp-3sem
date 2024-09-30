#include "bank-account.h"

BankAccount::BankAccount(std::string accNumber, double bal, std::string accHolder)
	: accountNumber(accNumber), balance(bal), accountHolder(accHolder) {}

void BankAccount::Deposit(double amount)
{
	balance += amount;
	printf("��������� �� ���� %s: %.2lf\n", accountNumber.c_str(), amount);
}

void BankAccount::Withdraw(double amount)
{
	if (amount > balance)
	{
		std::cout << "������������ ������� �� �����.\n";
	}
	else
	{
		balance -= amount;
		printf("����� �� �����: %.2lf\n", amount);
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

void BankAccount::PrintAccountInfo()
{
	printf("����� �����: %s\n��������: %s\n������: %.2lf\n",
		accountNumber.c_str(), accountHolder.c_str(), balance);
}
