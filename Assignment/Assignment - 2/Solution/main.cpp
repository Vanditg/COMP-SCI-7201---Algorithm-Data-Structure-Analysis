/*==================================
lgorithm-and-Data-Structure-Analysis
Student: Vandit Jyotindra Gajjar
id: a1779153
Semester: 1
Year: 2020
Assignment : 2
===================================*/
//Importing libraries.
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
using namespace std;

//Node Structure for AVL Tree
typedef struct structureOfNode {
    int data;
    int difference;
    //Defining node that has to child which are null at initialization
    struct structureOfNode *child[2];
} treeNodeObject;//The name of the datatype is treeNodeObject 

//Function treeRotation - Accepts two arguments node and leftOrRight - left and right rotation
void treeRotation(treeNodeObject **node, int leftOrRight) {
    int leftSide;
	int rightSide;
	int signature;
	if(leftOrRight) {
		leftSide = 0;
		rightSide = 1;
		signature = 1;
	} else {
		leftSide = 1;
		rightSide = 0;
		signature = -1;
	}
	//If no child found, we close the program by this condition. 
    if((*node)->child[leftSide] == NULL){ 
      exit(1);
    }
    else {
        treeNodeObject* left = (*node)->child[leftSide];
        int x = (*node)->difference * signature;
		int y = left->difference * signature;
        //Update the tree depth from nx and ny
		int nx = (y >= 0) ? (x - 1 - y) : (x - 1);
		int ny = (y >= 0) ? ((x - 1 - y >= 0) ? (y - 1) : (x - 2)) : ((x - 1 >= 0) ? (y - 1) : (x + y- 2));
        (*node)->difference = nx * signature;
        left->difference = ny * signature;
        //Perform the rotation here for left and right side of tree
        (*node)->child[leftSide] = (*node)->child[leftSide]->child[rightSide];
        left->child[rightSide] = *node;
        *node = left;
    }
}
//Defining treeModifier function takes three arguments - Node, data and removeOrAdd
//After removing and adding node on the tree, this function gives the difference of height 
int treeModifier(treeNodeObject **node, int data, int removeOrAdd) {
    if(*node == NULL) {
        if (!removeOrAdd) {
			return 0;
		} else {
            //We add a new node from here
            *node = new treeNodeObject();
            if(*node == NULL){
              exit(1);
            }
            else{
                //Instantiate the node from here 
                (*node)->data = data;
				//There will be no child in the tree and difference as this is the first 
                (*node)->difference = 0; 
                (*node)->child[0] = NULL;
                (*node)->child[1] = NULL;
            }
            return *node != NULL;
        }
    }
    else {
        int leftSidetreeModifier;
		int tmpDeltaDifference;
		int tmpDeltaSignature;
        treeNodeObject *nextNode;
        if(data == (*node)->data) {
            //Condition-check: If the previous node value is same as current node data, we do not do any operation here.
            if(removeOrAdd) {
                return 0;
            }
            else {
                //Perform deletion here for the node
                if((*node)->child[1] == NULL) {
                    //We'll add left child here, if there will be no right child for this current position
                    nextNode = (*node)->child[0];
                    delete(*node);
                    *node = nextNode;
                    //So the height will be -1 for this case
                    return -1;
                }
                else if((*node)->child[0] == NULL) {
                    //We'll add right child here, if there will be no left child for this current position
                    nextNode = (*node)->child[1];
                    delete(*node);
                    *node = nextNode;
                    //So the height will be -1 for this case
                    return -1;
                }
                else{
                    //If we encounter child on both the side of tree 
                    //The we perform to search for the maximum node on left subtree 
                    nextNode = (*node)->child[0];
					while (nextNode->child[1] != NULL) {
						nextNode = nextNode->child[1];
					}
                    //After, we return the data of the maximum node on left subtree 
                    (*node)->data = nextNode->data;
                    //We perform deletion for the maximum node on left subtree
                    leftSidetreeModifier = 0;
                    tmpDeltaSignature = 1;
                    tmpDeltaDifference = treeModifier(&(*node)->child[leftSidetreeModifier], nextNode->data, removeOrAdd); 
                }
            }
        }
        else {
            //Condition-check: We'll perform santiy check with the current node data to check where to go which side of the tree
            leftSidetreeModifier = (data < (*node)->data) ? 0 : 1;
			tmpDeltaSignature = (data < (*node)->data) ? 1 : -1;
            tmpDeltaDifference = treeModifier(&(*node)->child[leftSidetreeModifier], data, removeOrAdd);
        }
        if (tmpDeltaDifference != 0) {
            //Condition-check: If there will be any changes occurse to the child - we'll store the defined variables for rotation
            int tmpDifference = (*node)->difference;
            int performRotation = 0;
            int rotateLeftSide;
			int differenceSignature;
			int rotateRight;
            (*node)->difference = (*node)->difference + tmpDeltaDifference * tmpDeltaSignature; 
            if ((*node)->difference > 1) {
                //Here we check for the difference and perform right rotation
                performRotation = 1;
                rotateLeftSide = 0;
                differenceSignature = 1;
                rotateRight = 1;
            }
            else if((*node)->difference < -1) {
                //Here we check for the difference and perform left rotation
                performRotation = 1;
                rotateLeftSide = 1;
                differenceSignature = -1;
                rotateRight = 0;
            }
            if (performRotation) {
                int differenceInChild = (*node)->child[rotateLeftSide]->difference;
                //Perform the rotation here 
                if((*node)->child[rotateLeftSide]->difference * differenceSignature < 0) {
                    treeRotation(&(*node)->child[rotateLeftSide], !rotateRight);
                }
                //Perform rotation for the current node here 
                treeRotation(node, rotateRight);
                if(tmpDeltaDifference < 0 && differenceInChild != 0){
                  return -1;
                }
                else{
                  return 0;
                }
            }
            //We return diifference of the height on tree
            if (tmpDeltaDifference > 0 && tmpDifference == 0) {
                return 1;
            }
            else if (tmpDeltaDifference < 0 && tmpDifference != 0) {
                return -1;
            }
            else {
                return 0;
            }
        } else {
            return 0;
        }
    }
}
//Defining postOrderTraverse - Argument node 
//This will print post Order Traversal of tree
void postOrderTraverse(const treeNodeObject *node) {
	if (node == NULL) {
	  cout << endl;
	  return;
	}
    postOrderTraverse(node->child[0]);
    postOrderTraverse(node->child[1]);
    cout << node->data << " ";	
}
//Defining inOrderTraverse - Argument node 
//This will print in Order Traversal of tree
void inOrderTraverse(const treeNodeObject *node) {
	if(node==NULL) {
	  cout << endl;
	  return;
	}
    inOrderTraverse(node->child[0]);
    cout << node->data << " ";
    inOrderTraverse(node->child[1]);
}
//Defining preOrderTraverse - Argument node 
//This will print pre Order Traversal of tree
void preOrderTraverse(const treeNodeObject *node) {
	if(node==NULL) {
	  cout << endl;
	  return;
	}
    cout << node->data << " ";
    preOrderTraverse(node->child[0]);
    preOrderTraverse(node->child[1]);
}
//Defining printDataOfTree - Accepts tmp string, and dummy object
//Returns the traversal based on the testcases 
void printDataOfTree(string tmp, treeNodeObject *dummy) {
	if (dummy == NULL){
      cout << "EMPTY" << endl;
	  return;
    }
	if(tmp == "IN"){
        inOrderTraverse(dummy);
    }
    else if (tmp == "POST"){
        postOrderTraverse(dummy);
    }
    else if(tmp == "PRE"){
        preOrderTraverse(dummy);
    }
}
//Driver main method 
int main(void) {
    string inputData;
    getline( std::cin, inputData );
    istringstream is( inputData );
	//Convert the inputData and store in vectors - vectorData
    vector<string> vectorData( ( istream_iterator<string>( is ) ), istream_iterator<string>() );

    //Instantiate root which is null 
    treeNodeObject *root = NULL;
	int i = 0;
    while (i < vectorData.size()) {
		string tmp = vectorData[i];
		if(i==vectorData.size()-1) {
			printDataOfTree(vectorData[i],root);
		}
        else{
            int add = (tmp[0] == 'A') ? 1 : 0;
            int value = 0;
            tmp.erase(0,1);
            stringstream function(tmp);
            function >> value;
            treeModifier(&root, value, add);
        }
		i++;
	}
    return 0;
}
/* Useful References: Acknowledgements 
[1] https://en.wikipedia.org/wiki/AVL_tree
[2] https://en.wikipedia.org/wiki/Binary_search_tree
[3] https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
[4] https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
[5] https://gist.github.com/Harish-R/097688ac7f48bcbadfa5
[6] https://wkdtjsgur100.github.io/avl-tree/
[7] https://www.youtube.com/watch?v=jDM6_TnYIqE
[8] https://www.geeksforgeeks.org/binary-search-tree-data-structure/ 
*/