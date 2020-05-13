//Домашка Stack (на основе односвязного списка)

#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

struct Task					
	{
		string taskName;
		int time;
		Task *next; 
	};



void menu1();						//Выводит меню 1
void menu2();						//Выводит меня 2
void *pushTask (Task *&pFirst);				//Добавляет элемент в вершину стека
void print_all_tasks (Task *pFirst);			//Выводит список всех задач и их количество
void printTask (Task *pprint);				//Выводит найденную задачу
int check_input ();					//Проверяет правильность ввода цифр пользователем
Task *searchTask(Task *pFirst);				//Выводит задачу с нужным значением в поле taskName и возвращает указатель на нее
void del_first_Task (Task *&pFirst);			//Удаляет элемент на вершине стека
void del_any_Task (Task *&p_delTask,Task *&pFirst);	//Удаляет элемент внутри списка
void run_Lifo (Task *pFirst);				//Выполняет все задачи списка в режиме стека
void run_Fifo (Task *pFirst);				//Выполняет все задачи в режиме очереди
Task *get_ptr_predlastTask (Task *pFirst);		//Возвращает указатель на предпоследний элемент списка

//______________________________________________________________________________________________________________________________
int main() 
{
	char sym;
	Task *First=NULL;
	cout<<"Do you want input tasks in list? y/n:";
	cin>>sym;
	if (sym!='y') return 0;
	pushTask(First);
	
	int customChoice=10;
	int secondChoice=5;
	while (customChoice!=4)					
	{
		Task *Ptrs;
		menu1 ();
		customChoice=check_input();
		
		switch (customChoice)
		{
			case 1:							//Редактирование списка				
				print_all_tasks (First);
				secondChoice=5;
				
				while (secondChoice!=4)					
				{
					menu2();
					secondChoice=check_input();
		
					switch (secondChoice)
					{
						case 1:				//Поиск и вывод задачи с нужным именем
							Ptrs=searchTask (First);	
							if (Ptrs!=NULL)printTask (Ptrs);				
							break;
						case 2:	
							pushTask (First);	//Добавление задачи в список
							break;
						case 3:	
							Ptrs=searchTask (First);//Удаление задачи с нужным именем без выполнения
							
							if (Ptrs==NULL)break;
							del_any_Task (Ptrs,First);
							print_all_tasks(First);				
							break;
						case 4:						
							break;
					}
				}
				
				break;
			case 2:	
				run_Lifo (First);	//Выполнение задач в режиме стека
				customChoice=4;
				break;
				
			case 3:					
				run_Fifo(First);	//Выполнение задач в режиме очереди
				customChoice=4;
				break;
			case 4:						
				break;
		}
	}

	return 0;
}
//________________________________________________________________________________________________________________________________
void *pushTask (Task *&pFirst)
{
	char symbol;
	Task *newPtr=new Task;
	cout<<"Input name of  task: ";
	cin>>newPtr->taskName;
	cout<<"Input time for task: ";cin>>newPtr->time;
	newPtr->next=pFirst;
	pFirst=newPtr;
	
	cout<<"Do you want input another task? y/n: ";cin>>symbol;	
	if (symbol=='y')pushTask(pFirst);
	else print_all_tasks(pFirst);
}
void print_all_tasks(Task *pFirst)
{
	int count=0;
	Task *current=pFirst;
	while (current)
	{
		count++;
		printTask (current);
		
		current=current->next;
	}
	cout<<"\nThe quantity of tasks: "<<count<<endl;
	
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
Task *searchTask (Task *pFirst)
{
	Task *current=pFirst;
	string str;
	
	cout<<"\nInput name of task for search: ";
	
	getline (cin,str);
	
	while (current)
	{
		if (current->taskName==str)
		{
				
			 return (current);
		}
		else current=current->next;
	}
	cout<<"\nThere is no such task.";
	return (NULL);
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
void printTask (Task *pprint)
{
	Task *p=pprint;
	cout<<"\nTask name: "<<p->taskName;
	cout<<"\nTime for task: "<<p->time<<endl;
}
void del_first_Task (Task *&pFirst)
{
	Task *pdel=pFirst;
	pFirst=pFirst->next;
	delete pdel;
}
void del_any_Task (Task *&p_delTask,Task *&pFirst)
{
	Task *current=pFirst;
	Task *preddel;
	
	if (p_delTask==pFirst)
	{
		del_first_Task (pFirst);
	}
	else
	{
		while (current)
		{
			if (current->next==p_delTask)
			{
				preddel=current;
				preddel->next=p_delTask->next;
				delete p_delTask;
				
			}
			current=current->next;
		}
	}	
}
void run_Lifo (Task *pFirst)
{
	while (pFirst)
	{			
		cout<<"\nRunning task: "<<pFirst->taskName<<"\n";
		sleep(pFirst->time);
		cout<<"\nTask "<<pFirst->taskName<<" is fulfill.\n";
		del_first_Task (pFirst);
	}
	cout<<"\nThe list of task is empty.\n";
}
Task *get_ptr_predlastTask (Task *pFirst)
{
	Task *predlast=pFirst;
	while ((predlast->next)->next!=NULL)
	{
		predlast=predlast->next;
	}
	return predlast;
}


void run_Fifo (Task *pFirst)
{
	if ((pFirst->next)==NULL)
	{
		cout<<"\nRunning task: "<<pFirst->taskName<<"\n";
		sleep(pFirst->time);
		cout<<"\nTask "<<pFirst->taskName<<" is fulfill.\n";
		delete pFirst;
		cout<<"\nThe list of task is empty.\n";
	}
	else
	{
		Task *predlast=get_ptr_predlastTask (pFirst);
		Task *last=predlast->next;
	
	
	
		cout<<"\nRunning task: "<<last->taskName<<"\n";
		sleep(last->time);
		cout<<"\nTask "<<last->taskName<<" is fulfill.\n";
		
		predlast->next=NULL;
		delete last;
		run_Fifo (pFirst);
		
	}	
}		
