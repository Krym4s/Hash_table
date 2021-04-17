# Hash_Table with optimization
In this project I have made a hash table which can be used to translate word from English into Russian language. 
There are two steps of this project: 
1) Create Hash Table for fast word finding and translation into Russian language
2) Optimize code using assembler and other methods

## Creating hash table

First of all, we should choose which type of hash table we would implement. For this task I have chosen Separate chaining with linked lists because ease choice of hash functions, but it is also perfect to use open addressing because our hash table is concieved with constant size.

So, the  simplified structure of our project will look in this way:
Words are contained in char buffer and are reffered with array of pairs (key - value, english word - russian translation). Our hash Table contains buffer of Lists, which refers to pairs, each List have pairs with same hashsum of key word.   

![scheme](https://github.com/Krym4s/Hash_table/blob/main/hash_table/%D1%81%D1%85%D0%B5%D0%BC%D0%B01.jpg "схема")

### Choosing function

To implement a good hash table I have to implement good hash function. This function should have 2 main options
- It shouldn't have much collisions.
- It should work fast.
- Oh, I'm sorry, in previous two points there must be must, not should.

There are some ideas of hash functions that I've checked to see it\`s  and compaired them with better hashes.
To see colisions in more obvious way we should diminish size of hash table to make number of member in each list bigger. 

1. Н = 1 (dispersion: 0.9995)
<img align="center"  src="https://github.com/Krym4s/Hash_table/blob/main/1Pic">


2. H = sum of letters (dispersion: 0.285472)
<img align="center"  src="https://github.com/Krym4s/Hash_table/blob/main/hash_table/lenPic">


3. H = strlen (str) (dispersion: 0.0238834)
<img align="center"  src="https://github.com/Krym4s/Hash_table/blob/main/1Pic">


4. H = sum of letters devide strlen (dispersion: 0.252645)
<img align="center"  src="https://github.com/Krym4s/Hash_table/blob/main/hash_table/averageLenPic">


5. H = str[0] (dispersion: 0.264585)
<img align="center"  src="https://github.com/Krym4s/Hash_table/blob/main/hash_table/dedPic">


6. Ror (dispersion: 0.00747365)
<img align="center"  src="https://github.com/Krym4s/Hash_table/blob/main/hash_table/RorPic">


7. Rol (dispersion: 0.0214088)
<img align="center"  src="https://github.com/Krym4s/Hash_table/blob/main/hash_table/RolPic">


8. Murmur (dispersion: 0.00444014)
<img align="center"  src="https://github.com/Krym4s/Hash_table/blob/main/hash_table/murmurPic">


9. CRC (dispersion: 0.00445683)
<img align="center"  src="https://github.com/Krym4s/Hash_table/blob/main/hash_table/CRCPic">

As pictures and dispersions say the most effective are murmur and crc they have less colisiions than other hash functions, so we would use them. I have chosen CRC. I will explain further, why I have done so.

## Optimise our hash table

To optimise our hash table we should get rid of our old slow code and replace it with assembler. Also we should set normal size for our hash table (we have about 50000 words, so the size of our table should be about 30000). As we want to optimise our code to release it, we should run our programm with -O3 flag. Also, to see weak places of our programm we should make a stress test for it. As our hash table is created to FIND words we should run finding function many times. In my case I look for every word of vocabulary 100 times (5 000 000 finds at all).

### First step: rewrite crc
We should watch on the percent of time that each function works. 
<img align="center"  src="https://github.com/Krym4s/Hash_table/blob/main/hash_table/1.jpg">

As we see crc hash occupies about 93 percents of runtime.

First of all, there is intrinsic function that count crc hash, so we can use it.

This is the first version of crc hash: 

``` 
    const unsigned int tableSize = 256;
    const unsigned int mask = 0x6C40DF5F0B497347; 
    unsigned int table [tableSize];
    unsigned int hash  = 0;

    for (int i = 0; i < tableSize; i++)
    {
        hash = i;
        for (int j = 0; j < 8; j++)
            hash = hash & 1 ? (hash >> 1) ^ mask : hash >>  1;

        table[i] = hash;
    }

    hash = 0xFFFFFFFFUL;

    int strLen = strlen (value);
    for (int symbN = 0; symbN < strLen; symbN++)
    {
        hash = table [(hash ^ *(value + symbN)) & 0xFF] ^ (hash >> 8);
    }
    
    return hash;

```
Here is rewritten version of crc hash using intrinsics:
```
    unsigned int hash = 0;
    unsigned int len  = strlen (value);
    unsigned char* str = (unsigned char*) value;
    for (unsigned int i = 0; i < len ; i ++)
        hash = _mm_crc32_u8 (hash, *(str + i));
        
    return hash;
```
Avarage runtime without optimization is 2.503 seconds. Avavrage runtime with optimisation is 0.508 seconds, so gain in speed is 393 percents. 

### Second step 


