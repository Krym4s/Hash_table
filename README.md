# Hash_Table with optimization
In this project I have made a hash table which can be used to translate word from English into Russian language. 
There are two steps of this project: 
1) Create Hash Table for fast word finding and translation into Russian language
2) Optimize code using assembler and other methods

## Creating hash table

First of all, we should choose which type of hash table we would implement. For this task I have chosen Separate chaining with linked lists because ease choice of hash functions, but it is also perfect to use open addressing because our hash table is concieved with constant size.

So, the  simplified structure of our project will look in this way:
Words are contained in char buffer and are reffered with array of pairs (key - value, english word - russian translation). Our hash Table contains buffer of Lists, which refers to pairs, each List have pairs with same hashsum of key word.   

![scheme](https://github.com/Krym4s/Hash_table/blob/main/hash_table/%D0%BA%D1%83%D0%BB%D0%B0%D0%BA.png "схема")

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
<img align="center"  src="https://github.com/Krym4s/Hash_table/blob/main/hash_table/sumPic">


3. H = strlen (str) (dispersion: 0.0238834)
<img align="center"  src="https://github.com/Krym4s/Hash_table/blob/main/hash_table/lenPic">


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
<img align="center"  src="https://github.com/Krym4s/Hash_table/blob/main/hash_table/zero-opt.png">

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
Let us see situation after first optimization
<img align="center"  src="https://github.com/Krym4s/Hash_table/blob/main/hash_table/first-opt.png">

As we can see our next problem function is \_\_strcmp\_avx2 . It takes much more time because size of string is unknown. Having analised our key-words I could say that it's length less than 32 characters (max length is 30 characters). It means that we can use ymm registers to compare our strings as \_\_strcmp\_avx2 does, but we need only one iteration of comparing. It means that we can exclude counting number of 32 byte blocks in our programm.

I will not show you the original code of \_\_strcmp\_avx2 as you can find it in standart library. 

My IsE_strcmp needs third argument (length of string)

First attemp of rewriting:
```
global IsE_strcmp

IsE_strcmp:
vxorps ymm0, ymm0
vxorps ymm1, ymm1

vmovups ymm0, [rsi]
vmovups ymm1, [rdi]

vpcmpeqb ymm0, ymm1
xor rcx, rcx
vpmovmskb ecx, ymm0

not ecx
tzcnt ecx, ecx

xor rax, rax
test rcx, rdx

jae Equal

add rax, 1

Equal:
ret
```
It was even slower than standart strcmp because of unnecessary xors and assignments. Avarage runtime without optimization is 0.508 seconds. Avavrage runtime with optimisation is 0.632 seconds, so gain in speed is -19.6 percents.

After some corrections:
```
IsE_strcmp:

vmovups ymm0, [rsi]

vpcmpeqb ymm0, [rdi]
vpmovmskb ecx, ymm0

not ecx
tzcnt ecx, ecx

xor rax, rax
test rcx, rdx

jae Equal

add rax, 1

Equal:
ret
```

Avarage runtime without optimization is 0.508 seconds. Avavrage runtime with optimisation is 0.465 seconds, so gain in speed is 9.2 percents.

### Less length less time

<img align="center"  src="https://github.com/Krym4s/Hash_table/blob/main/hash_table/second-opt.png">

As we estimated length of words in our vocabulary we can omit calculatung length of strings in hash function. So, if all bytes after word in 32 bytes was zero there would be no negative effect on finding words. So we can use crc not only with 8 characters but also with 64 bytes.

First of all we should prepare 32 byte buffer for our key words:

```
        vocabulary[i].first  = (char*) calloc (32, sizeof(char));
        
        for (int j = 0; j < (lines.lines + 2 * i)->length; j++)
        {
            vocabulary[i].first[j] = (lines.lines + 2 * i)->line[j];
        }
```

After that we can improve our crc function:

```
    unsigned int hash = 0;
    for (int i = 0; i < 4; i++)
        hash = _mm_crc32_u64 (hash, *(value + i));
    return hash;

```

Avarage runtime without optimization is 0.366 seconds. Avavrage runtime with optimisation is 0.161 seconds, so gain in speed is 126 percents.

## Estimating results
After three optimisations we can see that only four functions can be optimised because other function's impact is less than 1 percent.

<img align="center"  src="https://github.com/Krym4s/Hash_table/blob/main/hash_table/second-opt.png">

Find_element: 
```
    unsigned int index = CountHash (key);
    ListMember* answer = FindValue(vocabulary + (index % size), key);
    if (!answer)
    return nullptr;

    return answer->value.second;
```
Find_value:
```
    int len = strlen (value);
    ListMember* index = thou->first;
    while (index)
    {
        int val = IsE_strcmp (value, index->value.first, len);
        if (!val)
            return index;

        index = index->next;
    }
    return NULL;
```
These two functions mostly call other functions, so they can't be optimised. 
getPair is simple getter so it is also can not be optimised.

Main function is not related to hash table, so it is not important to optimise it.

So, I think that it is time we stopped optimisation to save multiplatform.  

In the end we have got 437 percent optimization.

 
