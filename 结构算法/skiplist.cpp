#include<iostream>
#include<time.h>
using namespace std;

const int maxLevel=10;
template<class T>
class Node{
public:
	Node(){}
	T info;
	Node** next;
};

template<class T>
class Skiplist{
public:
	Skiplist();
	bool empty() const {
		return root[0]==0;
	}
	void choosePowers();
	int chooseLevel();
	T* skipSearch(const T&);
	void skipInsert(const T&);
private:
	Node<T>* root[maxLevel];
	int powers[maxLevel];
};

template<class T>
Skiplist<T>::Skiplist(){
	choosePowers();
	for(int i=0;i<maxLevel;i++)
		root[i]=0;
}

template<class T>
void Skiplist<T>::choosePowers(){
	powers[0]=(2<<(maxLevel-1));
	for(int i=1;i<maxLevel;i++)
		powers[i]=powers[i-1]-(2<<(maxLevel-i-1));
}

template<class T>
int Skiplist<T>::chooseLevel(){
	int i;
	int r=rand()%(powers[0])+1;
	for(i=maxLevel-1;i>=1;i--)
		if(r<powers[i])
			return i;
	return i;
}

template<class T>
void Skiplist<T>::skipInsert(const T& el){
	int level=chooseLevel();
	Node<T> *prev[maxLevel], *tmp[maxLevel],*newNode;
	tmp[maxLevel-1]=root[maxLevel-1];
	prev[maxLevel-1]=0;
	for(int i=maxLevel-1;i>=0;i--){                                 //由上而下遍历所有层数，把prev和tmp放到最后一层
		while(tmp[i]!=0 && el>tmp[i]->info) {                   //搜索当前层的可以插入的地方的prev和tmp for不能用
			prev[i]=tmp[i];
			tmp[i]=*(tmp[i]->next+i);
		}
		if(i>0){                                                //没到最下层就给下一层指针赋值
			if(prev[i]==0){
				prev[i-1]=0;
				tmp[i-1]=root[i-1];
			}
			else{
				tmp[i-1]=*(prev[i]->next+i-1);                 //减一层tmp等于上一层prev的-1层的指向，返回前一个节点准备重新搜索
				prev[i-1]=prev[i];
			}
		}
	}
	newNode=new Node<T>;
	newNode->next=new Node<T>*[level+1];
	newNode->info=el;
	for(int i=0;i<=level;i++){
		*(newNode->next+i)=tmp[i];
		if(!prev[i])
			root[i]=newNode;
		else	
			*(prev[i]->next+i)=newNode;
	}

}

template<class T>
T* Skiplist<T>::skipSearch(const T& el){
	if(empty()) return 0;
	Node<T> *prev,*tmp;
	int i=maxLevel-1;
	tmp=root[i];
	prev=0;
	while(i>=0){
		while(tmp&&tmp->info<el){
			prev=tmp;
			tmp=*(tmp->next+i);
		}
		if(tmp && tmp->info==el) return &tmp->info;
		if(i>0){
			if(prev) tmp=*(prev->next+i-1);
			else tmp=root[i-1];
		}

		i--;
	}
	return 0;
}

int main(){
	clock_t start;
	clock_t end;
	Skiplist<int> a;
	for(int i=0;i<1000000;i++)
	{
		int k=rand();
		a.skipInsert(k);
	}
	start=clock();
	for(int i=100000;i<200000;i++)
		a.skipSearch(i);

	end=clock();
	cout<<end-start;
	cin>>end;
	
}