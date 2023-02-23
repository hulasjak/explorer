
.PHONY: all
all: 
	mkdir -p build;\
	cd build;\
	cmake -DCMAKE_BUILD_TYPE=Debug ..;\
	cd ..;\
	make -C build

clean:
	rm -rf build;\
