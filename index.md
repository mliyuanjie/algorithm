# find and replace pattern
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
