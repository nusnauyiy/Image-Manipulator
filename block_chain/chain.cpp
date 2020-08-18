#include "chain.h"
#include "chain_given.cpp"
#include <cmath>
#include <iostream>
#include <cstdlib>

using namespace std;

// PA1 functions

/**
 * Destroys the current Chain. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain()
{
    clear();
}

void Chain::swapWithNext(Node *left) {

    bool isHead = (left == head_);
    bool isTail = (left == tail_);

    Node * right = left->next;
    bool isRightTail = (right == tail_);

    Node * leftLeft = left->prev;
    Node * rightRight = right->next;

    leftLeft->next = right;
    right->prev = leftLeft;

    left->prev = right;
    right->next = left;

    left->next = rightRight;
    rightRight->prev = left;
    //cout << "38";
    if (isHead) {
        head_ = right;
    }
    if (isTail) {
        head_ = left;
        tail_ = right;
    }
    if (isRightTail) {
        tail_ = left;
    }
    //cout << "49";
}

void Chain::swap(int pos1, int pos2) {
    Node * p1 = walk(head_, pos1);
    Node * p2 = walk(head_, pos2);
    if (p1 == p2  || p1 == NULL || p2 == NULL) return;
    swap(p1, p2);
}

void Chain::swap(Node* p1, Node* p2) {
    if (p1->next == p2) {
        swapWithNext(p1);
        return;
    } else if (p2->next == p1) {
        swapWithNext(p2);
        return;
    } 

    bool isHead1 = false;
    bool isHead2 = false;
    if (head_ == p1) isHead1 = true;
    if (head_ == p2) isHead2 = true;

    bool isTail1 = false;
    bool isTail2 = false;
    if (tail_ == p1) isTail1 = true;
    if (tail_ == p2) isTail2 = true;
    
    p1->prev->next = p2;
    p2->prev->next = p1;

    p1->next->prev = p2;
    p2->next->prev = p1;

    Node * prev1 = p1->prev;
    Node * prev2 = p2->prev;
    Node * next1 = p1->next;
    Node * next2 = p2->next;

    p1->prev = prev2;
    p2->prev = prev1;
    p1->next = next2;
    p2->next = next1;

    if (isHead1) head_ = p2;
    if (isHead2) head_ = p1;
    if (isTail1) tail_ = p2;
    if (isTail2) tail_ = p1;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
void Chain::insertBack(const Block &ndata)
{
    /* YOUR CODE HERE */
    /*Node * newNode = new Node(ndata);
    newNode->prev = tail_;
    newNode->next = head_;
    if (tail_ != NULL) {
        tail_->next = newNode;
    } 
    tail_ = newNode;

    if (head_ != NULL) {
        head_->prev = newNode;
    } else {
        head_ = newNode;
    }*/

    if (head_ == NULL) {
        Node * newNode = new Node(ndata);
        newNode->prev = newNode;
        newNode->next = newNode;
        head_ = newNode;
        tail_ = newNode;
    } else {
         Node * newNode = new Node(ndata);
         newNode->prev = tail_;
         newNode->next = head_;
         tail_->next = newNode;
         tail_ = newNode;
         head_->prev = newNode;
    }
    length_++;
}

/**
 * Mirrors the given chain across its center on the x-axis.
 */
void Chain::mirror()
{
    /* YOUR CODE HERE */
    if (head_ == NULL || head_ == tail_) return;  //chain with 0/1 block is same when mirrored
    /*
    //swap prev and next for all blocks that are not head and tail
    for (Node * trav = head_; trav != head_; trav = trav->prev) {
        cout << "swapping" << endl;
        Node * temp = trav->prev;
        trav->prev = trav->next;
        trav->next = temp;
    }*/

    Node * trav = head_;
    do {
        Node * temp = trav->prev;
        trav->prev = trav->next;
        trav->next = temp;
        trav = trav->prev;
    } while (trav != head_);

    //swap head and tail
    Node * temp = tail_;
    tail_ = head_;
    head_ = temp;
/*
    Node * frontTrav = head_;
    Node * backTrav = tail_;
    for (int i = 0; i < size() / 2; i++) {
        Node * tempFront = frontTrav;
        Node * tempBack = backTrav;
        swap (tempFront, tempBack);
        cout << "swapped" << endl;
        frontTrav = frontTrav->next;
        backTrav = backTrav->prev;
    }*/
}

/*
* Modifies the current chain by "rotating" every k nodes.
* Starting with the 0th node, swap with with the kth next node.
* Starting at the position you just swapped into, continue to
* swap nodes until you swap a node with the final node of the chain.
* Some examples with the chain a b c d e:
*   k = 0: a b c d e
*   k = 1: b c d e a    a b c d e -> b a c d e -> b c a d e -> b c d a e -> b c d e a
*   k = 2: c b e d a    a b c d e -> c b a d e -> c b e d a
*   k = 3: d e c b a    a b c d e -> d b c a e -> d a c b e -> d e c b a 
* You may assume that the rotation will not loop forever
* (i.e. you **will** swap the final node in the list at some point)
*/
void Chain::rotate(int k)
{
    /* YOUR CODE HERE */
    if (head_ == NULL || head_ == tail_ || k == 0) return;
    if (k == 1) {
        head_ = head_->next;
        tail_ = tail_->next;
        return;
    }

    Node * trav = head_;

    while (trav != tail_) {

        Node * swapWith = trav;
        for (int i = 0; i < k; i++) {
            swapWith = swapWith->next;
        }

        swap(trav, swapWith);

        //trav = swapWith;
    }
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */

void Chain::clear()
{
    length_ = 0;
    if (head_ == NULL) return;
    Node * trav = head_;
    head_ = NULL;
    while (trav != tail_) {
        trav = trav->next;
        delete trav->prev;
    }
    if (tail_ != NULL) {
        delete tail_;
        tail_ = NULL;
    }
    //length_ = 0;
}

/* makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 */

void Chain::copy(Chain const &other)
{
    /* YOUR CODE HERE */
    /*if (size() != 0) {
        clear();
    }*/
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
    width_ = other.width_;
    height_ = other.height_;
    for (Node * trav = other.head_; trav != other.tail_; trav = trav->next) {
        insertBack(trav->data);
    }

    if (other.tail_ != NULL) {
        insertBack(other.tail_->data);
    }
}
