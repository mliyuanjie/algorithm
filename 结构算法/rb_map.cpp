#include<iostream>
#include<stack>
#include<time.h>
#include<ctime>
#include<cstdlib>
#include<map>
#include<deque>
using namespace std;

template<class K,class T>
class RBNode{
public:
	bool red;
	RBNode* left;
	RBNode* right;
	K _key;
	T _value;
	RBNode(K key, T value){
		_key=key;
		_value=value;
		left=nullptr;
		right=nullptr;
		red=true;
	}
};
template<class K, class T>
class RBTree{
public:
	RBNode<K,T>* root;
	RBTree(){
		root=nullptr;
	}
	void insert(const K&,const T&);
	void remove(const K&);
	bool find(const K&);
	void print(RBNode<K,T>*);
	void clear(RBNode<K,T>*);
	bool empty(){
		if(root==nullptr) return true;
		else return false;
	}
private:
	stack<RBNode<K,T>*> myst;
	RBNode<K,T>* rotateL(RBNode<K,T>*);
	RBNode<K,T>* rotateR(RBNode<K,T>*);
	RBNode<K,T>* rotateLR(RBNode<K,T>*);
	RBNode<K,T>* rotateRL(RBNode<K,T>*);
	RBNode<K,T>* rebalance(RBNode<K,T>*);
	void replace(RBNode<K,T>*,RBNode<K,T>*,RBNode<K,T>*,RBNode<K,T>*);
	inline bool colors(RBNode<K,T>* cur){
		if(!cur) return false;
		else return cur->red;
	}
};
template<class K, class T>
RBNode<K, T>* RBTree<K, T>::rotateR(RBNode<K, T>* Q){
	RBNode<K,T>* P;
	P=Q;
	Q=P->left;
	P->left=Q->right;
	Q->right=P;
	return Q;
}
template<class K, class T>
RBNode<K, T>* RBTree<K, T>::rotateL(RBNode<K, T>* Q){
	RBNode<K, T>* P;
	P=Q;
	Q=P->right;
	P->right=Q->left;
	Q->left=P;
	return Q;
}
template<class K, class T>
RBNode<K, T>* RBTree<K, T>::rotateLR(RBNode<K, T>* Q){
	RBNode<K,T>* P;
	RBNode<K,T>* R;
	P=Q;
	R=P->left;
	Q=P->left->right;
	R->right=Q->left;
	Q->left=R;
	P->left=Q->right;
	Q->right=P;
	return Q;
}
template<class K, class T>
RBNode<K, T>* RBTree<K, T>::rotateRL(RBNode<K, T>* Q){
	RBNode<K,T>* P;
	RBNode<K,T>* R;
	P=Q;
	R=P->right;
	Q=P->right->left;
	R->left=Q->right;
	Q->right=R;
	P->right=Q->left;
	Q->left=P;
	return Q;
}

template<class K,class T>
void RBTree<K,T>::insert(const K& key,const T& value){
	while(!myst.empty()) myst.pop();
	RBNode<K,T>* Q;
	RBNode<K,T>* P;
	RBNode<K,T>* G;
	RBNode<K,T>* tmp;
	P=root;
	Q=new RBNode<K,T>(key,value);

	if(!root){
		root=Q;
		Q->red=false;
		return;
	}
	while(P){
		myst.push(P);
		if(P->_key>key){
			if(P->left==nullptr){
				P->left=Q;
				break;
				}
			P=P->left;
		}
		else if(P->_key<key){
			if(P->right==nullptr){
				P->right=Q;
				break;
			}
			P=P->right;
		}
		else
			return;
	}
	myst.push(Q);
	while(!myst.empty()){
		Q=myst.top();
		myst.pop();
		if(Q==root) {root->red=false;return;}
		P=myst.top();
		myst.pop();
		if(!colors(P)){
			return;
		}
		//根节点的情况
		G=myst.top();
		myst.pop();
		//case·1
		if(colors(G->left)&&colors(G->right)){
			G->red=true;
			G->left->red=false;
			G->right->red=false;
			myst.push(G);
		}
		//case·23
		else{
			if((P->right==Q) && (G->right==P)){
				G->red=true;
				P->red=false;
				if(G==root)
					root=rotateL(G);
				else{
					tmp=myst.top();
					if(tmp->right==G) tmp->right=rotateL(G);
					else tmp->left=rotateL(G);
				}
				return;
			}
			else if((P->left==Q) && (G->left==P)){
				G->red=true;
				P->red=false;
				if(G==root)
					root=rotateR(G);
				else{
					tmp=myst.top();
					if(tmp->right==G) tmp->right=rotateR(G);
					else tmp->left=rotateR(G);
				}
				return;
			}
			else if((P->right==Q) && (G->left==P)){
				G->red=true;
				Q->red=false;
				if(G==root)
					root=rotateLR(G);
				else{
					tmp=myst.top();
					if(tmp->right==G) tmp->right=rotateLR(G);
					else tmp->left=rotateLR(G);
				}
				return;
			}
			else{
				G->red=true;
				Q->red=false;
				if(G==root)
					root=rotateRL(G);
				else{
					tmp=myst.top();
					if(tmp->right==G) tmp->right=rotateRL(G);
					else tmp->left=rotateRL(G);
				}
				return;
			}
		}
	}
	return;
}

template<class K,class T>
void RBTree<K,T>::replace(RBNode<K,T>* Q_del, RBNode<K,T>* P_del,RBNode<K,T>* Q_rep, RBNode<K,T>* P_rep){
	if(!P_rep) Q_rep->left=Q_del->left;
	else {

		P_rep->left=Q_rep->right;
		Q_rep->left=Q_del->left;
		Q_rep->right=Q_del->right;

	}

	if(!P_del) root=Q_rep;
	else if(P_del->left==Q_del) P_del->left=Q_rep;
	else P_del->right=Q_rep;
	Q_rep->red=colors(Q_del);
	delete Q_del;
	Q_del=nullptr;
}

template<class K,class T>
void RBTree<K,T>::remove(const K& key){
	print(root);
	while(!myst.empty()) myst.pop();
	RBNode<K,T>* Q;
	RBNode<K,T>* P;
	RBNode<K,T>* tmp;
	Q=root;
	while(Q){
		if(key>Q->_key){
			myst.push(Q);
			Q=Q->right;
		}
		else if(key<Q->_key){
			myst.push(Q);
			Q=Q->left;
		}
		else break;
	}

	bool color;
	if(Q==nullptr) return;
	if(Q->right==nullptr || Q->left==nullptr){
		color=Q->red;
		if(Q==root){
			root=(Q->right) ? Q->right : Q->left;
			myst.push(root);
			
		}
		else{
			P=myst.top();
			if(P->left==Q){
				P->left=(Q->right) ? Q->right : Q->left;
				myst.push(P->left);
			}
			else{
				P->right=(Q->right) ? Q->right : Q->left;
				myst.push(P->right);
			}
		}
		delete Q;
		Q=nullptr;
		
	}
	else{
		tmp=Q;
		Q=Q->right;
		deque<RBNode<K,T>*> que;
		while(Q->left){
			que.push_back(Q);
			Q=Q->left;
		}
		color=Q->red;
		if(!myst.empty() && que.empty())
			replace(tmp,myst.top(),Q,nullptr);
		else if(myst.empty() && !que.empty())
			replace(tmp,nullptr,Q,que.back());
		else if(myst.empty() && que.empty())
			replace(tmp,nullptr,Q,nullptr);
		else
			replace(tmp,myst.top(),Q,que.back());
		tmp=nullptr;
		myst.push(Q);

		if(que.empty()) myst.push(myst.top()->right);
		else{
			while(!que.empty()){
			myst.push(que.front());
			que.pop_front();
			}
			myst.push(myst.top()->left);
		}
		
	}
	print(root);
	//已替换待删除的点，转为六种基本情况
	if(color) return;
	while(!myst.empty()){
		Q=myst.top();
		myst.pop();
		//case1
		if(colors(Q)) {Q->red=false; return;}
		if(Q==root) return;
		P=myst.top();
		myst.pop();
		if(Q==P->left){
			RBNode<K,T>* S;
			S=P->right;
			//case5 s左子为红
			if(S && colors(S->left)){

				S=rotateR(S);
				S->red=false;
				S->right->red=true;
				P->right=S;

			}
			//case6 s右子为红，即可平衡
			if(S && colors(S->right)){
				P=rotateL(P);
				P->red=colors(P->left);
				P->left->red=false;
				P->right->red=false;
				if(myst.empty()) root=P;
				else if(myst.top()->_key>P->_key) myst.top()->left=P;
				else myst.top()->right=P;
				return;
			}
			if(!colors(P)){

				//case2 P黑S红
				if(colors(S)){
					P=rotateL(P);\
					P->red=false;
					P->left->red=true;
					if(myst.empty()) root=P;
					else if(myst.top()->_key>P->_key) myst.top()->left=P;
					else myst.top()->right=P;
					myst.push(P);
					myst.push(P->left);
					myst.push(P->left->left);
				}
				//case3 P黑S黑
				else{
					P->right->red=true;
					myst.push(P);

				}
			}
			//case4 P红
			else{
				P->red=false;
				P->right->red=true;
				return;
			}
		}
		else if(Q==P->right){
			RBNode<K,T>* S;
			S=P->left;
			//Q兄弟的右子红
			if(S && colors(S->right)){
				S=rotateL(S);
				S->red=false;
				S->left->red=true;
				P->left=S;
			}
			//Q兄弟的左子红
			if(S && colors(S->left)){
				P=rotateR(P);
				P->red=colors(P->right);
				P->right->red=false;
				P->left->red=false;
				if(myst.empty()) root=P;
				else if(myst.top()->_key>P->_key) myst.top()->left=P;
				else myst.top()->right=P;
				return;
			}
			if(!colors(P)){
				if(colors(S)){
					P=rotateR(P);
					P->red=false;
					P->right->red=true;
					if(myst.empty()) root=P;
					else if(myst.top()->_key>P->_key) myst.top()->left=P;
					else myst.top()->right=P;
					myst.push(P);
					myst.push(P->right);
					myst.push(P->right->right);
				}
				else{
					P->left->red=true;
					myst.push(P);
				}
			}
			else{
				P->red=false;
				P->left->red=true;
				return;
			}
		}
	}
	return;
}

template<class K,class T>
bool RBTree<K,T>::find(const K& key){
	RBNode<K,T>* Q;
	Q=root;
	while(Q){
		if(Q->_key>key) Q=Q->left;
		else if(Q->_key<key) Q=Q->right;
		else return true;
	}
	return false;
}

template<class K, class T>
void RBTree<K,T>::clear(RBNode<K,T>* Q){
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
void RBTree<K,T>::print(RBNode<K,T>* Q){
	if(!Q) return;
	print(Q->left);
	cout<<Q->_key<<':'<<Q->_value<<"color:"<<Q->red<<' ';
	print(Q->right);
	return;
}

int main(){
	RBTree<int,int> a;
	map<int,int>b;
	clock_t start;
	clock_t end;
	start=clock();
	srand(int(time(0)));
	for(int i=0;i<20;i++){
		a.insert(i,i);
	}
	end=clock();
	cout<<"insert 10point:"<<end-start<<"ms"<<endl;
	//a.print(a.root);
	cout<<endl;
	start=clock();

	for(int i=0;i<30;i++){
		a.remove(i);
		cout<<endl;
	
	}
	
	//cout<<a.root->_key<<a.root->red;
	end=clock();
	cout<<endl<<end-start<<"ms"<<endl;
	a.print(a.root);
	




}

