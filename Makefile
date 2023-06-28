all: clean config build install
clean:
	rm -rf build
	rm -rf distrib
config:
	mkdir build
	cd build && cmake ..
build: config
	cd build && cmake --build .
install: build
	cd build && cmake --install . --prefix ../distrib
