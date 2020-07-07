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

	// получение фишки копма (рандомно от 1-6)
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
		cout << "Доступные фишки : ";
		for (int i = 0; i < sizeof openCapsPC / sizeof openCapsPC[0]; i++)
		{
			if (openCapsPC[i] != 0)
			{
				cout << openCapsPC[i] << " ";
			}
		}
		cout << endl;
		cout << "Выпавшие фишки : ";
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
		cout << "Доступные фишки : ";
		for (int i = 0; i < sizeof openCapsUser / sizeof openCapsUser[0]; i++)
		{
			if (openCapsUser[i] != 0)
			{
				cout << openCapsUser[i] << " ";
			}
		}
		cout << endl;
		cout << "Выпавшие фишки : ";
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
void ResultScore(int capsPC, int capsUser, int* scorePC, int* scoreUser); //функция подсчета очков

int main()
{
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string name;
	int count = 1;
	int capsPC, capsUser, scorePC = 0, scoreUser = 0;
	int noRepeatCapsUser;

	cout << "\t\t\tПриветствую тебя, Друг!" << endl << endl;
	cout << "Напиши свое имя " << endl << endl;
	cin >> name;

	PlayerPC playerPC("Комп", scorePC);
	PlayerUser playerUser(name, scoreUser);

	cout << "Ок," << name << ", начинаем игру! " << endl;
	// Цикл жизни игры
	while (count <= 6)
	{
		CharLine('*', 40);

		cout << "Раунд " << count << endl;

		CharLine('-', 30);

		playerPC.ShowInfo(scorePC);
		playerUser.ShowInfo(scoreUser);

		capsPC = playerPC.GetCapsPC();
		playerPC.SaveCapsPC(capsPC);

		CharLine('-', 30);

		cout << "Выберите фишку 1 - 6 " << endl;

		// Проверка на ввод цифр в заданном диапазоне 

		while (true)
		{
			cin >> capsUser;
			noRepeatCapsUser = playerUser.NoRepeatCapsUser(capsUser);
			if (!cin || capsUser < 1 || capsUser > 6 || capsUser == noRepeatCapsUser )
			{
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Эта фишка уже была или неверный выбор\n Повторите выбор фишки от 1 - 6 " << endl;
			}
			else if(capsUser >= 1 && capsUser <= 6)
			{
				break;
			}
		}

		playerUser.SaveCapsUser(capsUser);

		CharLine('*', 40);

		cout << "Фишка компьютера :\t" << capsPC << "\n" <<
			"Ваша фишка :\t\t" << capsUser << endl;

		CharLine('*', 40);

		ResultScore(capsPC, capsUser, &scorePC, &scoreUser);
		count++;
	}
	CharLine('-', 40);
	playerPC.ShowInfo(scorePC);
	playerUser.ShowInfo(scoreUser);
	cout << "\t\t\tИгра окончена!!!" << endl;
	if (scorePC > scoreUser)
	{
		cout << "Победил компьютер. Очки - " << scorePC <<
			"\nВаши очки - " << scoreUser << endl;
	}
	if (scorePC < scoreUser)
	{
		cout << "Вы победили. Очки - " << scoreUser <<
			"\nОчки компьютера - " << scorePC << endl;
	}
	if (scorePC == scoreUser)
	{
		cout << "Победила Дружба )))\n Очки компьютера - " << scorePC <<
			"\nВаши очки - " << scoreUser << endl;
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
		cout << "\tФишка компьютера больше. \n\tВ этом раунде победил комп ! " << endl;
		return;
	}
	if (capsUser > capsPC)
	{
		(*scoreUser) += capsPC + capsUser;
		cout << "\tВаша фишка больше. \n\tВ этом раунде победили вы !" << endl;
		return;
	}
	if (capsPC == capsUser)
	{
		cout << "\tРавные значения фишек!!!\n\tОчки не начисляются!!!" << endl;
		return;
	}
}


	
