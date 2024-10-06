build0:
	@clang -g main.c array.c cchars.c cstring.c -o /Users/user0/Desktop/Projects/C/8/a.out
	@./a.out

build1:
	@clang -E main.c -o main.i

build2:
	@clang -S main.c -o main.s

clean:
	@rm *.i a.out *.s
	@rm -fr a.out.dSYM