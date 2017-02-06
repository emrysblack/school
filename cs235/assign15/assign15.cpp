/***********************************************************************
* Program:
*    Homework 15, Huffman 
*    Brother Twitchell, CS 235
* Author:
*    Brady Field
* Summary: 
*    Reads in letters and frequencies from a file to build Huffman code
***********************************************************************/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/**********************************************************************
 * Binary Tree class
 **********************************************************************/
class BTree
{
   private:
      int data;          // --- data stored in node of tree
      char letter;
      BTree* left;       // --- pointer to left subtree
      BTree* right;      // --- pointer to right subtree
      BTree* parent;     // --- pointer to the parent node;

   public:
      BTree(int data = 0, char letter = 0);  
      ~BTree(void);
      void insertLeft(BTree* item);     // creates a new node and inserts left
      void insertRight(BTree* item);    // creates a new node and inserts right
      BTree* getLeftChild(void);     // return the ptr to the left child
      BTree* getRightChild(void);    // return the ptr to the right child
      BTree* getParent(void);        // return parent
      int getData(void);
      char getLetter(void);
      void setData(int item);
      void setLeft(BTree* tree);     
      void setRight(BTree* tree);
      void infix(void);              // do infix traversal
      void prefix(void);             // do prefix traversal
      void postfix(void);            // do postfix traversal
      void level(void);              // do level order traversal
};

/**********************************************************************
 * opens a file and does a Huffman code
 **********************************************************************/
int main (int argc, char** argv)
{
   BTree* chars [26]; // array to store leaf nodes with letters
   BTree* total; // pointer to new node containing total of children
   BTree* head; // pointer to head node
   int array [26];
   string path[26] = {"0000", "010110", "01110", "01010", "100", "11101", 
                      "010111", "1011", "0100", "1111100010", "1111101",
                      "00010", "11110", "0011", "0010", "11100", "111110000",
                      "1010", "0110", "110", "01111", "111111", "000110", 
                      "11111001", "000111", "1111100011"};
   ifstream in;
   
   if (argc < 2)
      in.open("assign15.in");
   else
      in.open(argv[1]);
   if (in.fail())
      cout << "ERROR: could not open file\n";
   else
   {
      int weight;
      int index = 0;
      // read in file
      while (!in.eof())
      {
         in >> weight;
         if (in.good())
            array[ index++ ] = weight;
      }
      in.close();
      
      // build nodes for tree
      char letter = 'a';
      for (int i = 0; i < 26; i++)
      {
         total = new BTree(array[i], letter++);
         chars[i] = total;
      }
      
      // build tree
      BTree* first = chars[0]; // start searching at beginning
      BTree* second = chars[1];
      bool done = false;
      int count = 0;
      int j = 0;
      while (!done)
      {
         for (int i = 0; i < 26; i++) // find lowest two numbers in list
         {
            if (first->getData() > chars[i]->getData() and 
                chars[i]->getData() > 0)
            {
               first = chars[i];
            }
         }
         for (int i = 0; i < 26; i++)
         {
            if (second->getData() > chars[i]->getData() and 
                chars[i]->getData() > 0 and chars[i] != first)
            {
               second = chars[i];
               j = i;
            }
            if (second == first and chars[i]->getData() > 0 and
                chars[i] != first)
            {
               second = chars[i];
               j = i;
            }
            if (second->getData() == chars[i]->getData() and 
                chars[i] != second)
               if (chars[i]->getRightChild() == NULL and 
                   chars[i]->getLeftChild() == NULL)
                  if (second->getRightChild() != NULL or 
                      second->getLeftChild() != NULL) // give priority to leaf
                  {
                     second = chars[i];
                     j = i;
                  }
         }
         // create new parent node and link together
         total = new BTree (first->getData() + second->getData());
         total->insertLeft(first);
         total->insertRight(second);
         first->setData(first->getData() * -1);
         chars[j] = total;
         first = chars[0]; // reset back to first nodes
         second = total;
         count = 0;
         for (int i = 0; i < 26; i++) // test if done with tree
            if (chars[i]->getData() > 0)
               count++;
         if (count <= 1)
            done = true;
      }
      // test tree
      for (int i = 0; i < 26; i++)
      {
         if (chars[i]->getData() > 0)
            head = chars[i];

      }
      total = head;

      // follow paths to show they are in the right place
      string myPath;
      for (int i = 0; i < 26; i++)
      {
         myPath = path[i];
         for (int j = 0; j < myPath.size(); j++)
         {
            if (myPath[j] == '0')
               total = total->getRightChild();
            else if (myPath[j] == '1')
               total = total->getLeftChild();
         }
         cout << total->getLetter() << " = " << myPath << endl;
         total = head; // reset to top
      }
   }   
   return 0;
}

/**********************************************************************
 * constructor
 **********************************************************************/
BTree::BTree(int item, char value)
{
   parent =  NULL;
   right = NULL;
   left = NULL;
   data = item;
   letter = value;
}

/**********************************************************************
 * destructor uses postfix algorithm to delete nodes
 **********************************************************************/
BTree::~BTree(void)
{
   if (left != NULL) left->~BTree();
   if (right != NULL) right->~BTree();
   delete this;
}

/**********************************************************************
 * inserts node to left
 **********************************************************************/
void BTree::insertLeft(BTree* item)
{
   left = item;
   item->parent = this;
}

/**********************************************************************
 * inserts node to right
 **********************************************************************/
void BTree::insertRight(BTree* item)
{
   right = item;
   item->parent = this;
}

/**********************************************************************
 * returns the pointer to the left child
 **********************************************************************/
BTree* BTree::getLeftChild(void)
{
   return left;
}

/**********************************************************************
 * returns the pointer to the right child
 **********************************************************************/
BTree* BTree::getRightChild(void)
{
   return right;
}

/**********************************************************************
 * returns pointer to the parent node
 **********************************************************************/
BTree* BTree::getParent(void)
{
   return parent;
}

/**********************************************************************
 * returns data of current node
 **********************************************************************/
int BTree::getData(void)
{
   return data;
}

/**********************************************************************
 * returns letter of current node
 **********************************************************************/
char BTree::getLetter(void)
{
   return letter;
}

/**********************************************************************
 * sets data of current node
 **********************************************************************/
void BTree::setData(int item)
{
   data = item;
}

/**********************************************************************
 * sets left child to node
 **********************************************************************/
void BTree::setLeft(BTree* tree)
{
   left = tree;
   if (left != NULL) left->parent = this;
}

/**********************************************************************
 * sets right child to node
 **********************************************************************/     
void BTree::setRight(BTree* tree)
{
   right = tree;
   if (right != NULL) right->parent = this;
}

/**********************************************************************
 * do infix traversal
 **********************************************************************/
void BTree::infix(void)
{
   if (left != NULL) left->infix();
   cout << data << " ";
   if (right != NULL) right->infix();
}

/**********************************************************************
 * do prefix traversal
 **********************************************************************/
void BTree::prefix(void)
{
   cout << data << " ";
   if (left != NULL) left->prefix();
   if (right != NULL) right->prefix();
}

/**********************************************************************
 * do postfix traversal
 **********************************************************************/
void BTree::postfix(void)
{
   if (left != NULL) left->postfix();
   if (right != NULL) right->postfix();
   cout << data << " ";
}

/**********************************************************************
 * do level order traversal
 **********************************************************************/
void BTree::level(void)
{
   const int MAX = 50;
   BTree *queue[MAX];
   BTree *temp;
   int front = 0;
   int back = 0;

   queue[back++ ] = this;

   while (front != back)
   {
      temp = queue[front];
      front = (front + 1) % MAX;
      if (temp != NULL)
      {
         // visit
         cout.width(4);
         cout << temp->data << " ";
         if (temp->parent == NULL)
            cout << " Parent = NULL! " << endl;
         else
            cout << " Parent = " << temp->parent->data << "   " << endl;
         // end Visit        
         queue[back] = temp->left;
         back = (back + 1) % MAX;
         queue[back] = temp->right;
         back = (back + 1) % MAX;

      }
   }
}