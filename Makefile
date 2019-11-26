CC = g++ -std=c++11
CPPFLAGS = -Wall -W

all: main

main: main.cpp
	$(CC) $(CPPFLAGS) -o main main.cpp

clean:
	rm main