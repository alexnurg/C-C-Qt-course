//Домашка 10 (Телефонный справочник)

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

struct Client					//Структура для записи данных абонента
	{
		string lastName;
		string firstName;
		string phoneNumber;
	};

void menu ();					//Выводит меню
void setClientData (Client &PhB);		//Заносит данные абонента в поля структуры
void sort_File(vector<Client> &Ptr,int m);	//Сортирует структуры в массиве по фамилии абонента (по алфавиту) 
void write_File(vector<Client> &Ptr,int m);	//Записывает массив структур в файл "PhoneBook.txt"
void write_File(Client PhB);			//Записывает нового абонента в конец файла

int main() 
{
	Client Buf;				//Структура для занесения данных нового абонента
	int k=0;				//Счетчик для подсчитывания кол-ва записей в телефонной книге
	int count;				//Счетчик, используемый при поиске нужного абонента
	char symbol;				//Переменная для сохранения выбора пользователя
	do
	{
		ifstream fin;
		fin.open("PhoneBook.txt");
		string str;
		while (getline(fin,str))	//Считываем данные из файла построчно и определяем количество записей
		{
			k++;
		}
		fin.close();
		if (k==0)
		{
			cout<<"\nPhone book is empty\n";		//Выводим это, если файл пуст		
			cout<<"Do you want to record a person? (y/n): ";//Предлагаем пользователю занести абонента
			cin>>symbol;
			if(symbol!='y') return 0;			//Выходим из программы в случае отказа
			setClientData (Buf);				//Заносим нового абонента
			write_File(Buf);
		}
	} while (k==0);
	
	vector<Client>list(k);		//Объявляем вектор структур 
	ifstream fin;			//И записываем в него данные абонентов из файла "PhoneBook.txt"
	fin.open("PhoneBook.txt");
	fin.seekg(0);
	for (int i=0;i<k;i++)
	{
		fin>>list[i].lastName>>list[i].firstName>>list[i].phoneNumber;
	}
	fin.close();
	cout<<endl<<"Number of records: "<<list.size()<<endl; //Показываем количество записей в справочнике
	
	int customChoice=10;
	while (customChoice!=4)					//Цикл, выводящий меню, пока пользователь не решит выйти
	{
		menu ();
		while (true)					//Цикл, не допускающий некорректный ввод
		{
			cout<<"\nInput number: ";
			cin>>customChoice;
			if (customChoice>4)
				cin.clear(ios::failbit);
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
			case 1:					//Выводит в консоль весь справочник
				for (int i=0;i<list.size();i++)	
				{
					cout<<setiosflags(ios::left)<<endl<<setw(20)<<list[i].lastName<<setw(20)
					<<list[i].firstName<<setw(20)<<list[i].phoneNumber;
				}
				cout<<'\n';
				break;
			case 2:					//Занесение нового абонента
				setClientData (Buf);		//Заносим данные абонента в поля структуры
				list.push_back(Buf);		//Добавляем новую структуру в вектор
				sort_File(list,list.size());	//Сортируем измененный вектор по фамилии (по алфавиту)
				break;
			case 3:					//Поиск требуемого абонента по фамилии
				count=0;			
				cout<<"\nInput wanted last name: ";cin>>Buf.lastName;
				for (int j=0;j<list.size();j++)
				{
					if (list[j].lastName==Buf.lastName) //Выводим данные абонента при совпадении
					{
						cout<<setiosflags(ios::left)<<endl<<setw(20)<<list[j].lastName<<setw(20)
						<<list[j].firstName<<setw(20)<<list[j].phoneNumber;
						count++;
					}
				}
				if (count==0) cout<<"\nNo matches\n";	//Выводим это, если совпадений нет
				break;
			case 4:						//Выход из цикла меню 
				write_File(list,list.size());		//Записываем перед выходом из программы измененные данные в файл
				break;
		}
	}
	
	
	return 0;
}


void menu ()
{
	cout<<"\n1-Get list";
	cout<<"\n2-Input new person";
	cout<<"\n3-Find a person";
	cout<<"\n4-exit";
}
void setClientData (Client& PhB)
{
	cout<<endl<<"Input last name: ";cin>>PhB.lastName;
	cout<<endl<<"Input first name: ";cin>>PhB.firstName;
	cout<<endl<<"Input phone number: ";cin>>PhB.phoneNumber;
}
void write_File(Client PhB)	
{
	ofstream fout;
	fout.open("PhoneBook.txt",ios::app);
	fout<<PhB.lastName<<" "<<PhB.firstName<<" "<<PhB.phoneNumber<<endl;
	fout.close();
}

void sort_File(vector<Client> &Ptr,int m)
{
	for (int i=0;i<m;i++)
	{
		Client min;
		min.lastName=Ptr[i].lastName;
		min.firstName=Ptr[i].firstName;
		min.phoneNumber=Ptr[i].phoneNumber;
		int nmin=i;

		for (int j=i+1;j<m;j++)
		{
			if (Ptr[j].lastName<min.lastName)
			{
				min.lastName=Ptr[j].lastName;
				min.firstName=Ptr[j].firstName;
				min.phoneNumber=Ptr[j].phoneNumber;
				nmin=j;
			}
		}
		Ptr[nmin].lastName=Ptr[i].lastName;
		Ptr[nmin].firstName=Ptr[i].firstName;
		Ptr[nmin].phoneNumber=Ptr[i].phoneNumber;
		
		Ptr[i].lastName=min.lastName;
		Ptr[i].firstName=min.firstName;
		Ptr[i].phoneNumber=min.phoneNumber;
	}
}
void write_File(vector<Client> &Ptr,int m)
{
	ofstream fout;
	fout.open("PhoneBook.txt");
	for (int i=0;i<m;i++)
	{
		fout<<Ptr[i].lastName<<" "<<Ptr[i].firstName<<" "<<Ptr[i].phoneNumber<<endl;
	}
	fout.close();
}	
