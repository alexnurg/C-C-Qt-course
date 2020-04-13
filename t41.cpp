#include <iostream>
using namespace std;

int sum ();

int main (){
	int sumdate=sum();
    	cout<<"Sum of numbers: "<<sumdate<<endl;
return 0;
}

int sum(){
    	static int s_k=1;
    	static int s_sumdate=0;
	int date;
	
	if (s_k<4){
		cout<<"Input number of date "<<s_k<<": ";
		cin>>date;
		
		s_sumdate+=date;
		s_k++;

		sum();
			   }
	return s_sumdate;
		}    
    
