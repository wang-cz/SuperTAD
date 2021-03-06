//
// Created by wang mengbo on 2019-09-02.
//

#include "binaryTree.h"


namespace binary {

    std::ostream& operator<< (std::ostream &os, const TreeNode &node)
    {
        os << "self=(" << node._val[0] << ", " << node._val[1] << ")";
        if (node._left != NULL && node._right != NULL) {
            os << ", left=(" << node._left->_val[0] << ", " << node._left->_val[1] << ")";
            os << ", right=(" << node._right->_val[0] << ", " << node._right->_val[1] << ")";
        }
        return os;
    }


    Tree::Tree ()
    {
        _root = NULL;
        _nodeList.reserve (1000);
    }


    Tree::~Tree()
    {
        for (int i = 0; i < _nodeList.size (); i++) {
            delete _nodeList[i];
        }
    }


    void Tree::add(int &start, int &end, int &k)
    {
        TreeNode *treeNode = new TreeNode(start, end);

        if (k == 0) {
            if (_DEBUG_)
                printf("leaf node: (%d, %d)\n", start, end);

            TreeNode *treeExistNode = _t.top ();
            if (treeExistNode->_left == NULL) {
                treeExistNode->_left = treeNode;
                treeNode->_parent = treeExistNode;
            }
            else {
                treeExistNode->_right = treeNode;
                treeNode->_parent = treeExistNode;
                _t.pop ();
            }
        }
        else {
            if (_root == NULL) {
                _root = treeNode;
                _t.push (_root);
            }
            else {
                TreeNode *treeExistNode = _t.top ();
                if (treeExistNode->_left == NULL) {
                    treeExistNode->_left = treeNode;
                    treeNode->_parent = treeExistNode;
                    _t.push (treeExistNode->_left);
                }
                else {
                    treeExistNode->_right = treeNode;
                    treeNode->_parent = treeExistNode;
                    _t.pop ();
                    _t.push (treeExistNode->_right);
                }
            }
        }
        if (treeNode != _root)
            _nodeList.emplace_back(treeNode);
    }

    void Tree::insert(TreeNode *treeNode, TreeNode *parentNode){
        if (parentNode->_left==NULL){
            parentNode->_left = treeNode;
            treeNode->_parent = parentNode;
            _nodeList.emplace_back(treeNode);
        }
        else if (treeNode->_val[1] <= parentNode->_left->_val[1])
            insert(treeNode, parentNode->_left);
        else if (parentNode->_right == NULL){
            parentNode->_right = treeNode;
            treeNode->_parent = parentNode;
            _nodeList.emplace_back(treeNode);
        } else
            insert(treeNode, parentNode->_right);

    }
}
