build0:
	@clang -fcolor-diagnostics -fansi-escape-codes -g main.c cstring.c carray.c testcarray.c testcstring.c -o /Users/user0/Desktop/Projects/C/cfoundation/a.out

build1:
	@clang -E main.c -o main.i
	@clang -E cstring.c -o cstring.i
	@clang -E testcstring.c -o testcstring.i

build2:
	@clang -S main.c -o main.s
	@clang -S cstring.c -o cstring.s
	@clang -S testcstring.c -o testcstring.s

build3:
	@clang -E macro.h -o macro.i

clean:
	@rm *.i a.out *.s
	rm -fr a.out.dSYM