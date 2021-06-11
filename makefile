build:
	g++ -Wall -std=c99 ./src/*.cpp -lSDL2 -lX11 -lXrandr -o game

run: build
	./game

clean:
	rm game	