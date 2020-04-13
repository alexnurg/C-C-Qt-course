//Домашка 5-1. Консольное меню со Switch.
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void menu ();//Функция, выводящая меню
void help ();//Функция, выводящая описания игр
void sportloto();//Функция, запускающая игру "5 из 36"
void roulette ();//Функция, запускающая игру "Рулетка"

int main ()
	{
	int customChoice=10;
		while (customChoice!=4)//Цикл, выводящий меню, пока пользователь не решит выйти
			{
				menu ();
				
				while (true)//Цикл, не допускающий некорректный ввод
				{
				cout<<"\nInput number: ";
				cin>>customChoice;
				
				if (cin.good())
					{
						cin.ignore(10,'\n');
						break;
					}
					cin.clear();
					cout<<"\nInvalid input\n";
					cin.ignore(10,'\n');

				}
				
				switch (customChoice)
				{
				case 1:
					sportloto ();
					break;
				case 2:
					roulette ();
					break;
				case 3:
					help ();
					break;
				case 4:
					cout<<"\nGood bye!\n";
					break;
				}
			}
	return 0;
	}

void sportloto ()
	{
	const int n=5;
	int i,j;
	int randomnums [n];//Выпавшие числа
	int customnums [n];//Числа, загаданные пользователем
	srand (time(0));
		for (i=0;i<n;i++)//Цикл, запрашивающий у пользователя 5 чисел
		{
		cout<<"\nEnter number "<<i+1<<" from 1 to 36:  ";
		
		cin>>customnums [i];
		}

	int buf;//Генерация 5-ти случайных неповторяющихся чисел от 1 до 36
	randomnums[0]=1+rand()%36;

	for (i=1;i<n;i++)
		{
		int k=1;
		while (k!=0)
			{
			buf=1+rand()%36;
			randomnums[i]=buf;
			k=0;
			for (j=0;j<i;j++)
				{
				if (buf==randomnums[j])
					{
					k=1; 
					break;
					}
				}	
			}
		}

	cout<<"\nThe winning numbers: ";
	
	for (i=0;i<n;i++)
		{
		cout<<randomnums[i]<<" ";
		}
		cout<<"\n";

	int match=0;
	for (i=0;i<n;i++)
		{
		for (j=0;j<n;j++)
			{
			if (customnums[i]==randomnums[j])
				match++;
			}
		}
	cout<<"\nYou have guessed "<<match<<" numbers\n";

	}

void menu ()
	{
	cout<<"\n1-game Sportloto 5 from 36";
	cout<<"\n2-game Roulette";
	cout<<"\n3-help";
	cout<<"\n4-exit";
	}

void help ()
	{
	cout<<"Description of games:.........\n";
	}

void roulette ()
	{
	int betNumber;
	int winNumber;
	cout<<"\nInput number from 0 to 36: ";
	cin>>betNumber;
	srand (time(0));
	winNumber=rand()%37;
	if (betNumber==winNumber)
		cout<<"\nYou win!";
	else
		{
		cout<<"\nThe winning number: "<<winNumber; 
		cout<<"\nYou lost!\n";
		}
	}






