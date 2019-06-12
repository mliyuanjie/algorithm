#include<iostream>
#include<time.h>
using namespace std;

class Queen{
public:
	Queen();
	Queen(int);
	void solution();
private:
    int squares;
	int number;
	int *res;
	void putQueen();
	void speedQueen();
	bool check(int);
};

Queen::Queen(){
	squares=8;
	number=0;
	res=new int[8];
	for(int i=0; i<8;i++) res[i]=-1;
}

Queen::Queen(int n){
	squares=n;
	number=0;
	res=new int[n];
	for(int i=0; i<n;i++) res[i]=-1;
}
bool Queen::check(int i){
	for(int j=0;j<i;j++)
		if((res[i]==res[j])||(int)abs(res[j]-res[i])==(i-j))
			return false;
	return true;
}
void Queen::putQueen(){
	int i=0;	
	while(i>=0){
		res[i]++;
		if(res[i]>=squares){res[i]=-1;i--;}
		else if(check(i)){
			if(i<squares)i++;
			else if(i==squares)number++;		
		}	
	}
}

void Queen::solution(){
	clock_t start;
	clock_t end;
	start=clock();
	putQueen();
	end=clock();
	cout<<number<<' '<<end-start<<endl;
}
int main(){
	for(int i=1;i<17;i++){
		Queen a(i);
		a.solution();}
}

