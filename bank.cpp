#include "bank.h"
#include <iomanip>
#include <iostream>
#include <map>
using namespace std;

//destructor for bank
Bank::~Bank() {
  for ( auto iter : bankAccountList) {
    delete bankAccounts.at(iter);
  }
  bankAccounts.clear();
}

//static definition of our static number for building account keys
int Bank::bankAccountKeys = 9999;

//returns the number of bank accounts in total
int const Bank::GetNumBankAccounts() {
  int numBankAccounts = bankAccounts.size();

  return numBankAccounts;
}

//returns number of saving accounts
int const Bank::GetNumSavingAccounts() {
  int returnVal = 0;
  for (auto iter : bankAccountList) {
    returnVal = returnVal + bankAccounts[iter]->GetSavingAccountNum();
  }
  return returnVal;
}

//returns number of checking accounts
int const Bank::GetNumCheckingAccounts() {
  int returnVal = 0;
  for (auto iter : bankAccountList) {
    returnVal = returnVal + bankAccounts[iter]->GetCheckingAccountNum();
  }

  return returnVal;
}

// get aggregate balance
int Bank::GetAggregateBalance() {
  vector<string> tempKeys;
  map<string, SubAccount*> tempSubs;
  int aggregateVal = 0;
  
  for (auto iter : bankAccountList) {
    //for each bank account
    
    //get subaccs
    tempSubs = bankAccounts.at(iter)->GetSubAccounts();
    //check each bank account's savings and checkings
    
      //start with savings
    tempKeys = bankAccounts.at(iter)->GetSubAccountKeys("savings");
    for (auto iter : tempKeys) {
      aggregateVal += tempSubs.at(iter)->GetBalance();
    }

      //then checkings
    tempKeys = bankAccounts.at(iter)->GetSubAccountKeys("checkings");
    for (auto iter : tempKeys) {
      aggregateVal += tempSubs.at(iter)->GetBalance();
    }
  }

  return aggregateVal;
}

//returns the static num for building a new key
int Bank::GetBankAccountKeys() {
  bankAccountKeys++;
  return bankAccountKeys;
}

//creates a new bank account, prompts user, then emplaces to map
void Bank::NewBankAccount() {
  string tempString = "";

  BankAccount *newBankAccount = new BankAccount();

  cout << "    Enter the first name of the account holder: " << flush;
  getline(cin, tempString);
  newBankAccount->SetFirst(tempString);

  cout << "    Enter the last name of the account holder: " << flush;
  getline(cin, tempString);
  newBankAccount->SetLast(tempString);

  cout << "    Enter the ssn of the account holder: " << flush;
  getline(cin, tempString);
  newBankAccount->SetSsn(tempString);

  tempString = "BNK" + to_string(GetBankAccountKeys());
  bankAccounts.emplace(tempString, newBankAccount);
  newBankAccount->SetAccNum(tempString);
  bankAccountList.push_back(tempString);
  cout << "    | Bank account created with key " << tempString << endl;
  // send user to bank account menu
  newBankAccount->BankAccountMenu();
}

//closes the bank account by removing it from map, then freeing up the data
void Bank::CloseBankAccount(string key) {
  BankAccount *tempBankAcc;
  // find the bank account to delete
  if (bankAccounts.count(key) == 1) {
    tempBankAcc = bankAccounts.at(key);
    bankAccounts.erase(key);
    delete tempBankAcc;
    vector<string> temp;
    for (int i = 0; i < bankAccountList.size(); i++) {
      if (bankAccountList.at(i) != key) {
        temp.push_back(bankAccountList.at(i));
      }
    }
    bankAccountList = temp;
    cout << "    | Account successfully deleted." << endl;
  } else {
    cout << "    | This bank account does not exist." << endl;
  }
}

//prompts user for key, finds account if it exists, then opens it
void Bank::ModifyBankAccount(string key) {
  if (bankAccounts.count(key) == 1) {
    // if it exists open menu
    bankAccounts.at(key)->BankAccountMenu();
  } else {
    cout << "Could not find bank account";
  }
}

void Bank::PrintBankInfo() {
  cout << endl;
  cout << "    | Bank Name : " << name << endl;
  cout << "    | Bank Address : " << address << endl;
  cout << "    | Bank Working Hours : " << workingHours << endl;
  cout << "    | Aggregated Balance : " << GetAggregateBalance() << endl;
  cout << "    | Consists of " << GetNumBankAccounts() << " bank-accounts" << endl << endl;
}

// detailed bank account info
void Bank::PrintDetailedInfo() {
  PrintBankInfo();

  for (auto iter : bankAccountList) {
    cout << endl;
    BankAccount *temp = bankAccounts.at(iter);
    cout << "    | Bank Account Number: " << temp->GetAccNum() << endl;
    cout << "    | Account holder Full Name: " << temp->GetFirst() << " " << temp->GetLast() << endl;
    cout << "    | Account holder SSN: " << temp->GetSsn() << endl;
    cout << "    | Aggregated Balance: " << temp->AggregateBalanceCalc();
    cout << "    | Consists of " << temp->GetSubAccounts().size() << " Sub-Accounts" << endl;
    temp->PrintDetailedSubInfo();
    cout << endl;
  }
}

//brief bank account info
void Bank::PrintBriefInfo() {
  PrintBankInfo();

  for ( auto iter : bankAccountList) {
    bankAccounts.at(iter)->PrintAggregatedBalances();
  }
  cout << endl;
}

//user option loop
void Bank::UserMenu() {
  string userString;
  char userInput;
  // bank menuing - looping til 'x' is chosen
  // init userinput
  cin >> userInput;

  // userinput loop
  while (toupper(userInput) != 'X') {
    switch (toupper(userInput)) {
    case 'A':
      // number of bankaccounts
      cout << "    | Number of Bank Accounts: " << GetNumBankAccounts() << endl;
      break;

    case 'S':
      // number of saving account
      cout << "    | Number of Saving Accounts: " << GetNumSavingAccounts() << endl;
      break;

    case 'H':
      // number of checking account
      cout << "    | Number of Checking Accounts: " << GetNumCheckingAccounts() << endl;
      break;

    case 'O':
      cin.ignore();
      NewBankAccount();
      // send user to bankaccount menu;
      break;

    case 'C':
      // close bank account
      cout << "Please input the key of the account you would like to delete: " << endl;
      cin >> userString;
      CloseBankAccount(userString);
      break;

    case 'M':
      // modify bank account
      cout << "Please input the key of the account you would like to modify: ";
      cin >> userString;
      ModifyBankAccount(userString);
      break;

    case 'D':
      // detailed bank account
      PrintDetailedInfo();
      break;

    case 'B':
      // brief bank accounts info sorted based on aggregate
      PrintBriefInfo();
      break;

    default:
      cout << "Error not valid character" << endl;
      break;
    }

    PrintBankMenu();
    cin >> userInput;
  }
  
  cout << "    | End of service for " << name << endl;
}

//print user input options, and then prompt user
void Bank::PrintBankMenu() {
  cout << endl << endl;
  cout << "|";
  cout << setfill('-') << setw(50) << "|" << endl;

  cout << "| Eligible services for " << name << endl;
  cout << "| A -- Number of Bank-Accounts" << endl;
  cout << "| S -- Number of Saving-Accounts" << endl;
  cout << "| H -- Number of Checking-Accounts" << endl;
  cout << "| O -- Open Bank-Account" << endl;
  cout << "| C -- Close Bank-Account" << endl;
  cout << "| M -- Modify Bank-Account" << endl;
  cout << "| D -- Detailed Bank-Account Info" << endl;
  cout << "| B -- Brief Bank-Account Info Based on Aggregate Balances" << endl;
  cout << "| X -- Exit" << endl;
  cout << "|";
  cout << setfill('-') << setw(50) << "|" << endl;
  cout << "Please enter your selection: ";
}
