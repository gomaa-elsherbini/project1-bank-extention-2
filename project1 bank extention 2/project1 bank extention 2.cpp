#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;



enum enChoice { Show = 1, Add, Delete, Update, Find, Transactions, Users, LogOut};
enum enTransaction { Deposit = 1, Withdraw, TatalBalances };
enum enUserOption { showUser = 1, AddUser, DeleteUser, UpdateUser, FindUser};

struct stPermission
{
	bool ToShowClient = false;
	bool ToAddClient = false;
	bool ToUpdateClient = false;
	bool ToDeleteClient = false;
	bool ToFindClient = false;
	bool ToTransaction = false;
	bool ToManageUsers = false;
};
struct stClient
{
	string Number;
	string pinCode;
	string name;
	string phone;
	double balance;
	bool markToDelete = false;
};
struct stUser
{
	string name;
	string password;
	short permissions;
	//stPermission validation;
	bool markToDelete = false;
	/*short ShowClient;
	short AddClient;
	short UpdateClient;
	short DeleteClient;
	short FindClient;
	short Transactions;
	short ManageUsers;*/
};
char readAnswer(string msg)
{
	char answer;

	cout << msg;
	cin >> answer;

	return answer;

}
stUser readUser(string userName)
{
	
	stUser user;
	char answer;
	
	short ShowClient   = 0;     
	short AddClient    = 0;      
	short UpdateClient = 0;   
	short DeleteClient = 0;   
	short FindClient   = 0;     
	short Transactions = 0;   
	short ManageUsers  = 0;    
	
	user.permissions = 0;

	//user.permissionsTo.ShowClient = 0;
	//user.permissionsTo.AddClient = 0;
	//user.permissionsTo.UpdateClient = 0;
	//user.permissionsTo.DeleteClient = 0;
	//user.permissionsTo.FindClient = 0;
	//user.permissionsTo.Transactions = 0;
	//user.permissionsTo.ManageUsers = 0;

	user.name = userName;

	cout << "Enter User Password? ";
	cin >> user.password;

	answer = readAnswer("\nDo you want to give full access? y/n");
	if (answer == 'y' || answer == 'Y')
	{
		user.permissions = -1;
		return user;
	}

	cout << "\nDo you want to give access to: \n";
	
	answer = readAnswer("\nShow Client List? y/n ");
	if (answer == 'y' || answer == 'Y')
	{
		//user.validation.ToShowClient = true;
		ShowClient = 1;
	}

	answer = readAnswer("\nAdd Client? y/n ");
	if (answer == 'y' || answer == 'Y')
	{
		//user.validation.ToAddClient = true;
		AddClient = 2;
	}

	answer = readAnswer("\nUpdate Client? y/n ");
	if (answer == 'y' || answer == 'Y')
	{
		//user.validation.ToUpdateClient = true;
		UpdateClient = 4;
	}

	answer = readAnswer("\nDelete Client? y/n ");
	if (answer == 'y' || answer == 'Y')
	{
		//user.validation.ToDeleteClient = true; 
		DeleteClient = 8;
	}

	answer = readAnswer("\nFind Client? y/n ");
	if (answer == 'y' || answer == 'Y')
	{
		//user.validation.ToFindClient = true; 
		FindClient = 16;
	}

	answer = readAnswer("\nTransactions? y/n ");
	if (answer == 'y' || answer == 'Y')
	{
		//user.validation.ToTransaction = true; 
		Transactions = 32;
	}
	
	answer = readAnswer("\nManage Users? y/n ");
	if (answer == 'y' || answer == 'Y')
	{
		//user.validation.ToManageUsers = true; 
		ManageUsers = 64;
	}

	user.permissions = ShowClient | AddClient |UpdateClient |
					  DeleteClient | FindClient | Transactions | ManageUsers;
					  
	return user;
}
stClient readClient(string AccountNumber)
{
	stClient client;

	client.Number = AccountNumber;

	cout << "\nEnter PinCode? ";
	cin >> client.pinCode;

	cout << "Enter Name? ";
	getline(cin >> ws, client.name);

	cout << "Enter Phone ";
	cin >> client.phone;

	cout << "Enter Account balance ";
	cin >> client.balance;

	return client;
}
string readAccountNumber(string msg)
{
	string AccountNumber = "";

	cout << msg;
	cin >> AccountNumber;

	return AccountNumber;
}
string readUserPassword(string msg)
{
	string userPassword;
	
	cout << msg;
	cin >> userPassword;

	return userPassword;
}
string readUserName(string msg)
{
	string userName;
	
	cout << msg;
	cin >> userName;

	return userName;
}
enChoice readOperationChoice(string msg)
{
	enChoice taskNum;
	int choice;
	cout << msg;
	cin >> choice;

	taskNum = (enChoice)choice;

	return taskNum;
}
enTransaction transactionChoice(string msg)
{
	int choice;

	cout << msg;
	cin >> choice;

	return (enTransaction)choice;
}
enUserOption readUserOption(string msg)
{
	int choice;

	cout << msg;
	cin >> choice;

	return (enUserOption)choice;
}

void showTaskTitle(string TaskTitle)
{
	cout << "\n----------------------------------\n";
	cout << "           " << TaskTitle << "          \n";
	cout << "----------------------------------\n";
}
void MainMenuScreen()
{
	cout << "\n==============================================================\n";
	cout << "                     Main Menu Screen                             ";
	cout << "\n==============================================================\n";
	cout << "                     [1] Show Client List.                      \n";
	cout << "                     [2] Add New Client.                        \n";
	cout << "                     [3] Delete Client.                         \n";
	cout << "                     [4] Update Client.                         \n";
	cout << "                     [5] Find Client.                           \n";
	cout << "                     [6] Transactions.                          \n";
	cout << "                     [7] Manage Users.                          \n";
	cout << "                     [8] Logout.                                \n";
	cout << "==============================================================\n";
}

stClient VectorDataToStClient(vector <string> vClient)
{
	stClient client;

	client.Number = vClient[0];
	client.pinCode = vClient[1];
	client.name = vClient[2];
	client.phone = vClient[3];
	client.balance = stod(vClient[4]);

	return client;
}
stUser VectorDataToStUser(vector <string> vStrUser)
{
	stUser user;

	user.name = vStrUser[0];
	user.password = vStrUser[1];
	user.permissions = stoi(vStrUser[2]);

	return user;
}
vector <string> LineDataToVector(string line)
{//A150#//#1234#//#Gomaa ElSherbini#//#00925365232#//#5000.000000

	vector <string> vClient;
	string delim = "#//#";
	short pos = 0;
	string clientItem = "";

	while ((pos = line.find(delim)) != -1)
	{
		clientItem = line.substr(0, pos);
		if (clientItem != "")
		{
			vClient.push_back(clientItem);
		}
		line.erase(0, pos + delim.length());
	}
	if (line != "")
	{
		vClient.push_back(line);
	}
	return vClient;
}
vector <string> LineDataToUserVector(string line)
{//line=>      Admin#//#1234#//#-1

	vector <string> vStrUser;
	string delim = "#//#";
	short pos = 0;
	string userItem = "";

	while ((pos = line.find(delim)) != -1)
	{
		userItem = line.substr(0, pos);

		if (userItem != "")
			vStrUser.push_back(userItem);

		line.erase(0, pos + delim.length());
	}

	if (line != "")
		vStrUser.push_back(line);
	
	return vStrUser;
}
vector <stClient> loadDataToVector(string fileName)
{
	fstream ClientsFile;
	string line;
	vector <stClient> vStClients;

	ClientsFile.open(fileName, ios::in);

	if (ClientsFile.is_open())
	{
		while (getline(ClientsFile, line))
		{
			if (line != "")
			{
				vStClients.push_back(VectorDataToStClient(LineDataToVector(line)));
			}
		}
		ClientsFile.close();
	}
	return vStClients;
}
vector <stUser> loadUserDataToVector(string fileName)
{
	fstream UsersFile;
	string line;
	vector <stUser> vStUsers;

	UsersFile.open(fileName, ios::in);

	if (UsersFile.is_open())
	{
		while (getline(UsersFile, line))
		{
			if (line != "")
				vStUsers.push_back(VectorDataToStUser(LineDataToUserVector(line)));
		}
		UsersFile.close();
	}
	return vStUsers;
}

string convertStUserToStringLine(stUser userRecord)
{
	string recordDataLine;
	string delim = "#//#";

	recordDataLine = userRecord.name;
	recordDataLine += delim + userRecord.password;
	recordDataLine += delim + to_string(userRecord.permissions);

	return recordDataLine;
}
string convertStAccountToStringLine(stClient clientRecord)
{
	string recordAataLine;
	string delim = "#//#";

	recordAataLine = clientRecord.Number;
	recordAataLine += delim + clientRecord.pinCode;
	recordAataLine += delim + clientRecord.name;
	recordAataLine += delim + clientRecord.phone;
	recordAataLine += delim + to_string(clientRecord.balance);

	return recordAataLine;
}

void accessDenied()
{
	system("cls");
	cout << "\n----------------------------------------\n";
	cout << "Access Denied!\n";
	cout << "You Do not have permission to Do this\n";
	cout << "Please contact your admin\n";
	cout << "----------------------------------------\n";
	system("pause");
}
stPermission validateToDoTask(stUser user)
{
	stPermission validation;

	if (user.permissions >= 64)//permissions= 63
	{
		validation.ToManageUsers = true;
		user.permissions -= 64;
	}

	if (user.permissions >= 32)//permissions= 31
	{
		validation.ToTransaction = true;
		user.permissions -= 32;
	}


	if (user.permissions >= 16)//permissions= 15
	{
		validation.ToFindClient = true;
		user.permissions -= 16;
	}


	if (user.permissions >= 8)//permissions= 7
	{
		validation.ToDeleteClient = true;
		user.permissions -= 8;
	}


	if (user.permissions >= 4)//permissions= 3
	{
		validation.ToUpdateClient = true;
		user.permissions -= 4;
	}


	if (user.permissions >= 2)//permissions= 1
	{
		validation.ToAddClient = true;
		user.permissions -= 2;
	}

	if (user.permissions >= 1)//permissions= 0
	{
		validation.ToShowClient = true;
		user.permissions -= 1;
	}

	if (user.permissions == -1)//permissions= 0
	{
		validation.ToShowClient = true;
		validation.ToAddClient = true;
		validation.ToUpdateClient = true;
		validation.ToDeleteClient = true;
		validation.ToFindClient = true;
		validation.ToTransaction = true;
		validation.ToManageUsers = true;
	}
	return validation;
}
void printStUsertData(stUser user)
{
	cout << "The Following are the User details:\n";
	cout << "------------------------------------------\n";
	cout << "UserName    : " << user.name << "\n";
	cout << "Password    : " << user.password << "\n";
	cout << "Permissions : " << user.permissions << "\n";
	cout << "------------------------------------------\n\n\n";
}
void printStClientData(stClient client)
{
	system("cls");
	cout << "\nThe following are the eclient details:\n\n";
	cout << "------------------------------------------------------\n";
	cout << " Account Number       :  " << client.Number << endl;
	cout << " Pin Code             :  " << client.pinCode << endl;
	cout << " Name                 :  " << client.name << endl;
	cout << " Phone                :  " << client.phone << endl;
	cout << " Balance              :  " << client.balance << endl;
	cout << "------------------------------------------------------\n";
}

bool findAUserWithUserName(vector <stUser>& vStUsers, string userName, stUser& userToFind)
{
	for (stUser& user : vStUsers)
	{
		if (user.name == userName)
		{
			userToFind = user;
			return 1;
		}
	}
	return 0;
}
bool findAccountWithAccountNumber(vector <stClient>& vStClients, string AccountNumber, stClient& clientToFind)
{
	for (stClient& client : vStClients)
	{
		if (client.Number == AccountNumber)
		{
			clientToFind = client;
			return 1;
		}
	}
	return 0;
}

void findAccount(stUser user, vector <stClient>& vStClients, string fileName)
{
	stPermission validate = validateToDoTask(user);

	if (validate.ToFindClient)
	{
		system("cls");
		showTaskTitle("Find Client Screen");

		vStClients = loadDataToVector(fileName);
		string AccountNumber = readAccountNumber("\n Please Enter Account Number? ");
		stClient clientToFind;

		if (findAccountWithAccountNumber(vStClients, AccountNumber, clientToFind))
			printStClientData(clientToFind);
		else
			cout << "\n\n Client with account Number (" << AccountNumber << ") Not Found!\n";

		system("pause");
	}
	else
		accessDenied();
}

void updateClient(vector <stClient>& vStClients, string AccountNumber)
{
	stClient updatedClient = readClient(AccountNumber);

	for (stClient& client : vStClients)
	{
		if (client.Number == AccountNumber)
		{
			client = updatedClient;
			break;
		}
	}
}
void updateUser(vector <stUser> &vStUsers, string userName)
{
	stUser updatedUser = readUser(userName);

	for (stUser& user : vStUsers)
	{
		if (user.name == userName)
		{
			user = updatedUser;
			break;
		}
	}
}

void markAccountToDelete(vector <stClient>& vStClients, string AccountNumber)
{
	for (stClient& client : vStClients)
	{
		if (client.Number == AccountNumber)
		{
			client.markToDelete = 1;
			break;
		}
	}
}
void markUserToDelete(vector <stUser> &vStUsers, string userName)
{
	for (stUser& user : vStUsers)
	{
		if (user.name == userName)
		{
			user.markToDelete = 1;
			break;
		}
	}
}
void saveUsersToFile(string fileName, vector <stUser> vStUsers)
{
	fstream myFile;

	myFile.open(fileName, ios::out);

	if (myFile.is_open())
	{
		for (stUser& user : vStUsers)
		{
			if (user.markToDelete != 1)
				myFile << convertStUserToStringLine(user) << "\n";
		}
		myFile.close();
	}
}
void saveAccountsToFile(string fileName, vector <stClient> vStClients)
{
	fstream myFile;

	myFile.open(fileName, ios::out);

	if (myFile.is_open())
	{
		for (stClient& client : vStClients)
		{
			if (client.markToDelete != 1)
				myFile << convertStAccountToStringLine(client) << "\n";
		}
		myFile.close();
	}
}

void showClientList(stUser user, vector <stClient>& vStClients)
{
	system("cls");

	stPermission validate = validateToDoTask(user);

	if (validate.ToShowClient==true)
	{
		cout << endl;
		cout << "                                         Client List (" << vStClients.size() << ") Client(s)\n";
		cout << " ___________________________________________________________________________________________________________________\n";
		cout << endl;
		cout << " |" << " Account Number " << "|" << " Pin Code " << "|" << " Client Name " << setw(35) << "|" << " Phone " << setw(12) << "|" << " Balance " << setw(10) << "|" << endl;
		cout << " ___________________________________________________________________________________________________________________\n";
		cout << endl;

		for (stClient& line : vStClients)
		{
			cout << "| " << setw(15) << left << line.Number
				 << "| " << setw(9) << left << line.pinCode
				 << "| " << setw(46) << left << line.name
				 << "| " << setw(17) << left << line.phone
				 << "| " << setw(17) << left << line.balance
				 << "|";

			cout << endl;
		}
		cout << " ___________________________________________________________________________________________________________________\n";

		cout << "\nPress any key to go back to main menu screen... ";
		system("pause");
	}
	else
		accessDenied();
}
void addNewClient(stUser user, string fileName, vector <stClient>& vStClients)
{
	char answer = 'y';
	stClient client;     // 1  2  4  8  16  32  64 
	string AccountNumber;// 2  3  6  10  18 34  66 7 15 29 51

	stPermission validate = validateToDoTask(user);

	if (validate.ToAddClient)
	{
		while (answer == 'y' || answer == 'Y')
		{
			system("cls");

			showTaskTitle("Add New Client Screen");
			cout << "Adding New Client:\n";

			AccountNumber = readAccountNumber("\n Please Enter Account Number? ");

			while (findAccountWithAccountNumber(vStClients, AccountNumber, client))
			{
				cout << "\nClient with [" << AccountNumber << "] aready exists, ";
				AccountNumber = readAccountNumber("Enter another account number? ");
			}

			client = readClient(AccountNumber);
			vStClients.push_back(client);
			saveAccountsToFile(fileName, vStClients);

			cout << "\n\nClient added successfully,";
			answer = readAnswer("\ndo you want to add more clients? Y/N ");
		}
		system("pause");
	}
	else
		accessDenied();
}
void updateAccount(stUser user, vector <stClient>& vStClients, string fileName)
{
	stPermission validate = validateToDoTask(user);

	if (validate.ToUpdateClient)
	{
		system("cls");
		showTaskTitle("Update Client Screen:");
	
		char answer;
		stClient client;
		string AccountNumber = readAccountNumber("\n Please Enter Account Number? ");

		if (findAccountWithAccountNumber(vStClients, AccountNumber, client))
		{
			printStClientData(client);

			answer = readAnswer("\nAre You sure to update This Account? y/n ");

			if (answer == 'y' || answer == 'Y')
			{
				updateClient(vStClients, AccountNumber);
				saveAccountsToFile(fileName, vStClients);
				cout << "\n\nClient uodated Successfully!\n";
			}
		}
		else
		{
			cout << "\n\n Client with account Number (" << AccountNumber << ") Not Found!\n";
		}
		system("pause");
	}
	else
		accessDenied();
}
void deleteAccount(stUser user, vector <stClient>& vStClients, string fileName)
{
	stPermission validate = validateToDoTask(user);

	if (validate.ToDeleteClient)
	{
		system("cls");

		showTaskTitle("Delete Client Screen");

		char answer;
		stClient client;
		string AccountNumber = readAccountNumber("\n Please Enter Account Number? ");

		if (findAccountWithAccountNumber(vStClients, AccountNumber, client))
		{
			printStClientData(client);

			answer = readAnswer("\nAre you sure do you want to delete This Client? Y/N ");

			if (answer == 'y' || answer == 'Y')
			{
				markAccountToDelete(vStClients, AccountNumber);
				saveAccountsToFile(fileName, vStClients);
				cout << "\n\nClient deleted Successfully!\n";
			}
		}
		else
			cout << "\n\n Client with account Number (" << AccountNumber << ") Not Found!\n";
	
		system("pause");
	}
	else
		accessDenied();
}

void TransactionsMenuScreen()
{
	cout << "\n==============================================================\n";
	cout << "                     Main Menu Screen                             ";
	cout << "\n==============================================================\n";
	cout << "                     [1] Deposit.                               \n";
	cout << "                     [2] Withdraw.                              \n";
	cout << "                     [3] Total Balances.                        \n";
	cout << "                     [4] Main menu.                             \n";
	cout << "==============================================================\n";
}

void depositToAccountBalance(vector <stClient>& vStClients, string AccountNumber, int depositAmmount)
{
	for (stClient& client : vStClients)
	{
		if (client.Number == AccountNumber)
		{
			client.balance += depositAmmount;
		}
	}
}

void depositTransaction(vector <stClient>& vStClients, string fileName)
{
	system("cls");
	showTaskTitle("Deposit Screen");

	int depositAmmount = 0;
	stClient client;
	string AccountNumber = readAccountNumber("\nPlease enter Account number? ");
	char answer;

	if (findAccountWithAccountNumber(vStClients, AccountNumber, client))
	{
		printStClientData(client);

		cout << "\nPlease enter deposit ammount? ";
		cin >> depositAmmount;

		answer = readAnswer("\nAre you sure you want to perform this transaction? y/n ? ");

		if (answer == 'y' || answer == 'Y')
		{
			depositToAccountBalance(vStClients, AccountNumber, depositAmmount);
			saveAccountsToFile(fileName, vStClients);
			cout << "\nDone successfully, New Balance is: " << client.balance + depositAmmount << endl;

		}
	}
	else
	{
		cout << "\n\n Client with account Number (" << AccountNumber << ") Not Found!\n\n";
	}
	system("pause");
}

int calculateSumOfNumbers(vector <stClient>& vStClients)
{
	int sumOfBalances = 0;

	for (stClient& client : vStClients)
	{
		sumOfBalances += client.balance;
	}
	return sumOfBalances;
}

void showBalancesList(vector <stClient>& vStClients, string fileName)
{
	int totalBalances = 0;

	system("cls");

	cout << endl;
	cout << "                                         Balances List (" << vStClients.size() << ") Client(s)\n";
	cout << " ___________________________________________________________________________________________________________________\n";
	cout << endl;
	cout << " |" << " Account Number " << " |" << " Client Name " << setw(36) << " |" << " Balance " << setw(10) << endl;
	cout << " ___________________________________________________________________________________________________________________\n";
	cout << endl;

	for (stClient& line : vStClients)
	{
		cout << " | " << setw(15) << left << line.Number
			<< " | " << setw(46) << left << line.name
			<< " | " << setw(17) << left << line.balance;
		cout << endl;
	}
	cout << " ___________________________________________________________________________________________________________________\n";

	cout << "                                             Total Balances = " << calculateSumOfNumbers(vStClients) << endl;

	cout << "\nPress any key to go back to transactions menu screen... ";
	system("pause");
}

void withdrawToAccountBalance(vector <stClient>& vStClients, string AccountNumber, int WithdrawAmmount)
{
	for (stClient& client : vStClients)
	{
		if (client.Number == AccountNumber)
		{
			client.balance -= WithdrawAmmount;
		}
	}
}

void WithdrawTransaction(vector <stClient>& vStClients, string fileName)
{
	system("cls");
	showTaskTitle("Withdraw Screen");

	int WithdrawAmmount = 0;
	stClient client;
	string AccountNumber = readAccountNumber("\nPlease enter Account number? ");
	char answer;

	if (findAccountWithAccountNumber(vStClients, AccountNumber, client))
	{
		printStClientData(client);

		cout << "\nPlease enter withdraw ammount? ";
		cin >> WithdrawAmmount;

		while (WithdrawAmmount > client.balance)
		{
			cout << "\n\nAmount Exceeds the balance, you can withdraw up to : " << client.balance << endl;

			cout << "\nPlease enter another withdraw ammount? ";
			cin >> WithdrawAmmount;
		}

		answer = readAnswer("\nAre you sure you want to perform this transaction? y/n ? ");

		if (answer == 'y' || answer == 'Y')
		{
			withdrawToAccountBalance(vStClients, AccountNumber, WithdrawAmmount);
			saveAccountsToFile(fileName, vStClients);

			cout << "\nDone successfully, New Balance is: " << client.balance - WithdrawAmmount << endl;
		}
	}
	else
	{
		cout << "\n\n Client with account Number (" << AccountNumber << ") Not Found!\n\n";
	}
	system("pause");
}

void transactionProccess(enTransaction transaction, vector <stClient> vStClients, string fileName)
{
	vStClients = loadDataToVector(fileName);

	switch (transaction)
	{
	case Deposit:
		depositTransaction(vStClients, fileName);
		break;
	case Withdraw:
		WithdrawTransaction(vStClients, fileName);
		break;
	case TatalBalances:
		showBalancesList(vStClients, fileName);
		break;
	}
}

void startTransactions(stUser user, vector <stClient>& vStClients, string fileName)
{
	enTransaction transaction;
	stPermission validate = validateToDoTask(user);
	
	if (validate.ToTransaction) {

		do
		{
			system("cls");
			TransactionsMenuScreen();
			transaction = transactionChoice("\nChoose what do you want to do from [1 to 4]? ");
			transactionProccess(transaction, vStClients, fileName);

		} while (transaction != 4);
	}
	else
		accessDenied();
}

void ManageUsersMenuScreen()
{
	cout << "\n==============================================================\n";
	cout << "                     Manage Users Menu Screen                             ";
	cout << "\n==============================================================\n";
	cout << "                     [1] List Users.                            \n";
	cout << "                     [2] Add New User.                          \n";
	cout << "                     [3] Delete User.                           \n";
	cout << "                     [4] Update User.                           \n";
	cout << "                     [5] Find User.                             \n";
	cout << "                     [6] Main Menu.                             \n";
	cout << "==============================================================\n";
}

void showUsersList(stUser user ,vector <stUser> &vStUsers)
{
	system("cls");

	cout << endl;
	cout << "                                         Users List (" << vStUsers.size() << ") User(s)\n";
	cout << " ___________________________________________________________________________________________________________________\n";
	cout << endl;
	cout << " |" << " User Name " << setw(12) << "|" << " Password " << setw(9) << "|" << " Permisions " << setw(35) << endl;
	cout << " ___________________________________________________________________________________________________________________\n";
	cout << endl;

	for (stUser& user : vStUsers)
	{
		cout << " | " << setw(20) << left << user.name
			 << " | " << setw(16) << left << user.password
			 << " | " << setw(46) << left << user.permissions;
		cout << endl;
	}
	cout << " ___________________________________________________________________________________________________________________\n";
	
	cout << "\nPress any key to go back to main menu screen... ";
	system("pause");
}
void addNewUser(stUser user, vector <stUser>& vStUsers, string fileName)
{
	char answer = 'y';
	string userName = "";

	while (answer == 'y' || answer == 'Y')
	{
		system("cls");

		showTaskTitle("Add New User Screen");
		cout << "Adding New Client:\n";

		userName = readUserName("Enter username? ");

		while (findAUserWithUserName(vStUsers, userName, user))
		{
			cout << "\nUser with [" << userName << "] aready exists, ";
			userName = readUserName("Enter another username? ");
		}

		user = readUser(userName);

		vStUsers.push_back(user);

		saveUsersToFile(fileName, vStUsers);

		cout << "\nUser added successfully,\n\n";

		answer = readAnswer("\nDo you want to add more Users? Y/N ");
	}
}
void findUser(stUser user, vector <stUser> vStUsers )
{
	string userName = readUserName("Enter username? ");

	if (findAUserWithUserName(vStUsers, userName, user))
	{
		system("cls");
		printStUsertData(user);
	}
	system("pause");
}
void updateUser(stUser user, vector <stUser> vStUsers, string fileName)
{
	system("cls");
	showTaskTitle("Update Users Screen:");

	char answer;
	string userName = readUserName("\n Please Enter User Name? ");

	if (findAUserWithUserName(vStUsers, userName, user))
	{
		printStUsertData(user);

		answer = readAnswer("\nAre You sure to update This User? y/n ");

		if (answer == 'y' || answer == 'Y')
		{
			updateUser(vStUsers, userName);
			saveUsersToFile(fileName, vStUsers);
			cout << "\nUser updated Successfully!\n";
		}
	}
	else
		cout << "\n\n User with Name (" << userName << ") Not Found!\n";
		
	system("pause");
}
void deleteUser(stUser user, vector <stUser> vStUsers, string fileName)
{
	system("cls");

	showTaskTitle("Delete User Screen");

	char answer;
	string userName = readUserName("\n Please Enter User Name? ");

	if (userName != "Admin")
	{
		if (findAUserWithUserName(vStUsers, userName, user))
		{
			printStUsertData(user);
			answer = readAnswer("\nAre you sure do you want to delete This Client? Y/N ");

			if (answer == 'y' || answer == 'Y')
			{

				cout << "\nUser deleted Successfully!\n";
				markUserToDelete(vStUsers, userName);
				saveUsersToFile(fileName, vStUsers);
			}
		}
		else
			cout << "\n\n User with Name (" << userName << ") Not Found!\n";
	}
	else
		cout << "\n\nYou can not Delete This User\n";

	system("pause");
}

void manageUsersProcess(stUser user, enUserOption option, vector <stUser> vStUsers, string fileName)
{
	vStUsers = loadUserDataToVector(fileName);

	switch (option)
	{
	case showUser:
		showUsersList(user, vStUsers);
		break;
	case AddUser:
		addNewUser(user, vStUsers, fileName);
		break;
	case DeleteUser:
		deleteUser(user, vStUsers, fileName);
		break;
	case UpdateUser:
		updateUser(user, vStUsers, fileName);
		break;
	case FindUser:
		findUser(user, vStUsers);
		break;
	}
}

void startManageUsers(stUser user, vector <stUser>& vStUsers, string fileName)
{
	enUserOption option;
	stPermission validate = validateToDoTask(user);

	if (validate.ToManageUsers)
	{
		do
		{
			system("cls");
			ManageUsersMenuScreen();

			option = readUserOption("\nChoose what do you want to do from [1 to 6]? ");
			manageUsersProcess(user, option, vStUsers, fileName);

		} while (option != 6);
	}
	else
		accessDenied();
}

stUser logIn()
{
	stUser userToLogIn;
	string fileName = "users.txt";
	vector <stUser> vStUsers = loadUserDataToVector(fileName);
	bool resultCheck = false;

	system("cls");

	showTaskTitle("Login Screen");

	do
	{
		string userName = readUserName("\nEnter username? ");
		string userPassword = readUserPassword("\nEnter Password? ");
		
		//string userName = "user1";
		//string userPassword = "1111";

		for (stUser& user : vStUsers)
		{
			if (user.name == userName && user.password == userPassword)
			{
				userToLogIn = user;
				resultCheck = true;
			}
		}
		cout << "\nInvalid username/password!\n\n";
	}
	while (resultCheck == false);
	
	return userToLogIn;
}

void doOperation(stUser user, enChoice choice, vector <stClient> vStClients, vector <stUser> vStUsers, string clientsFile, string usersfile)
{
	vStClients = loadDataToVector(clientsFile);
	vStUsers = loadUserDataToVector(usersfile);

	switch (choice)
	{
	case Show:
		showClientList(user, vStClients);
		break;
	case Add:
		addNewClient(user, clientsFile, vStClients);
		break;
	case Delete:
		deleteAccount(user, vStClients, clientsFile);
		break;
	case Update:
		updateAccount(user, vStClients, clientsFile);
		break;
	case Find:
		findAccount(user, vStClients, clientsFile);
		break;
	case Transactions:
		startTransactions(user, vStClients, clientsFile);
		break;
	case Users:
		startManageUsers(user, vStUsers, usersfile);
		break;
	}
}
void start()
{
	string clientsFile = "clients.txt";
	string usersFile = "users.txt";
	vector <stUser> vStUsers = loadUserDataToVector(usersFile);
	vector <stClient> vStClients = loadDataToVector(clientsFile);

	enChoice choice;

	do
	{
		stUser user = logIn();

		do
		{
			system("cls");

			MainMenuScreen();
			choice = readOperationChoice("\nChoose what do you want to do from [1 to 8]? ");

			doOperation(user, choice, vStClients, vStUsers, clientsFile, usersFile);

		} while (choice != 8);

	} while (choice == 8);

}








int main()
{
	start();


	system("pause>0");

	return 0;
}