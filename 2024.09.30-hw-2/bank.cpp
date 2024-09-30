#include "bank.h"

void Bank::AddAccount(BankAccount account)
{
	accounts.push_back(account);
	printf("�������� ���� %s\n", account.GetAccountNumber().c_str());
}

double Bank::GetTotalBalance()
{
	double total = 0.0;
	for (int i = 0; i < accounts.size(); ++i)
	{
		total += accounts[i].GetBalance();
	}
	return total;
}

void Bank::PrintAllAccounts()
{
	std::cout << "���������� � ���� ������:\n";
	for (int i = 0; i < accounts.size(); ++i)
	{
		accounts[i].PrintAccountInfo();
		std::cout << "\n";
	}
}

