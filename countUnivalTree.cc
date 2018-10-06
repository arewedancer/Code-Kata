
//count number of unival (sub)trees
//recursive, O(N)

static int cnt = 0;
bool isUnival(TreeNode * p)
{
	if ( p->left == NULL && p->right == NULL )
	{
		cnt++;
		return true;
	};
	if ( p->left != NULL && p->right != NULL)
  {
		if (p->val == p->left->val && p->val == p->right->val && isUnival(p->left) && isUnival(p->right))
		{
			cnt++;
			return true;
		};
		else
			return false;
	};
	if (p->left != NULL && p->right == NULL)
	{
		if (p->val == p->left->val && isUnival(p->left))
		{
			cnt++;
			return true;
		};
		else
			return false;
	};
	if (p->left == NULL && p->right != NULL)
	{
		if (p->val == p->right->val && isUnival(p->right))
		{
			cnt++;
			return true;
		};
		else
			return false;
	};
	return false;
};

