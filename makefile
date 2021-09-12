main.exe: main.o dynarray.o
    gcc -o main.exe dynarray.o main.o
dynarray.o: dynarray.c dynarray.h
    gcc -c dynarray.c
main.o: main.c dynarray.h
    gcc -c main.c
