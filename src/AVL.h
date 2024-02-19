#ifndef AVL_H
#define AVL_H

#include "Data.h"
#include <string>
#include <regex>
#include <algorithm>
#include <vector>

#pragma once
using namespace std;



//define private variables within the nodes of the tree
//public constructor for each tree node

class Node {
private:
    string name;
    string ufid;
    Node* left;
    Node* right;
    int balanceFactor;

public:
    Node(string name, string ufid, int height) : name(name), ufid(ufid), balanceFactor(height), left(nullptr), right(nullptr) {};

    //Getters
    string getName() const {return name;}
    string getUFID() const {return ufid;}
    int getBalanceFactor() const {return balanceFactor;}
    Node* getLeftNode() const {return left;}
    Node* getRightNode() const {return right;}

    //Setters
    void setName(const string& newName) {name = newName;}
    void setUFID(const string& newUFID) {ufid = newUFID;}
    void setLeftNode(Node* newLeft) {left = newLeft;}
    void setRightNode(Node* newRight) {right = newRight;}
    void setBalanceFactor(const int& newBalanceFactor) {balanceFactor = newBalanceFactor;}
};

/*****************************************************************************
*    Title: AVL Project Breakdown/Q+A Session
        *    Author: Penton, Andrew
        *    Date: May 4, 2023
        *    Content: Node class structure, AVL Tree class structure and helper functions
*    Availability: https://www.youtube.com/watch?v=BjH_Pdu_2W4&ab_channel=Penton%2CAndrew
****************************************************************************/

//AVLTree is a Class of TreeNodes
class AVLTree {
private:
    Node* root; //track the root of the AVL tree
    int count; //keep count during searches
    Node* InsertHelper(Node* node, string name, string ufid); //Inserts new nodes into the tree privately/validates unique ID value
    void TraverseInOrder(Node* root, vector<Node*>& nodes); //Assign values to the traversal vector in order
    void TraversePreorder(Node* root, vector<Node*>& nodes); //Assign values to the traversal vector preorder
    void TraversePostorder(Node* root, vector<Node*>& nodes); //Assign values to the traversal vector postorder
    Node* RotateLeft(Node* node); //Node Rotations for Tree Balancing
    Node* RotateRight(Node* node);
    Node* RotateLeftRight(Node* node);
    Node* RotateRightLeft(Node* node);
    int Height(Node* root); //determine the height of a given root/node
    int UpdateBalanceFactor(Node* node); //update a given node's balance factor
    Node* DeleteNodeHelper(Node* root, string ufid); //Delete a node and balance the tree based on UFID

public:
    AVLTree() : root(), count(0) {} //AVL Tree Constructorr

    void Insert(string name, string ufid)
    {this->root = InsertHelper(this->root, name, ufid);};  //collects insert info for private helper function
    void Search(Node* root, string name); //Search the tree
    void SearchID(Node* root, string ufid); //search the tree for a specific ID
    void SearchName(Node* root, string name); //search the tree for a specific name
    void DeleteNode(string ufid); // accessor for private member vars
    Node* SearchDeletedNode(Node* root, string ufid); //check to see if the node was deleted from the tree
    void RemoveInorder(Node* root, int& targetCount);//Removes a node at a given count (InorderTraversal)

    bool ValidateCommand(string& command); //Ensure initial command is valid
    void ReviewCommands(vector<Data> dataArray, int numOfCommands); //Review all commands input by the user, determine output in order
    void printVector(vector<Node*>& nodesToBePrinted); //print contents of traversal vector in designated order
    bool VerifyName(string& name); //verify if name is valid
    bool VerifyID(string& ufid); //verify if ID is valid
    bool VerifyTargetCount(string &targetCount); //verify that the targetCount is valid

    int RightSubtreeCount(Node* root); //right subtree count
    int LeftSubtreeCount(Node* root); //left subtree count
};

#endif // AVL_H
