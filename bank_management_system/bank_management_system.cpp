#include "Header.h";
using namespace std;

//***************************************************************
//    	function declaration
//****************************************************************
void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void modify_account(int);	//function to modify record of file
void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();	//introductory screen function

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************


int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout << "\n\n\n\tMAIN MENU";
		cout << "\n\n\t1. CREATE NEW ACCOUNT";
		cout << "\n\n\t2. DEPOSIT AMOUNT";
		cout << "\n\n\t3. WITHDRAW AMOUNT";
		cout << "\n\n\t4. BALANCE ENQUIRY";
		cout << "\n\n\t5. DISPLAY ALL ACCOUNT HOLDERS";
		cout << "\n\n\t6. CLOSE AN ACCOUNT";
		cout << "\n\n\t7. MODIFY AN ACCOUNT'S NAME AND TYPE";
		cout << "\n\n\t8. EXIT";
		cout << "\n\n\tSelect One Option From 1-8: ";

		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			delete_account(num);
			break;
		case '7':
			cout << "\n\n\tEnter The account No. : "; cin >> num;
			modify_account(num);
			break;
		case '8':
			cout << "\n\n\tThanks for using my bank managemnt system\n\n";
			break;
		default:cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != '8');

	system("pause");
	return 0;
}


//***************************************************************
//    	FUNCTION TO CREATE ACCOUNT RECORD
//****************************************************************

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat", ios::binary | ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
	outFile.close();
}


//***************************************************************
//    	FUNCTION TO DISPLAY ACCOUNT DETAILS
//****************************************************************

void display_sp(int n)
{
	account ac;
	bool flag = false;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\nBALANCE DETAILS\n";

	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.getAccNum() == n)
		{
			ac.show_account();
			flag = true;
		}
	}
	inFile.close();
	if (flag == false)
		cout << "\n\n [ERROR] Account number does not exist";
}


//***************************************************************
//    	FUNCTION TO MODIFY ACCOUNT DETAILS
//****************************************************************

void modify_account(int n)
{
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.getAccNum() == n)
		{
			ac.show_account();
			cout << "\n\nEnter The New Details of account" << endl;
			ac.modify();
			int pos = (-1) * static_cast<int>(sizeof(account));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n [ERROR] Account Not Found ";
}


//***************************************************************
//    	FUNCTION TO DELETE ACCOUNT RECORD
//****************************************************************


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "[ERROR] File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat", ios::binary);
	inFile.seekg(0, ios::beg);
	bool notAcc = true;
	while (inFile.read(reinterpret_cast<char*> (&ac), sizeof(account)))
	{
		if (ac.getAccNum() != n)
		{
			outFile.write(reinterpret_cast<char*> (&ac), sizeof(account));
		}
		else { notAcc = false; }
	}
	if (notAcc) {
		cout << "\n\n\t [ERROR] Account Does Not Exist!";
		return;
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	int newName = rename("Temp.dat", "account.dat");
	cout << "\n\n\t [SUCCESS] Account Deleted Successfully ..";
}

//***************************************************************
//    	FUNCTION TO DISPLAY ALL ACCOUNTS
//****************************************************************

void display_all()
{
	account acc;
	ifstream inFile;
	inFile.open("account.dat", ios::binary);
	if (!inFile)
	{
		cout << "[ERROR] File could not be open !! Press any Key...";
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << "====================================================\n";
	cout << "A/c no.      NAME           Type  Balance\n";
	cout << "====================================================\n";
	while (inFile.read(reinterpret_cast<char*> (&acc), sizeof(account)))
	{
		acc.report();
	}
	inFile.close();
}

//***************************************************************
//    	FUNCTION HANDLING DEPOSITS AND WITHDRAWALS
//****************************************************************

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary | ios::in | ios::out);
	if (!File)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char*> (&ac), sizeof(account));
		if (ac.getAccNum() == n)
		{
			ac.show_account();
			if (option == 1)
			{
				cout << "\n\n\tTO DEPOSIT AMOUNT ";
				cout << "\n\nEnter The amount to be deposited: ";
				cin >> amt;
				ac.depositAmt(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tTO WITHDRAW AMOUNT ";
				cout << "\n\nEnter The amount to be withdrawn: ";
				cin >> amt;
				int bal = ac.getDeposit() - amt;

				// allow withdrawal only if remianing balance will be at least 500
				// for Savings account and 1000 for Current account.
				if ((bal < 500 && ac.getAccType() == 'S') || (bal < 1000 && ac.getAccType() == 'C'))
					cout << "Insufficient balance";
				else
					ac.draw(amt);
			}
			int pos = (-1) * static_cast<int>(sizeof(ac));
			File.seekp(pos, ios::cur);
			File.write(reinterpret_cast<char*> (&ac), sizeof(account));
			cout << "\n\n\t Account Updated";
			found = true;
		}
	}
	File.close();
	if (found == false)
		cout << "\n\n [ERROR] Account Not Found. Please Try again.";
}


//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************


void intro()
{
	cout << "\n\n\n\t   BANK";
	cout << "\n\n\tMANAGEMENT";
	cout << "\n\n\t  SYSTEM";
	cout << "\n\n\n\n BY : Glory Adedayo";
	cout << "\n\nSCHOOL : Alcorn State University\n\n";
	//cin.get();
	system("pause");
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************