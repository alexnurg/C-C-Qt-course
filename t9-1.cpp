//Домашка 9.1 (Сравнение времени выполнения сортировок)

#include <iostream>
#include <ctime>
#include <iomanip>
#include <algorithm>
using namespace std;

void genarray(int *array, int m);		//Функция генерирует массив целых чисел размерности "м" в диапазоне 0-999

//void print_array (int *array, int m);		//Функция выводит в консоль массив целых чисел 
//void print_array (double *array,int m);	//Функция выводит в консоль массив вещественных чисел

double sortpuz (int *array, int m);		//Функция сортирует массив методом "пузырька" и возвращает время выполнения
double sortmin (int *array, int m);		//Функция сортирует массив поиском минимума и возвращает время выполнения
double sortq (int *array, int m);		//Функция сортирует массив с помощью функции sort и возвращает время выполнения

double average_time (double *array, int p);	//Функция вычисляет среднее значение элементов массива

int main() 
{	
	const int n=10000;			//Количество элементов сортируемого массива
	int nums1 [n];				//Массив 1 для сортировки пузырьком
	int nums2 [n];				//Копия массива 1 для сортировки минимумом
	int nums3 [n];				//Копия массива 1 для быстрой сортировки
	const int k=10;				//Количество замеров времени выполнения сортировок
	double time_sortpuz[k];			//Массив для хранения времени выполнения сортировки пузырьком
	double time_sortmin[k];			//Массив для хранения времени выполнения сортировки поиском минимума
	double time_sortq[k];			//Массив для хранения времени выполнения быстрой сортировки (sort)

	for (int i=0;i<k;i++)
	{
		genarray (nums1,n);
		for (int j=0;j<n;j++)		//Цикл для создания 2-х копий сгенерированного массива случайных чисел
		{
			nums2[j]=nums1[j];
			nums3[j]=nums1[j];
		}
	
		time_sortpuz[i]=sortpuz(nums1,n);//Запись результатов замеров времени сортировок в массивы
		time_sortmin[i]=sortmin(nums2,n);
		time_sortq[i]=sortq(nums3,n);
	
	}
	cout<<"\n"<<"Average time of sortpuz: "<<average_time(time_sortpuz,k)<<" sec\n";//Выводим в консоль среднее время сорт.пузырьком
	cout<<"\n"<<"Average time of sortmin: "<<average_time(time_sortmin,k)<<" sec\n";//Выводим в консоль среднее время сорт.минимумом
	cout<<"\n"<<"Average time of quick sort: "<<average_time(time_sortq,k)<<" sec\n";//Выводим в консоль среднее время быстрой сорт.
	return 0;
}

void genarray(int *array,int m)
{
	srand(time(0));
	for (int i=0;i<m;i++)
	{
		array[i]=rand()%1000;
	}
}

void print_array (int *array,int m)
{
	for (int i =0;i<m;i++)
	{
		cout<<setw(8)<<array[i];
	}
}

void print_array (double *array,int m)
{
	for (int i =0;i<m;i++)
	{
		cout<<setw(10)<<array[i];
	}
}

double sortpuz (int *array, int m)
{
	clock_t time_sortpuz=clock();
	
	for (int i=1;i<=m-1;i++)
	{
		for (int j=0;j<m-i;j++)
		{
			if (array[j]>array[j+1])
			{
				int buf=array[j];
				array[j]=array[j+1];
				array[j+1]=buf;
			}
		}
	}
	time_sortpuz=clock()-time_sortpuz;
	
	double time_sortpuz_sec=(double)time_sortpuz/CLOCKS_PER_SEC;
	
	return time_sortpuz_sec;
}

double average_time (double *array, int p)
{
	double a_time=0;
	for (int i=0;i<p;i++)
	{a_time+=array[i];}
	return a_time/p;
}

double sortmin (int *array, int m)	
{
	clock_t time_sortmin=clock();
	
	for (int i=0;i<m;i++)
	{
		int min=array[i];
		int nmin=i;

		for (int j=i+1;j<m;j++)
		{
			if (array[j]<min)
			{
				min=array[j];
				nmin=j;
			}
		}
		array[nmin]=array[i];
		array[i]=min;			
	}
	time_sortmin=clock()-time_sortmin;
	
	double time_sortmin_sec=(double)time_sortmin/CLOCKS_PER_SEC;
	
	return time_sortmin_sec;
}

double sortq (int *array, int m)
{
	clock_t time_sortq=clock();
	sort(array,array+m);
	time_sortq=clock()-time_sortq;
	double time_sortq_sec=(double)time_sortq/CLOCKS_PER_SEC;
	return time_sortq_sec;
}
