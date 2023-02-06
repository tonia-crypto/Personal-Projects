#pragma once

#include <functional> // std::less
#include <iostream>
#include <queue> // std::queue
#include <utility> // std::pair


template <typename K, typename V, typename Comparator = std::less<K>>
class BinarySearchTree
{
  public:
    using key_type        = K;
    using value_type      = V;
    using key_compare     = Comparator;
    using pair            = std::pair<key_type, value_type>;
    using pointer         = pair*;
    using const_pointer   = const pair*;
    using reference       = pair&;
    using const_reference = const pair&;
    using difference_type = ptrdiff_t;
    using size_type       = size_t;

  private:
    struct BinaryNode
    {
        pair element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const_reference theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( pair && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    using node           = BinaryNode;
    using node_ptr       = node*;
    using const_node_ptr = const node*;

    node_ptr _root;
    size_type _size;
    key_compare comp;

  public:
    BinarySearchTree(): _root(nullptr), _size(0), comp() {
        // Nothing TODO in the function
    }
    BinarySearchTree( const BinarySearchTree & rhs ): _root(nullptr), _size(rhs._size), comp() {
        // copy constructor
        _root = clone(rhs._root);
    }
    BinarySearchTree( BinarySearchTree && rhs ): _root(nullptr), _size(0), comp() {
        // move constructor ==> move ownership
        _root = rhs._root;
        _size = rhs._size;
        
        // delete the older owner
        rhs._size = 0;
        rhs._root = nullptr;

    }
    ~BinarySearchTree() {
        // destructor
        clear();
    }

    const_reference min() const { return min( _root )->element; }
    const_reference max() const { return max( _root )->element; }
    const_reference root() const {
        
        return _root->element;
    }
    bool contains( const key_type & x ) const { return contains( x, _root ); }
    value_type & find( const key_type & key ) { return find( key, _root )->element.second; }
    const value_type & find( const key_type & key ) const { return find( key, _root )->element.second; }
    bool empty() const {
        
        if(_size == 0 ) {
            return true;
        }else{
            return false;
        }
    }
    size_type size() const {
        
        return _size;
    }

    void clear() {
        clear( _root );
        
        _size = 0;
    }
    void insert( const_reference x ) { insert( x, _root ); }
    void insert( pair && x ) { insert( std::move( x ), _root ); }
    void erase( const key_type & x ) { erase(x, _root); }

    BinarySearchTree & operator=( const BinarySearchTree & rhs ) {
        // TODO
        if(&rhs == this){

            return *this;
        }else{

            clear();
            _size = rhs._size;
            _root = clone(rhs._root);
        }


        return *this;
    }
    BinarySearchTree & operator=( BinarySearchTree && rhs ) {
        // TODO
        if(&rhs == this){

            return *this;
        }else{

            clear();
            _root = rhs._root;
            _size = rhs._size;
            rhs._root = nullptr;
            rhs._size = 0;
            
        }

        return *this;
    }

  private:
    void insert( const_reference x, node_ptr & t ) {
        // TODO
        if (t == nullptr){

            t = new node{x, nullptr, nullptr}; 


            _size++;
        }
        
        else if (comp(t->element.first,x.first)){

            insert(x , t->right);
        }
        else if (comp(x.first,t->element.first)){

            insert(x , t->left);
        }
       else{

            t->element = x;
        }
    }
    void insert( pair && x, node_ptr & t ) {
        // TODO

        if (t == nullptr){

            t = new node{std::move(x), nullptr, nullptr};


            _size++;
        }
        else if (comp(t->element.first,x.first)){

            insert(std::move(x) , t->right);
        }
        else if (comp(x.first,t->element.first)){

            insert(std::move(x) , t->left);
        }
        else{

            t->element = std::move(x);
        }
    }

    void erase( const key_type & x, node_ptr & t ) {
        // TODO -- Bonus
        // find
         if(t == nullptr){
            return;
        }
        else if(comp(t->element.first, x)){
            return erase(x, t->right);
        }
        else if(comp(x, t->element.first)){
            return erase(x, t->left);
        }
        
        // two children
        else if(t->right != nullptr && t->left != nullptr && t != nullptr){
            const_node_ptr minimum = min(t->right);
            t->element = minimum->element;
            erase(minimum->element.first, t->right);
        }
        // one child
        else if(t->right != nullptr && t != nullptr){
            node_ptr temp =  t;
            t = t->right;
            delete temp;
            _size--;
        }
        // one child the opposite direction
        else if(t->left != nullptr && t != nullptr){
            node_ptr temp =  t;
            t = t->left;
            delete temp;
            _size--;
        }
        else{
            delete t;
            t = nullptr;
            _size--;
        }
        // error in line 43 in erase.cpp
    }

    const_node_ptr min( const_node_ptr t ) const {
        // TODO
    
        // find the left most
        while((t->left) != nullptr && t != nullptr) {
            return min(t->left);
        }
        
        return t;
        
    }
    const_node_ptr max( const_node_ptr t ) const {
        // TODO
        while(t->right != nullptr && t != nullptr) {
            return max(t->right);
        }

        return t;
     
    }

    bool contains( const key_type & x, const_node_ptr t ) const {
        // TODO

        if(find(x, t) != nullptr){
            return true;
        } 
        return false;
        
    }
    node_ptr find( const key_type & key, node_ptr t ) {
        // TODO
        if(t == nullptr){
            return nullptr;
        }
        else if(comp(t->element.first, key)){
            return find(key, t->right);
        }
        else if(comp(key, t->element.first)){
            return find(key, t->left);
        }
        else{
            return t;
        }
    }
    const_node_ptr find( const key_type & key, const_node_ptr t ) const {
        // TODO
        if(t == nullptr){
            return nullptr;
        }
        else if(comp(t->element.first, key)){
            return find(key, t->right);
        }
        else if(comp(key, t->element.first)){
            return find(key, t->left);
        }
        else{
            return t;
        }
    }

    ////////////// height function
    int height() const{
        return height(_root);

    }
    int height(node_ptr n_height) const{
        if(n_height == nullptr){
            return 0;
        }
        else{
            return 1 + std::max(height(n_height->right),height(n_height->left));

        }
    }

    void clear( node_ptr & t ) {
        // TODO
        if(t != nullptr){
            clear(t->right);
            clear(t->left); 
            
        }
        delete t;
        t = nullptr;
    }
    
    
    node_ptr clone ( const_node_ptr t ) const {
        // TODO
        if(t != nullptr){

            return new BinaryNode{t->element, clone(t->left), clone(t->right)};
        }
        else{

            return nullptr;
        }
    }

  public:
    template <typename KK, typename VV, typename CC>
    friend void printLevelByLevel( const BinarySearchTree<KK, VV, CC>& bst, std::ostream & out );

    template <typename KK, typename VV, typename CC>
    friend std::ostream& printNode(std::ostream& o, const typename BinarySearchTree<KK, VV, CC>::node& bn);

    template <typename KK, typename VV, typename CC>
    friend void printTree( const BinarySearchTree<KK, VV, CC>& bst, std::ostream & out );

    template <typename KK, typename VV, typename CC>
    friend void printTree(typename BinarySearchTree<KK, VV, CC>::const_node_ptr t, std::ostream & out, unsigned depth );

    template <typename KK, typename VV, typename CC>
    friend void vizTree(
        typename BinarySearchTree<KK, VV, CC>::const_node_ptr node, 
        std::ostream & out,
        typename BinarySearchTree<KK, VV, CC>::const_node_ptr prev
    );

    template <typename KK, typename VV, typename CC>
    friend void vizTree(
        const BinarySearchTree<KK, VV, CC> & bst, 
        std::ostream & out
    );
};

template <typename KK, typename VV, typename CC>
std::ostream& printNode(std::ostream & o, const typename BinarySearchTree<KK, VV, CC>::node & bn) {
    return o << '(' << bn.element.first << ", " << bn.element.second << ')';
}
/// //////////// exp

int exp(int base, int height){
        if(height == 0){
            return 1;
        }
        else{
            return (exp(base, height - 1)) * base;
        }
    }
template <typename KK, typename VV, typename CC>
void printLevelByLevel( const BinarySearchTree<KK, VV, CC>& bst, std::ostream & out = std::cout ) {
    using node = typename BinarySearchTree<KK, VV, CC>::node;
    using node_ptr = typename BinarySearchTree<KK, VV, CC>::node_ptr;
    using const_node_ptr = typename BinarySearchTree<KK, VV, CC>::const_node_ptr;
    
    // TODO -- Guide in Instructions

    std::queue <node_ptr> queueOrder;
    node_ptr nextNode = bst._root;

    queueOrder.push(nextNode);

    int h = bst.height();

    int printed = 0;
    
    int height = exp(2,h) - 1;

    while(printed != height){
        
        nextNode = queueOrder.front();
        queueOrder.pop();

        if(nextNode == nullptr){
            out<<"null ";
            queueOrder.push(nullptr);
            queueOrder.push(nullptr);
            printed++;
        }
        else{
            queueOrder.push(nextNode->left);
            queueOrder.push(nextNode->right);
            printed++;

            printNode<KK,VV,CC>(out,*nextNode);
            
        }
    }

    // // current level print
    // //new node
    // node_ptr nextNode = bst._root;
       
    // // queue of the tree and examination
    // std::queue <node_ptr> queueOrder;

    // // nullptr counter
    // int null_count = 0;
    // int Count = 0;
    
    // int row = 1; 
    // int actual_row = 0;
    // // no roots
    // queueOrder.push(bst._root);


    // if(bst._root == nullptr){
    //     return;
    // }    
    // else{
    //     while(!queueOrder.empty()){
            
    //         // check fronts
    //         nextNode = queueOrder.front();

    //         if(nextNode != nullptr){
    //             //check right side
    //             if(nextNode->right != nullptr){
                    
    //                 queueOrder.push(nextNode->right);
    //                 Count++;
                    

    //             }
    //             // we need to show that it is null          
    //             else{
      
    //                 queueOrder.push(nullptr);
    //                 null_count++;
                   

    //             }
    //             //check left side
    //             if (nextNode->left != nullptr){
                    
    //                 queueOrder.push(nextNode->left);
    //                 Count++;
                    
    //             }
    //             // we need to show that it is null
    //             else{
    //                 queueOrder.push(nullptr);
    //                 null_count++;
                    
                   
    //             }
    //             printNode<KK,VV,CC>(out,*nextNode);
    //             out<<" ";
    //         }
            
    //         // if there is nothing on the left nor on the right we need to show 2 null ptrs
    //         else{
                
    //             queueOrder.push(nullptr);
    //             queueOrder.push(nullptr);
    //             null_count++;
    //             null_count++;
    //             out<<"null";
                
    //         }
            
    //         //now we remove the element and we start with the second
    //         queueOrder.pop();
    //         out<<" ";
            
    //         actual_row++;
            
    //         if(actual_row == row){
                
    //             if(Count == 0){
    //                 break;
    //             } 
    //             out<< std::endl;
    //             actual_row = 0;
    //             row = row * 2;
    //             Count = 0;

    //         } 
              
          
    //     }
    // }
}


template <typename KK, typename VV, typename CC>
void printTree( const BinarySearchTree<KK, VV, CC> & bst, std::ostream & out = std::cout ) { printTree<KK, VV, CC>(bst._root, out ); }

template <typename KK, typename VV, typename CC>
void printTree(typename BinarySearchTree<KK, VV, CC>::const_node_ptr t, std::ostream & out, unsigned depth = 0 ) {
    if (t != nullptr) {
        printTree<KK, VV, CC>(t->right, out, depth + 1);
        for (unsigned i = 0; i < depth; ++i)
            out << '\t';
        printNode<KK, VV, CC>(out, *t) << '\n';
        printTree<KK, VV, CC>(t->left, out, depth + 1);
    }
}

template <typename KK, typename VV, typename CC>
void vizTree(
    typename BinarySearchTree<KK, VV, CC>::const_node_ptr node, 
    std::ostream & out,
    typename BinarySearchTree<KK, VV, CC>::const_node_ptr prev = nullptr
) {
    if(node) {
        std::hash<KK> khash{};

        out << "\t" "node_" << (uint32_t) khash(node->element.first)
            << "[label=\"" << node->element.first 
            << " [" << node->element.second << "]\"];" << std::endl;
        
        if(prev)
            out << "\tnode_" << (uint32_t) khash(prev->element.first) <<  " -> ";
        else
            out << "\t";
        
        out << "node_" << (uint32_t) khash(node->element.first) << ";" << std::endl;
    
        vizTree<KK, VV, CC>(node->left, out, node);
        vizTree<KK, VV, CC>(node->right, out, node);
    }
}

template <typename KK, typename VV, typename CC>
void vizTree(
    const BinarySearchTree<KK, VV, CC> & bst, 
    std::ostream & out = std::cout
) {
    out << "digraph Tree {" << std::endl;
    vizTree<KK, VV, CC>(bst._root, out);
    out << "}" << std::endl;
}
