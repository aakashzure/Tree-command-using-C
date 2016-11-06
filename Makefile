project: tree.o
	cc tree.o -o project

tree.o: tree.c
	cc -c tree.c
