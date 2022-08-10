all : exec

exec : Bin/main.o Bin/key.o Bin/signature.o Bin/src.o Bin/Protected.o Bin/cellKey.o Bin/cellProtected.o Bin/hashtab.o Bin/Block.o  Bin/CellTree.o Bin/Votes.o
	gcc -g -Wall -o exec Bin/*.o -lm -lssl -lcrypto
	
	
Bin/main.o : Lib/main.c 
	gcc -g -o Bin/main.o -c Lib/main.c

Bin/hashtab.o : Lib/hashtab.c
	gcc -g -o Bin/hashtab.o -c Lib/hashtab.c

Bin/src.o : Lib/src.c
	gcc -g -o Bin/src.o -c Lib/src.c
		
Bin/key.o : Lib/key.c
	gcc -g -o Bin/key.o -c Lib/key.c
	
Bin/signature.o : Lib/signature.c
	gcc -g -o Bin/signature.o -c Lib/signature.c
	
	
Bin/Protected.o : Lib/Protected.c
	gcc -g -o Bin/Protected.o -c Lib/Protected.c
	
Bin/cellKey.o : Lib/cellKey.c
	gcc -g -o Bin/cellKey.o -c Lib/cellKey.c

Bin/cellProtected.o : Lib/cellProtected.c 
	gcc -g -o Bin/cellProtected.o -c Lib/cellProtected.c

Bin/Block.o : Lib/Block.c 
	gcc -g -o Bin/Block.o -c Lib/Block.c

Bin/CellTree.o : Lib/CellTree.c
	gcc -g -o Bin/CellTree.o -c Lib/CellTree.c

Bin/Votes.o : Lib/Votes.c
	gcc -g -o Bin/Votes.o -c Lib/Votes.c
	
clean :
	rm Bin/*.o
	rm exec
	



