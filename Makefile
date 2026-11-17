.PHONY: build run test clean

build:
	cmake --workflow --preset build

run:
	cmake --workflow --preset start

test:
	cmake --workflow --preset test

clean:
	cmake --workflow --preset clean
