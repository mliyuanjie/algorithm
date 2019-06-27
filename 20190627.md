# 排序 
## quicksort  
**选择第一个点i，往后找小于它的点t，替换，i=i+1，t++** 
```
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
```
## mergesort
**先分段，后合并，用一个半长度的数组记录第一段，然后往里填，实现inplace**  
```
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
```
## heapsort
**maxheap维护堆操作，递归实现，交换情况三个值中最大值到堆顶-》从底网上调用maxheap-》交换读取第一个-》maxheap**  
```
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
```
## 速度提升方案
**小于1000000的merge排序，大于的先拆分然后归并 veryfast stl---2s fast---1.5s 10000000point**
[排序实现](结构算法/sort.cpp)

