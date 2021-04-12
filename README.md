# Hash_Table with optimization
In this project I have made a hash table for english to russian vocabulary. 
There are two steps of this project: 
1) Create Hash Table for fast word finding
2) Optimize code with using assembler code 

## Creating hash table

First of all we should choose which type of hash table we would write. For this task I have chosen Separate chaining with linked lists because of easier choose of hash functions, but it is also perfect to use open addressing because our hash table is concieved with constant size.

So, the  simplified structure of our project will look in this way:

![схема](https://github.com/Krym4s/Hash_table/blob/main/hash_table/%D1%81%D1%85%D0%B5%D0%BC%D0%B01.jpg "схема")

### Choosing function

To write a good hash table I have to write good hash function. This function should have 2 main options
- It shouldn't have much collisions.
- It should work fast.
- Oh, I'm sorry, in previous two ppoints there must be must, not should.

There are some naive ideas of hash functions that I've checked and compaired them with better hashes.
To see 

1. Н = 1
![1](https://github.com/Krym4s/Hash_table/blob/main/1Pic "1")
2. H = strlen (str)
![2](https://github.com/Krym4s/Hash_table/blob/main/hash_table/lenPic "2")
3. H = sum of letters
![3](https://github.com/Krym4s/Hash_table/blob/main/hash_table/sumPic "3")
4. H = sum of letters devide strlen
![4](https://github.com/Krym4s/Hash_table/blob/main/hash_table/averageLenPic "4")
5. H = str[0]
![5](https://github.com/Krym4s/Hash_table/blob/main/hash_table/dedPic "5") 
6. Ror
![6](https://github.com/Krym4s/Hash_table/blob/main/hash_table/RorPic "6") 
7. Rol
![7](https://github.com/Krym4s/Hash_table/blob/main/hash_table/RolPic "7")
8. Murmur
![8](https://github.com/Krym4s/Hash_table/blob/main/hash_table/murmurPic "8")
9. CRC
![9](https://github.com/Krym4s/Hash_table/blob/main/hash_table/CRCPic"9")

As pictures says the most effective are murmur and crc they have less colisiions than other hash functions, so we would use them.
