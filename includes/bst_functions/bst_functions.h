#ifndef BST_FUNCTIONS_H
#define BST_FUNCTIONS_H

#include "../tree_node/tree_node.h"
#include <iostream>
#include <iomanip>
using namespace std;
template <typename T>
void tree_insert(tree_node<T>* &root, const T& insert_me);

template <typename T>
tree_node<T>* tree_search(tree_node<T>* root, const T& target);
template <typename T>
bool tree_search(tree_node<T>* root, const T& target,
                 tree_node<T>* &found_ptr);

template<typename T>
void tree_print(tree_node<T>* root, int depth=0,
                                    ostream& outs=cout);

template<typename T> //prints detailes info about each node
void tree_print_debug(tree_node<T>* root, int depth=0,
                                          ostream& outs=cout);

template <typename T> //clear the tree
void tree_clear(tree_node<T>* &root);

template <typename T> //erase target from the tree
bool tree_erase(tree_node<T>*& root, const T& target);
template <typename T> //erase rightmost node from the tree -> max_value
void tree_remove_max(tree_node<T>* &root, T& max_value);


template <typename T> //print in_order
void in_order(tree_node<T>* root,ostream& outs=cout);

template <typename T> //print pre_order
void  pre_order(tree_node<T>* root,ostream& outs=cout);

template <typename T> //print post_order
void  post_order(tree_node<T>* root,ostream& outs=cout);

template <typename T> //string in_order
string in_order_string(tree_node<T>* root);

template <typename T> //string pre_order
string pre_order_string(tree_node<T>* root);

template <typename T> //string post_order
string post_order_string(tree_node<T>* root);


template <typename T> //return copy of tree pointed to by root
tree_node<T>* tree_copy(tree_node<T>* root);

template <typename T> //Add tree src to dest
void tree_add(tree_node<T>* & dest, const tree_node<T>* src);

template <typename T> //sorted array of ints -> tree
tree_node<T>* tree_from_sorted_list(const T* a);

template <typename T> // sorted array -> tree
tree_node<T>* tree_from_sorted_list(const T* a, int size);
//---------------------------------------------------------------------
template <typename T>
tree_node<T>* sortedArrayBST(const T* a, int start, int end);

// //do I use inorder??
// template <typename T>
// T* extractArrayFromBST(tree_node<T>* root, int level = 0);

template <typename T>
void print_array(T* a, int size, std::ostream& outs = cout);
// --------------------------------------------------------------------
template <typename T>
void tree_insert(tree_node<T>* &root, const T& insert_me)
{
    if (!root)
        root = new tree_node<T>(insert_me);

    else if (insert_me < root->_item)
        tree_insert(root->_left, insert_me);
    else 
        tree_insert(root->_right, insert_me);
    
    root->update_height();

}

template <typename T>
tree_node<T>* tree_search(tree_node<T>* root, const T& target)
{
    const bool debug = false;

    if (!root)  
    {
        if (debug) cout << "Tree search: not found. root is NULL" << endl;
        return root;
    }
    if (root->_item == target)
    {
        if (debug) cout << "Tree search: found target [" << root->_item << "]\n";
        return root;
    }
    if (target < root->_item )
    {
        if (debug) cout << "Tree search: going left. item: " << target 
                    << " less than root: " << root->_item << endl;
        return tree_search(root->_left, target);
    }
    if ( target > root->_item )
    {
        if ( debug ) cout << "Tree search: going right. item " << target
                        << "greater than root : " << root->_item << endl;
        return tree_search(root->_right, target);
    }   
    return root;
}
template <typename T>
bool tree_search(tree_node<T>* root, const T& target, tree_node<T>* &found_ptr)
{
    found_ptr = tree_search(root, target);
    bool return_me = false;
    found_ptr != nullptr ? return_me = true : return_me = false;
    return return_me;
}

template<typename T>
void tree_print(tree_node<T>* root, int depth, ostream& outs)
{
    if (root)
    {
        tree_print(root->_right, depth + 1); 
        outs << setw(4 * depth) << "" << "[" << root->_item << "]" << endl;
        tree_print(root->_left, depth + 1);
    }
}

template<typename T> //prints detailes info about each node
void tree_print_debug(tree_node<T>* root, int depth,
    ostream& outs)
{
        if (root)
    {
        tree_print(root->_right, depth + 1); 
        outs << setw(4 * depth) << "" << "[ " << root->_item << ":" << 
            root->_height << " ]" << endl;
        tree_print(root->_left, depth + 1);
    }
}

template <typename T> //clear the tree
void tree_clear(tree_node<T>* &root) 
{
    if (root)
    {
        tree_clear(root->_left);
        tree_clear(root->_right);
        delete root;
        root = nullptr;
    }
}
template <typename T> //erase target from the tree
bool tree_erase(tree_node<T>*& root, const T& target) 
{ 
    if (!root) //1
    {
        return false;
    }
    else
    {
        if (target < root->_item ) //2
        {
            tree_erase(root->_left, target);
        }
        else if (target > root->_item) //3
        {
            tree_erase(root->_right, target);
        }
        else if (root->_item == target) //4
        {
            if ( !(root->_left) ) 
            {
                tree_node<T>* old_root = root;
                root = root->_right;
                delete old_root;
            }else
            {
                //find some entry in the non-empty left subtree, 
                //and move this entry up to the root.
                tree_remove_max(root->_left, root->_item);
            }
        }
        if (root)
            root->update_height();
    }
    return true; 
}
template <typename T> //erase rightmost node from the tree -> max_value
void tree_remove_max(tree_node<T>* &root, T& max_value) 
{
    if (root->_right)
    {
        tree_remove_max(root->_right, max_value);
    }
    else
    {
        max_value = root->_item;
        tree_node<T>* deleted_ptr = root;
        root =root->_left;
        delete deleted_ptr;
    }
}
template <typename T> // LEFT ROOT RIGHT 
void in_order(tree_node<T>* root,ostream& outs)
{

    if (root)
    {
        in_order(root->_left);
        outs<<"|"<<root->_item<<"|";
        in_order(root->_right);
    }
}

template <typename T> //ROOT LEFT RIGHT 
void  pre_order(tree_node<T>* root,ostream& outs)
{
    if (root)
    {
        outs<<"|"<<root->_item<<"|";
        pre_order(root->_left);
        pre_order(root->_right);
    }
}

template <typename T> //LEFT RIGHT ROOT
void  post_order(tree_node<T>* root,ostream& outs)
{
    if (root)
    {
        post_order(root->_left);
        post_order(root->_right);
        outs<<"|"<<root->_item<<"|";
    }
}

template <typename T> //LEFT ROOT RIGHT
string in_order_string(tree_node<T>* root)
{
    string str = "";

    if (root)
    {
        str += in_order_string(root->_left);
        str += "[";
        str += to_string(root->_item);
        str += "]";
        str += in_order_string(root->_right);
    }
    return str;
}

template <typename T> //ROOT LEFT RIGHT 
string pre_order_string(tree_node<T>* root)
{
    string str = "";

    if (root)
    {
        str += "[";
        str += to_string(root->_item);
        str += "]";
        str += pre_order_string(root->_left);
        str += pre_order_string(root->_right);
        
    }
    return str;
}

template <typename T> //LEFT RIGHT ROOT
string post_order_string(tree_node<T>* root)
{
    string str = "";

    if (root)
    {
        str += post_order_string(root->_left);
        str += post_order_string(root->_right);
        str += "[";
        str += to_string(root->_item);
        str += "]";
    }
    return str;
}


template <typename T> //return copy of tree pointed to by root
tree_node<T>* tree_copy(tree_node<T>* root)
{
    if (root)
    {
        return new tree_node<T>
        (
            root->_item, 
            tree_copy(root->_left), 
            tree_copy(root->_right)
        );
    }
    else 
        return nullptr;

}
//FUNCTION IS FROM THE TEXTBOOK. . . PAGE 529
template <typename T> 
void tree_add(tree_node<T>* & dest, const tree_node<T>* src)
{

    if (src)
    {
        tree_insert(dest, src->_item);
        tree_add(dest->_left, src->_left);
        tree_add(dest->_right, src->_right);
    }
}

template <typename T> //sorted array of ints -> tree
tree_node<T>* tree_from_sorted_list(const T* a)
{
    cout << "I should not be here!\n";
    return nullptr;
}

template <typename T> // sorted array -> tree
tree_node<T>* tree_from_sorted_list(const T* a, int size)
{
    return sortedArrayBST(a, 0, size -1);
}
template <typename T>
tree_node<T>* sortedArrayBST(const T* a, int start, int end)
{
    /* Base Case */
    if (start > end)
        return nullptr;
    
    /* Get the middle element and make it root */
    int middle_index = ((start + end) + 1) / 2;
    T middle_element = *(a + middle_index);
    tree_node<T>* root = new tree_node<T>(middle_element);

    /* Recursively construct the left subtree
    and make it left child of root */
    root->_left = sortedArrayBST(a, start, middle_index - 1);

    /* Recursively construct the right subtree
    and make it right child of root */
    root->_right = sortedArrayBST(a, middle_index + 1, end);
    
    root->update_height();
    
    return root;
}
//has to be friend function in order to obtain tree from bst class
// template <typename T>
// T* extractArrayFromBST(tree_node<T>* root, int level)
// {
//     T* array_inorder;
//     if (root)
//     {
//         extractArrayFromBST( root->_left, level + 1);
//         *(array_inorder + level) = root->_item;
//         extractArrayFromBST( root->_right, level + 1);
//     }
// }
template <typename T>
void print_array(T* a, int size, std::ostream& outs)
{
    for (int i = 0; i < size; i++)
        outs << *(a + i) << " ";
}
#endif //BST_FUNCTIONS_H