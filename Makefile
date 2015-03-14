CFLAGS=-Wall -g

all: oscar print_children assign add_ints

oscar: 
	gcc test/oscar.c src/cheney.c src/value.c -o bin/oscar

print_children:
	gcc test/print_children.c src/cheney.c src/value.c -o bin/print_children

assign:
	gcc test/assign.c src/cheney.c src/value.c src/vertex.c -o bin/assign

add_ints:
	gcc test/add_ints.c src/cheney.c src/value.c -o bin/add_ints

clean:
	rm -ri bin

