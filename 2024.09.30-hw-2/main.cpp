#include"bank-account.h"
#include"bank.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Russian");
	BankAccount acc1("001", 104.50, "Pavel");
	BankAccount acc2("002", 500, "Artem");
	BankAccount acc3("003", 426.12, "Den");
	BankAccount acc4("004", 46356.19 , "Charlie");
	BankAccount acc5("005", 891974.09, "Nathan");
	Bank bank;
	bank.AddAccount(&acc1);
	bank.AddAccount(&acc2);
	bank.AddAccount(&acc3);
	bank.AddAccount(&acc4);
	bank.AddAccount(&acc5);

	acc1.Deposit(500);
	acc2.Deposit(101000);
	acc3.Withdraw(1000);
	acc4.Withdraw(43000);

	bank.PrintAllAccounts();
	printf("Общий баланс: %.2lf\n", bank.GetTotalBalance());

	return 0;
}