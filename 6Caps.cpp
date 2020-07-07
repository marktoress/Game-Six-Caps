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
	int openCapsPC[6] = { 1,2,3,4,5,6 };
	int closedCapsPC[6] = { 0,0,0,0,0,0 };
public:
	PlayerPC(string n, int s) : Game(n)
	{
		scorePC = s;
	}

	// ��������� ����� ����� (�������� �� 1-6)
	int GetCapsPC()
	{
		for (int i = 0; i < sizeof closedCapsPC/sizeof closedCapsPC[0]; i++)
		{
			if (closedCapsPC[i] == 0)
			{
				bool fl = false;
				int num = rand() % 6 + 1;
				for (int j = 0; j < sizeof closedCapsPC / sizeof closedCapsPC[0]; j++)
				{
					if (closedCapsPC[j] == num)
					{
						fl = true;
						i--;
						break;
					}
				}
				if (!fl)
				{
					closedCapsPC[i] = num;
					return num;
				}
			}
		}
	} 

	void SaveCapsPC(int capsPC)
	{
		for (int i = 0; i < sizeof openCapsPC / sizeof openCapsPC[0]; i++)
		{
			if (openCapsPC[i] == capsPC)
			{
				openCapsPC[i] = 0;
				break;
			}
		}
	}

	void ShowInfo(int s) override
	{
		Game::ShowInfo(s);
		cout << "��������� ����� : ";
		for (int i = 0; i < sizeof openCapsPC / sizeof openCapsPC[0]; i++)
		{
			if (openCapsPC[i] != 0)
			{
				cout << openCapsPC[i] << " ";
			}
		}
		cout << endl;
		cout << "�������� ����� : ";
		for (int i = 0; i < sizeof closedCapsPC/sizeof closedCapsPC[0]; i++)
		{
			if (closedCapsPC[i] != 0)
			{
				cout << closedCapsPC[i] << " ";
			}
		}
		cout << endl << endl;
	}
};

class PlayerUser : public Game
{
private:
	int scoreUser;
	int openCapsUser[6] = { 1,2,3,4,5,6 };
	int closedCapsUser[6] = { 0,0,0,0,0,0 };
public:
	PlayerUser(string n, int s) : Game(n) 
	{
		scoreUser = s;
	}

	void SaveCapsUser(int capsUser)
	{
		for (int i = 0; i < sizeof openCapsUser/sizeof openCapsUser[0]; i++)
		{
			if (openCapsUser[i] == capsUser)
			{
				openCapsUser[i] = 0;
				break;
			}
		}
		for (int i = 0; i < sizeof closedCapsUser / sizeof closedCapsUser[0]; i++)
		{
			if (closedCapsUser[i] == 0)
			{
				closedCapsUser[i] = capsUser;
				break;
			}
		}
	}

	int NoRepeatCapsUser(int capsUser)
	{
		for (int i = 0; i < sizeof closedCapsUser / sizeof closedCapsUser[0]; i++)
		{
			if (closedCapsUser[i] == capsUser)
			{
				return closedCapsUser[i];
			}
		}
		return 0;
	}

	void ShowInfo(int s) override
	{
		Game::ShowInfo(s);
		cout << "��������� ����� : ";
		for (int i = 0; i < sizeof openCapsUser / sizeof openCapsUser[0]; i++)
		{
			if (openCapsUser[i] != 0)
			{
				cout << openCapsUser[i] << " ";
			}
		}
		cout << endl;
		cout << "�������� ����� : ";
		for (int i = 0; i < sizeof closedCapsUser / sizeof closedCapsUser[0]; i++)
		{
			if (closedCapsUser[i] != 0)
			{
				cout << closedCapsUser[i] << " ";
			}
		}
		cout << endl << endl;
	}
};

void CharLine(char ch, int n);
void ResultScore(int capsPC, int capsUser, int* scorePC, int* scoreUser); //������� �������� �����

int main()
{
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string name;
	int count = 1;
	int capsPC, capsUser, scorePC = 0, scoreUser = 0;
	int noRepeatCapsUser;

	cout << "\t\t\t����������� ����, ����!" << endl << endl;
	cout << "������ ���� ��� " << endl << endl;
	cin >> name;

	PlayerPC playerPC("����", scorePC);
	PlayerUser playerUser(name, scoreUser);

	cout << "��," << name << ", �������� ����! " << endl;
	// ���� ����� ����
	while (count <= 6)
	{
		CharLine('*', 40);

		cout << "����� " << count << endl;

		CharLine('-', 30);

		playerPC.ShowInfo(scorePC);
		playerUser.ShowInfo(scoreUser);

		capsPC = playerPC.GetCapsPC();
		playerPC.SaveCapsPC(capsPC);

		CharLine('-', 30);

		cout << "�������� ����� 1 - 6 " << endl;

		// �������� �� ���� ���� � �������� ��������� 

		while (true)
		{
			cin >> capsUser;
			noRepeatCapsUser = playerUser.NoRepeatCapsUser(capsUser);
			if (!cin || capsUser < 1 || capsUser > 6 || capsUser == noRepeatCapsUser )
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "��� ����� ��� ���� ��� �������� �����\n ��������� ����� ����� �� 1 - 6 " << endl;
			}
			else if(capsUser >= 1 && capsUser <= 6)
			{
				break;
			}
		}

		playerUser.SaveCapsUser(capsUser);

		CharLine('*', 40);

		cout << "����� ���������� :\t" << capsPC << "\n" <<
			"���� ����� :\t\t" << capsUser << endl;

		CharLine('*', 40);

		ResultScore(capsPC, capsUser, &scorePC, &scoreUser);
		count++;
	}
	CharLine('-', 40);
	playerPC.ShowInfo(scorePC);
	playerUser.ShowInfo(scoreUser);
	cout << "\t\t\t���� ��������!!!" << endl;
	if (scorePC > scoreUser)
	{
		cout << "������� ���������. ���� - " << scorePC <<
			"\n���� ���� - " << scoreUser << endl;
	}
	if (scorePC < scoreUser)
	{
		cout << "�� ��������. ���� - " << scoreUser <<
			"\n���� ���������� - " << scorePC << endl;
	}
	if (scorePC == scoreUser)
	{
		cout << "�������� ������ )))\n ���� ���������� - " << scorePC <<
			"\n���� ���� - " << scoreUser << endl;
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
void ResultScore(int capsPC, int capsUser, int* scorePC, int* scoreUser)
{
	if (capsPC > capsUser)
	{
		(*scorePC) += capsPC + capsUser;
		cout << "\t����� ���������� ������. \n\t� ���� ������ ������� ���� ! " << endl;
		return;
	}
	if (capsUser > capsPC)
	{
		(*scoreUser) += capsPC + capsUser;
		cout << "\t���� ����� ������. \n\t� ���� ������ �������� �� !" << endl;
		return;
	}
	if (capsPC == capsUser)
	{
		cout << "\t������ �������� �����!!!\n\t���� �� �����������!!!" << endl;
		return;
	}
}


	
