# Book Store (DLL + Adapter)

A book store inventory system I built using a doubly linked list under the hood, wrapped with an adapter class so the rest of the program doesn't have to deal with the DLL directly.

## What it does

- Stores and manages a collection of books using a custom doubly linked list
- `BookStore` class acts as an adapter — gives a clean interface for adding, removing, and searching books without exposing the linked list internals
- Handles book data (title, author, etc. — via the `Book` class)

## What I got out of it

- Adapter design pattern — wrapping a lower-level data structure with a cleaner interface
- Doubly linked lists from scratch (insert, remove, traverse both directions)
- Splitting responsibilities across classes instead of shoving everything into one file

## Run it

```bash
make
./main
```

## Notes

Built this for CPSC 131 (Data Structures) at CSUF.
