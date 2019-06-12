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
	bool *row, *left, *right;
	void putQueen(int,int);
	void speedQueen(int,int,int,int,int);
};

Queen::Queen(){
	squares=8;
	number=0;
	row=new bool[8];
	left=new bool[15];
	right=new bool[15];

	for(int i=0; i<15;i++){
		if(i<8){
			row[i]=true;
			
		}
		left[i]=true;
		right[i]=true;
	}
}

Queen::Queen(int n){
	squares=n;
	number=0;
	row=new bool[n];
	left=new bool[2*n-1];
	right=new bool[2*n-1];

	for(int i=0; i<(2*n-1);i++){
		if(i<n){
			row[i]=true;
			
		}
		left[i]=true;
		right[i]=true;
	}
}

void Queen::putQueen(int n,int k){
	if(n==squares) {number++; return;}
	for(int i=0;i<k;i++)
	if(left[n+i]&&right[n-i+squares-1]&&row[i]){
		left[n+i]=false;
		right[n-i+squares-1]=false;
		row[i]=false;
		if(n==0 && squares%2 && i==(k-1)) putQueen(1,(squares)/2);
		else putQueen(n+1,squares);
		left[n+i]=true;
		right[n-i+squares-1]=true;
		row[i]=true;	
	}	
}

void Queen::speedQueen(int n, int k,int pos,int rig,int lef){
	if(n==squares) {number++; return;}
	unsigned int temp=pos|lef|rig;
	for(int i=0;i<k;i++)
		if(!(temp&(1<<i))){
			if(n==0 && squares%2 && i==(k-1)) speedQueen(1,(squares)/2,pos^(1<<i),(rig^(1<<i))>>1,(lef^(1<<i))<<1);
			else speedQueen(n+1,squares,pos^(1<<i),(rig^(1<<i))>>1,(lef^(1<<i))<<1);
		}
	
}

void Queen::solution(){
	clock_t start;
	clock_t end;
	start=clock();
	speedQueen(0,(squares+1)/2,0,0,0);
	end=clock();
	cout<<2*number<<' '<<end-start<<endl;
}

int main(){
	for(int i=1;i<17;i++){
		Queen a(i);
		a.solution();}
}
