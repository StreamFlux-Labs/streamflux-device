# StreamFlux Device

The client-side application for the StreamFlux ecosystem, featuring V4L2 capture and SRT streaming.

## Documentation

- [Architecture Overview](docs/ARCHITECTURE.md)
- [Coding Standards](docs/CODING_STANDARD.md)

## Quick Start

### 1. Building for Development (Debug Mode on PC)

This enables debug symbols (-g), disables optimization (-O0), and defines DEBUG_MODE.

```bash
mkdir build_debug && cd build_debug
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j$(nproc)
```

Output binary will be in: build_debug/bin/StreamFluxDevice

### 2. Building for Production (Release Mode on PC)

This enables high optimization (-O3), removes debug symbols, and defines NDEBUG.

```bash
mkdir build_release && cd build_release
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)
```

### 3. Building for Embedded (Cross-compilation)

When you are ready to move to the board:

```bash
mkdir build_arm && cd build_arm
cmake -DCMAKE_BUILD_TYPE=Release \
      -DBUILD_FOR_EMBEDDED=ON \
      -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchain-Rockchip.cmake \
      ..
make -j$(nproc)
```
