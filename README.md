#### Generic Data Structures in C
Implementation of some data structures in pure C, with no objects.  

Starting from those explained in the awesome Stanford Course "Paradigms of Programming", and continued with other I have needed in my job, studied in other 
courses, books, etc.

* Stack:  implemented like java array list (resizable array).
* Queue:  idem.
* List:   deprecated.
* Vector: like a java array list.
* Linked List:  to store any kind of data or struct in the same list (like python lists).
* HashSet: implemented using vector structure.
* HashMap: open addresing with double hash. Based on https://github.com/jamesroutley/write-a-hash-table and Introduction to Algorithms. Working nicely with char* -> char* and char* -> struct. It would be easy to use different types for keys using unions, but everything can be reduced to strings, so I decided not to give the possibility to use anything different.

