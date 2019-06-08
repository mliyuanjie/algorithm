#include<iostream>

template<class T>
class DLLNode{
public:
	DLLNode(){
		next=prev=0;
	}
	DLLNode(const T& el, DLLNode* n=0, DLLNode* p=0){
		info=el;
		next=n;
		prev=p;
	}
	T info;
	DLLNode *next, *prev;
};

template<class T>
class DLList{
public:
	DLList(){
		head=tail=0;
	}
	bool isEmpty(){
		return head==0;
	}
	void add_tail(const T&);
	void add_head(const T&);
	T del_tail();
	T del_head();
	bool isIn(const T&);
	void print();
protected:
	DLLNode<T> *head, *tail;
};

template<class T>
void DLList<T>::add_tail(const T& el){
	if(isEmpty())
		head=tail=new DLLNode<T>(el);
	else {
		tail->next=new DLLNode<T>(el,0,tail);
		tail=tail->next;
		
	}
	
}
template<class T>
void DLList<T>::add_head(const T& el){
	if(isEmpty()) head=tail=new DLLNode<T>(el);
	else {
		head=new DLLNode<T>(el,head,0);
		head->next->prev=head;
	}
}
template<class T>
T DLList<T>::del_head(){
	T el=head->info;
	if(head==tail){
		delete head;
		head=tail=0;
	}
	else{
		head=head->next;
		delete head->prev;
		head->prev=0;
}	return el;
}
template<class T>
T DLList<T>::del_tail(){
	T el=head->info;
	if(head==tail){
		delete head;
		head=tail=0;
	}
	else{
		tail=tail->prev;
		delete tail->next;
		tail->next=0;
}	return el;
 }
 template<class T>
 bool DLList<T>::isIn(const T& el){
	DLLNode<T>* tmp;
	for(tmp=head;tmp!=0 && tmp->info!=el;tmp=tmp->next);
	return tmp!=0;
 }
 template<class T>
 void DLList<T>::print(){
	for(DLLNode<T>* tmp=head;tmp!=0;tmp=tmp->next)
		std::cout<<tmp->info<<std::endl;
 }
 
int main(){
	DLList<int>* a=new DLList<int>();
	for(int i=0;i<10;i++){
		a->add_tail(i);
	}
	a->del_head();
	a->del_tail();
	a->print();
}