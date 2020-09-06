
#include <iostream>

struct Node {
    int value;
    Node * left;
    Node * right;
};

Node * rootNode;

bool exists ( int value, Node * root ) {
    if ( root == nullptr )
        return false;

    while ( root != nullptr ) {
        if ( value == root->value )
            return true;

        if ( value > root->value )
            root = root->right;
        else if ( value < root->value )
            root = root->left;
    }

    return false;
}

void insert ( int value, Node * & root ) {
    if ( root == nullptr ) {
        root = new Node;
        root->value = value;
        root->left = nullptr;
        root->right = nullptr;
        return;
    }

    Node * copy = root;
    while ( true ) {
        if ( copy->value > value ) {
            // stg
            if ( copy->left == nullptr ) {
                copy->left = new Node;
                copy->left->value = value;
                copy->left->left = nullptr;
                copy->left->right = nullptr;
                return;
            } else {
                copy = copy->left;
                continue;
            }
        } else if ( copy->value < value ) {
            // drp
            if ( copy->right == nullptr ) {
                copy->right = new Node;
                copy->right->value = value;
                copy->right->left = nullptr;
                copy->right->right = nullptr;
                return;
            } else {
                copy = copy->right;
                continue;
            }
        } else if ( copy->value == value ) {
            return;
        }
    }
}

void print ( Node * root ) {
    if ( root != nullptr ) {
        print ( root->left );
        std::cout << root->value << ' ';
        print ( root->right );
    }
}

int main () {
    insert( 4, rootNode );
    insert( 6, rootNode );
    insert( 10, rootNode );
    insert( 15, rootNode );
    insert( 2, rootNode );
    insert( 3, rootNode );
    insert( 5, rootNode );
    insert( 20, rootNode );
    insert( 6, rootNode );
    insert( 18, rootNode );
    insert( 1, rootNode );
    insert( 4, rootNode );
    insert( 11, rootNode );
    insert( 13, rootNode );

    print ( rootNode );

    std::cout << '\n';

    std::cout << "7 exista in arb : " << exists ( 7, rootNode ) << '\n';
    std::cout << "11 exista in arb : " << exists ( 11, rootNode ) << '\n';
    std::cout << "3553 exista in arb : " << exists ( 3553, rootNode ) << '\n';
}