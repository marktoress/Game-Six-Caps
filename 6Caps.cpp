#include<iostream>
#include<ctime>
#include<string>
#include<conio.h>
#define NOMINMAX
#include<Windows.h>
#include<iomanip>
#include <limits>


using namespace std;

class Game
{
protected:
	string name;
public:
	Game(string n)
	{
		name = n;
	}
	virtual void ShowInfo(int s)
	{
		cout << "Name :\t" << name <<
			"\n" << "Score :\t" << s << endl; 
	}
};

class PlayerPC : public Game
{
private:
	int scorePC;
	int openChipsPC[6] = { 1,2,3,4,5,6 };
	int closedChipsPC[6] = { 0,0,0,0,0,0 };
public:
	PlayerPC(string n, int s) : Game(n)
	{
		scorePC = s;
	}

	// Get ChipsPC (at random from 1 to 6)
	int GetChipsPC()
	{
		for (int i = 0; i < sizeof closedChipsPC/sizeof closedChipsPC[0]; i++)
		{
			if (closedChipsPC[i] == 0)
			{
				bool fl = false;
				int num = rand() % 6 + 1;
				for (int j = 0; j < sizeof closedChipsPC / sizeof closedChipsPC[0]; j++)
				{
					if (closedChipsPC[j] == num)
					{
						fl = true;
						i--;
						break;
					}
				}
				if (!fl)
				{
					closedChipsPC[i] = num;
					return num;
				}
			}
		}
	} 

	void SaveChipsPC(int chipsPC)
	{
		for (int i = 0; i < sizeof openChipsPC / sizeof openChipsPC[0]; i++)
		{
			if (openChipsPC[i] == chipsPC)
			{
				openChipsPC[i] = 0;
				break;
			}
		}						
	}

	void ShowInfo(int s) override
	{
		Game::ShowInfo(s);
		cout << "Open Chips : ";
		for (int i = 0; i < sizeof openChipsPC / sizeof openChipsPC[0]; i++)
		{
			if (openChipsPC[i] != 0)
			{
				cout << openChipsPC[i] << " ";
			}
		}
		cout << endl;
		cout << "Closed Chips : ";
		for (int i = 0; i < sizeof closedChipsPC/sizeof closedChipsPC[0]; i++)
		{
			if (closedChipsPC[i] != 0)
			{
				cout << closedChipsPC[i] << " ";
			}
		}
		cout << endl << endl;
	}
};

class PlayerUser : public Game
{
private:
	int scoreUser;
	int openChipsUser[6] = { 1,2,3,4,5,6 };
	int closedChipsUser[6] = { 0,0,0,0,0,0 };
public:
	PlayerUser(string n, int s) : Game(n) 
	{
		scoreUser = s;
	}

	void SaveChipsUser(int chipsUser)
	{
		for (int i = 0; i < sizeof openChipsUser/sizeof openChipsUser[0]; i++)
		{
			if (openChipsUser[i] == chipsUser)
			{
				openChipsUser[i] = 0;
				break;
			}
		}
		for (int i = 0; i < sizeof closedChipsUser / sizeof closedChipsUser[0]; i++)
		{
			if (closedChipsUser[i] == 0)
			{
				closedChipsUser[i] = chipsUser;
				break;
			}
		}
	}

	int NoRepeatChipsUser(int chipsUser)
	{
		for (int i = 0; i < sizeof closedChipsUser / sizeof closedChipsUser[0]; i++)
		{
			if (closedChipsUser[i] == chipsUser)
			{
				return closedChipsUser[i];
			}
		}
		return 0;
	}

	void ShowInfo(int s) override
	{
		Game::ShowInfo(s);
		cout << "Open Chips : ";
		for (int i = 0; i < sizeof openChipsUser / sizeof openChipsUser[0]; i++)
		{
			if (openChipsUser[i] != 0)
			{
				cout << openChipsUser[i] << " ";
			}
		}
		cout << endl;
		cout << "Closed Chips : ";
		for (int i = 0; i < sizeof closedChipsUser / sizeof closedChipsUser[0]; i++)
		{
			if (closedChipsUser[i] != 0)
			{
				cout << closedChipsUser[i] << " ";
			}
		}
		cout << endl << endl;
	}
};

void CharLine(char ch, int n);
void ResultScore(int chipsPC, int chipsUser, int* scorePC, int* scoreUser); // function result score

int main()
{
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string name;
	int count = 1;
	int chipsPC, chipsUser, scorePC = 0, scoreUser = 0;
	int noRepeatChipsUser;

	cout << "\t\t\tHello, My Friend!" << endl << endl;
	cout << "What's your name ? " << endl << endl;
	cin >> name;

	PlayerPC playerPC("PC", scorePC);
	PlayerUser playerUser(name, scoreUser);

	cout << "Îê," << name << ", Start the Game! " << endl;

	// the life cycle of the game

	while (count <= 6)
	{
		CharLine('*', 40);

		cout << "Round " << count << endl;

		CharLine('-', 30);

		playerPC.ShowInfo(scorePC);
		playerUser.ShowInfo(scoreUser);

		chipsPC = playerPC.GetChipsPC();
		playerPC.SaveChipsPC(chipsPC);

		CharLine('-', 30);

		cout << "Choose a chip from 1 to 6 " << endl;

		// Checking for entering digits in the specified range 

		while (true)
		{
			cin >> chipsUser;
			noRepeatChipsUser = playerUser.NoRepeatChipsUser(chipsUser);
			if (!cin || chipsUser < 1 || chipsUser > 6 || chipsUser == noRepeatChipsUser )
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "This chip was already there or the wrong choice\n Repeat the selection of the chip 1 - 6 " << endl;
			}
			else if(chipsUser >= 1 && chipsUser <= 6)
			{
				break;
			}
		}

		playerUser.SaveChipsUser(chipsUser);

		CharLine('*', 40);

		cout << "Chip PC :\t" << chipsPC << "\n" <<
			"Your Chip :\t" << chipsUser << endl;

		CharLine('*', 40);

		ResultScore(chipsPC, chipsUser, &scorePC, &scoreUser);
		count++;
	}
	CharLine('-', 40);
	playerPC.ShowInfo(scorePC);
	playerUser.ShowInfo(scoreUser);
	cout << "\t\t\tGame Over!!!" << endl;
	if (scorePC > scoreUser)
	{
		cout << "Won PC. Score- " << scorePC <<
			"\nYour Score - " << scoreUser << endl;
	}
	if (scorePC < scoreUser)
	{
		cout << "You Won. Score- " << scoreUser <<
			"\nScore PC - " << scorePC << endl;
	}
	if (scorePC == scoreUser)
	{
		cout << "Friendship Won )))\n Score PC- " << scorePC <<
			"\nYour Score - " << scoreUser << endl;
	}

	_getche();
}

void CharLine(char ch, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << ch;
	}
	cout << endl;
}
void ResultScore(int chipsPC, int chipsUser, int* scorePC, int* scoreUser)
{
	if (chipsPC > chipsUser)
	{
		(*scorePC) += chipsPC + chipsUser;
		cout << "\tThe computer chip is bigger. \n\tIn this round, the computer won ! " << endl;
		return;
	}
	if (chipsUser > chipsPC)
	{
		(*scoreUser) += chipsPC + chipsUser;
		cout << "\tYour chip is bigger. \n\tYou won this round !" << endl;
		return;
	}
	if (chipsPC == chipsUser)
	{
		cout << "\tEqual values of chips!!!\n\tNo points are awarded!!!" << endl;
		return;
	}
}


	
