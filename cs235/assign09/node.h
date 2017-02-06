/*******************************************************************
 *
 *     FILE: node.h
 *
 *  PURPOSE: Contains the class definition of a Node
 *
 *******************************************************************/
class Node
{
   private:
     int data;                 // --- data in each node
     Node* next;               // --- pointer to next node

   public:
     Node();                   // --- Creates empty node
     Node* getNext();          // --- returns next pointer of a node
     int getData();            // --- returns data of a node
     void setData(int item);   // --- stores item in data member of current node
     void setNext(Node* node); // --- sets next to point to node
};

/**********************************************************************
 * Default constructor
 **********************************************************************/
Node::Node()
{
   data = 0;
   next = NULL;
}
 
/**********************************************************************
 * Gets pointer to next node in list
 **********************************************************************/
Node* Node::getNext()
{
   return next;
}

/**********************************************************************
 * Gets integer of current node
 **********************************************************************/
int Node::getData()
{
   return data;
}

/**********************************************************************
 * Stores an integer in the current node
 **********************************************************************/
void Node::setData(int item)
{
   data = item;
}

/**********************************************************************
 * Sets pointer to the next node
 **********************************************************************/
void Node::setNext(Node* node)
{
   next = node;
}
