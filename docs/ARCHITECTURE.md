# StreamFlux Device Architecture

## 1. Overview

`streamflux-device` is a client-side application running on Edge Devices.
**Goal:** Capture video from Camera -> Encode (H.264/H.265) -> Transmit via SRT (Secure Reliable Transport) protocol.

**Core Requirements:**

- **Cross-Platform:** The codebase must compile and run on both the Development Environment (Ubuntu x86_64) and the Production Environment (Rockchip ARM64/Linux).
- **Low Latency:** Pipeline optimization to minimize end-to-end latency.

## 2. Project Structure

The project follows a standard CMake structure:

```text
streamflux-device/
├── cmake/                  # CMake helper modules (FindSRT, Toolchain...)
├── configs/                # Runtime configuration files (JSON/TOML)
├── docs/                   # Technical documentation
├── include/                # Public Headers
│   ├── common/             # Common data structures (Buffer, Config)
│   └── interfaces/         # Pure Virtual Classes (HAL Interfaces)
├── src/                    # Implementation
│   ├── core/               # Main logic (Pipeline orchestration)
│   ├── modules/            # Functional components
│   │   ├── capture/        # V4L2 handling
│   │   ├── encoder/        # Video compression (Soft/Hard)
│   │   └── transport/      # SRT handling
│   └── utils/              # Logger, Time, Helper functions
├── third_party/            # External libraries (Git Submodules)
└── tests/                  # Unit Tests (GoogleTest)
```

## 3. Software Design

We utilize the Strategy Pattern combined with a Hardware Abstraction Layer (HAL) to ensure cross-platform compatibility.

### 3.1. Interfaces

All interactions between modules must occur through Interfaces defined in include/interfaces/. No module shall directly invoke the concrete implementation of another module.

- IVideoSource: Abstracts video acquisition (Webcam, CSI Camera, Mock File).

- IVideoEncoder: Abstracts video compression.

- On PC: Implementation calls FFmpeg/x264.

- On Embedded: Implementation calls Rockchip MPP (Media Process Platform).

- IStreamTransport: Abstracts data transmission (SRT, UDP, etc.).

### 3.2. Data Flow

The pipeline operates with a Zero-Copy philosophy wherever possible.

```
[Camera (V4L2)] --(DMA/Ptr)--> [Encoder] --(Packet)--> [SRT Sender] --(Net)--> Server
```
