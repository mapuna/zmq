CC = g++

FLAGS = -std=c++17 -ggdb -Wall -Wextra \
		`pkg-config --cflags --libs opencv4` \
		`pkg-config --cflags --libs libzmq`

publisher: publisher.cpp
	$(CC) -o $@ $< $(FLAGS)

clean:
	rm -f publisher