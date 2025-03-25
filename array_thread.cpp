#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace std::chrono;

int* generateArray(int n){
	int* arr = new int[n];
	srand(time(0));
	for(int i=0;i<n;i++){
		arr[i]=rand()%100+1;
	}
	return arr;
}

int seqSum(int* arr,int n){
	int sum=0;
	for(int i=0;i<n;i++){
		sum+=arr[i];
	}
	return sum;
}

bool searchSeq(int* arr,int n,int key){
	for(int i=0;i<n;i++){
		if(arr[i]==key){
			return true;
		}
	}
	return false;
}

void paraSum(int* arr,int start,int end,int& result){
	int local_sum = 0;
	for(int i=start ; i<end ; i++){
		local_sum += arr[i];
	}
	result = local_sum;
}

void paraSearch(int* arr,int start,int end ,int key,bool& found){
	for(int i=start; i<end; i++){
		if(arr[i]==key){
			found=true;
			return;
		}
	}
}

int main(){
	
	int n,key;
	cout<<"Enter size of array : " ;
	cin>>n;
	cout<<"Enter key to search : ";
	cin>>key;

	int* arr = generateArray(n);
	
	cout<<"\n=== Sequential execution ===\n";
	
	auto start = high_resolution_clock::now();
	int sum_seq = seqSum(arr,n);
	auto end = high_resolution_clock::now();
	auto duration_seq_sum = duration_cast<microseconds>(end - start);
	cout<<"Sequential sum : "<<sum_seq<<endl;
	cout<<"Time taken for sequential sum : "<<duration_seq_sum.count()<<" microsec"<<endl;

	
	start = high_resolution_clock::now();
	bool found_seq = searchSeq(arr, n, key);
    end = high_resolution_clock::now();
    auto duration_seq_search = duration_cast<microseconds>(end - start);
    cout << "Sequential Search: " << (found_seq ? "Found" : "Not Found") << endl;
    cout << "Time taken for search: " << duration_seq_search.count() << " microseconds" << endl;

	cout<<"\n=== Thread Execution ===\n";
	int mid = n/2;
	int sum1 = 0,sum2 = 0;
	bool found1 = false, found2 = false;
	
	start = high_resolution_clock::now();
	thread t1(paraSum,arr,0,mid,ref(sum1));
	thread t2(paraSum,arr,mid,n,ref(sum2));
	t1.join();
	t2.join();
	
	int sum_thread = sum1+sum2;
	end = high_resolution_clock::now();
	auto duration_thread_sum = duration_cast<microseconds>(end - start);
	cout<<"parallel sum : "<<sum_thread<<endl;
	cout<<"Time taken : "<<duration_thread_sum.count()<<" microseconds"<<endl;

	start = high_resolution_clock::now();
    thread t3(paraSearch, arr, 0, mid, key, ref(found1));
   	thread t4(paraSearch, arr, mid, n, key, ref(found2));
   	t3.join();
   	t4.join();
   	bool found_thread = found1 || found2;
   	end = high_resolution_clock::now();
   	auto duration_thread_search = duration_cast<microseconds>(end - start);
   	cout << "Threaded Search: " << (found_thread ? "Found" : "Not Found") << endl;
   	cout << "Time taken for search: " << duration_thread_search.count() << " microseconds" << endl;
	
	return 0;
}
