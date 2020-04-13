//Домашка 4.2 (Создание 10 текстовых файлов со случайными числами)

#include <fstream>
#include <ctime>

using namespace std;

//Функция получает в качестве аргумента имя файла,открывает его и записывает в него 10 случайных чисел от 0 до 9
void randomfile (char *symbol);

int main() 
	{
	int n=10;//Количество создаваемых файлов
	char filename[6]="A.txt";//Имя текущего файла
	for (int i=0;i<10;i++)
		{
		randomfile (filename);
		filename[0]+=1;//Первый символ в имени следующего файла увеличивается на 1
		}
return 0;
	}

void randomfile (char *symbol)
	{
	srand(time(0));
	ofstream fout;
	fout.open(symbol,ios::app);
	for (int i=1; i<=10;i++)//10-количество случайных чисел в каждом файле
		{
		fout<<rand()%10;
		}
	fout.close();
	}
