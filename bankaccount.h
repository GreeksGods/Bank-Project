#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include "subaccount.h"
#include <iostream>
#include <vector>
#include <map>
using namespace std;

class BankAccount {
public:
  // Constructor
  BankAccount();

  //destructor
  ~BankAccount();

  // get count of accounts in saving and checking
  int const GetSavingAccountNum();
  int const GetCheckingAccountNum();
  int AggregateBalanceCalc();
  void PrintAggregatedBalances();
  void PrintDetailedSubInfo();

  //new saving account
  void NewSavingAccount();

  //new checking account
  void NewCheckingAccount();

  //close sub account
  void CloseSubAccount(string key);

  //modify sub account
  void ModifySubAccount(string key);

  //print menu
  void PrintMenu();

  //insertion sort for subaccounts
  void InsertionSortSub(vector<SubAccount *> &vect);

  // setter and getters for private members
  void SetAccNum(string accNum) {this->accNum = accNum;}
  string GetAccNum() {return this->accNum;}
  void SetFirst(string first) { this->first = first; }
  string GetFirst() { return this->first; }
  void SetLast(string last) { this->last = last; }
  string GetLast() { return this->last; }
  void SetSsn(string ssn) { this->ssn = ssn; }
  string GetSsn() { return this->ssn; }

  map<string, SubAccount*> GetSubAccounts() {return subAccounts;}

  vector<string> GetSubAccountKeys(string type) {
    if (type == "savings") {
      return savingAccountKeys;
    } else {
      return checkingAccountKeys;
    }
  }

  //bank account menu here
  void BankAccountMenu();
  
private:
  string accNum;
  string first;
  string last;
  string ssn;
  vector<string> savingAccountKeys;
  vector<string> checkingAccountKeys;
  map<string, SubAccount*> subAccounts;
};

#endif
