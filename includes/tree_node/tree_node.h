#ifndef TREE_NODE_H
#define TREE_NODE_H

template <typename T>
struct tree_node
{
    T _item;
    tree_node<T>* _left;
    tree_node<T>* _right;
    int _height;
    int balance_factor(){
        //balance factor = height of the left subtree 
        //                        - the height of the right subtree
        //a NULL child has a height of -1
        //a leaf has a height of 0
        if (_left && _right) 
            return (_left->_height - _right->_height);
        else if (!_left && _right)
        {
            return ( -1 - (_right->_height));
        }else if (_left && !_right)
        {
            return (_left->_height + 1);
        }else
            return 0;
    }

    int height(){
        // Height of a node is 1 + height of the "taller" child
        //A leaf node has a height of zero: 1 + max(-1,-1)
        if (_left && _right) //has both subtrees
            return 1 + std::max(_left->_height, _right->_height);
        else if (!_left && _right) //no left substree but has right substree
        {
            return 1 + std::max(-1, _right->_height);
        }else if (_left && !_right) // has left subtree but no right subtree
        {
            return 1 + std::max(-1, _left->_height);
        }else //leaf
            return 0;
    }
    int update_height(){
        //set the _height member variable (call height();)
        _height = height();
        return _height;
    }

    tree_node(T item=T(), tree_node* left=nullptr, 
                          tree_node* right=nullptr):
                    _item(item), _left(left), _right(right)
    {

        //don't forget to set the _height.
        _height = 0;
    }
    friend std::ostream& operator <<(std::ostream& outs, 
                                const tree_node<T>& t_node){
        outs<<"|"<<t_node._item<<"|";

        return outs;
    }
};
    #endif //TREE_NODE_H