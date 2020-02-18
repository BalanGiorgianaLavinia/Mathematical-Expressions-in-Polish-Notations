build:	
	gcc main.c functii.c -o tema3 -Wall -Wno-missing-braces -lm

clean:	
	rm tema3

run:	
	./tema3 ./in/test0.in ./out.txt