#include <iostream>
#include <iomanip>
#include <vector>
#include "bankaccount.h"
using namespace std;

BankAccount::~BankAccount() {
  //clear all saving accounts and checking accounts associated
  for ( auto iter : savingAccountKeys) {
    delete subAccounts.at(iter);
  }

  for ( auto iter: checkingAccountKeys) {
    delete subAccounts.at(iter);
  }

  subAccounts.clear();
}

//prints the options menu for the user, and prompts user
void BankAccount::PrintMenu() {
  cout << endl << endl;
  cout << "|";
  cout << setfill('-') << setw(50) << "|" << endl;

  cout << "| Eligible services for Bank-Account " << accNum << endl;

  cout << "| S -- Open Saving Sub-Account" << endl;
  cout << "| C -- Open Checking Sub-Account" << endl;
  cout << "| M -- Modify a Sub-Account" << endl;
  cout << "| E -- Close a Sub-Account" << endl;
  cout << "| D -- Detailed Bank Account Info Sorted on Balances of Sub-Accounts"
       << endl;
  cout << "| B -- Brief Bank Account Info" << endl;
  cout << "| X -- Exit" << endl;
  cout << "|";
  cout << setfill('-') << setw(50) << "|" << endl;
  cout << "Please enter your selection: ";
}

//bank account constructor
BankAccount::BankAccount() {
  first = "Jonesy";
  last = "Fortnite";
  ssn = "xxx-xx-xxx";
}

//returns number of saving accounts
int const BankAccount::GetSavingAccountNum() {
  int numSaving = 0;
  for (auto iter : savingAccountKeys) {
    numSaving++;
  }

  return numSaving;
}

//returns number of checking accounts
int const BankAccount::GetCheckingAccountNum() {
  int numChecking = 0;
  for (auto iter : checkingAccountKeys) {
    numChecking++;
  }

  return numChecking;
}

//calculate the aggregate balance;
int BankAccount::AggregateBalanceCalc() {
  int aggregateBalance = 0;
      
      vector<SubAccount*> allSubAccounts;
      //put into one vect (saving accounts
      for (auto iter : savingAccountKeys) {
        allSubAccounts.push_back(subAccounts[iter]);
      }
  
      //put into one vect (checking accounts
      for (auto iter : checkingAccountKeys) {
        allSubAccounts.push_back(subAccounts.at(iter));
      }

      for (auto iter : allSubAccounts) {
        aggregateBalance += iter->GetBalance();
      }
  
  return aggregateBalance;
}

//returns the aggreagte value of the current bank account (breif info)
void BankAccount::PrintAggregatedBalances() {
  int aggregateBalance = AggregateBalanceCalc();

      cout << "    | Aggregated Balance of the bank account : " << accNum << " with " << subAccounts.size() << " sub-accounts is " << aggregateBalance << endl;
}

//print the detailed sub account info
void BankAccount::PrintDetailedSubInfo() {
  vector<SubAccount*> allSubAccounts;
      
      //put into one vect (saving accounts
      for (auto iter : savingAccountKeys) {
        allSubAccounts.push_back(subAccounts[iter]);
      }
      //put into one vect (checking accounts
      for (auto iter: checkingAccountKeys) {
        allSubAccounts.push_back(subAccounts.at(iter));
      }

      //insertion sort here
      InsertionSortSub(allSubAccounts);

      cout << endl;
      
      for (auto iter : allSubAccounts) {
        iter->PrintSubAccount();
        cout << endl;
      }
}

//insertion sort fr all of the sub accounts
void BankAccount::InsertionSortSub(vector<SubAccount*> &vect) {
  int i = 0;
  int j = 0;
  SubAccount *temp;

  for (i = 1; i < vect.size(); i++) {
    j = i;
    //insert subaccounts[i] into sorted part
    //stopping once subaccounts[i] in correct position
    while (j > 0 && vect.at(j)->GetBalance() > vect.at(j - 1)->GetBalance()) {

      //swap subaccounts[j] and subaccounts[j-1]
      temp = vect.at(j);
      vect.at(j) = vect.at(j - 1);
      vect.at(j - 1) = temp;
      j--;
    }
  }
}

//creates a new saving accounts and emplaces it to our map
void BankAccount::NewSavingAccount() {
  int userAmount;
  SavingAccount *newSavingAccount;
  string accNum;

  // open saving subaccount
  cout << "    Enter initial amount: ";
  cin >> userAmount;
  
  accNum = "SAV" + to_string(newSavingAccount->GetSavingAccountKeys());

  newSavingAccount = new SavingAccount(userAmount, accNum);

  if (subAccounts.size() < 1) {
    newSavingAccount->SetBalance(userAmount + 100);
  }
  
  subAccounts.emplace(accNum, newSavingAccount);
  savingAccountKeys.push_back(accNum);

  cout << "    | A new saving sub-account " << newSavingAccount->GetAccNum() << " was successfully created." << endl;
}

//creates a new checking account and emplaces it to our map
void BankAccount::NewCheckingAccount() {
  char userInput;
  int userAmount;
  int maxCap;
  bool lock;
  string accNum;
  
  CheckingAccount *newCheckingAccount;

  cout << "    Enter the initial balance: ";
  cin >> userAmount;

  cout << "    Enter the desired maximum capacity: ";
  cin >> maxCap;

  cout << "    Define initial state: (L - Locked, Otherwise - Unlocked): ";
  cin >> userInput;

  if (toupper(userInput) == 'L') {
    lock = true;
  } else {
    lock = false;
  }

  accNum = "CHK" + to_string(newCheckingAccount->GetCheckingAccountKeys());

  newCheckingAccount = new CheckingAccount(userAmount, accNum, lock, maxCap);

  subAccounts.emplace(accNum, newCheckingAccount);
  checkingAccountKeys.push_back(accNum);

  cout << "    | A new checking sub-account " << newCheckingAccount->GetAccNum() << " was successfully created." << endl;
}

//takes a string for the key of the sub account, and then opens the menu to edit the sub account.
void BankAccount::ModifySubAccount(string key) {
  if (subAccounts.count(key) == 1) {
    subAccounts.at(key)->SubAccountMenu();
  } else {
    cout << "    | This sub-account does not exist" << endl;
  }
}

//closes the sub account, deletes the data, and removes it from the map
void BankAccount::CloseSubAccount(string key) {
  SubAccount *tempSub;
  if (subAccounts.count(key) == 1) {
    tempSub = subAccounts.at(key);
    subAccounts.erase(key);
    delete tempSub;
    vector<string> temp;
    for (int i = 0 ; i < savingAccountKeys.size(); i++) {
      if (savingAccountKeys.at(i) != key) {
        temp.push_back(savingAccountKeys.at(i));
      } 
    }
    savingAccountKeys = temp;
    temp.clear();
    for (int i = 0; i < checkingAccountKeys.size(); i++) {
      if (checkingAccountKeys.at(i) != key) {
        temp.push_back(checkingAccountKeys.at(i));
      }
    }
    checkingAccountKeys = temp;
    cout << "    | Sub-Account " << key << " was successfuly closed." << endl;
  } else {
    cout << "    | This sub-account does not exist" << endl;
  }
}

//prints and loops user input until user decides to cancel
void BankAccount::BankAccountMenu() {
  char userInput;
  string userString;
  BankAccount::PrintMenu();
  cin >> userInput;

  while (toupper(userInput) != 'X') {
    switch (toupper(userInput)) {
    case 'S':
      NewSavingAccount();
      break;

    case 'C':
      // open checking subaccount
      NewCheckingAccount();
      break;

    case 'M':
      // modify a subaccount
      cout << "    Enter the sub-account number to modify: ";
      cin >> userString;
      ModifySubAccount(userString);
      break;

    case 'E':
      // close a subaccount
      cout << "    Enter the sub-account number to close: ";
      cin >> userString;
      CloseSubAccount(userString);
      break;

    case 'D' : {
      // detailed bank account info sorted based on balance
      PrintDetailedSubInfo();
      break;
    }

    case 'B': {
      // brief bank account info
      PrintAggregatedBalances();
      break;
    }

    default:
      cout << "Error not valid character" << endl;
      break;
    
    }

    PrintMenu();
    cin >> userInput;
  }
  
  cout << endl << "    | End of service for bank-account " << GetAccNum() << endl;
}
