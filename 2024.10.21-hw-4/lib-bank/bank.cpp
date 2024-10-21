#include "bank.h"

void Bank::AddAccount(BankAccount* account)
{
	accounts.push_back(account);
	printf("Added account %s\n", (*account).GetAccountNumber().c_str());
}

double Bank::GetTotalBalance()
{
	double total = 0.0;
	for (int i = 0; i < accounts.size(); ++i)
	{
		total += accounts[i]->GetBalance();
	}
	return total;
}

std::string Bank::PrintAllAccounts()
{
	std::string outstr = "";
	outstr = "Information about all accounts:\n";
	for (int i = 0; i < accounts.size(); ++i)
	{
		outstr += accounts[i]->PrintAccountInfo();
		outstr += "\n";
	}
	std::cout << outstr;
	return outstr;
}

size_t Bank::AccountsCount()
{
    return accounts.size();
}
