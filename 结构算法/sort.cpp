#include<iostream>
#include<vector> 
#include<time.h>
#include<ctime>
#include<cstdlib>
#include<algorithm>
using namespace std;

class Sort{
public:
void swap(int&,int&);
void quicksort(int, int);
void heapsort(int,int);
void fastsort(int,int);
void maxheap(int,int);
void insertsort(int,int);
void bubblesort(int,int);
void mergesort(int,int);
void test(int);
int* array;
};
inline void Sort::swap(int& a,int& b){
	a=a^b;
	b=a^b;
	a=a^b;
	return;
}
void Sort::fastsort(int s, int e){
	if((e-s)<=1000000){quicksort(s,e);return;}
	else{
		int t=(s+e)/2;
		int* tmp=new int[t-s+1];
		fastsort(s,t);
		fastsort(t+1,e);
		for(int i=0;i<=t-s;i++) tmp[i]=array[i+s];
		int p2=t+1;
		int i=0;
		int p1=s;
		while(i<=t-s){
			if(p2<=e&&array[p2]<tmp[i]){
				array[p1]=array[p2];
				p1++;
				p2++;
			}
			else {
				array[p1]=tmp[i];
				p1++;
				i++;}
		}
		delete tmp;
		tmp=NULL;
	}
	return;
}
	
void Sort::maxheap(int s, int e){
	int left=s*2+1;
	int right=left+1;
	if(left>e) return;
	if(right<=e && array[s]<array[right] && array[left]<=array[right]) {
		swap(array[s],array[right]); 
		maxheap(right,e);
		}
	else if((right>e && array[s]<array[left]) || (right<=e && array[s]<array[left] && array[right]<=array[left])) {
		swap(array[s],array[left]); 
		maxheap(left,e);
		}
	return;
}
void Sort::heapsort(int s,int e){
	for(int i=(e+1)/2-1;i>=s;i--) maxheap(i,e);
	int i=e;
	while(i>s){
		swap(array[s],array[i]);
		i--;
		maxheap(s,i);
	}
	return;
}
void Sort::quicksort(int s, int e){
	if((e-s)<=30){insertsort(s,e);return;}
	int tmp=array[s];
	int t=s;
	for(int i=s+1;i<=e;i++){
		if(array[i]<tmp){
			array[t]=array[i];
			array[i]=array[t+1];
			t++;
		}
	}
	array[t]=tmp;
	quicksort(s,t-1);
	quicksort(t+1,e);
	return;
}

void Sort::mergesort(int s, int e){
	int t=(s+e)/2;
	int* tmp=new int[t-s+1];
	if((e-s)<=50){insertsort(s,e);return;}
	mergesort(s,t);
	mergesort(t+1,e);
	for(int i=0;i<=t-s;i++) tmp[i]=array[i+s];
	int p2=t+1;
	int i=0;
	int p1=s;
	while(i<=t-s){
		if(p2<=e&&array[p2]<tmp[i]){
			array[p1]=array[p2];
			p1++;
			p2++;
			}
		else {
			array[p1]=tmp[i];
			p1++;
			i++;}
		}
	delete tmp;
	tmp=NULL;
	return;
}

void Sort::insertsort(int s,int e){
	for(int i=s+1;i<=e;i++){
		int t=i-1;
		int cur=i;
		int tmp=array[i];
		while(tmp<array[t] && t>=s){
			array[cur]=array[t];
			cur=t;
			t--;
		}
		array[cur]=tmp;
	}
}
	
void Sort::bubblesort(int s,int e){
	for(int i=e;i>=s;i--)
		for(int j=s;j<i;j++){
			if(array[j]>array[j+1]) swap(array[j],array[j+1]);
		}
}

	
void Sort::test(int n){
	clock_t start;
	clock_t end;
	array=new int[n];
	//std
	srand(int(time(0)));
	for(int i=0;i<n;i++){
		array[i]=rand();
	}
	start=clock();
	sort(array,array+n);
	end=clock();
	for(int i=0;i<n-1;i++){
		if(array[i]>array[i+1]) {cout<<"unsorted"<<endl; return;}
	}
	cout<<"stl sorted!"<<endl<<end-start<<"ms"<<endl;
	//quick
	for(int i=0;i<n;i++){
		array[i]=rand();
	}
	start=clock();
	quicksort(0,n-1);
	end=clock();
	for(int i=0;i<n-1;i++){
		if(array[i]>array[i+1]) {cout<<"unsorted"<<endl; return;}	
	}
	cout<<"quick sorted!"<<endl<<end-start<<"ms"<<endl;
	//heap
	for(int i=0;i<n;i++){
		array[i]=rand();
	}
	start=clock();
	fastsort(0,n-1);
	end=clock();
	for(int i=0;i<n-1;i++){
		//cout<<array[i]<<' ';
		if(array[i]>array[i+1]) {cout<<"unsorted"<<endl; return;}	
	}
	cout<<"fast sorted!"<<endl<<end-start<<"ms"<<endl;
	
	//merge
	for(int i=0;i<n;i++){
		array[i]=rand();
	}
	start=clock();
	mergesort(0,n-1);
	end=clock();
	for(int i=0;i<n-1;i++){
		if(array[i]>array[i+1]) {cout<<"unsorted"<<endl; return;}
	}
	cout<<"merge sorted!"<<endl<<end-start<<"ms"<<endl;
	
	delete array;
	array=NULL;
}


int main(){
	Sort sort;
	sort.test(10000000);
}