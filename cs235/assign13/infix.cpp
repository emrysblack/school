void BTree::infix()
{
  if (left != NULL) left->infix();
  cout << data << " ";
  if (right != NULL) right->infix();
}
