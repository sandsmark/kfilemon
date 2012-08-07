ALL: libkfilemon.so kfilemond

libkfilemon.so: libkfilemon.c config.h
	gcc -c -fPIC libkfilemon.c -D_GNU_SOURCE -Wall
	gcc -shared -fPIC -o libkfilemon.so libkfilemon.o -ldl -Wall

kfilemond: kfilemond.cpp config.h
	g++ -g kfilemond.cpp -o kfilemond -lQtCore

clean:
	rm -f kfilemond libkfilemon.so libkfilemon.o

