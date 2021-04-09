all: hash_table

hash_table: main.o IsE_LinesF.o IsE_Vocabulary.o List_Pointer.o IsE_Hash_Table.o laba1.o
	g++ main.o IsE_LinesF.o IsE_Vocabulary.o List_Pointer.o IsE_Hash_Table.o laba1.o -o hash_table

main.o: main.cpp
	g++ -g -c -O3 main.cpp

IsE_Vocabulary.o: IsE_Vocabulary.cpp
	g++ -g -c -O3 IsE_Vocabulary.cpp

IsE_LinesF.o: IsE_LinesF.cpp
	g++ -g -c -O3 IsE_LinesF.cpp

List_Pointer.o: List_Pointer.cpp
	g++ -g -c -O3 List_Pointer.cpp

IsE_Hash_Table.o: IsE_Hash_Table.cpp
	g++ -g -c -O3 IsE_Hash_Table.cpp

laba1.o: laba1.cpp
	g++ -g -c -O3 laba1.cpp

clean:
	rm -rf *.o Kalash