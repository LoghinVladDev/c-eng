#include <iostream>

// O(n^2) > O(n) <= push back <-> push front => O(1)
// pop_front -> O(1)
// pop_back -> O(n)
// find(x) -> O(n)

// list : pop_front, pop_back, push_front, push_back, front, back, isEmpty

//// Coada / Stive
//// Stiva -> pop_front, push_front, front, isEmpty. O(1)
//// Coada -> pop_front, <<  push_back  >> O(n) , front, isEmpty
//// add1 : Coada cu dublu inlantuit -> push_back-ul este O(1)
//
//struct SimpleListNode {
//    int val;
//    SimpleListNode* next;
//};      /// sizeof(SimpleListNode) = 4 + sizeof(*) = 4 + 8 = 12 B + 4 B (struct) =  16B
//
//struct DoubleListNode {
//    int val;
//    DoubleListNode* next;
//    DoubleListNode* prev;
//}; /// sizeof(DoubleListNode) = 4 + 2 * sizeof(*) = 4 + 16 = 20 B + 4 B (struct) =  24B


// O(n), O(n^2) , O(n + m), O(log2 n) <- termeni de complexitate. Marginire superioara
// n -> n/2 -> n/4 -> n/8 -> .... -> 1  = de cate ori se imparte n la 2 = log 2 n = x, unde 2 ^ x = n

// preferam mai multa memorie -> mai rapid / nu ne prea pasa de viteza

struct Node {
    int val;
    Node * next;
    Node * prev;

};

Node * front    = NULL;
Node * back     = NULL;

// TODO : represent with structure instead of two ptrs
//struct DoubleList {
//    Node * front;
//    Node * back;
//};


// push, pop, front/back -> push_back, pop_back, front, print

void push_back(int value, Node * & front, Node * & back) {

    if( back == NULL ) {
        back = new Node;
        front = back;

        back->next = back->prev = NULL;
        back->val = value;

        return;
    }

    Node * p = new Node;
    p->val = value;

    p->next = NULL;
    p->prev = back;

    back->next = p; /// asta poate da segfault, back poate fi null
    back = p;
}

void push_front (int value, Node* & front, Node*  & back) {
    if (front == NULL) {
        front = new Node;
        front->val = value;
        front->prev = NULL;
        front->next = NULL;
        back = front;
        return;
    }
    Node* p = new Node;
    p->val = value;
    p->next = front;
    p->prev = NULL;
    front->prev = p; /// aveam 1 nod inainte, se m
    front = p;
}

void pop_front (Node* & front, Node* & back) {
    Node* p;
    if (front == NULL) {
        return;
    }
    if (front == back) {
        delete front;
        front = back = NULL;
        return;
    }
    p = front;
    front = front->next;
    delete p;
    front->prev = NULL;
}

void pop_back(Node* & front, Node* & back) {
    if(back == NULL) {
        return;
    }

    if( back->prev == NULL ) { // front == back
        delete back;    /// back = 0x102

//        delete front; /// front = 0x102 (nu mai e in prog nostru) => segfault

        front = back = NULL; // obl. amandoua !!!
        return;
    }

    back = back->prev; // 1 . back = nullptr, 2. back->prev = nullptr => back = back->prev <=> back = nullptr
    delete back->next; // 2. cont . back = nullptr, back->next <=> nullptr->next => segfault // back->prev = null => avem un singur el.
    back->next = NULL;
}

int Front(Node* front, Node*  back) {
    if ( front == NULL ) {
        return -1;
    }

    return front->val;
}

int Back (Node* front, Node* back) {
    if (back == NULL)
        return -1;
    else
        return back->val;
}

void print_from_front(Node*  front, Node*  back) {

    while(front != NULL) {
        std::cout << front->val << ' ';
        front = front->next;
    }
    std::cout << '\n';
}

void print_from_back (Node* front, Node* back) {
    while (back != NULL) {
        std::cout << back->val << ' ';
        back = back->prev;
    }
}

void delete_list (Node* & front, Node* & back) {
    while(front != NULL) {
        Node* p = front;
        front = front->next;
        delete p;
    }

    back = NULL;
}

int main() {

//    push_back(5, front, back);
//    push_back(10, front, back);

    push_front(5, front, back);
    //pop_front (front, back);
    push_front(90, front, back);
    print_from_front(front, back);
    std::cout<<'\n';
    print_from_back(front, back);
    delete_list(front, back);

    return 0;
}