void BTree::level()
{
  const int MAX = 50;
  BTree *queue[MAX];
  BTree *temp;
  int front = 0;
  int back = 0;

  queue[back++] = this;

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
