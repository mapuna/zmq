CC = g++

FLAGS = -std=c++17 -ggdb -Wall -Wextra \
		`pkg-config --cflags --libs opencv4` \
		`pkg-config --cflags --libs libzmq`

pair_send: pair_send.cpp
	$(CC) -o $@ $< $(FLAGS)

.PHONY: clean
clean:
	rm -f pair_send