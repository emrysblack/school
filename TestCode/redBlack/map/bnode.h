// you might want to put these methods into your BinaryNode class
// to help you debug your red-black balancing code

/****************************************************
 * BINARY NODE :: FIND DEPTH
 * Find the depth of the black nodes. This is useful for
 * verifying that a given red-black tree is valid
 * Author: Br. Helfrich
 ****************************************************/
template <class T>
int BinaryNode <T> :: findDepth() const
{
   // if there are no children, the depth is ourselves
   if (pRight == NULL && pLeft == NULL)
      return (isRed ? 0 : 1);

   // if there is a right child, go that way
   if (pRight != NULL)
      return (isRed ? 0 : 1) + pRight->findDepth();
   else
      return (isRed ? 0 : 1) + pLeft->findDepth();
}

/****************************************************
 * BINARY NODE :: VERIFY RED BLACK
 * Do all four red-black rules work here?
 * Author: Br. Helfrich
 ***************************************************/
template <class T>
void BinaryNode <T> :: verifyRedBlack(int depth) const
{
   depth -= (isRed == false) ? 1 : 0;

   // Rule a) Every node is either red or black
   assert(isRed == true || isRed == false); // this feels silly

   // Rule b) The root is black
   if (pParent == NULL)
      assert(isRed == false);

   // Rule c) Red nodes have black children
   if (isRed == true)
   {
      if (pLeft != NULL)
         assert(pLeft->isRed == false);
      if (pRight != NULL)
         assert(pRight->isRed == false);
   }

   // Rule d) Every path from a leaf to the root has the same # of black nodes
   if (pLeft == NULL && pRight && NULL)
      assert(depth == 0);
   if (pLeft != NULL)
      pLeft->verifyRedBlack(depth);
   if (pRight != NULL)
      pRight->verifyRedBlack(depth);
}

/******************************************************
 * VERIFY B TREE
 * Verify that the tree is correctly formed
 * Author: Br. Helfrich
 ******************************************************/
template <class T>
void BinaryNode <T> :: verifyBTree() const
{
   // check parent
   if (pParent)
      assert(pParent->pLeft == this || pParent->pRight == this);

   // check left
   if (pLeft)
   {
      assert(pLeft->data <= data);
      assert(pLeft->pParent == this);
      pLeft->verifyBTree();
   }

   // check right
   if (pRight)
   {
      assert(pRight->data >= data);
      assert(pRight->pParent == this);
      pRight->verifyBTree();
   }
}
