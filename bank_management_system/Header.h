#pragma once
//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************
#ifndef bankAccount
#define bankAccount

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<vector>
using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();	//function to get data from user
	void show_account() const;	//function to show data on screen
	void modify();	//function to add new data
	void depositAmt(int);	//function to accept amount and add to balance amount
	void draw(int);	//function to accept amount and subtract from balance amount
	void report() const;	//function to show data in tabular format
	int getAccNum() const;	//function to return account number
	int getDeposit() const;	//function to return balance amount
	char getAccType() const;	//function to return type of account
};         //class ends here

void account::create_account()
{
	cout << "\nEnter The account No. :";
	cin >> acno;
	cout << "\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nEnter Type of The account (C/S) : ";
	cin >> type;
	type = toupper(type);
	cout << "\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin >> deposit;
	cout << "\n\n\n  [SUCCESS] Account Created Successfully..";
}

void account::show_account() const
{
	cout << "\nAccount No. : " << acno;
	cout << "\nAccount Holder Name : ";
	cout << name;
	cout << "\nType of Account : " << type;
	cout << "\nBalance amount : " << deposit;
}


void account::modify()
{
	cout << "\nAccount No. : " << acno;
	cout << "\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nModify Type of Account : ";
	cin >> type;		// type => 'S' or 'C'
	type = toupper(type);
	//cout << "\nModify Balance amount : ";
	//cin >> deposit;
}


void account::depositAmt(int x)
{
	deposit += x;
}

void account::draw(int x)
{
	deposit -= x;
}

void account::report() const
{
	cout << acno << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}


int account::getAccNum() const
{
	return acno;
}

int account::getDeposit() const
{
	return deposit;
}

char account::getAccType() const
{
	return type;
}

#endif // !bankAccount