#include <iostream>
#include <thread>

void printNatural(int n){
	for(int i=1;i<=n;i++){
		std::cout<<i<<" ";
	}
}

int main(){

	int n;
	
	std::cout<<"Enter number N : ";
	std::cin>>n;
	
	std::thread t(printNatural,n);
	
	t.join();

	std::cout<<"Thread done";

	return 0;
}
