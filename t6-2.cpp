//Домашка 6.2 (Определение частоты использования символа в файле input.txt)

#include <iostream>
#include <cstdio>

using namespace std;

int main() 
{	

	//freopen("CON","r",stdin);Здесь есть вопрос к Константину


	char symbol;			//Символ, частоту появления которого в исходном файле нужно определить
	cout<<"Input symbol: ";
	cin>>symbol;

		
	char symbolFile;		//Символ, который мы считываем из файла
	freopen("input.txt","r",stdin);	//Перенаправление входного потока с консоли на файл для ввода
	int k=0;			//Счетчик для определения частоты использования символа в файле
	cin.unsetf(ios::skipws);	//Указание не пропускать при считывании разделители (пробелы и Enter)
	while (cin)			//Считываем из потока пока не закончится файл или не появится иная ошибка			
	{
		cin>>symbolFile;	//Считывание очередного символа и запись его в переменную symbolFile
		cout<<symbolFile;
		
		
		if (symbol==symbolFile)k++;
	}
	cout<<"k="<<k<<endl;		//Заданный символ встречается в тексте файла "к" раз*/
		
	
	fclose(stdin);
	

	return 0;
}
