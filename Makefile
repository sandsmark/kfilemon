ALL: libkfilemon.so kfilemond

libkfilemon.so: libkfilemon.c
	gcc -c -fPIC libkfilemon.c -D_GNU_SOURCE -Wall
	gcc -shared -fPIC -o libkfilemon.so libkfilemon.o -ldl -Wall

kfilemond: kfilemond.cpp
	g++ kfilemond.cpp -o kfilemond -lQtCore

