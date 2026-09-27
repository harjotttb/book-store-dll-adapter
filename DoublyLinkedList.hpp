#ifndef MY_DOUBLY_LINKED_LIST_HPP
#define MY_DOUBLY_LINKED_LIST_HPP


/**
 * TODO: Implement DoublyLinkedList, its Node, and its Iterator!
 * Name: Harjot Bhangu
 * CWID: 828073312
 * Email: harjottb@csu.fullerton.edu
 * 
 * I've left some methods filled out for you,
 * 	and stubbed out some structure, to reduce difficulty.
 * 
 * You may add helper methods as you see fit,
 * 	as long as you can still pass all unit tests.
 * 
 * Notice we're inside a namespace here.
 * The DLL is inside a namespace called DoublyLinkedList,
 * 	which is itself inside a namespace called CPSC131
 * This means, if you'd like to play around with your class later,
 * 	you'll need to access it like so:
 * ::CPSC131::DoublyLinkedList::DoublyLinkedList<int> list;
 * 
 * Look into main.cpp and CPP_Tests.cpp for examples of using
 * 	the DLL and your BookStore. But don't worry too much, as you
 * 	only need to implement these classes
 * (main and tests are already done for you)
 */


//
#include <iostream>
#include <stdlib.h>
#include <stdexcept>


/**
 * Namespace for our classroom and DLL !
 */
namespace CPSC131::DoublyLinkedList
{
	/**
	 * Implement our DoublyLinkedList class !
	 */
	template <class T>
	class DoublyLinkedList
	{
		public:
			
			/**
			 * Node class, representing a single item in our linked list
			 */
			// TODO: Complete all class methods
			class Node
			{
				public:
					
					/// CTORS
					/// Member initialization lists?
					Node() { 
						prev_ = nullptr; 
						next_ = nullptr;
					}

					Node(T element) { 
						prev_ = nullptr; 
						next_ = nullptr; 
						element_ = element;
					}

					Node(T element, Node* prev, Node* next) {
						prev_ = prev; 
						next_ = next; 
						element_ = element;
					}
					
					/// Set the pointer to the previous element
					void setPrevious(Node* prev) {
						prev_ = prev;
					}
					
					/// Set the pointer to the previous element
					void setPrev(Node* prev) {
						prev_ = prev;
					}
					
					/// Get a pointer to the previous element
					Node* getPrevious() {
						return prev_;
					}
					
					/// Get a pointer to the previous element
					Node* getPrev() {
						return prev_;
					}
					
					/// Set the pointer to the next node
					void setNext(Node* next) {
						next_ = next;
					}
					
					/// Get a pointer to the next node
					Node* getNext() {
						return next_;
					}
					
					/// Set the element this node holds
					void setElement(T element) {
						element_ = element;
					}
					
					/// Get the element this node holds
					///	YOUR WELCOME
					T& getElement() { return this->element_; }
					
					/// Return a reference to the element
					///	YOUR WELCOME
					T& operator*() { return this->element_; }
					
				private:
					T element_;
					Node* prev_;
					Node* next_;
			};
			
			/**
			 * Nested Iterator class.
			 * This allows user code to refer to the Iterator's type as:
			 * 
			 * CPSC131::DoublyLinkedList::DoublyLinkedList<int>::Iterator
			 * 
			 * (as opposed to specifying the template argument two times)
			 */
			class Iterator
			{
				public:
					
					///	Constructor that does nothing; YOUR WELCOME
					Iterator()
					{
						/// yw
					}
					
					///	Constructor taking a head and tail pointer; YOUR WELCOME
					Iterator(Node* head, Node* tail) : head_(head), tail_(tail)
					{
						this->cursor_ = this->end();	/// yw
					}
					
					///	Constructor taking a head, tail, and cursor pointer; YOUR WELCOME
					Iterator(Node* head, Node* tail, Node* cursor) : head_(head), tail_(tail), cursor_(cursor) {}
					
					///	Get a pointer to the head node, or end() if this list is empty
					Node* begin()
					{
						return head_;
					}
					
					///	Get a node pointer representing "end" (aka "depleted"). Probably want to just use nullptr.
					Node* end()
					{
						return nullptr;
					}
					
					///	Get the node to which this iterator is currently pointing
					Node* getCursor()
					{
						return cursor_;
					}
					
					///	Return true if this iterator has hit its end; false otherwise
					/// YOUR WELCOME
					bool isAtEnd()
					{
						return this->cursor_ == nullptr;
					}
					
					/**
					 * Assignment operator
					 * Return a copy of this Iterator, after modification
					 */
					Iterator& operator=(const Iterator& other)
					{
						head_ = other.head_;
						tail_ = other.tail_;
						cursor_ = other.cursor_;
						return *this;
					}
					
					///	Comparison operator
					bool operator==(const Iterator& other)
					{
						return (cursor_ == other.cursor_);
					}
					///	Inequality comparison operator
					bool operator!=(const Iterator& other)
					{
						return (cursor_ != other.cursor_);
					}
					
					/**
					 * Addition operator
					 */
					Iterator operator +(size_t add)
					{
						Iterator iter = *this;
						for (size_t i = 0; i < add; i++){
							if (iter.cursor_ != nullptr){
								iter.cursor_ = iter.cursor_->getNext();
							}
						}
						return iter;
					}
					
					/**
					 * Subtraction operator
					 */
					Iterator operator -(size_t subtract)
					{
						Iterator iter = *this;
						for(size_t i = 0; i < subtract; i++){
							if (iter.cursor_ != nullptr){
								iter.cursor_ = iter.cursor_->getPrev();
							}
						}
						return iter;
					}
					
					/**
					 * Prefix increment operator
					 * Return a reference to this Iterator, after modification
					 */
					Iterator& operator++()
					{
						if(cursor_ != nullptr){
							cursor_ = cursor_->getNext();
						}
						return *this;
					}
					
					/**
					 * Postfix increment
					 * Return a copy of this Iterator, BEFORE it was modified
					 */
					Iterator operator++(int)
					{
						Iterator iter = *this;
						if(cursor_ != nullptr){
							cursor_ = cursor_->getNext();
						}
						return iter;
					}
					
					/**
					 * Prefix decrement operator
					 * Return a reference to this Iterator, after modification
					 */
					Iterator& operator--()
					{
						if(cursor_ != nullptr){
							cursor_ = cursor_->getPrev();
						} else{
							cursor_ = tail_;
						}
						return *this;
					}
					
					/**
					 * Postfix decrement operator
					 * Return a copy of this Iterator BEFORE it was modified
					 */
					Iterator operator--(int)
					{
						Iterator iter = *this;
						if (cursor_ != nullptr){
							cursor_ = cursor_->getPrev();
						} else {
							cursor_ = tail_;
						}
						return iter;
					}
					
					/**
					 * AdditionAssignment operator
					 * Return a copy of the current iterator, after modification
					*/
					Iterator operator +=(size_t add)
					{
						*this = *this + add;
						return *this;
					}
					/**
					 * SubtractionAssignment operator
					 * Return a copy of the current iterator, after modification
					 */
					Iterator operator -=(size_t sub)
					{
						*this = *this - sub;
						return *this;
					}
					
					/**
					 * AdditionAssignment operator, supporting positive or negative ints
					 */
					Iterator operator +=(int add)
					{
						if (add >= 0){
							*this += size_t(add);
						} else {
							*this -= size_t(-add);

						}
						return *this;
					}
					
					/**
					 * SubtractionAssignment operator, supporting positive or negative ints
					 */
					Iterator operator -=(int subtract)
					{
						if (subtract >= 0){
							*this -= size_t(subtract);
						} else {
							*this -= size_t(-subtract);

						}
						return *this;
					}
					
					/**
					 * Dereference operator returns a reference to the ELEMENT contained with the current node
					 */
					T& operator*()
					{
					    if (cursor_ == nullptr){
							throw std::out_of_range("Iterator can't be derefrenced");
					    }
					    return cursor_->getElement();
					}
				
				private:
					
					/// Pointer to the head node
					Node* head_ = nullptr;
					
					/// Pointer to the tail node
					Node* tail_ = nullptr;
					
					/**
					 * Pointer to the cursor node.
					 */
					Node* cursor_ = nullptr;
				
				friend class DoublyLinkedList;
			};
			
			/// Default constructor
			DoublyLinkedList()
			{
				head_ = nullptr;
				tail_ = nullptr;
				size_ = 0;
			}
			
			///	Copy Constructor
			DoublyLinkedList(const DoublyLinkedList& other)
			{
				*this = other;
			}
			
			/// DTOR
			~DoublyLinkedList()
			{
				clear();
			}
			
			/**
			 * Clear the list and assign the same value, count times.
			 * 
			 * Example:
			 *   T is an int
			 *   count is 5
			 *   value = 3
			 * 
			 * Our list would become:
			 *   {3, 3, 3, 3, 3}
			 */
			void assign(size_t count, const T& value)
			{
				clear();
				for(size_t i = 0; i < count; i++){
					push_back(value);
				}
			}
			
			/**
			 * Clear the list and assign values from another list.
			 * The 'first' iterator points to the first item copied from the other list.
			 * The 'last' iterator points to the last item copied from the other list.
			 * 
			 * Example:
			 * 	Suppose we have a source list like {8, 4, 3, 2, 7, 1}
			 * 	Suppose first points to the 4 node
			 *	Suppose last points to the 7 node
			 * 	We should end up with our list becoming: {4, 3, 2, 7}
			 *
			 * If the user code sends out-of-order iterators,
			 * 	just copy from 'first' to the end of the source list
			 * 
			 * Example:
			 *  If we have the same source list {8, 4, 3, 2, 7, 1},
			 *  and first points to the 7 node,
			 *  and last points to the 4 node,
			 *  we would end up with: {7, 1}
			 */
			void assign(Iterator first, Iterator last)
			{
				clear();
				if (first.getCursor() == nullptr) {
					return;
				}
				typename DoublyLinkedList<T>::Node*cursor1 = first.getCursor();
				typename DoublyLinkedList<T>::Node*cursor2 = last.getCursor();
				while (cursor1 != nullptr){
					push_back(cursor1->getElement());
					if(cursor1 == cursor2){
						break;
					}
					cursor1 = cursor1->getNext();
				}
			}
			
			/// Return a pointer to the head node, if any
			Node* head() const
			{
				return head_;
			}
			
			/// Return a pointer to the tail node, if any
			Node* tail() const
			{
				return tail_;
			}
			
			/**
			 * Return an iterator that points to the head of our list
			 */
			Iterator begin() const
			{
				return Iterator(head_, tail_, head_);
			}
			
			/**
			 * Return an iterator that points to the last element (tail) of our list
			 */
			Iterator last() const
			{
				return Iterator(head_, tail_, tail_);
			}
			
			/**
			 * Should return an iterator that represents being past the end of our nodes,
			 * or just that we are finished.
			 * 
			 * You can make this a nullptr or use some other scheme of your choosing,
			 * 	as long as it works with the logic of the rest of your implementations.
			 */
			Iterator end() const
			{
				return Iterator(head_, tail_, nullptr);
			}
			
			/**
			 * Returns true if our list is empty
			 */
			bool empty() const
			{
				return (size_ == 0);
			}
			
			/**
			 * Returns the current size of the list
			 * 
			 * Should finish in constant time!
			 * (keep track of the size elsewhere)
			 */
			size_t size() const
			{
				return size_;
			}
			
			/**
			 * Clears our entire list, making it empty
			 */
			void clear()
			{
				Node* cursor1 = head_;
				while(cursor1 != nullptr){
					Node* next = cursor1->getNext();
					delete cursor1;
					cursor1 = next;

				}
				head_ = nullptr;
				tail_ = nullptr;
				size_ = 0;
			}
			
			/**
			 * Insert an element after the node pointed to by the pos Iterator
			 * 
			 * If the list is currently empty,
			 * 	ignore the iterator and just make the new node at the head/tail (list of length 1).
			 * 
			 * If the incoming iterator is this->end(),
			 *   insert the element as the new tail
			 * 
			 * Should return an iterator that points to the newly added node
			 */
			Iterator insert_after(Iterator pos, const T& value)
			{
				if (empty() || pos.getCursor() == nullptr){
					return push_back(value);
				}
				Node* cursor1 = pos.getCursor();
				Node* cursor2 = cursor1->getNext();
				Node* n = new Node(value, cursor1, cursor2);
				cursor1->setNext(n);
				if (cursor2 != nullptr){
					cursor2->setPrev(n);
				} else{
					tail_ = n;
				}
				size_++;
				return Iterator(head_, tail_, n);
			}
			
			/**
			 * Insert a new element after the index pos.
			 * Should work with an empty list.
			 * 
			 * If the user attempts to insert to an index
			 * that is out of range (e.g., size=5 but index=13),
			 * just add to the end of the list.
			 * 
			 * Should return an iterator pointing to the newly created node
			*/
			Iterator insert_after(size_t pos, const T& value)
			{
				if (empty()){
					return push_back(value);
				}
				if (pos >= size_){
					return push_back(value);
				}
				Node* cursor1 = head_;
				for(size_t i = 0; i < pos; i++){
					cursor1 = cursor1->getNext();
				}
				return insert_after(Iterator(head_, tail_, cursor1), value);
			}
			
			/**
			 * Erase the node pointed to by the Iterator's cursor.
			 * 
			 * If the 'pos' iterator does not point to a valid node,
			 * 	throw an std::range_error
			 * 
			 * Return an iterator to the node AFTER the one we erased,
			 * 	or this->end() if we just erased the tail
			 */
			Iterator erase(Iterator pos)
			{
				Node* cursor1 = pos.getCursor();
				if (cursor1 == nullptr) {
					throw std::range_error("Invalid iterator");
				}
				Node* previous = cursor1->getPrev();
				Node* next = cursor1->getNext();
				if (previous) {
					previous->setNext(next);
				} else {
					head_ = next;
				}
				if (next) {
					next->setPrev(previous);
				} else {
					tail_ = previous;
				}
				delete cursor1;
				size_--;
				return Iterator(head_, tail_, next);
			}
			
			/**
			 * Add an element just after the one pointed to by the 'pos' iterator
			 * 
			 * Should return an iterator pointing to the newly created node
			 */
			Iterator push_after(Iterator pos, const T& value)
			{
				return insert_after(pos, value);
			}
			
			/**
			 * Add a new element to the front of our list.
			 */
			void push_front(const T& value)
			{
				Node* n = new Node(value, nullptr, head_);
				if (head_ != nullptr) {
					head_->setPrev(n);
				}
				head_ = n;
				if (tail_ == nullptr) {
					tail_ = n;
				}
				size_++;
			}
			
			/**
			 * Add an element to the end of this list.
			 * 
			 * Should return an iterator pointing to the newly created node.
			 */
			Iterator push_back(const T& value)
			{
				Node* n = new Node(value, tail_, nullptr);
				if (tail_ != nullptr) {
					tail_->setNext(n);
				}
				tail_ = n;
				if (head_ == nullptr) {
					head_ = n;
				}
				size_++;
				return Iterator(head_, tail_, n);
			}
			
			/**
			 * Remove the node at the front of our list
			 * 
			 * Should throw an exception if our list is empty
			 */
			void pop_front()
			{
				if (empty()) {
					throw std::range_error("List is empty");
				}
				Node* cursor1 = head_;
				Node* next = cursor1->getNext();
				delete cursor1;
				head_ = next;
				if (head_ != nullptr) {
					head_->setPrev(nullptr);
				} else {
					tail_ = nullptr;
				}
				size_--;
			}
			
			/**
			 * Remove the node at the end of our list
			 * 
			 * Should throw an exception if our list is empty
			 */
			void pop_back()
			{
				if (empty()){
					throw std::range_error("List empty");
				}
				Node* cursor1 = tail_;
				Node* previous = cursor1->getPrev();
				delete cursor1;
				tail_ = previous;
				if (tail_ != nullptr) {
					tail_->setNext(nullptr);
				} else {
					head_ = nullptr;
				}
				size_--;

			}
			
			/**
			 * Return a reference to the element at the front.
			 * 
			 * Throw an exception if the list is empty
			 */
			T& front()
			{
				if (empty()) {
					throw std::range_error("List is empty");
				}
				return head_->getElement();

			}
			
			/**
			 * Return a reference to the element at the back.
			 * 
			 * Throw an exception if the list is empty
			 */
			T& back()
			{
				if (empty()) {
					throw std::range_error("List is empty");
				}
				return tail_->getElement();

			}
			
			/**
			 * Return the element at an index
			 * 
			 * Should throw a range_error is out of bounds
			 */
			T& at(size_t index)
			{
			    if (index >= size_) {
					throw std::range_error("Index out of bounds");
				}
				Node* cursor1 = head_;
				for (size_t i = 0; i < index; i++) {
					cursor1 = cursor1->getNext();
				}
				return cursor1->getElement();

			}
			
			/**
			 * Reverse the current list
			 */
			void reverse()
			{
				Node* cursor1 = head_;
				Node* temp = nullptr;
				while (cursor1 != nullptr) {
					temp = cursor1->getPrev();
					cursor1->setPrev(cursor1->getNext());
					cursor1->setNext(temp);
					cursor1 = cursor1->getPrev();
				}
				temp = head_;
				head_ = tail_;
				tail_ = temp;
			}
			
			/**
			 * I bet you're happy I'm not making you do this.
			 * No tests will be run against this function,
			 * 	but feel free to try it out, as a challenge!
			 * 
			 * If I were doing this and didn't care too much for efficiency,
			 * 	I would probably create an extra helper function to swap two
			 * 	positions in the current list.
			 * Then I would simply sweep through the list and perform
			 *  the bubble-sort algorithm. Perhaps selection sort.
			 * 
			 * If you want a huge challenge, try implementing quicksort.
			 * 
			 * (but again, don't worry about this method; it will not be tested)
			 */
			void sort()
			{
				//	TODO: Your code here
			}
			
			/**
			 * Assignment operator
			 * 
			 * Clear this list and fill it with the others' values
			 * (by value, not by reference)
			 * 
			 * Return a reference to this list
			 */
			DoublyLinkedList<T>& operator =(const DoublyLinkedList<T>& other)
			{
				if (this == &other) return *this;
				clear();
				Node* cursor1 = other.head_;
				while (cursor1 != nullptr) {
					push_back(cursor1->getElement());
					cursor1 = cursor1->getNext();
				}
				return *this;

			}
			
			/**
			 * Return true if the lists are "equal"
			 * 
			 * "Equal" here is defined as:
			 * - Same size
			 * - Elements at the same indexes would return true for their own comparison operators
			 * 
			 * In other words: "They contain all the same values"
			 * (no need for their pointers or addresses to be the same)
			 */
			bool operator ==(DoublyLinkedList<T>& other)
			{
				if (size_ != other.size_) return false;
				Node* a = head_;
				Node* b = other.head_;
				while (a != nullptr && b != nullptr) {
					if (!(a->getElement() == b->getElement())) return false;
					a = a->getNext();
					b = b->getNext();
				}
				return true;
			}
			
			/**
			 * Return true if the lists are "not equal"
			 * 
			 * See the operator== stub for definition of "equal"
			 */
			bool operator !=(DoublyLinkedList<T>& other)
			{
				return !(*this == other);
			}
			
		private:
			
			Node* head_ = nullptr;
			Node* tail_ = nullptr;
			size_t size_ = 0;
	};
}

#endif
