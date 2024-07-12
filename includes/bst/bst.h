#ifndef BST_H
#define BST_H
#include "../bst_functions/bst_functions.h"
#include "../tree_node/tree_node.h"
#include <iostream>
using namespace std;

template <typename T>
class BST{
public:
    BST(): _root(nullptr) { }
    BST(const T *sorted_list, int size = -1)
    {
        _root = tree_from_sorted_list(sorted_list, size);
    }
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    BST(const BST<T> &copy_me)
    {
        _root = tree_copy( copy_me._root);
    }
    BST<T> &operator=(const BST<T> &rhs)
    {
        if (this == &rhs)
            return *this;

        tree_clear(_root);

        _root = tree_copy(rhs._root);

        return *this;
    }
    ~BST() 
    {
        tree_clear(_root);
    }
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    void insert(const T &insert_me)
    {
        tree_insert(_root, insert_me);
    }

    void erase(const T &target)
    {
        tree_node<T>* found_ptr = nullptr;
        if (tree_search(_root, target, found_ptr))
            tree_erase(_root, found_ptr->_item); 
    }
    bool contains(const T &target)const
    {
        tree_node<T>* found_target_ptr = nullptr;
        return tree_search(_root, target, found_target_ptr);
    }
    void clear_all()
    {
        tree_clear(_root);
    }
    bool empty()const
    {
        return (_root == nullptr);
    }
    friend ostream &operator<<(ostream &outs, const BST<T> &tree)
    {
        const bool debug = false;
        if (debug){
            cout<<"-------------------------------"<<endl;
            tree_print_debug(tree._root, 0, outs);
            cout<<". . . . . . . . . . . . . . . ."<<endl;
        }
        tree_print(tree._root, 0, outs);
        return outs;
    }
    void insert_all(const tree_node<T>* root)
    {

    }
    //tree var has to be a treenode pointer 
    // friend T* extractArrayFromBST(BST<T>& tree, int level = 0)
    // {
    // T* array_inorder;
    //     if (tree._root)
    //     {
    //         return extractArrayFromBST( tree._root->_left, level + 1);
    //         *(array_inorder + level) = tree._root->_item;
    //         return extractArrayFromBST( tree._root->_right, level + 1);
    //     }

    //     return array_inorder;
    // }   
    BST<T> operator+=(const BST<T> &rhs)
    {
        if (this == &rhs)
            return *this;

        tree_add(this->_root, rhs._root);
        
        return *this;
    }
    string pre_order()
    {
        return pre_order_string(_root);
    }
    string in_order()
    {
        return in_order_string(_root);
    }
    string post_order()
    {
        return post_order_string(_root);
    }

private:
    tree_node<T>* _root;
};
#endif //BST_H