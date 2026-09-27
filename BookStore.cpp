
#include "BookStore.hpp"


//
#include <iostream>
#include <sstream>
#include <string>


//
using std::cout, std::cin, std::endl;
using std::string, std::to_string;
using std::stringstream;


//
namespace CPSC131::BookStore
{

	BookStore::BookStore() {}
	
	///	Copy CTOR
	BookStore::BookStore(const BookStore& other)
	{
		book_list_ = other.book_list_;
		account_balance_ = other.account_balance_;
	}
	
	/**
	 * Adjust the store's account balance
	 * Should accept positive or negative adjustments
	 */
	void BookStore::adjustAccountBalance(int adjustment)
	{
		account_balance_ += adjustment;
	}
	
	/**
	 * Return the store's current account balance
	 */
	int BookStore::getAccountBalance() const
	{
		return account_balance_;
	}
	
	/**
	 * Find a book by its ISBN
	 * 
	 * Return this->book_list_.end() if the book isn't found.
	 * 
	 * Return an interator pointing to the Book if it is found.
	 */
	DoublyLinkedList::DoublyLinkedList<Book>::Iterator BookStore::findBook(std::string isbn) const
	{
		for (auto iterate = book_list_.begin(); iterate != book_list_.end(); iterate++){
            if ((*iterate).getIsbn() == isbn)
                return iterate;
        }
        return book_list_.end();

	}
	
	/**
	 * Check whether a book exists, by its ISBN
	 * 
	 * Return true if it exists, or false otherwise
	 */
	bool BookStore::bookExists(std::string isbn) const
	{
		return findBook(isbn) != book_list_.end();
	}
	
	/**
	 * Check the quantity of stock we have for a particular book, by ISBN
	 * 
	 * If the book doesn't exist, just return 0
	 */
	size_t BookStore::getBookStockAvailable(std::string isbn) const
	{
		auto iterate = findBook(isbn);
        if (iterate != book_list_.end())
            return (*iterate).getStockAvailable();
        return 0;
	}
	
	/**
	 * Locate a book by ISBN and return a reference to the Book
	 * 
	 * If the book doesn't exist, throw an exception
	 */
	Book& BookStore::getBook(std::string isbn) const
	{
		auto iterate = findBook(isbn);
        if (iterate == book_list_.end()){
            throw std::range_error("Book cannot be found");
		}
        return *iterate;


	}
	
	/**
	 * Take a Book instance and add it to inventory
	 * 
	 * If the book's ISBN already exists in our store,
	 * 	simply adjust account balance by the book's price and quantity,
	 * 	but ignore other details like title and author.
	 * 
	 * If the book's ISBN doesn't already exist in our store,
	 * 	adjust our account balance and push the book into our list
	 */
	void BookStore::purchaseInventory(const Book& book)
	{
		auto iterate = findBook(book.getIsbn());
        int total_cost = static_cast<int>(book.getPriceCents() * book.getStockAvailable());
        adjustAccountBalance(-total_cost);

        if (iterate != book_list_.end())
        {
            (*iterate).adjustStockAvailable(static_cast<int>(book.getStockAvailable()));
        }
        else
        {
            book_list_.push_back(book);
        }
	}
	
	/**
	 * Take some book details and add the book to our inventory.
	 * 
	 * Use the same rules as the other overload for this function.
	 * 
	 * You might want to avoid repeating code by simply building a Book
	 * 	object from the details, then calling the other overload
	 * 	with the new Book object.
	 */
	void BookStore::purchaseInventory(
		std::string title, std::string author, std::string isbn,
		size_t price_cents,
		size_t unit_count
	)
	{
		Book book_ (title, author, isbn, price_cents, unit_count);
        purchaseInventory(book_);
	}
	
	/**
	 * Print out inventory.

	 */
	void BookStore::printInventory() const
	{
		cout << "*** Book Store Inventory ***" << endl;
        for (auto iterate = book_list_.begin(); iterate != book_list_.end(); iterate++)
        {
            cout << "\"" << (*iterate).getTitle() << "\", by " << (*iterate).getAuthor() << " [" << (*iterate).getIsbn() << "] (" << (*iterate).getStockAvailable() << " in stock)" << endl;
        }
	}
	
	/**
	 * Sell a book to a customer!
	 * 
	 * Takes the ISBN of the book, the selling price of the book, and the quantity of books sold
	 * 
	 * Uses the same rules as the other overload.
	 * 
	 * You may wish to just grab a reference to the book and call the other overload,
	 * 	to avoid repeating code
	 */
	void BookStore::sellToCustomer(std::string isbn, size_t price_cents, size_t quantity)
	{
		Book& book = getBook(isbn);
        sellToCustomer(book, price_cents, quantity);
	
	}
	
	/**
	 * Sell a book to a customer!

	 */
	void BookStore::sellToCustomer(Book& book, size_t price_cents, size_t quantity)
	{
		if (book.getStockAvailable() < quantity){
            throw InsufficientInventory("Not enough stock available");
		}
		book.adjustStockAvailable(-static_cast<int>(quantity));
        adjustAccountBalance(static_cast<int>(price_cents * quantity));
	}
}







