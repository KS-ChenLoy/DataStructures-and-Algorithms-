#include <iostream>
#include <string>
#include <sstream>
#include <vector>
//Creating a Node Class to be used in AVL structure
class Node{
public:
    std::string studentName, studentID ;
    int balanceTreeF;
    Node* left, * right;

    //CONSTRUCTORS
    Node(): studentName(""), studentID(""),balanceTreeF(0),left(nullptr), right(nullptr){}
    Node(std::string _name, std::string ID , int _bal) : studentName(std::move(_name)), studentID(std::move(ID)), balanceTreeF(_bal),left(nullptr), right(nullptr){}
    Node(std::string _name, std::string ID , int _bal , Node* left, Node* right) : studentName(std::move(_name)), studentID(std::move(ID)), balanceTreeF(_bal),left(left), right(right){}
};

class Gator_AVL {
public:
    Node *root;
    std::vector<Node*> myVecList;

    Gator_AVL():root(nullptr),myVecList(){}

    //Insert Functions

    //Recursively Insert Nodes
    Node* recursiveInsert(Node* node, std::string& name, std::string &ID){
        if (!node){
            node = new Node;
            node->studentName = name;
            node->studentID = ID;
            return node;
        }
        if (ID > node->studentID)
            node->right = recursiveInsert(node->right,name, ID);
        else
            node->left = recursiveInsert(node->left, name, ID);

       node->balanceTreeF = getHeight(node);
        return node;
    }

    //Insert Name and ID, calls the recursive function to insert node and then balances the tree
    bool insertNameId( std::string& name, std::string& ID){
        if(searchId(root,ID) == nullptr) {
            root = recursiveInsert(root, name, ID);
            root = balanceTree(root);
            newBalance(root);
            return true;
        }else
            return false;
    }

    //Remove Functions

    //Removes listed ID, calls recursive function to delete node and the balances the tree
    bool removeId(std::string& ID){
        if(searchId(root,ID) != nullptr) {
            root = recursiveRemove(root,ID);
            root = balanceTree(root);
            newBalance(root);
            return true;
        }else
            return false;
    }
    //Recursively searches for a given ID
    Node* searchId(Node* node, std::string& ID){
        if (node != nullptr) {
            if (ID < node->studentID)
                return searchId(node->left, ID);
            if (ID > node->studentID)
                return searchId(node->right, ID);
            return node;
        }
        else
            return nullptr;
        if (ID == node->studentID){
            std::cout << node->studentName << std::endl;
            return node;
        }
    }
    void inOrder(Node* node){
        if (node != nullptr) {
            inOrder(node->left);
            myVecList.push_back(node);
            inOrder(node->right);
        }
        else return;
    }
    std::vector<Node*> searchName(std::string& name){
        std::vector<Node*> found;
        myVecList.clear();
        inOrder(root);
        for (auto & i : myVecList) {
            if (!(i->studentName == name))
                continue;
            found.push_back(i);
        }
        return found;
    }


    bool removeInorderN(int key){
        inOrder(root);
        return !(key > myVecList.size() - 1 || key < 0) && removeId(myVecList.at(key)->studentID);
    }

    Node* recursiveRemove(Node* node, std::string& ID){
        if (!node)
            return node;
        auto current = node->studentID;
        if (current < ID) {
            node->right = recursiveRemove(node->right, ID);
        }
        if (current > ID) {
            node->left = recursiveRemove(node->left, ID);
        }
        if (current == ID){
            return nodeDelete(node);
        }
        return node;
    }

    Node* nodeDelete(Node* node){
        //this takes care of a node that has no children
        if (node->right == nullptr && node->left == nullptr){
            delete node;
            return nullptr;
        }
        Node* current ;
        //Takes care of right node
        if (node->left == nullptr){
            current = node->right;
            delete node;
            return current;
        }
        else if (node->right == nullptr){
            //Takes care of left node
            current = node->left;
            delete node;
            return current;
        }
        else{
            //goes to right subtree and finds leftmost node
            current = helperLeast(node->right);
            //store replaced information.
            node->studentID = current->studentID;
            node->studentName = current->studentName;
            node->right = recursiveRemove(node->right,current->studentID);
        }
        return node;
    }

    int getHeight(Node* node){
        //if we have no node
        if (!node)
            return 0;
        //if we have a single node
        if(node->left == nullptr && node->right == nullptr)
            return 1;

        return std::max(getHeight(node->left), getHeight(node->right)) +1;
    }

    void newBalance(Node* node){
        if (node!= nullptr){
            node->balanceTreeF = getHeight(node->left) - getHeight(node->right);
            newBalance(node->left);
            newBalance(node->right);
        }
        else
            return;
    }

    Node* balanceTree(Node* node){
        //if we have no node present or if we have a single node present
        if (!node)
            return node;

        newBalance(root);
        node->left = balanceTree(node->left);
        node->right = balanceTree(node->right);
        newBalance(root);

        if (node->right != nullptr) {
            //Right Right case
            if (node->balanceTreeF == -2 && node->right->balanceTreeF == -1)
                return rotateLeft(node);
            //Right Left case
            else if (node->balanceTreeF == -2 && node->right->balanceTreeF == 1)
                return rotateRightLeft(node);
        }

        if (node->left != nullptr){
            //Left Left case
            if (node->balanceTreeF == 2 && node->left->balanceTreeF == 1)
                return rotateRight(node);
            //Left Right case
            else if(node->balanceTreeF == 2 && node->left->balanceTreeF == -1)
                return rotateLeftRight(node);
        }
        return node;
    }

    //Print Functions

    void printInorder(Node* node){
        if (!node)
            return;
        else{
            printInorder(node->left);
            std::cout << node->studentName;
           // check(node);

            if(node == helperBig(root))
                std:: cout << std:: endl;
            else
                std::cout<<", ";
            printInorder(node->right);
        }
    }

    void printPostorder(Node* node){
        if (!node)
            return;
        else{
            printPostorder(node->left);
            printPostorder(node->right);
            std::cout << node->studentName;
            //check2(node);

            if(node == root)
                std:: cout << std:: endl;
            else
                std::cout<<", ";
        }
    }

    void printPreorder(Node* node){
        if (!node)
            return;
        else {
            std::cout << node->studentName;
            //check3(node);
            if (node != helperBig(root))
                std::cout<< ", ";
            else{
                if (node->left == nullptr)
                    std::cout << std::endl;
                else
                    std::cout << ", " << node->left->studentName << std::endl;
                return;
            }
            printPreorder(node->left);
            printPreorder(node->right);
        }
    }

    void printLevelCount(Node* node){
        if (!node)
            return;
        else
            std::cout<<getHeight(root) << std::endl;
    }


    Node* rotateLeft(Node *node)
    {
        //your code here
        Node* grandchild = node->right->left;
        Node* newparent = node->right;
        newparent->left = node;
        node->right = grandchild;
        return newparent;

    }

    Node* rotateRight(Node *node)
    {
        //your code here
        Node* grandchild = node->left->right;
        Node* newparent = node->left;
        newparent->right = node;
        node->left = grandchild;
        return newparent;

    }

    Node* rotateLeftRight(Node *node)
    {
        //your code here
        Node* current , *temp;
        current = node->left;
        node->left = rotateLeft(current);
        temp = rotateRight(node);
        return temp;
    }

    Node* rotateRightLeft(Node *node)
    {
        //your code here
        Node* current , *temp;
        current = node->right;
        node->right = rotateRight(current);
        temp = rotateLeft(node);
        return temp;
    }
    //Helper Funtions

    Node* helperLeast(Node* node){
        return node->left == nullptr ? node : helperLeast(node->left);
    }

    Node* helperBig(Node* node){
        return node->right == nullptr ? node : helperBig(node->right);
    }

//Functions below used in the print functions to ensure we have the commas in the right places and to ensue the last name printed does not have a comma.
//print inorder
    void check(Node *node){
        if (!node)
            return;
        if(node == helperBig(root))
            std::cout<< std::endl;
        else
            std::cout <<", " ;
    }

    //print postorder
    void check2(Node *node){
        if (!node)
           return;
        if(node == root)
            std::cout<< std::endl;
        else
            std::cout <<", " ;
    }
//print pre order
    void check3(Node *node){
        if (!node)
            return;
        if (node == helperBig(root)){
            if (node->left == nullptr)
                std::cout << std::endl;
            else
                std::cout << ", "<< node->left->studentName << std::endl;
            return;
        }
        else
            std::cout << ", ";
    }
};
int main(){
    std::string operation, name,iD;
    //creating an object for the tree
    Gator_AVL obj;
    int inputs;

    std::cin >> inputs;
    for (int i = 0; i < inputs ; ++i) {
        std::cin>>operation;
//insert name and id into tree.
        if (operation == "insert") {
            std::string continueString;
            getline(std::cin, continueString, '\"');
            getline(std::cin, name, '\"');
            std::cin >> iD;
            //check to see if name is valid
            bool isValidName =true ;
            for (char i : name) {
                if (i != ' ' && !isalpha(i))
                    isValidName = false;
                break;
            }
            //ensures ID is valid and is also 8 digits
            bool isValidId= true;
            int validIdLength = 8;
            if(iD.size()!=validIdLength)
                isValidId= false;
            for (char i : iD) {
                if (!isdigit(i))
                    isValidId = false;
                break;
            }

            if (isValidId && isValidName){
                if(obj.insertNameId(name, iD))
                    std::cout << "successful\n";
                else
                    std::cout << "unsuccessful\n";
            } else
                std::cout << "unsuccessful\n";

        }
//searches for name and id in tree
        else if(operation == "search"){
            std::string both, continueString;
            getline(std::cin, continueString, ' ');
            getline(std::cin, both);
            bool isValidName =true ;
            bool isValidId = true;
            if (isalpha(both[1])) {
                name = both.substr(1, both.size() - 2);

                for (char i : name) {
                    if (i != ' ' && !isalpha(i))
                        isValidName = false;
                    break;
                }
                if (isValidName) {
                    auto found = obj.searchName(name);
                    if (!found.empty())
                        for (auto &valid : found)
                            std::cout << valid->studentID << std::endl;
                    else
                        std::cout << "unsuccessful" << std::endl;
                } else
                    std::cout << "unsuccessful" << std::endl;
            }
            else {
                iD = both;
                int validIdLength = 8;
                if (iD.size() != validIdLength)
                    isValidId = false;
                for (char i : iD) {
                    if (!isdigit(i))
                        isValidId = false;
                    break;
                }
                if (isValidId) {
                    auto found = obj.searchId(obj.root, iD);
                    if (found == nullptr)
                        std::cout << "unsuccessful" << std::endl;
                    else
                        std::cout << found->studentName << std::endl;
                } else
                    std::cout << "unsuccessful" << std::endl;
            }
        }
        //removes name and id in tree
        else if (operation == "remove"){
            std::cin >> iD;
            bool isValidId = true;
            int validIdLength = 8;
            if (iD.size() != validIdLength)
                isValidId = false;
            for (char i : iD) {
                if (!isdigit(i))
                    isValidId = false;
                break;
            }
            if (isValidId)
            {
                if (obj.removeId(iD))
                    std::cout << "successful" << std::endl;
            }
            else
                std::cout << "unsuccessful" << std::endl;
        }
//removes a specific id in tree
        else if (operation == "removeInorder"){
            int idRemove;
            std::cin >> idRemove;
            if (obj.removeInorderN(idRemove))
                std::cout << "successful" << std::endl;
            else
                std::cout << "unsuccessful" << std::endl;
        }
        //the print functions
        else if (operation == "printInorder")
            obj.printInorder(obj.root);

        else if (operation == "printPreorder")
            obj.printPreorder(obj.root);

        else if (operation == "printPostorder")
            obj.printPostorder(obj.root);

        else if (operation == "printLevelCount")
            obj.printLevelCount(obj.root);

    }
    return 0;
}

//References
/* //https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
 *  //Trees-3.pdf
 *  https://stepik.org/lesson/390627/step/2?unit=379727
 *  https://stepik.org/lesson/390628/step/3?unit=379728
 *  https://stepik.org/lesson/390628/step/1?unit=379728
 *  https://stepik.org/lesson/390628/step/2?unit=379728
 *  https://github.com/cverbsky/AVL-Tree
 * https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
 * https://www.geeksforgeeks.org/sorted-array-to-balanced-bst/
 * https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
 * Oracle employee Juan Calle helped explain how certain functions worked in an AVL tree as well as offered insight on how to call these function in the main.
 */