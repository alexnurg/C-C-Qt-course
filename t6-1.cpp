//Домашка 6.1 (Создание и вывод на консоль массива со случайными символами)

#include <iostream>
#include <ctime>

using namespace std;

int main() 
{
	const int n=10;//Количество случайных символов в массиве
	int number;
	unsigned char symbol[n];
	srand(time(0));
	for (int i=0;i<n;i++)
	{
		number=rand()%256;
		symbol[i]=(char) number;
		cout<<"("<<number<<")"<<symbol[i]<<" ";//Выводим на консоль код символа и сам символ, являющийся элементом массива	
	}
cout<<'\n';
return 0;
}


