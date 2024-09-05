#ifndef SUBACCOUNT_H
#define SUBACCOUNT_H
#include <iostream>
using namespace std;

class SubAccount {
public:
  // constructor
  SubAccount() : balance(0), accNum("null") {};
  SubAccount(int balance, string accNum) {
    this->balance = balance;
    this->accNum = accNum;
  }

  // deposit -- withdraw
  virtual void Deposit(int amount) {
    balance += amount;
    cout << "    | Deposit was successful" << endl;
    cout << "    | Balance is now: " << balance << endl;
  }

  virtual void Withdraw(int amount) {
    if (balance - amount < 0) {
      cout << "    | Withdraw exceeds current funds" << endl;
      cout << "    | Withdraw was unsuccessful";
      return;
    } else {
      balance -= amount;
      cout << "    | Withdraw was successful" << endl;
      cout << "    | Balance is now: " << balance << endl;
    }
  }

  // setters && getters
  void SetAccNum(string accNum) { this->accNum = accNum; }
  string GetAccNum() { return this->accNum; }
  void SetBalance(int amount) { this->balance = amount; }
  int GetBalance() { return this->balance; }

  // print account info
  virtual void PrintSubAccount() const;

  // sub account menu
  virtual void SubAccountMenu();

  // print options menu
  virtual void PrintMenu() const;

protected:
  string accNum;
  int balance;
};

class SavingAccount : public SubAccount {
public:
  SavingAccount() : SubAccount() {}
  SavingAccount(int balance, string accNum)
      : SubAccount(balance, accNum) {}

  static int GetSavingAccountKeys() {
    savingAccountKeys++;
    return savingAccountKeys;
  }

private:
  static int savingAccountKeys;
};

class CheckingAccount : public SubAccount {
public:
  CheckingAccount() : SubAccount(), lock(false), maxCap(0) {}
  CheckingAccount(int balance, string accNum, bool lock, int maxCap)
      : SubAccount(balance, accNum), lock(lock), maxCap(maxCap) {}

  void Deposit(int amount) override;
  void Withdraw(int amount) override;

  void Lock();
  void Unlock();

  void PrintMenu() const override;

  void SetMaxCap(int amount) { maxCap = amount; }
  int const GetMaxCap() { return this->maxCap; }

  static int GetCheckingAccountKeys() {
    checkingAccountKeys++;
    return checkingAccountKeys;
  }

  void SubAccountMenu() override;

  void PrintSubAccount() const override;

private:
  static int checkingAccountKeys;
  bool lock;
  int maxCap;
};
#endif