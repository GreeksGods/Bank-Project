#ifndef BANK_H
#define BANK_H

#include "bankaccount.h"
#include <iostream>
#include <map>
#include <string>
using namespace std;

class Bank {
public:
  // constructor for Bank();
  Bank() : name("nullName"), address("nullAddress"), workingHours("nullWorkingHours") {}

  // destructor for bank
  ~Bank();

  // make new bank account
  void NewBankAccount();

  //get aggregate balance
  int GetAggregateBalance();

  // getter for num bank accounts
  int const GetNumBankAccounts();

  //get bankAccounts
  map<string, BankAccount*> &GetBankAccounts() { return bankAccounts;};

  // get number of saving accounts
  int const GetNumSavingAccounts();

  // get number of checking accounts
  int const GetNumCheckingAccounts();

  // close bank account
  void CloseBankAccount(string key);

  // find bank account and open
  void ModifyBankAccount(string key);

  //print our bank account info
  void PrintBankInfo();

  //detailed bank account info
  void PrintDetailedInfo();

  // brief bank accounts sorted
  void PrintBriefInfo();

  //print menu
  void PrintBankMenu();

  //menu input loop
  void UserMenu();

  // static getter to access our keys
  static int GetBankAccountKeys();

// ----------------------------------------------------------
  void SetName(string name) { this->name = name; }
  string PrintName() { return this->name; }
  void SetAddress(string address) { this->address = address; }
  string PrintAddress() { return this->address; }
  void SetWorkingHours(string workingHours) {
    this->workingHours = workingHours;
  }
  string PrintWorkingHours() { return this->workingHours; }
//------------------------------------------------------------

private:
  // keep track of keys so we can make more accounts
  static int bankAccountKeys;

  // private data members
  string name;
  string address;
  string workingHours;
  vector<string> bankAccountList;
  map<string, BankAccount *> bankAccounts;
  
};
#endif