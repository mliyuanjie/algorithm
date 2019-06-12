# 链表c++  
**跳跃链表真的好快啊,和正常链表不是一个数量级啊**  
**1.链表 核心功能插入删除查找**  
*插入比较简单，head和tail 用一个tmp指针即可*  
*删除同上，但是定点删除要用两个指针，tmp和prev*  
*查找，loop到某个点或者0，返回!指针*  
[正常链表实现](结构算法/list.cpp)  
**2.跳跃链表 核心功能查找,太快了**  
*查找和插入都有一个类似找位置的过程，查找用两个指针即可，插入需要用两个指针数组*  
*对不同层数循环->找到待找值的后一个点，以及prev指针->换层考虑i>0-></br>更新第二层的两个指针->得到指针数组，每一层的两个指针都是待插入的两个节点*
 ```
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
  ```  
  *每个节点有一个值(val)和指针数组,用随机法确定每个节点的高度，也就是指针数组的长度*  
  [跳跃表](结构算法/skiplist.cpp)  
  # N皇后  
  **就是递归加一层循环 dfs搜索**   
  *speedqueen采用了位运算，用bit表示一个元素速度提升很大，还通过对称减了一半工作量*  
  [Nqueen](结构算法/queen.cpp)

  
