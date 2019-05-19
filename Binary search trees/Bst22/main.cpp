#include <iostream>
#include <string>
#include<stdlib.h>
#include<fstream>
#include<vector>
/*#Title: Binary Search Tree
#Author: Hintea, D.
#Date: 2017
#Availability: http://moodle.coventry.ac.uk */
using namespace std;
class BinTreeNode {
public:
	BinTreeNode(string value) {
		this->value = value;
		this->left = NULL;
		this->right = NULL;
	}
	string value;


	BinTreeNode* left;
	BinTreeNode* right;

};

BinTreeNode* tree_insert(BinTreeNode* tree, string item) {
	if (tree == NULL)
		tree = new BinTreeNode(item);
	else
		if (item < tree->value)
			if (tree->left == NULL)
				tree->left = new BinTreeNode(item);//Adds new node towards the left side
			else
				tree_insert(tree->left, item);
		else
			if (tree->right == NULL)
				tree->right = new BinTreeNode(item);//Adds new node towards the right side
			else
				tree_insert(tree->right, item);
	return tree;
}
//Function for pre-order
void preorder(BinTreeNode* tree) {
    std::cout << tree->value << std::endl;
 if (tree->left != NULL)
  preorder(tree->left);
 if (tree->right != NULL)
  preorder(tree->right);
 }

 BinTreeNode* findMin(BinTreeNode* node)
{
	BinTreeNode* current = node;
	while (current->left != NULL)
		current = current->left;

	return current;
}

bool findWord(BinTreeNode* tree, string value)//Used to find the word and check the path traversed,
//if path is found gives us the path traversed.
{
    if(tree==NULL){
        return false;
    }
    else if(tree->value==value){
            cout<<tree->value<<"\n Found!:"<<endl;
        return true;
    }
    else if(value <= tree ->value){
        cout<<tree->value<<" tleft ";
        return findWord(tree->left,value);
            }
     else{
          cout<<tree->value<<" tright ";
        return findWord(tree->right,value);

     }
}

   BinTreeNode* tree_delete(BinTreeNode* tree, string value) {
	if (tree == NULL) {
		return tree;
	}
	else if (value<tree->value) {
		tree->left = tree_delete(tree->left, value);//looks for the element to be deleted on the left side of tree
	}
	else if (value>tree->value) {
		tree->right = tree_delete(tree->right, value);//looks for the element to be deleted on the right side of tree
	}
	else {
		if (tree->left == NULL && tree->right == NULL) {
			delete tree;
			tree = NULL;//If tree has no child
		}
		else if (tree->left == NULL) {
			BinTreeNode* temp = tree;
			tree = tree->right;
			delete temp;
		}//if tree has one child
		else if (tree->right == NULL) {
			BinTreeNode* temp = tree;
			tree = tree->left;
			delete temp;
		}
		else {
			BinTreeNode* temp = findMin(tree->right);//Looks for the min element in the right subtree
			tree->value = temp->value;
			tree->right = tree_delete(tree->right, temp ->value);
					}
	}//if the word is root
	return tree;
}
/*#Title: Binary Search Tree
#Author: Hintea, D.
#Date: 2017
#Availability: http://moodle.coventry.ac.uk */

int main(int argc, char *argv[])
{
 std::ifstream infile;
 infile.open("file8.txt");
 if (infile.fail()) {
  cerr << "Error opening the file:" << endl;
  exit(1);
 }
 string engLang;
  BinTreeNode* t;
  int counter=0;
  //Inserts words in the file to the tree
 while (infile >> engLang) {
        if(counter==0){
           t = tree_insert(0,engLang);
           counter++;
        }
        else{
        t = tree_insert(t, engLang);
        }
}
    preorder(t);//calling preorder
    string word;
    cout<<"\nEnter the word to be found"<<endl;
    cin>>word;
    if(findWord(t,word)== true){
            cout<<"Yes"<<endl;
    }else{
         cout<<"No"<<endl;
      }

	cout<<"\nEnter the word to be deleted"<<endl;
	string deleteWord;
	cin>>deleteWord;
	t = tree_delete(t, deleteWord);
	preorder(t);
	//preorder after deleting a word


	cout<<"\nTesting for Inserting a word into a tree";
      bool yup = true;
      bool nope = false;
     if(t = tree_insert(0,"This")){
        cout<<"\nPass";
     }
        else{
        cout<<"\nFail";
        }

    cout<<"\nTest to find word";
    BinTreeNode* k = tree_insert(0,"This");
    tree_insert(k,"is");
    tree_insert(k,"else");
    if(findWord(k,"is")==true){
         cout<<"Pass";    }
    else{
         cout<<"Fail";
      }

      cout<<"\nPreorder Test"<<endl;
       BinTreeNode* l = tree_insert(0,"This");
      tree_insert(l,"im");
       tree_insert(l,"really");
      tree_insert(l,"Happy");
       tree_insert(l,"for");
       preorder(l);




	return 0;
}
