#include<iostream>
#include<time.h>
using namespace std;
class IntSLLNode {
public:
	IntSLLNode(){
	next=0;}
	IntSLLNode(int i, IntSLLNode* in=0){
	info=i; next=in;}
	int info;
	IntSLLNode* next;
};

class IntSLList{
public:
	IntSLList(){
		head=tail=0;
	}
	~IntSLList();
	int isEmpty(){
		return head==0;
	}
	void addToHead(int);
	void addToTail(int);
	int deleteFromTail();
	int deleteFromHead();
	void deleteNode(int);
	int* isInList(int) const;
	void print();
private:
	IntSLLNode *head,*tail;
};	

IntSLList::~IntSLList(){
	for(IntSLLNode* p; !isEmpty();){
		p=head->next;
		delete head;
		head=p;
	}
}
void IntSLList::addToHead(int el){
	head=new IntSLLNode(el,head);
	if(tail==0)
		tail=head;
}
	
void IntSLList::addToTail(int el){
	if(tail!=0){
		tail->next=new IntSLLNode(el);
		tail=tail->next;
	}
	else head=tail=new IntSLLNode(el);
}

int IntSLList::deleteFromHead(){
	int el=head->info;
	IntSLLNode* temp=head;
	if (head==tail) head=tail=0;
	else head=head->next;
	delete temp;
	return el;
}

int IntSLList::deleteFromTail(){
	int el=tail->info;	
	if (head==tail){
		IntSLLNode* temp=tail;
		head=tail=0;
		delete temp;
		}			
	else{
		IntSLLNode* temp;
		for(temp=head;temp->next!=tail;temp=temp->next);
		delete tail;
		tail=temp;
		tail->next=0;	
		}
	return el;
	
}

void IntSLList::deleteNode(int el){
	if(!head) return;
	if(head==tail && el==head->info){
		delete head;
		head=tail=0;
	}
	else if(el==head->info){
		IntSLLNode* tmp;
		tmp=head;
		head=head->next;
		delete tmp;

	}
	else{
	IntSLLNode* tmp;
	IntSLLNode* pred;
	for(pred=head,tmp=head->next;
		tmp!=0 && !(tmp->info==el);
		pred=pred->next,tmp = tmp->next);
	if(tmp!=0){
		pred->next=tmp->next;
		if(tmp==tail) tail=pred;
		delete tmp;
		tmp=0;
	}
	}	
}

void IntSLList::print(){
	IntSLLNode* tmp;
	for(tmp=head;tmp!=0;tmp=tmp->next) cout<<tmp->info<<endl;
}

int* IntSLList::isInList(int el) const{
	IntSLLNode* tmp;
	for(tmp=head; tmp!=0 && !(tmp->info==el);tmp=tmp->next);
	if(tmp)
		return &tmp->info;
	else
		return 0;
}
int main(){
	clock_t start;
	clock_t end;
	IntSLList a;
	for(int i=0;i<1000000;i++){
		int k=rand();
		a.addToHead(k);
	}
	start=clock();
	for(int i=100000;i<200000;i++)
		a.isInList(i);

	end=clock();
	cout<<end-start;
	cin>>end;	
}
