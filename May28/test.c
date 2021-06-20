struct node *tree_succesor(struct node *x)
{
    if (x->right != NULL)
        return tree_minimum(x->right);
    struct node *y = x->parent;
    while (y != NULL && x == y->right)
    {
        x = y;
        y = y->parent;
    }
    return y;
}

struct node *tree_delete(struct node *T, struct node *x)
{
    struct node *r = T;
    struct node *y;
    struct node *z;

    if (x->left == NULL || x->right == NULL)
        y = x;
    else
        y = tree_succesor(x);

    if (y->left != NULL)
    {
        z = y->left;
    }
    else
    {
        z = y->right;
    }

    if (z != NULL)
    {
        z->parent = y->parent;
    }

    if (y->parent == NULL)
    {
        r = z;
    }
    else
    {
        if (y == y->parent->left)
        {
            y->parent->left = z;
        }
        else
        {
            y->parent->right = z;
        }
    }

    if (y != x)
    {
        x->key = y->key;
    }
    free(y);
    return r;
}