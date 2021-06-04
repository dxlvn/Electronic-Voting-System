exe: AAA
	./AAA
	
AAA: AAA.o encryption.o
	g++ -o AAA AAA.o encryption.o -lgmp -g -Wall

AAA.o: AAA.cc encryption.h
	g++ -g -Wall -c AAA.cc -lgmp

KEYGEN: KEYGEN.o encryption.o
	g++ -o KEYGEN KEYGEN.o encryption.o -lgmp -g -Wall

KEYGEN.o: KEYGEN.cc encryption.h
	g++ -g -Wall -c KEYGEN.cc -lgmp

ENCRYPT: ENCRYPT.o encryption.o
	g++ -o ENCRYPT ENCRYPT.o encryption.o -lgmp -g -Wall

ENCRYPT.o: ENCRYPT.cc encryption.h
	g++ -g -Wall -c ENCRYPT.cc -lgmp

DECRYPT: DECRYPT.o encryption.o
	g++ -o DECRYPT DECRYPT.o encryption.o -lgmp -g -Wall

DECRYPT.o: DECRYPT.cc encryption.h
	g++ -g -Wall -c DECRYPT.cc -lgmp

encryption.o : encryption.cc encryption.h
	g++ -g -Wall -c encryption.cc -lgmp

clean:
	rm -f ∗.o

mrproper: clean
	rm -f AAA ENCRYPT DECRYPT KEYGEN