# Makefile

.PHONY: all build clean shell

all: build

build:
	./scripts/cmake_wrapper.sh "cmake -DCMAKE_TOOLCHAIN_FILE=/opt/luckfox-toolchain/toolchain.cmake .. && make -j$(nproc)"

clean:
	rm -rf build_arm

shell:
	./scripts/cmake_wrapper.sh /bin/bash
