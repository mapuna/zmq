CC = g++

FLAGS = -std=c++17 -ggdb -Wall -Wextra \
		`pkg-config --cflags --libs opencv4` \
		`pkg-config --cflags --libs libzmq`

rep_server: server.cpp
	$(CC) -o $@ $< $(FLAGS)

req_client: client.cpp
	$(CC) -o $@ $< $(FLAGS)

.PHONY: clean

clean:
	rm -f rep_server req_client