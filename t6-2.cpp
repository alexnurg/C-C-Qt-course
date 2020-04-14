//Домашка 6.2 (Определение частоты использования символа в файле input.txt)

#include <iostream>
#include <cstdio>

using namespace std;

int main() 
{	

	//freopen("CON","r",stdin);Здесь есть вопрос к Константину


	char symbol;//Символ, частоту появления которого в исходном файле нужно определить
	cout<<"Input symbol: ";
	cin>>symbol;

		
	string story;
	freopen("input.txt","r",stdin);//Перенаправление входного потока с консоли на файл для ввода
	getline(cin,story,'.');//Считывание данных из файла и запись их в строковую переменную	
	
	fclose(stdin);
	cout<<story<<'\n';

	int k=0;
	for (int i=0;story[i];i++)
	{
		if (symbol==story[i])k++;
	}
	cout<<"k="<<k<<endl;//Заданный символ встречается в тексте файла "к" раз

return 0;
}

