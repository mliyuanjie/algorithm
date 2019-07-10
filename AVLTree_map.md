# AVLTree map
**增加，删除，查询功能**   
*增加：*  
***1.四种基本旋转类型，rebalance***  
***2.找到带插入的点，把走过的点全部入栈***  
***3.从栈逐个访问修改height然后rebalance***  
```
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
	return;}
  ```
  *删除*  
  ***1.找到待删除的点，走过的点入栈删除分为三种基本情况，没有右节点，右节点没有左节点，右节点有左节点***  
  ***2.最后一种情况最难，找到最小左节点，同时走过的点入栈*** 
  ***3.从栈访问更新height，rebalance，到了已经删除的点父节点，更新一下那个点，然后继续***  
  ***要注意根节点的情况***  
  ```
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
 ```
 [c++实现](结构算法/treemap.cpp)
