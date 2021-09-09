/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * 2021년도 2학기
 * BankAccountTest.cpp
 * @author 김상
 * BankAccount 클래스 단위검사 프로그램
 */

#include "BankAccount.h"
#include "gtest/gtest.h"

TEST(BankAccountTest, DepositTest)
{
	BankAccount aliceAccount;
	ASSERT_EQ(aliceAccount.getBalance(), 0);
	aliceAccount.deposit(10000);
	ASSERT_EQ(aliceAccount.getBalance(), 10000);
	ASSERT_THROW(aliceAccount.deposit(-1000), std::invalid_argument);
}

TEST(BankAccountTest, WithdrawalTest)
{
	BankAccount aliceAccount;
	aliceAccount.deposit(10000);
	aliceAccount.withdraw(5000);
	ASSERT_EQ(aliceAccount.getBalance(), 5000);
	ASSERT_THROW(aliceAccount.withdraw(10000), std::invalid_argument);
	ASSERT_THROW(aliceAccount.withdraw(-1000), std::invalid_argument);
}

TEST(BankAccountTest, TransferTest)
{
	BankAccount aliceAccount;
	BankAccount bobAccount;
	aliceAccount.deposit(10000);
	transfer(6000, aliceAccount, bobAccount);
	ASSERT_EQ(aliceAccount.getBalance(), 4000);
	ASSERT_EQ(bobAccount.getBalance(), 6000);
	ASSERT_THROW(transfer(6000, aliceAccount, bobAccount), std::invalid_argument);
	ASSERT_EQ(aliceAccount.getBalance(), 4000);
	ASSERT_EQ(bobAccount.getBalance(), 6000);
}

