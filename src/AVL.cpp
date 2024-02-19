#include "AVL.h"
#include <iostream>

using namespace std;

//Global Variables
vector<Node*> nodesToBePrinted;

/*****************************************************************************
*    Title: Binary Search Tree Insert
        *    Author: OnlineGBD
        *    Date: Accessed Feb 5, 2024
        *    Content: TreeNode class Structure, inOrder traversal, public insert methodology
*    Availability: https://www.onlinegdb.com/BygDgQCjI
****************************************************************************/

//Insert privately onto the AVL tree
Node* AVLTree::InsertHelper(Node *node, string name, string ufid) {

    //Regular expressions for name and ufid
    regex namePattern("[a-zA-Z\\s]+");
    regex ufidPattern("[0-9]{8,8}");

    //if root, start from scratch
    if (node == nullptr)
    {
        cout << "successful" << endl;
        return new Node(name, ufid, 1);
    }

    //Validate name and ufid using regular expressions
    if (!regex_match(name, namePattern) || !regex_match(ufid, ufidPattern)) {
        cout << "unsuccessful" << endl;
        return node;
    }

    //if value is less than, insert left
    if (ufid < node->getUFID()) {
        node->setLeftNode(InsertHelper(node->getLeftNode(), name, ufid));

    }
        //if value is greater than, insert right
    else if (ufid > node->getUFID()) {
        node->setRightNode(InsertHelper(node->getRightNode(), name, ufid));
    }
    //if value already exists, reject it
    if (ufid == node->getUFID())
        cout << "unsuccessful" << endl;

    else if (ufid != node->getUFID())
    {
        //update balance factor
        node->setBalanceFactor(UpdateBalanceFactor(node));

        //perform necessary rotations to balance the tree
        if (node->getBalanceFactor() > 1)
        {
            if (ufid > node->getRightNode()->getUFID())
                return RotateLeft(node);
            else
                return RotateRightLeft(node);
        }
        if (node->getBalanceFactor() < -1)
        {
            if (ufid < node->getLeftNode()->getUFID())
                return RotateRight(node);
            else
                return RotateLeftRight(node);
        }
    }
    return node;
}

/*****************************************************************************
*    Title: Removing White Space from a String
        *    Author: Scaler Topics, Prateek Narang
        *    Date: Accessed Feb 7, 2024
        *    Content: How to remove leading/trailing white space from a string
*    Availability: https://www.scaler.com/topics/removing-whitespace-from-a-string-in-cpp/
****************************************************************************/

/*****************************************************************************
*    Title: Removing Double Quotation Marks from a String
        *    Author: CPlusPlus.com - Duthomhas
        *    Date: Accessed Feb 13, 2024
        *    Content: How to remove leading/trailing double quotes from a string
*    Availability: https://cplusplus.com/forum/beginner/14373/
*****************************************************************************/

void AVLTree::Search(Node *root, string followUpData)
{
    count = 0;

    //determine if searchToken is name or ID, search accordingly
    string searchToken = followUpData;
    searchToken.erase(remove_if(searchToken.begin(), searchToken.end(), ::isspace)); //SEE REFERENCE ABOVE
    searchToken.erase(remove(searchToken.begin(), searchToken.end(), '\"'), searchToken.end()); //SEE REFERENCE ABOVE

    if(!VerifyID(searchToken) && !VerifyName(searchToken)){
        cout << "unsuccessful" << endl;
        return;

    }

    //search by name or by ID
    if (VerifyID(searchToken))
        SearchID(root, searchToken);
    else
        SearchName(root, searchToken);

    //If search yields no results print Unsuccessful
    if(count == 0)
        cout << "unsuccessful" << endl;
}
void AVLTree::SearchID(Node* root, string ufid)
{
    if(root == nullptr)
        return;

    SearchID(root->getLeftNode(), ufid);

    if(root->getUFID() == ufid)
    {
        cout << root->getName() << endl;
        count += 1;
    }
    else
        SearchID(root->getRightNode(), ufid);
}
void AVLTree::SearchName(Node* root, string name)
{
    if(root == nullptr)
        return;

    SearchName(root->getLeftNode(), name);

    if(root->getName() == name)
    {
        cout << root->getUFID() << endl;
        count += 1;
    }
    else
        SearchName(root->getRightNode(), name);
}


void AVLTree::TraverseInOrder(Node* root, vector<Node*>& nodes)
{
    //Traverse In Order: Left, Node, Right. Assign values to referenced vector of names
    if(root == nullptr)
        return;
    else{
        TraverseInOrder(root->getLeftNode(), nodes);
        nodes.push_back(root);
        TraverseInOrder(root->getRightNode(), nodes);
    }
};
void AVLTree::TraversePreorder(Node* root, vector<Node*>& nodes)
{
    //Traverse Preorder: Node, Left, Right. Assign values to referenced vector of names
    if(root == nullptr)
        return;

    nodes.push_back(root);
    TraversePreorder(root->getLeftNode(), nodes);
    TraversePreorder(root->getRightNode(), nodes);

};
void AVLTree::TraversePostorder(Node* root, vector<Node*>& nodes)
{
    //Traverse Preorder: Left, Right, Node. Assign values to referenced vector of names
    if(root == nullptr)
        return;

    TraversePostorder(root->getLeftNode(), nodes);
    TraversePostorder(root->getRightNode(), nodes);
    nodes.push_back(root);

};

/*****************************************************************************
*    Title: Stepik: Balancing Trees
        *    Author: Lisha Zhou, Amanpreet Kapoor
        *    Date: Accessed Feb 7, 2024
        *    Content: Left, Right, LeftRight and RightLeft Rotations for Balancing Trees
*    Availability: https://stepik.org/lesson/714338/step/1?unit=715142
****************************************************************************/

Node* AVLTree::RotateLeft(Node* node)
{
    Node* temp = node->getRightNode();
    node->setRightNode(temp->getLeftNode());
    temp->setLeftNode(node);
    return temp;
}
Node* AVLTree::RotateRight(Node* node)
{
    Node *temp = node->getLeftNode();
    node->setLeftNode(temp->getRightNode());
    temp->setRightNode(node);
    return temp;
}
Node* AVLTree::RotateLeftRight(Node* node)
{
    node->setLeftNode(RotateLeft(node->getLeftNode()));
    return RotateRight(node);
}
Node* AVLTree::RotateRightLeft(Node* node)
{
    node->setRightNode(RotateRight(node->getRightNode()));
    return RotateLeft(node);
}

/*****************************************************************************
*    Title: Module 4: Balanced Trees PowerPoint
        *    Author: Amanpreet Kapoor
        *    Date: Accessed Feb 7, 2024
        *    Content: Measuring height recursively to determine a nodes balance factor
*    Availability: https://ufl.instructure.com/courses/500074/pages/module-4-balanced-trees
****************************************************************************/

int AVLTree::Height(Node* root)
{
    if(root == nullptr)
        return 0;
    return 1 + max(Height(root->getLeftNode()), Height(root->getRightNode()));
}
int AVLTree::UpdateBalanceFactor(Node* node)
{
    return Height(node->getRightNode()) - Height(node->getLeftNode());
}

/*****************************************************************************
*    Title: Module 4: Balanced Trees PowerPoint
        *    Author: Amanpreet Kapoor
        *    Date: Accessed Feb 8, 2024
        *    Content: How to balance an AVL tree after performing a deletion/AVL rotations
*    Availability: https://ufl.instructure.com/courses/500074/pages/module-4-balanced-trees
****************************************************************************/

/*****************************************************************************
*    Title: Module 4: Trees PowerPoint
        *    Author: Amanpreet Kapoor
        *    Date: Accessed Feb 8, 2024
        *    Content: Binary Search Tree Deletion Pseudocode
*    Availability: https://ufl.instructure.com/courses/500074/pages/module-3-trees?module_item_id=10779338
****************************************************************************/

/*****************************************************************************
*    Title: Office Hours Review Session - Delete the in-order successor (CurrentNode->setRightNode(DeleteNodeHelper...)
        *    Author: Amanpreet Kapoor
        *    Date: Accessed Feb 15, 2024
        *    Content: Binary Search Tree Deletion
*    Availability: N/A Zoom Call
****************************************************************************/

void AVLTree::DeleteNode(string ufid)
{
    //check if the tree is empty
    if (root == nullptr) {
        cout << "unsuccessful" << endl;
        return;
    }

    root = DeleteNodeHelper(root, ufid);

    //Check if deletion was successful by searching
    Node* deletedNode = SearchDeletedNode(root, ufid);
    if (deletedNode == nullptr) {
        cout << "successful" << endl;
    } else {
        cout << "unsuccessful" << endl;
    }
}
Node* AVLTree::DeleteNodeHelper(Node* currentNode, string ufid)
{
    if (currentNode == nullptr) {
        cout << "unsuccessful" << endl;
        return nullptr;
    } //redundant

    //If the ufid to be deleted is smaller than the currentNode's ufid, then it's in the left subtree
    if (ufid < currentNode->getUFID()){
        currentNode->setLeftNode(DeleteNodeHelper(currentNode->getLeftNode(), ufid));}
        //If the ufid to be deleted is larger than the currentNode's ufid, then it's in the right subtree
    else if(ufid > currentNode->getUFID()){
        currentNode->setRightNode(DeleteNodeHelper(currentNode->getRightNode(), ufid));}

        //If the ufids are the same, then this is the node to be deleted
    else {
        //Delete node w/ no children - return nullptr;
        if(currentNode->getLeftNode() == nullptr && currentNode->getRightNode() == nullptr)
            return nullptr;
        //Delete node with: 1 child left OR right
        else if (currentNode->getLeftNode() == nullptr || currentNode->getRightNode() == nullptr)
        {
            return (currentNode->getLeftNode() == nullptr) ? currentNode->getRightNode() : currentNode->getLeftNode();
        }//? ternary operator condition on left true, go first, if false, go to second
        //ifcurrent node has no left child, then return the right subtree, otherwise left subtree
        else {

            //find in-order successor
            Node* inOrderSuccessor = currentNode->getRightNode();
            while(inOrderSuccessor->getLeftNode() != nullptr){
                inOrderSuccessor = inOrderSuccessor->getLeftNode();
            }
            //copy the data from in-order predecessor to the current node
            currentNode->setName(inOrderSuccessor->getName());
            currentNode->setUFID(inOrderSuccessor->getUFID());

            //recursively delete the in-order predecessor node from its original location
            currentNode->setRightNode((DeleteNodeHelper(currentNode->getRightNode(), inOrderSuccessor->getUFID())));

        }
    }
    return currentNode;
}
Node* AVLTree::SearchDeletedNode(Node* root, string ufid)
{
    //if root is null or its UFID matches the target UFID, return root
    if (root == nullptr || root->getUFID() == ufid)
        return root;

    //moving to left subtree
    if (ufid < root->getUFID()) {
        return SearchDeletedNode(root->getLeftNode(), ufid);
    }
        //move to right subtree
    else {
        return SearchDeletedNode(root->getRightNode(), ufid);
    }
}

/*****************************************************************************
*    Title: Erasing Elements from a vector in C++
        *    Author: N/A
        *    Date: Accessed Feb 19, 2024
        *    Content: How to remove a single element from a vector and its time complexity
*    Availability: N/A Zoom Call
****************************************************************************/
void AVLTree::RemoveInorder(Node* root, int& targetCount) {

    //clear the vector
    nodesToBePrinted.clear();

    //traverse in order
    if(root == nullptr)
        return;

    //recursive  call to removeInOrder, increment count, when count matches N, call Delete on currentNode
    else{
        RemoveInorder(root->getLeftNode(), targetCount);
        if(count == targetCount) {
            DeleteNode(root->getUFID());
            return;
        }
        else{
        count++;
        RemoveInorder(root->getRightNode(), targetCount);
        }
    }

};

bool AVLTree::ValidateCommand(string& command)
{
    //verify command for correctness. EXACT values only
    if (command == "insert" || command == "remove" || command == "search" || command == "printInorder" ||
        command == "printPreorder" || command == "printPostorder" || command == "printLevelCount" || command == "removeInorder")
        return true;
    else
        return false;
}
void AVLTree::ReviewCommands(vector<Data> dataArray, int numOfCommands) {
    //review commands provided by the user
    for(int i = 0; i < numOfCommands; i++) {
        string command = dataArray[i].getCommand();
        string followUpData = dataArray[i].getFollowUpData();

        if (ValidateCommand(command)){
            if (command == "insert") {
                //parse the follow-up data for name and UFID
                string name, ufid;
                stringstream ss(followUpData);
                getline(ss, name, '"');
                getline(ss, name, '"');
                ss >> ufid;

                if(VerifyName(name) && VerifyID(ufid))
                    Insert(name, ufid);
            }
            else if (command == "remove") {
                //remove whitespace from the follow-up data
                followUpData.erase(remove_if(followUpData.begin(), followUpData.end(), ::isspace));
                if(VerifyID(followUpData))
                    DeleteNode(followUpData);
            }
            else if (command == "search") {
                Search(root, followUpData);
            }
            else if (command == "printInorder") {
                TraverseInOrder(root, nodesToBePrinted);
                printVector(nodesToBePrinted);
            }
            else if (command == "printPreorder") {
                TraversePreorder(root, nodesToBePrinted);
                printVector(nodesToBePrinted);
            }
            else if (command == "printPostorder") {
                TraversePostorder(root, nodesToBePrinted);
                printVector(nodesToBePrinted);
            }
            else if (command == "printLevelCount"){
                int treeHeight = Height(root);
                cout << treeHeight << endl;
            }
            else if (command == "removeInorder")
            {
                //parse follow-up data for target count
                if(VerifyTargetCount(followUpData)) {
                    int targetCount = stoi(followUpData);
                    RemoveInorder(root, targetCount);
                }
                else
                    cout << "unsuccessful" << endl;
                } //if targetCount is incompatible
            }
        else
            cout << "unsuccessful" << endl;
    }
}

/*****************************************************************************
*    Title: C Plus Plus Vector Reference Sheet
        *    Author: CPlusPlus.com
        *    Date: Accessed Feb 7, 2024
        *    Content: How to access/Clear the contents of a vector
*    Availability: https://cplusplus.com/reference/vector/
****************************************************************************/

void AVLTree::printVector(vector<Node*>& nodesToBePrinted)
{
    //Iterate through the namesToBePrinted vector, filled through a specified previous traversal of the tree
    cout << nodesToBePrinted[0]->getName();
    for (int i = 1; i < nodesToBePrinted.size(); i++)
    {
        cout << ", " << nodesToBePrinted[i]->getName();
    }
    cout << endl;
    //clear the vector to start over/re-traverse and print
    nodesToBePrinted.clear();
}

/*****************************************************************************
*    Title: C Plus Plus cctype Reference Sheet
        *    Author: CPlusPlus.com
        *    Date: Accessed Feb 7, 2024
        *    Content: Using cctype functions to verify the contents of a string
*    Availability: https://cplusplus.com/reference/cctype/
****************************************************************************/

bool AVLTree::VerifyName(string& name)
{
    //verify name using Regex
    regex namePattern("[a-zA-Z\\s]+");
    return regex_match(name, namePattern);
}
bool AVLTree::VerifyID(string& ufid)
{
    //verify ufid using Regex
    regex ufidPattern("[0-9]{8,8}");
    return regex_match(ufid, ufidPattern);
}
bool AVLTree::VerifyTargetCount(string &targetCount)
{
    targetCount.erase(remove_if(targetCount.begin(), targetCount.end(), ::isspace));
    //verify targetCount is positive int >= 0
    regex targetCountPattern ("[0-9]+");
    return regex_match(targetCount, targetCountPattern);
}

//FIXME add a reference to the slides for subtree counts

int AVLTree::LeftSubtreeCount(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + LeftSubtreeCount(root->getLeftNode()) + LeftSubtreeCount(root->getRightNode());
}
int AVLTree::RightSubtreeCount(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    return 1 + RightSubtreeCount(root->getLeftNode()) + RightSubtreeCount(root->getRightNode());
}