hello_exe : hello.o
	gcc -o hello_exe hello.o  
hello.o : hello.c
	gcc -c -o hello.o hello.c
clean : 
	rm *.o hello_exe
	
