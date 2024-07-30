#include <bits/stdc++.h>
using namespace std;

class hufftree {
public:
    char c;
    int freq;
    hufftree *left;
    hufftree *right;

    hufftree(char c, int freq) {
        this->c = c;
        this->freq = freq;
        left = nullptr;
        right = nullptr;
    }
};
hufftree *root;
unordered_map<char, string> coded;

struct compare {
    bool operator()(hufftree *a, hufftree *b) {
        return a->freq > b->freq;
    }
};

void inorder(hufftree *top, string s) {
    if (top == nullptr) return;
    if (top->c != '*') {
        coded[top->c] = s;
        return;
    }
    inorder(top->left, s + '0');
    inorder(top->right, s + '1');
}

void huffmanage(unordered_map<char, int> &m) {
    priority_queue<hufftree*, vector<hufftree*>, compare> minhuff;
    for (auto i : m) {
        hufftree* node = new hufftree(i.first, i.second);
        minhuff.push(node);
    }
    while (minhuff.size() > 1) {
        hufftree *l = minhuff.top();
        minhuff.pop();
        hufftree *r = minhuff.top();
        minhuff.pop();
        hufftree *top = new hufftree('*', l->freq + r->freq);
        top->left = l;
        top->right = r;
        minhuff.push(top);
    }
    root=minhuff.top();
    inorder(minhuff.top(), "");
}
char traverse(int &i,string s,hufftree *rt){
    if(!rt->left && !rt->right){
        return rt->c;
    }
    if(i>=s.size())
    return '\0';
    if(s[i]=='0'){
        i=i+1;
       return traverse(i,s,rt->left);
    }else{
        i=i+1;
        return traverse(i,s,rt->right);
    }
}
void decodes(int &i,string encoded,string &decoded){
    if(i>=encoded.size())
    return;
    char c=traverse(i,encoded,root);
    // if(c!='\0'){
    decoded+=c;
    decodes(i,encoded,decoded);
// }
}
int main() {
    string s,encoded,inp;
    cin>>inp;
    ifstream inputf(inp);
    stringstream ss;
    ss<<inputf.rdbuf();
    s=ss.str();
    unordered_map<char,int> m;
    for(int i=0;i<s.size();i++){
        m[s[i]]++;
    }
    huffmanage(m);
    encoded="";
    for(int i=0;i<s.size();i++){
        encoded+=coded[s[i]];
    }
    cout<<"encoded is"<<encoded<<"\n";
    int i=0;
    string decode="";
    decodes(i,encoded,decode);
    // cout<<"jubjfrr";
    cout<<decode;
}
