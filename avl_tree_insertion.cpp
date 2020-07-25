int height_fun(struct Node *root){
    if(root==NULL)
        return 0;
    return root->height;
}
int balance(struct Node *root){
    if(root==NULL)
        return 0;
    return height_fun(root->left)-height_fun(root->right);
}
struct Node *rightRotation(struct Node *root){
    struct Node *t1=root->left;
    struct Node *t2=t1->right;
    
    t1->right=root;
    root->left=t2;
    
    root->height=1+max(height_fun(root->left),height_fun(root->right));
    t1->height=1+max(height_fun(t1->left),height_fun(t1->right));
    
    return t1;
}
struct Node *leftRotation(struct Node *root){
    struct Node *t1=root->right;
    struct Node *t2=t1->left;
    
    t1->left=root;
    root->right=t2;
    
    root->height=1+max(height_fun(root->left),height_fun(root->right));
    t1->height=1+max(height_fun(t1->left),height_fun(t1->right));
    
    return t1;
}
struct Node *newNode(int key){
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data=key;
    temp->left=NULL;
    temp->right=NULL;
    temp->height=1;
    return temp;
}
Node* insertToAVL(Node* root, int key){
    if(root==NULL)
        return newNode(key);
    if(key<root->data)
        root->left=insertToAVL(root->left,key);
    else if(key>root->data)
        root->right=insertToAVL(root->right,key);
    
    root->height=1+max(height_fun(root->left),height_fun(root->right));

    int b=balance(root);
    // left left
    if(b>1 && key<root->left->data)
        return rightRotation(root);
    // right right
    if(b<-1 && key>root->right->data)
        return leftRotation(root);
    // left right
    if(b>1 && key>root->left->data){
        root->left=leftRotation(root->left);
        return rightRotation(root);
    }
    // right left
    if(b<-1 && key<root->right->data){
        root->right=rightRotation(root->right);
        return leftRotation(root);
    }
    return root;
}
