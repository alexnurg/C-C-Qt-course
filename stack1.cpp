//Домашка Stack (на основе массива класса Вектор)

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
using namespace std;

struct Task					
	{
		string taskName;
		int time; 
	};

void pushTask (vector<Task> &Ptr);		//Добавляет новый элемент в начало списка
void print_all_tasks (vector<Task> &Ptr);	//Выводит полный список задач 
void menu1();					//Выводит меню 1
void menu2();					//Выводит меня 2
int check_input ();				//Проверяет правильность ввода цифр пользователем
void readTask (vector<Task> &Ptr);		//Выводит задачу с заданным номером
void deleteTask (vector<Task> &Ptr);		//Удаляет задачу с заданным номером
void run_Lifo (vector<Task> &Ptr);		//Выполняет задачи в режиме стека
void run_Fifo (vector<Task> &Ptr);		//Выполняет задачи в режиме очереди
//______________________________________________________________________________________________________________________________
int main() 
{
	vector <Task> list;
	char sym;
	cout<<"Do you want input tasks in list? y/n:";
	cin>>sym;
	if (sym!='y') return 0;
	pushTask(list);

	int customChoice=10,secondChoice=5;
	while (customChoice!=4)					
	{
		menu1 ();
		customChoice=check_input();
		
		switch (customChoice)
		{
			case 1:					
				print_all_tasks (list);
				
				secondChoice=5;
				while (secondChoice!=4)					
				{
					menu2();
					secondChoice=check_input();
		
					switch (secondChoice)
					{
						case 1:	
							readTask (list);				
							break;
						case 2:	
							pushTask (list);
							break;
						case 3:	
							deleteTask (list);				
							break;
						case 4:						
							break;
					}
				}
				
				break;
			case 2:	
				run_Lifo(list);
				break;
			case 3:					
				run_Fifo(list);
				break;
			case 4:						
				break;
		}
	}
	return 0;
}
//_______________________________________________________________________________________________________________________________
void pushTask (vector<Task> &Ptr)
{
	char symbol;
	Task nextTask;
	cout<<"Input name of task: ";
	
	cin>>nextTask.taskName;
	cout<<"Input time for task: ";cin>>nextTask.time;
	Ptr.push_back(nextTask);
	cout<<"Quantity of tasks in list: "<<Ptr.size()<<endl;
	cout<<"Do you want input another task? y/n: ";cin>>symbol;	
	if (symbol=='y')pushTask(Ptr);
	else print_all_tasks(Ptr);
	
}
void print_all_tasks (vector<Task> &Ptr)
{
	if (Ptr.empty())
	{
		cout<<"The list of tasks is empty.";
	}
	else
	{
		cout<<"\nList of tasks:\n";
		for (int i=0;i<Ptr.size();i++)
		{
			cout<<i+1<<". "<<Ptr[i].taskName<<endl;
		}
	}
}

void menu1()
{
	cout<<"\n1-Edit list";
	cout<<"\n2-Run tasks (LIFO)";
	cout<<"\n3-Run tasks (FIFO)";
	cout<<"\n4-exit";
}

void menu2()
{
	cout<<"\n1-Read task";
	cout<<"\n2-Add task";
	cout<<"\n3-Delete task";
	cout<<"\n4-exit";
}
int check_input ()
{
	int choice;
	while (true)					
		{
			cout<<"\nInput number: ";
			cin>>choice;
			if (choice>4)
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
return choice;
}
void readTask (vector<Task> &Ptr)
{
	if (!Ptr.empty())
	{
		int numberTask;
		cout<<"Input number of task to read: ";
		cin>>numberTask;
		if (numberTask>Ptr.size())
		{
			cout<<"The quantity of tasks is :"<<Ptr.size();
		}
		else
		{
			cout<<"The name of task "<<numberTask<<" :"<<Ptr[numberTask-1].taskName<<endl;
		}
	}
	else print_all_tasks (Ptr);
}

void deleteTask (vector<Task> &Ptr)
{
	if (!Ptr.empty())
	{
		int numberTask;
		cout<<"Input number of task to delete: ";
		cin>>numberTask;
		if (numberTask>Ptr.size())
		{
			cout<<"The quantity of tasks is :"<<Ptr.size();
		}
		else
		{
			Ptr.erase(Ptr.begin()+numberTask-1);
			print_all_tasks (Ptr);
		}
	}
	else print_all_tasks (Ptr);

}
void run_Lifo (vector<Task> &Ptr)
{
	char symb;
	if (!Ptr.empty())
	{
	
		cout<<"\nRunning task: "<<Ptr.back().taskName<<"\n";
		sleep(Ptr.back().time);
		cout<<"\nTask "<<Ptr.back().taskName<<" is fulfill.\n";
		Ptr.pop_back();
		print_all_tasks (Ptr);
		if (!Ptr.empty())
		{
			cout<<"\nRun another task? y/n: "; cin>>symb;
			if (symb=='y')run_Lifo (Ptr);
		}
	}
	else print_all_tasks (Ptr);
}
void run_Fifo (vector<Task> &Ptr)
{
	char symb;
	if (!Ptr.empty())
	{
	
		cout<<"\nRunning task: "<<Ptr.front().taskName<<"\n";
		sleep(Ptr.front().time);
		cout<<"\nTask "<<Ptr.front().taskName<<" is fulfill.\n";
		Ptr.erase(Ptr.begin());
		print_all_tasks (Ptr);
		if (!Ptr.empty())
		{
			cout<<"\nRun another task? y/n: "; cin>>symb;
			if (symb=='y')run_Fifo (Ptr);
		}
	}
	else print_all_tasks (Ptr);
}
	
