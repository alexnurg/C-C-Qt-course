//Домашка 5-3. Игра "Угадай число".
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

void guessnumber ();//Функция, предлагающая угадать число

int getnumber ();//Функция,получающая от пользователя число и проверяющая корректность ввода

int main ()
	{
	guessnumber ();
	return 0;
	}

int getnumber ()
	{
	int number;
	
	while (true)//Проверяется коректность ввода
		{
		cout<<"Guess the hidden integer number from 0 to 99: ";
		cin.unsetf (ios::skipws);		
		cin>>number;
		if (number<0 || number>99)
			{
			cout<<"The number must be from 0 to 99";
			cin.clear(ios::failbit);
			}
		if (cin.good())
			{
			cin.ignore(10,'\n');
			break;
			}
		cin.clear();
		cin.ignore(10,'\n');
		cout<<"\n"<<"Invalid input"<<"\n";
		}
	return number;
	}

void guessnumber ()
	{
	int hiddennumber,pnumber;
	int choice;
	srand(time(0));
	hiddennumber=rand()%100;
	pnumber=getnumber();
	
	while (pnumber!=hiddennumber)
		{
		if (pnumber>hiddennumber)
			cout<<"Your number is more than hidden number"<<"\n";
		else 
			cout<<"Your number is less than hidden number"<<"\n";
		pnumber=getnumber();
		}

		cout<<"You guessed hidden number!"<<"\n";
		cout<<"Do you want to play again?"<<"\n";
		cout<<"Yes-1,No-2: ";

	while (true)//Цикл,позволяющий пользователю ввести только 1 или 2
		{	
		cin.unsetf (ios::skipws);
		cin>>choice;
		if (choice!=1 && choice!=2)
			{
			cin.clear(ios::failbit);
			}
		if (cin.good())
			{
			cin.ignore(10,'\n');
			break;
			}
		cin.clear();
		cin.ignore(10,'\n');
		cout<<"\n"<<"Yes-1,No-2: ";
		}

	if (choice==1)
		{
		guessnumber();//По желанию пользователя снова запускается игра
		}
	if (choice==2) 
		cout<<endl<<"Good bye"<<"\n";
	}
