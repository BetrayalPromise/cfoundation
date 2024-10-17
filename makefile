build0:
	@clang -g main.c array.c cstring.c testcstring.c -o /Users/user0/Desktop/Projects/C/8/a.out

build1:
	@clang -E main.c -o main.i
	@clang -E cstring.c -o cstring.i
	@clang -E testcstring.c -o test.i

build2:
	@clang -S main.c -o main.s
	@clang -S cstring.c -o cstring.s
	@clang -S testcstring.c -o testcstring.s

clean:
	@rm *.i a.out *.s
	rm -fr a.out.dSYM