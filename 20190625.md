# read traversal binary tree not recursive 
```
vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> st;
        vector<int> res;
        if(!root) return res;
        st.push(root);
        while(!st.empty()){
            while(root){
                st.push(root);
                root=root->left;
            }
            root=st.top();
            res.emplace_back(root->val);
            st.pop();
            root=root->right;
        }
        res.pop_back();
        return res;
        
    }
    
vector<int> postorderTraversal(TreeNode* root) {
        stack<TreeNode*> st;
        vector<int> res;
        TreeNode *prev;
        if(!root) return res;
        st.push(root);
        while(!st.empty()){
            root=st.top();
            while(root->left){
                root=root->left;
                st.push(root); 
            }
            while(!(root->right) || (root->right==prev)){
                res.push_back(root->val);
                prev=root;
                st.pop();
                if(st.empty()) return res;
                root=st.top();
                cout<<root->val<<endl;
            }
            st.push(root->right);
        }
        return res;
        
    }

vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> tempstack;
        vector<int> res;
        if(!root) return res;
        tempstack.push(root);
        while(!tempstack.empty()){
            root=tempstack.top();
            tempstack.pop();
            res.push_back(root->val);
            if(root->right) tempstack.push(root->right);
            if(root->left) tempstack.push(root->left);
            
        }
    return res;
    }
```
