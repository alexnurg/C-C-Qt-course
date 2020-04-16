//Домашка 7.1 (Цикл с goto)

#include <iostream>

using namespace std;

int main() 
{	

	int number=1;
	int n=100;//Количество чисел, которые нужно вывести в консоль
	
	start:
	if (number<=n)
	{
		cout<<number++<<" ";
		goto start;
	}
	return 0;
}

