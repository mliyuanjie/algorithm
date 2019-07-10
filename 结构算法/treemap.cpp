#include<iostream>
#include<stack>
#include<time.h>
#include<ctime>
#include<cstdlib>
#include<map>
using namespace std;

template<class K, class T>
class treeNode{
public:
	K _key;
	T _value;
	int height;
	treeNode* left;
	treeNode* right;
	treeNode(K key, T value){
		_key=key;
		_value=value;
		height=0;
		left=nullptr;
		right=nullptr;
	}
};

template<class K, class T>
class AVLTree{
private:
	treeNode<K,T>* rotateR(treeNode<K,T>*);
	treeNode<K,T>* rotateL(treeNode<K,T>*);
	treeNode<K,T>* rotateRL(treeNode<K,T>*);
	treeNode<K,T>* rotateLR(treeNode<K,T>*);
	treeNode<K,T>* rebalance(treeNode<K,T>*);
	inline int height(treeNode<K, T>* cur){
		if(cur==nullptr) return -1;
		return cur->height;
		}

public:
	treeNode<K,T>* root;
	int balance;
	int R=0;
	int L=0;
	int RL=0;
	int LR=0;
	stack<treeNode<K,T>*> myst;
	AVLTree(){
		root=nullptr;
		balance=0;
	}
	~AVLTree(){
		clear(root);
	}
	void insert(const K&, const T&);
	void remove(const K&);
	void print(treeNode<K,T>*);
	void clear(treeNode<K,T>*);
	bool find(const K&);
	T get(const K&);
	bool empty(){
		if(root==nullptr) return true;
		else return false;
	}
};

template<class K, class T>
treeNode<K, T>* AVLTree<K, T>::rotateR(treeNode<K, T>* Q){
	treeNode<K,T>* P;
	P=Q;
	Q=P->left;
	P->left=Q->right;
	Q->right=P;
	P->height=max(height(P->left),height(P->right))+1;
	return Q;
}
template<class K, class T>
treeNode<K, T>* AVLTree<K, T>::rotateL(treeNode<K, T>* Q){
	treeNode<K, T>* P;
	P=Q;
	Q=P->right;
	P->right=Q->left;
	Q->left=P;
	P->height=max(height(P->left),height(P->right))+1;
	return Q;
}
template<class K, class T>
treeNode<K, T>* AVLTree<K, T>::rotateLR(treeNode<K, T>* Q){
	treeNode<K,T>* P;
	treeNode<K,T>* R;
	P=Q;
	R=P->left;
	Q=P->left->right;
	R->right=Q->left;
	Q->left=R;
	P->left=Q->right;
	Q->right=P;
	P->height=max(height(P->left),height(P->right))+1;
	R->height=max(height(R->left),height(R->right))+1;
	return Q;
}
template<class K, class T>
treeNode<K, T>* AVLTree<K, T>::rotateRL(treeNode<K, T>* Q){
	treeNode<K,T>* P;
	treeNode<K,T>* R;
	P=Q;
	R=P->right;
	Q=P->right->left;
	R->left=Q->right;
	Q->right=R;
	P->right=Q->left;
	Q->left=P;
	P->height=max(height(P->left),height(P->right))+1;
	R->height=max(height(R->left),height(R->right))+1;
	return Q;
}
template<class K, class T>
treeNode<K, T>* AVLTree<K, T>::rebalance(treeNode<K, T>* Q){
	if(balance==2 && (height(Q->right->right)-height(Q->right->left)==1))
	{Q=rotateL(Q);L++;}
	else if(balance==-2 && (height(Q->left->right)-height(Q->left->left)==-1))
	{Q=rotateR(Q);R++;}
	else if(balance==2 && (height(Q->right->right)-height(Q->right->left)==-1))
	{Q=rotateRL(Q);RL++;}
	else if(balance==-2 && (height(Q->left->right)-height(Q->left->left)==1))
	{Q=rotateLR(Q);LR++;}
	return Q;
}

template<class K, class T>
void AVLTree<K,T>::insert(const K& key,const T& value){
	treeNode<K,T>* Q;
	Q=root;
	if(root==nullptr) {root=new treeNode<K,T>(key,value); return;}
	while(Q){
		myst.push(Q);
		if(key>Q->_key){
			if(Q->right==nullptr){
				Q->right=new treeNode<K,T>(key,value); 
				break;
				}
			Q=Q->right;
		}
		else if(key<Q->_key){
			if(Q->left==nullptr){
				Q->left=new treeNode<K,T>(key,value);
				break;
				}
			Q=Q->left;
		}
		else return;
	}
	//寻找插入点
	while(!myst.empty()){
		Q=myst.top();
		myst.pop();
		balance=height(Q->right)-height(Q->left);
		//cout<<"ba:"<<balance<<endl;
		//cout<<Q->_key<<endl;
		if(balance==2 || balance==-2){
			if(Q==root) root=rebalance(Q);
			else if(myst.top()->_key>Q->_key) myst.top()->left=rebalance(Q);
			else if(myst.top()->_key<Q->_key) myst.top()->right=rebalance(Q);
		}
		Q->height=max(height(Q->left),height(Q->right))+1;
	}
	//cout<<key<<endl;
	//更新height,旋转
	return;
}

template<class K, class T>
void AVLTree<K,T>::remove(const K& key){
	treeNode<K,T>* Q;
	treeNode<K,T>* P;
	treeNode<K,T>* tmp;
	P=root;
	Q=root;
	//找到待删除的点，栈记录
	while(Q&&key!=Q->_key){
		P=Q;
		myst.push(Q);
		if(key>Q->_key) Q=Q->right;
		else if(key<Q->_key) Q=Q->left;
	}
	tmp=Q;
	if(Q==nullptr) return;
	//case 1
	if(Q->right==nullptr){
		if(P==root) root=tmp->left;
		else if(P->_key>tmp->_key) P->left=tmp->left;
		else if(P->_key<tmp->_key) P->right=tmp->left;
		delete tmp;
		while(!myst.empty()){
			Q=myst.top();
			myst.pop();
			balance=height(Q->right)-height(Q->left);
			if(balance==2 || balance==-2){
				if(Q==root) root=rebalance(Q);
				else if(myst.top()->_key>Q->_key) myst.top()->left=rebalance(Q);
				else if(myst.top()->_key<Q->_key) myst.top()->right=rebalance(Q);
			}
			Q->height=max(height(Q->left),height(Q->right))+1;
		}
	}
	//case 2
	else if(Q->right->left==nullptr){
		if(tmp==root){
			root=tmp->right;
			myst.push(root);
			tmp->right->left=tmp->left;
		}
		else if(P->_key>tmp->_key){
			P->left=tmp->right;
			myst.push(P->left);
			tmp->right->left=tmp->left;
		}
		else if(P->_key<tmp->_key){
			P->right=tmp->right;
			myst.push(P->right);
			tmp->right->left=tmp->left;
		}
		delete tmp; 
		while(!myst.empty()){
			Q=myst.top();
			myst.pop();
			balance=height(Q->right)-height(Q->left);
			if(balance==2 || balance==-2){
				if(Q==root) root=rebalance(Q);
				else if(myst.top()->_key>Q->_key) myst.top()->left=rebalance(Q);
				else if(myst.top()->_key<Q->_key) myst.top()->right=rebalance(Q);
			}
			Q->height=max(height(Q->left),height(Q->right))+1;
		}
	}
	//case 3
	else{
		Q=Q->right;
		while(Q->left){
			myst.push(Q);
			Q=Q->left;
		}
		myst.top()->left=Q->right;
		Q->left=tmp->left;
		Q->right=tmp->right;
		if(tmp==root) root=Q;
		else if(P->_key>tmp->_key) P->left=Q;
		else if(P->_key<tmp->_key) P->right=Q;
		delete tmp;
		tmp=Q;
		while(!myst.empty()){
			Q=myst.top();
			if(Q==P){
				balance=height(tmp->right)-height(tmp->left);
				if(balance==2 || balance==-2){
					if(tmp==root) root=rebalance(tmp);
					else if(P->_key>tmp->_key) P->left=rebalance(tmp);
					else if(P->_key<tmp->_key) P->right=rebalance(tmp);
				}
				tmp->height=max(height(tmp->left),height(tmp->right))+1;
				
			}
			myst.pop();
			balance=height(Q->right)-height(Q->left);
			if(balance==2 || balance==-2){
				if(Q==root) root=rebalance(Q);
				else if(myst.top()->_key>Q->_key) myst.top()->left=rebalance(Q);
				else if(myst.top()->_key<Q->_key) myst.top()->right=rebalance(Q);
			}
			Q->height=max(height(Q->left),height(Q->right))+1;
		}
		
	}
	//cout<<'s';
	return;
}

template<class K, class T>
bool AVLTree<K,T>::find(const K& key){
	treeNode<K,T>* Q;
	Q=root;
	while(Q){
		if(Q->_key>key) Q=Q->left;
		else if(Q->_key<key) Q=Q->right;
		else return true;
	}
	return false;
}

template<class K, class T>
T AVLTree<K,T>::get(const K& key){
	treeNode<K,T>* Q;
	Q=root;
	while(Q){
		if(Q->_key>key) Q=Q->left;
		else if(Q->_key<key) Q=Q->right;
		else return Q->_value;
	}
	return 0;
}

template<class K, class T>
void AVLTree<K,T>::clear(treeNode<K,T>* Q){
	if(Q==root){
		delete root;
		root=nullptr;
		return;
	}
	clear(Q->left);
	clear(Q->right);
	cout<<Q->_key<<endl;
	delete Q;
	return;
}
template<class K, class T>
void AVLTree<K,T>::print(treeNode<K,T>* Q){
	if(!Q) return;
	print(Q->left);
	cout<<Q->_key<<':'<<Q->_value<<' ';
	print(Q->right);
	return;
}


int main(){
	AVLTree<int,int> a;
	map<int,int>b;
	clock_t start;
	clock_t end;
	start=clock();
	srand(int(time(0)));
	for(int i=0;i<1000000;i++){
		a.insert(rand(),i);
	}
	end=clock();
	cout<<"insert 20point:"<<end-start<<"ms"<<endl;
	cout<<"right:"<<a.R<<endl;
	cout<<"left:"<<a.L<<endl;
	cout<<"right and left:"<<a.RL<<endl;
	cout<<"left and right:"<<a.LR<<endl;
	start=clock();
	int n=0;
	for(int i=0;i<100;i++){
		if(a.find(rand()))
			n++;
	}
	end=clock();
	cout<<"find 1000000point:"<<n<<endl;
	
}
