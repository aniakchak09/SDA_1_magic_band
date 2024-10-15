build:
	gcc -g -std=gnu11 -o tema1 tema1.c functii.c
run:
	./tema1
clean:
	rm tema1
valgrind:
	valgrind -s --leak-check=full --show-leak-kinds=all --leak-check=yes --track-origins=yes ./tema1