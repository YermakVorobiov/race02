all: way_home

way_home:
	clang -std=c11 -Wall -Wextra -Werror -Wpedantic -Iinc -o way_home src/*.c

clean:
	rm -rf way_home

uninstall:
	rm -rf way_home

reinstall:
	make uninstall
	make
