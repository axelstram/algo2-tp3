all: driver.o arbolCat.o LinkLinkIt.o tp3.o tp3
##testsdicc: testsdicc.o
##	g++ testsdicc.o -o testsdicc
	
##testsdicc.o: Tests_diccTrie.cpp
##	g++ -c Tests_diccTrie.cpp -o testsdicc.o

tp3: tp3.o
	g++ tp3.o driver.o arbolCat.o LinkLinkIt.o -o tp3
	
tp3.o: tp3.cpp
	g++ tp3.cpp -c -g -o tp3.o

driver.o: Driver.cpp
	g++ -c -g Driver.cpp -o driver.o

arbolCat.o: arbolCat.cpp
	g++ -c -g arbolCat.cpp -o arbolCat.o

LinkLinkIt.o: LinkLinkIt.cpp
	g++ -c -g LinkLinkIt.cpp -o LinkLinkIt.o

clean:
	rm *.o

