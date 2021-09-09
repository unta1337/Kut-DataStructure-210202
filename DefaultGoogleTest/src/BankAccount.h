/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * 2021년도 2학기
 * BankAccount.h
 * @author 김상진
 * 은행계좌 클래스
 */

#ifndef BANKACCOUNT_H_
#define BANKACCOUNT_H_

#include <stdexcept>

class BankAccount {
private:
	int balance = 0;
public:
	BankAccount() = default;
	virtual ~BankAccount() = default;
	int getBalance() const{
		return balance;
	}
	void withdraw(int amount){
		if(amount<0||amount>balance)
			throw std::invalid_argument("잔액부족, 음수인출");
		balance -= amount;
	}
	void deposit(int amount){
		if(amount<0) throw std::invalid_argument("음수 입금");
		balance += amount;
	}
	friend void transfer(int amount, BankAccount& from, BankAccount& to);
};

void transfer(int amount, BankAccount& from, BankAccount& to){
	if(amount<0) throw std::invalid_argument("음수 계좌이체");
	from.withdraw(amount);
	to.deposit(amount);
}

#endif /* BANKACCOUNT_H_ */
