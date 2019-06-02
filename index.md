# find and replace pattern
----
**two functions->match and mainloop**  
*mainloop: vector ans to store the result*  
*match: two dict to store the pattern and words's char hashmap*  
*add char to the map, check if 1 to 1map*
```
class Solution {
public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        int L=words.size();
        vector<string> ans;
        for(int i=0;i<L;i++){
            if (match(words[i],pattern)) ans.push_back(words[i]);
        }
        return ans;
        
    }
    
    bool match(string words, string pattern){
        map<char,char> map1;
        map<char,char> map2;
        int m=words.size();
        int n=pattern.size();
        if (m!=n) return false;
        for(int i=0; i<m; i++){
            if(map1.count(words[i])==0)
                map1[words[i]]=pattern[i];
            if(map2.count(pattern[i])==0)
                map2[pattern[i]]=words[i];
            if(map1[words[i]]!=pattern[i]||map2[pattern[i]]!=words[i])
                    return false;  
            }
        return true;
        }
    
};
```
----
# unique paths iii
**dfs and recursion,two functions dfs and pathiii**  
*pathiii: find the start point and the longest path*  
*dfs: recursion implement </br>basic case: edge and -1 or 2(if longest path result++)</br> then: four direction*   

*so the problem is how to define the longest path and avoid repeat visit.*  
*if we visit a point longest-- and replace by -1.</b>after that longest++ replace by 0*
```
class Solution {
public:
    int ROW;
    int COL;
    int length=1;
    int num=0;
    std::vector<std::vector<int>> grid;
    
    int uniquePathsIII(std::vector<std::vector<int>> &data) {
        grid=data;
        ROW=grid.size();
        COL=grid[0].size();
        int m,n;
        for(int row=0;row<ROW;++row){
            for(int col=0;col<COL;++col)
            {
                if(grid[row][col]==1){
                    m=row;
                    n=col;
                } 
                if(grid[row][col]==0)
                    ++length;
            }
            }   
        dfs(m,n);
        return num;
}
    void dfs(int i,int j){
        if(i<0||i>=ROW||j<0||j>=COL||grid[i][j]==-1)
            return;
        if(grid[i][j]==2){
            if(length==0) ++num;
            return; 
        }
        
        grid[i][j]=-1;
        --length;
        dfs(i-1,j);
        dfs(i+1,j);
        dfs(i,j-1);
        dfs(i,j+1);
        ++length;
        grid[i][j]=0;          
                
        }
};
```
----
# binary tree pruning  
**递归**  
*1.递归函数应该有返回值 because the pointer was copy and into the function</br>2.先左右赋值再删除-主要是要排除0->,->0,0的情况*
```
class Solution {
public:
    TreeNode* pruneTree(TreeNode* root) {
        if(!root) return nullptr;
        root->left=pruneTree(root->left);
        root->right=pruneTree(root->right);
        if(root->val==0 && !root->left && !root->right){delete root;return nullptr;}
        return root;
    }

};
```
