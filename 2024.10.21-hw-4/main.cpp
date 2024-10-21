#include <gtest/gtest.h>
#include "lib-text-editor/text-editor.h"
#include "lib-bank/bank.h"
#include "lib-bank/bank-account.h"

//hw-1

//Blank text after text editor initialization
TEST(TestGroupName_hw1, Subtest_1_constructor) 
{
  TextEditor text;
  ASSERT_EQ(text.length(), 0);
}

//Changing text length after addText() applying
TEST(TestGroupName_hw1, Subtest_2_addText_1) 
{
  TextEditor text;
  text.addText("hello ");
  size_t tl1 = 0;
  tl1 = text.length();
  std::string two = "two";
  text.addText(two);
  ASSERT_EQ(text.length(), tl1 + two.length());
}

//True inserting position while addText() applying
TEST(TestGroupName_hw1, Subtest_3_addText_2) 
{
  TextEditor text;
  text.addText("hello ");
  std::string two = "two";
  text.addText(two);
  ASSERT_EQ(text.find(two), text.posistion());
}

//Changing cursor position after cursorRight() applying
TEST(TestGroupName_hw1, Subtest_4_cursorRight_1) 
{
  TextEditor text;
  text.addText("hello!");
  text.cursorRight(2);
  ASSERT_EQ(text.posistion(), 2);
}

//cursorRight() true return
TEST(TestGroupName_hw1, Subtest_5_cursorRight_2) 
{
  TextEditor text;
  text.addText("hello!");
  std::string str = "";
  str = text.cursorRight(2);
  ASSERT_EQ(str, text.substr(text.posistion(), text.length() - text.posistion()));
}

//Changing cursor position after cursorLeft() applying
TEST(TestGroupName_hw1, Subtest_6_cursorLeft_1) 
{
  TextEditor text;
  text.addText("hello!");
  text.cursorRight(4);
  text.cursorLeft(2);
  ASSERT_EQ(text.posistion(), 2);
}

//cursorLeft() true return
TEST(TestGroupName_hw1, Subtest_7_cursorLeft_2) 
{
  TextEditor text;
  text.addText("hello!");
  text.cursorRight(4);
  std::string str = "";
  str = text.cursorLeft(2);
  ASSERT_EQ(str, text.substr(0, text.posistion()));
}

//Changing text length after deleteText() applying
TEST(TestGroupName_hw1, Subtest_8_deleteText_1) 
{
  TextEditor text;
  text.addText("hello!");
  text.cursorRight(4);
  size_t tl1 = 0;
  tl1 = text.length();
  size_t diff = 0;
  diff = text.deleteText(10);
  ASSERT_LE(diff, 10);
  ASSERT_EQ(diff, tl1 - text.length());
}

//Changing cursor position after deleteText() applying
TEST(TestGroupName_hw1, Subtest_9_deleteText_2) 
{
  TextEditor text;
  text.addText("hello!");
  text.cursorRight(4);
  size_t LastPos = 0;
  LastPos = text.posistion();
  size_t diff = 0;
  diff = text.deleteText(2);
  ASSERT_EQ(diff, LastPos - text.posistion());
}

//hw-2

//Bank-account constructor
TEST(TestGroupName_hw2, Subtest_1_BankAccountConstructor) 
{
	BankAccount acc("001", 104.50, "Pavel");
  ASSERT_EQ(acc.GetAccountNumber(), "001");
  ASSERT_EQ(acc.GetBalance(), 104.50);
  ASSERT_EQ(acc.GetAccountHolder(), "Pavel");
}

//Deposit true sum
TEST(TestGroupName_hw2, Subtest_2_Deposit) 
{
	BankAccount acc("001", 104.50, "Pavel");
  double bal = 0;
  bal = acc.GetBalance();
  acc.Deposit(500);
  ASSERT_EQ(acc.GetBalance(), bal + 500);
}

//Withdraw availability
TEST(TestGroupName_hw2, Subtest_3_Withdraw_1) 
{
	BankAccount acc("001", 104.50, "Pavel");
  double bal = 0;
  bal = acc.GetBalance();
  acc.Withdraw(500);
  ASSERT_EQ(acc.GetBalance(), bal);
}

//Withdraw true sum
TEST(TestGroupName_hw2, Subtest_4_Withdraw_2) 
{
	BankAccount acc("001", 104.50, "Pavel");
  double bal = 0;
  bal = acc.GetBalance();
  acc.Withdraw(50);
  ASSERT_EQ(acc.GetBalance(), bal - 50);
}

//BankAddAccount change accounts count
TEST(TestGroupName_hw2, Subtest_5_BankAddAccount_1) 
{
	BankAccount acc1("001", 104.50, "Pavel");
	BankAccount acc2("002", 500, "Artem");
  Bank bank;
	bank.AddAccount(&acc1);
	bank.AddAccount(&acc2);
  ASSERT_EQ(bank.AccountsCount(), 2);
}

//BankAddAccount change TotalBalance
TEST(TestGroupName_hw2, Subtest_6_BankAddAccount_2) 
{
	BankAccount acc("001", 104.50, "Pavel");
  Bank bank;
	bank.AddAccount(&acc);
  ASSERT_EQ(bank.GetTotalBalance(), acc.GetBalance());
}

//TotalBalance is true
TEST(TestGroupName_hw2, Subtest_7_TotalBalance) 
{
	BankAccount acc1("001", 104.50, "Pavel");
	BankAccount acc2("002", 500, "Artem");
  Bank bank;
	bank.AddAccount(&acc1);
	bank.AddAccount(&acc2);
  ASSERT_EQ(bank.GetTotalBalance(), acc1.GetBalance() + acc2.GetBalance());
}

//PrintAccountInfo works correctly
TEST(TestGroupName_hw2, Subtest_8_PrintAccountInfo) 
{
	BankAccount acc("001", 104.50, "Pavel");
  ASSERT_TRUE(acc.PrintAccountInfo().find("001") != -1);
  ASSERT_TRUE(acc.PrintAccountInfo().find("104.50") != -1);
  ASSERT_TRUE(acc.PrintAccountInfo().find("Pavel") != -1);
}

//PrintAllAccounts works correctly
TEST(TestGroupName_hw2, Subtest_9_PrintAllAccounts) 
{
	BankAccount acc1("001", 104.50, "Pavel");
	BankAccount acc2("002", 500, "Artem");
  Bank bank;
	bank.AddAccount(&acc1);
	bank.AddAccount(&acc2);
  ASSERT_TRUE(bank.PrintAllAccounts().find(acc1.PrintAccountInfo()) != -1);
  ASSERT_TRUE(bank.PrintAllAccounts().find(acc2.PrintAccountInfo()) != -1);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
