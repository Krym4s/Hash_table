all: hash_table

hash_table: main.o IsE_LinesF.o IsE_Vocabulary.o List_Pointer.o IsE_Hash_Table.o laba1.o IsE_strcmp.o
	g++ -no-pie -o hash_table main.o IsE_LinesF.o IsE_Vocabulary.o List_Pointer.o IsE_Hash_Table.o laba1.o IsE_strcmp.o 

main.o: main.cpp
	g++ -g -c -O3 main.cpp

IsE_Vocabulary.o: IsE_Vocabulary.cpp
	g++ -g -c -O3 -msse4.2 IsE_Vocabulary.cpp

IsE_LinesF.o: IsE_LinesF.cpp
	g++ -g -c -O3 -msse4.2 IsE_LinesF.cpp

List_Pointer.o: List_Pointer.cpp
	g++ -g -c -O3 -msse4.2 List_Pointer.cpp

IsE_Hash_Table.o: IsE_Hash_Table.cpp
	g++ -g -c -O3 -msse4.2 IsE_Hash_Table.cpp

laba1.o: laba1.cpp
	g++ -g -c -O3 -msse4.2 laba1.cpp

IsE_strcmp.o:
	nasm -f elf64 IsE_strcmp.asm

clean:
	rm *.o 