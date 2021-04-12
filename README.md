# Hash_Table with optimization
In this project I have made a hash table for english to russian vocabulary. 
There are two steps of this project: 
1) Create Hash Table for fast word finding
2) Optimize code with using assembler code 

## Creating hash table

First of all we should choose which type of hash table we would write. For this task I have chosen Separate chaining with linked lists because of easier choose of hash functions, but it is also perfect to use open addressing because our hash table is concieved with constant size.

So, the  simplified structure of our project will look in this way:

![текст](https://github.com/Krym4s/Hash_table/blob/main/hash_table/%D1%81%D1%85%D0%B5%D0%BC%D0%B01.jpg "схема")

###Choosing function

To write a good hash table I have to write good hash function. This function should have 2 main options
- It shouldn't have much collisions.
- It should work fast.
- Oh, I'm sorry, in previous two ppoints there must be must, not should.

There are some naive ideas of hash functions that I've checked and compaired them with better hashes.

1. 
