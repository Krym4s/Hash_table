//#include "IsE_List.hpp"
//#include "IsE_LinesF.h"
#include "IsE_Vocabulary.hpp"
#include "IsE_Hash_Table.hpp"
#include "IsE_Pair.hpp"
//#include "IsE_PairF.hpp"
#include "IsE_LinesF.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "laba1.hpp"



int main()
{
    setlocale (LC_ALL, "rus");
    //system ("gnuplot");

    
    //unsigned int maxwordLen = 0;
    IsE_Vocabulary vocabulary ("ENRUS.txt");

    /*   
    for (int i = 0; i < vocabulary.getSize(); i++)
    {
        unsigned int len = strlen(vocabulary.getPair(i).first);
        if (maxwordLen < len)
            maxwordLen = len;
        if (len > 32)
        printf ("%s\n", vocabulary.getPair(i).first);
    }
    printf ("max len : %d\n", maxwordLen);
    */
    /*
    CreateNewAnaliticPicture ({1000, "logs", "1Dat", "1Pic",                   hash1},      vocabulary);
    CreateNewAnaliticPicture ({1000, "logs", "lenDat", "lenPic",               hash2},      vocabulary);
    CreateNewAnaliticPicture ({1000, "logs", "sumDat", "sumPic",               hash3},      vocabulary);
    CreateNewAnaliticPicture ({1000, "logs", "averageLenDat", "averageLenPic", hash4},      vocabulary);
    CreateNewAnaliticPicture ({1000, "logs", "dedDat", "dedPic",               hash5},      vocabulary);
    CreateNewAnaliticPicture ({1000, "logs", "RorDat", "RorPic",               hashRor},    vocabulary);
    CreateNewAnaliticPicture ({1000, "logs", "RolDat", "RolPic",               hashRol},    vocabulary);
    CreateNewAnaliticPicture ({1000, "logs", "CRCDat", "CRCPic",               hashCRC},    vocabulary);
    CreateNewAnaliticPicture ({1000, "logs", "MurmurDat", "MurmurPic",         hashMurMur}, vocabulary);
    */
    

   //--------------------------------------------------------------------------------
    
    IsE_Hash_Table table (30000, hashCRC, "logs.txt");

    unsigned int vocSize = vocabulary.getSize();
    
    //table.InsertToHashTable (vocabulary.getPair(0));
    for (unsigned int i = 0; i < vocSize; i++) //
        table.InsertToHashTable (vocabulary.getPair(i));


    for (int j = 0; j < 100; j++)
        for (unsigned int i = 0; i < vocSize; i++)
            table.FindElement(vocabulary.getPair(i).first);

    printf ("%s\n", table.FindElement ("rat"));
    
    
    return 0;
}

