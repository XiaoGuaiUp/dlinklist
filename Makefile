dlinklist:dlinklist.c
	gcc -g -o $@ $^

.PHONY:clean
	clean:rm -f dlinklist
