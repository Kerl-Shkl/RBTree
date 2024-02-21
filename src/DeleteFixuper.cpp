#include "DeleteFixuper.h"
#include "IRBTree.h"

DeleteFixuper::DeleteFixuper(IRBTree& tree)
: tree(tree)
{}

void DeleteFixuper::MyFixUp(std::shared_ptr<Node> x)
{
    while (x != tree.getRoot() && tree.isBlack(x)) {
        setParentAndSibling(x);
        if (isFirstCase()) {
            solveFirstCase(x);
        }
        if (isSecondCase()) {
            solveSecondCase(x);
        }
        else {
            if (isThirdCase()) {
                solveThirdCase(x);
            }
            solveFourthCase(x);
        }
    }
    x->color = NodeColor::black;
}

void DeleteFixuper::setParentAndSibling(const std::shared_ptr<Node>& x)
{
    parent = x->parent.lock();
    sibling = tree.isLeftDesc(x) ? parent->right : parent->left;
}

bool DeleteFixuper::isFirstCase() const
{
    return tree.isRed(sibling);
}

bool DeleteFixuper::isSecondCase() const
{
    return tree.isBlack(sibling->left) && tree.isBlack(sibling->right);
}

bool DeleteFixuper::isThirdCase() const
{
    auto sibling_desc =
        tree.isLeftDesc(sibling) ? sibling->left : sibling->right;
    return tree.isBlack(sibling_desc);
}

void DeleteFixuper::solveFirstCase(std::shared_ptr<Node>& x)
{
    sibling->color = NodeColor::black;
    parent->color = NodeColor::red;
    if (tree.isLeftDesc(x)) {
        tree.LeftRotate(parent);
    }
    else {
        tree.RightRotate(parent);
    }
    setParentAndSibling(x);
}

void DeleteFixuper::solveSecondCase(std::shared_ptr<Node>& x)
{
    sibling->color = NodeColor::red;
    x = parent;
}

void DeleteFixuper::solveThirdCase(std::shared_ptr<Node>& x)
{
    sibling->right->color = NodeColor::black;
    sibling->color = NodeColor::red;
    if (tree.isLeftDesc(x)) {
        tree.RightRotate(sibling);
    }
    else {
        tree.LeftRotate(sibling);
    }
    setParentAndSibling(x);
}

void DeleteFixuper::solveFourthCase(std::shared_ptr<Node>& x)
{
    sibling->color = parent->color;
    parent->color = NodeColor::black;
    sibling->right->color = NodeColor::black;
    if (tree.isLeftDesc(x)) {
        tree.LeftRotate(parent);
    }
    else {
        tree.RightRotate(parent);
    }
    x = tree.getRoot();
}

/* void DeleteFixuper::FixUp(std::shared_ptr<Node> x)
{
    while (x != tree.root && RBTree::isBlack(x)) {
        if (RBTree::isLeftDesc(x)) {
            setParentAndSibling(x);
            if (RBTree::isRed(sibling)) {
                solveFirstCase(x);
                // sibling->color = NodeColor::black;
                // parent->color = NodeColor::red;
                // tree.LeftRotate(parent);
                // parent = x->parent.lock();
                // sibling = parent->right;
            }
            if (RBTree::isBlack(sibling->left) &&
                RBTree::isBlack(sibling->right))
            {
                sibling->color = NodeColor::red;
                x = parent;
            }
            else {
                if (RBTree::isBlack(sibling->right)) {
                    sibling->left->color = NodeColor::black;
                    sibling->color = NodeColor::red;
                    tree.RightRotate(sibling);
                    parent = x->parent.lock();
                    sibling = parent->right;
                }
                sibling->color = parent->color;
                parent->color = NodeColor::black;
                sibling->right->color = NodeColor::black;
                tree.LeftRotate(parent);
                x = tree.root;
            }
        }
        else {
            setParentAndSibling(x);
            if (RBTree::isRed(sibling)) {
                // sibling->color = NodeColor::black;
                // parent->color = NodeColor::red;
                // tree.RightRotate(parent);
                // parent = x->parent.lock();
                // sibling = parent->left;
                solveFirstCase(x);
            }
            if (RBTree::isBlack(sibling->left) &&
                RBTree::isBlack(sibling->right))
            {
                sibling->color = NodeColor::red;
                x = parent;
            }
            else {
                if (RBTree::isBlack(sibling->left)) {
                    sibling->right->color = NodeColor::black;
                    sibling->color = NodeColor::red;
                    tree.LeftRotate(sibling);
                    parent = x->parent.lock();
                    sibling = parent->left;
                }
                sibling->color = parent->color;
                parent->color = NodeColor::black;
                sibling->left->color = NodeColor::black;
                tree.RightRotate(parent);
                x = tree.root;
            }
        }
    }
    x->color = NodeColor::black;
} */
