//Домашка 7.2 (Определение размера текстового файла input.txt)

#include <iostream>
#include <fstream>

using namespace std;

int main() 
{	
	char symbolFile;		//Символ, который мы считываем из файла
	ifstream fin;			// Создаем поток для чтения из файла
	fin.open("input.txt");
	int k=0;			//Счетчик для подсчитывания символов в файле
	fin.unsetf(ios::skipws);	//Указание не пропускать при считывании разделители (пробелы и Enter)
	while (fin)			//Считываем из потока пока не закончится файл или не появится иная ошибка			
	{
		fin>>symbolFile;	//Считывание очередного символа и запись его в переменную symbolFile
		cout<<symbolFile;
		k++;
	}
	fin.close();

	cout<<"file size "<<k-1<<" bytes"<<endl;	
	return 0;
}
