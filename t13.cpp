//Домашка 12 (Крестики-нолики)

#include <iostream>
#include <vector>

using namespace std;

class Cell //Класс Клетка					
{
	private:
		int key;			//Ключ объекта-порядковый номер клетки
		char status;			//Статус объекта - "Х", "О", или пробел
	public:
		Cell()
		{}
		void setCell (int k,char s)	//Установка значений в поля объекта 
		{key=k;status=s;}
		void changeStatus (char s)	//Изменение статуса клетки
		{status=s;}
		void showStatus ()		//Вывод в консоль статуса клетки
		{cout<<status;}		
		char readStatus ()		//Читает статус клетки
		{return status;}
		void showKey ()			//Вывод в консоль ключа клетки
		{cout<<key;}
};


void showField (vector<vector<Cell>> &fld);	//Выводит в консоль игровое поле из 9-ти клеток
void get_numberCell(vector<vector<Cell>> &fld,char sym);//Запрашивает у игрока номер клетки и проверяет,допустим ли он, и ставит в нее sym
int findLine_2_1 (vector<vector<Cell>> &fld,char s1,char s2);	//Находит линию,в которой две клетки со статусом s1 и одна с пробелом, и 									//ставит вместо пробела s2 и возвращает 1. Если нет-то 0.
 								
int findStr_1_2 (vector<vector<Cell>> &fld,char s1,char s2);	//Находит строку, в которой одна клетка со статусом  s1 и две с пробелом
								// и ставит вместо дальнего пробела s2
int findLine_3 (vector<vector<Cell>> &fld,char s1);		// Ищет линию с тремя одинаковыми статусами s1. В этом случае возвращает 1 
int find_Empty_Cell (vector<vector<Cell>> &fld,char s1);	//Находит пустую клетку и ставит в нее s1. Если пустой нет, возвращает 0
void clear_All_Status(vector<vector<Cell>> &fld);		//Очищает статусы клеток для новой игры
 			
//_______________________________________________________________________________________________________
int main() 
{
	vector<vector<Cell>> field(3);	//Все 9 объектов размещаем в двумерном векторе [3][3]
	field[0].resize(3);
	field[1].resize(3);
	field[2].resize(3);
	
	int count=1,i,j;
	char symbol=' ';
	for (i=0;i<3;i++)		//Заносим исходные значения в поля объекта
	{
		for (j=0;j<3;j++)
		{
			field[i][j].setCell(count,symbol);
			count++;
		}
	}
	char customChoice='y';
	while (customChoice=='y')
	{
		showField (field);
		char choice;
		int step;
		cout<<"\nDo you want to do first move? (y/n): ";
		cin>>choice;
		if (choice=='y')	//Вариант, когда первым ходит игрок
		{
//Первый ход
			get_numberCell(field,'X');
			showField (field);
			if (field[1][1].readStatus()!='X') {field[1][1].changeStatus('O');}
			else	{field[0][0].changeStatus('O');}
			showField (field);

//Второй ход
			get_numberCell(field,'X');
			showField (field);
			int result=findLine_2_1 (field,'X','O');
			if (result==0)
			{
				if(((int)(field[0][0].readStatus()+field[1][1].readStatus()
				+field[2][2].readStatus())==(int)('O'+'X'+'X'))
		 		&& (field[0][0].readStatus()=='O'))
				
				{
					field[2][0].changeStatus('O');
					result=1;		
				}
					if(((int)(field[0][0].readStatus()+field[1][1].readStatus()
					+field[2][2].readStatus())==(int)('X'+'O'+'X'))
		 			&& (field[0][0].readStatus()=='X'))
				{
					field[1][0].changeStatus('O');
					result=1;		
				}
					if((int)(field[0][2].readStatus()+field[1][1].readStatus()
					+field[2][1].readStatus())==(int)('O'+'X'+'X'))
				{
					field[1][0].changeStatus('O');
					result=1;		
				}
					if((int)(field[0][0].readStatus()+field[1][1].readStatus()
					+field[2][1].readStatus())==(int)('X'+'O'+'X'))
				{
					field[2][0].changeStatus('O');
					result=1;		
				}
					if((int)(field[1][0].readStatus()+field[1][1].readStatus()
					+field[1][2].readStatus())==(int)('X'+'O'+'X'))
				{
					field[0][1].changeStatus('O');
					result=1;		
				}
					if (result!=1)
					{findStr_1_2 (field,'X','O');}
			}
			showField (field);
//Третий  ход
			int flag=0;			
			get_numberCell(field,'X');
			showField (field);
			if (findLine_3 (field,'X')==1)
			{
				cout<<"\nYou are winner!\n";
				flag=1;
			}
			else
			{
				if (findLine_2_1 (field,'O','O')==1)
				{
					cout<<"\nYou are loser!\n";
					flag=1;
				}
				else
				{
					if (findLine_2_1 (field,'X','O')!=1)
					{find_Empty_Cell (field,'O');}
				}
			}
			showField (field);
//Четвертый ход
			if (flag!=1)
			{
				get_numberCell(field,'X');
				showField (field);
				if (findLine_3 (field,'X')==1)
				{
					cout<<"\nYou are winner!\n";
				}
				else
				{
					if (findLine_2_1 (field,'O','O')==1)
					{
						cout<<"\nYou are loser!\n";
					}
					else
					{
						if (findLine_2_1 (field,'X','O')!=1)
						{
							find_Empty_Cell (field,'O');
						}
						cout<<"\nThis is a draw!\n";
					}
				}
				showField (field);
			}
		}	
		else 		//Вариант, когда первым ходит компьютер
		{	
//Первый ход		
			field[1][1].changeStatus('X');
			showField (field);
			get_numberCell(field,'O');
			showField (field);
//Второй ход
			
			if ((int)(field[0][0].readStatus()+field[1][1].readStatus()+field[2][2].readStatus())==(int)(' '+'X'+' '))
			{field[0][0].changeStatus('X');}
			else {field[0][2].changeStatus('X');}
			showField (field);
			get_numberCell(field,'O');
			showField (field);
//Третий ход
			int flag=findLine_2_1 (field,'X','X');
			if (flag==1)
			{
				cout<<"\nYou are loser!\n";
				showField (field);
			}
			else
			{
				if (findLine_2_1 (field,'O','X')!=1)
				{
					if (field[0][1].readStatus()=='O') {field[2][0].changeStatus('X');}
					if (field[1][0].readStatus()=='O') {field[0][2].changeStatus('X');}
				}
			
			
			showField (field);
			get_numberCell(field,'O');
			showField (field);
//Четвертый ход
				if (findLine_2_1 (field,'X','X')==1)
				{
					cout<<"\nYou are loser!\n";
					showField (field);
				}
				else
				{
					cout<<"\nThis is a draw!\n";
					showField (field);
				}
			}
		}
	cout<<"\nDo you want play again? (y/n): ";
	cin>>customChoice;
	if (customChoice=='y')
		clear_All_Status(field);
	}
	return 0;	
}
//_________________________________________________________________________________________________________
void showField (vector<vector<Cell>> &fld)
{
	for (int i=0;i<3;i++)
	{
			fld[i][0].showStatus();
			cout<<"|";
			fld[i][1].showStatus();
			cout<<"|";
			fld[i][2].showStatus();
			cout<<"  ";fld[i][0].showKey();cout<<"|";fld[i][1].showKey();cout<<"|";fld[i][2].showKey();
			cout<<endl;
	}
	cout<<endl;
}

void get_numberCell(vector<vector<Cell>> &fld,char sym)
{
	int ind;
	
	do
	{
		ind=1;
	
		cout<<"Your move: ";
		int numberCell;
		cin>>numberCell;
	
	
		switch (numberCell)
		{
			case 1:
				if ((fld[0][0].readStatus()=='X') || (fld[0][0].readStatus()=='O'))
				{
					cout<<"This cell is busy\n";
					ind=0;
				}
				else
					{fld[0][0].changeStatus (sym);}
					break;
			case 2:
				if ((fld[0][1].readStatus()=='X') || (fld[0][1].readStatus()=='O'))
				{
					cout<<"This cell is busy\n";
					ind=0;
				}
				else
					fld[0][1].changeStatus (sym);
				break;
			case 3:
				if ((fld[0][2].readStatus()=='X') || (fld[0][2].readStatus()=='O'))
				{
					cout<<"This cell is busy\n";
					ind=0;
				}
				else
					fld[0][2].changeStatus (sym);
				break;
			case 4:
				if ((fld[1][0].readStatus()=='X') || (fld[1][0].readStatus()=='O'))
				{
					cout<<"This cell is busy\n";
					ind=0;
				}
				else
					fld[1][0].changeStatus (sym);
				break;
			case 5:
				if ((fld[1][1].readStatus()=='X') || (fld[1][1].readStatus()=='O'))
				{
					cout<<"This cell is busy\n";
					ind=0;
				}
				else
					fld[1][1].changeStatus (sym);
				break;
			case 6:
				if ((fld[1][2].readStatus()=='X') || (fld[1][2].readStatus()=='O'))
				{
					cout<<"This cell is busy\n";
					ind=0;
				}
				else
					fld[1][2].changeStatus (sym);
				break;
			case 7:
				if ((fld[2][0].readStatus()=='X') || (fld[2][0].readStatus()=='O'))
				{
					cout<<"This cell is busy\n";
					ind=0;
				}
				else
					fld[2][0].changeStatus (sym);
				break;
			case 8:
				if ((fld[2][1].readStatus()=='X') || (fld[2][1].readStatus()=='O'))
				{
					cout<<"This cell is busy\n";
					ind=0;
				}
				else
					fld[2][1].changeStatus (sym);
				break;
			case 9:
				if ((fld[2][2].readStatus()=='X') || (fld[2][2].readStatus()=='O'))
				{
					cout<<"This cell is busy\n";
					ind=0;
				}
				else
					fld[2][2].changeStatus (sym);
				break;
		}
	}	
	while (ind==0);		
}
int findLine_2_1 (vector<vector<Cell>> &fld,char s1,char s2)	//Ищем "опасную строку"
{
	int ineed,jneed,i,j;
	for (i=0;i<3;i++)
	{
		ineed=0;
		jneed=0;
		for (j=0;j<3;j++)
		{
			if (fld[i][j].readStatus()==' ')
			{
				ineed=i;
				jneed=j;
			}
		}
		if ((int)(fld[i][0].readStatus()+fld[i][1].readStatus()+fld[i][2].readStatus())==(int)(s1+s1+' '))
		{
			//cout<<"ineed="<<ineed<<" jneed="<<jneed;
			fld[ineed][jneed].changeStatus(s2);
			return 1;
		}
	}
	for (j=0;j<3;j++)					//Ищем "опасный столбец
	{
		jneed=0;
		ineed=0;
		for (i=0;i<3;i++)
		{
			if (fld[i][j].readStatus()==' ')
			{
				ineed=i;
				jneed=j;
			}
		}
		if ((int)(fld[0][j].readStatus()+fld[1][j].readStatus()+fld[2][j].readStatus())==(int)(s1+s1+' '))
		{
			//cout<<"ineed="<<ineed<<" jneed="<<jneed;
			fld[ineed][jneed].changeStatus(s2);
			return 1;
		}
	}
	for (i=0;i<3;i++)		//Проверяем диагональ 1-9
	{
		ineed=0;
		if (fld[i][i].readStatus()==' ')
		{ineed=i;}
	}
		if ((int)(fld[0][0].readStatus()+fld[1][1].readStatus()+fld[2][2].readStatus())==(int)(s1+s1+' '))
		{
			fld[ineed][ineed].changeStatus(s2);
			return 1;
		}
	
	for (i=0;i<3;i++)		//Проверяем диагональ 3-7
	{
		ineed=0;
		if (fld[i][2-i].readStatus()==' ')
		{ineed=i;}
	}
		if ((int)(fld[0][2].readStatus()+fld[1][1].readStatus()+fld[2][0].readStatus())==(int)(s1+s1+' '))
		{
			fld[ineed][2-ineed].changeStatus(s2);
			return 1;
		}
	
	return 0;
}

int findStr_1_2 (vector<vector<Cell>> &fld,char s1,char s2)
{
	int ineed,jneed,i,j;
	for (i=0;i<3;i++)
	{
		ineed=0;
		jneed=0;
		for (j=0;j<3;j++)
		{
			if (fld[i][j].readStatus()==' ')
			{
				ineed=i;
				jneed=j;
			}
		}
		if ((int)(fld[i][0].readStatus()+fld[i][1].readStatus()+fld[i][2].readStatus())==(int)(s1+' '+' '))
		{
			fld[ineed][jneed].changeStatus(s2);
			return 1;
		}
	}
	return 0;
}
int findLine_3 (vector<vector<Cell>> &fld,char s1)	
{
	int i,j;
	for (i=0;i<3;i++)
	{
		if ((int)(fld[i][0].readStatus()+fld[i][1].readStatus()+fld[i][2].readStatus())==(int)(s1+s1+s1))
		{
			return 1;
		}
	}
	for (j=0;j<3;j++)					
	{
		if ((int)(fld[0][j].readStatus()+fld[1][j].readStatus()+fld[2][j].readStatus())==(int)(s1+s1+s1))
		{
			return 1;
		}
	}
	if ((int)(fld[0][0].readStatus()+fld[1][1].readStatus()+fld[2][2].readStatus())==(int)(s1+s1+s1))
			return 1;
	if ((int)(fld[0][2].readStatus()+fld[1][1].readStatus()+fld[2][0].readStatus())==(int)(s1+s1+s1))
			return 1;
	return 0;
}


int find_Empty_Cell (vector<vector<Cell>> &fld,char s1)
{
	int i,j;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			if (fld[i][j].readStatus()==' ')
			{
				fld[i][j].changeStatus(s1);
				return 1;
			}
		}
	}
	return 0;
}
void clear_All_Status(vector<vector<Cell>> &fld)
{
	int i,j;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			fld[i][j].changeStatus(' ');
		}
	}
}




