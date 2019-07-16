# RBTree map实现
---
*1.节点由红河黑组成，根节点和最后null是黑色*  
*2.红节点的父节点为黑色《红节点不能相邻》*  
*3.黑色节点树高度一样《把红色节点向上合并，得到的黑色树高度完全等长，类似于2，3，4-tree》*  

---
**2.插入**  
*1.待插入节点Q为红色*  
*2.如果Q的父节点P为黑色，则返回，若红色则调整*  
*3.如果P的另一个儿子N是红色，则向Q方向旋转，新P变红，旧P变黑，P=Q返回2步骤*  
![case1](https://upload.wikimedia.org/wikipedia/commons/thumb/d/d6/Red-black_tree_insert_case_3.svg/400px-Red-black_tree_insert_case_3.svg.png)
*4.如果N黑色，则判断5*   
*5.如果Q是顺子，则向右转，调整颜色就可以返回，如果Q是逆子，则double旋转，然后调整颜色返回*    
![case2](https://upload.wikimedia.org/wikipedia/commons/thumb/8/89/Red-black_tree_insert_case_4.svg/400px-Red-black_tree_insert_case_4.svg.png)  
![case3](https://upload.wikimedia.org/wikipedia/commons/thumb/d/dc/Red-black_tree_insert_case_5.svg/400px-Red-black_tree_insert_case_5.svg.png)
---
**3.删除**  
*1.把待删除的点全部带颜色替换为最多一个儿子的点*  
*2.删除，如果颜色红色返回，如果少了黑色，继续。记录少黑色节点的子树为N*    
*3.如果N红色，变黑，N为root返回，否则继续*  
*4.如果N的兄弟S有带红色的儿子，则调整红儿子为顺，逆旋转，调整颜色即可返回，否则继续*  
![case1](https://upload.wikimedia.org/wikipedia/commons/thumb/9/99/Red-black_tree_delete_case_6_as_svg.svg/337px-Red-black_tree_delete_case_6_as_svg.svg.png)
![case2](https://upload.wikimedia.org/wikipedia/commons/thumb/3/36/Red-black_tree_delete_case_5_as_svg.svg/243px-Red-black_tree_delete_case_5_as_svg.svg.png)
*5.如果P红色，S变红，P变黑返回*  
![case3](https://upload.wikimedia.org/wikipedia/commons/thumb/3/3d/Red-black_tree_delete_case_4_as_svg.svg/337px-Red-black_tree_delete_case_4_as_svg.svg.png)
*6.如果S为红色，向N旋转，调整颜色，N则可重2开始*  
![case4](https://upload.wikimedia.org/wikipedia/commons/thumb/5/5c/Red-black_tree_delete_case_2_as_svg.svg/337px-Red-black_tree_delete_case_2_as_svg.svg.png)
*7.如果S为黑色，其父P为黑色，则S变红，P=Q重2开始*   
![case5](https://upload.wikimedia.org/wikipedia/commons/thumb/a/a0/Red-black_tree_delete_case_3_as_svg.svg/337px-Red-black_tree_delete_case_3_as_svg.svg.png)

[红黑树实现](结构算法/rb_map.cpp)
