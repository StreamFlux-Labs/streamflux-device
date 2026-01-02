# Coding Standards & Conventions

## 1. C++ Standard

- **Version:** C++17.
- **Compiler:** GCC/G++ (compatible with buildroot toolchain).

## 2. Naming Convention

We use a variation of the Google Style Guide adapted for Embedded Systems.

| Component            | Rule                             | Example                                      |
| :------------------- | :------------------------------- | :------------------------------------------- |
| **File Name**        | PascalCase                       | `VideoEncoder.cpp`, `SrtClient.h`            |
| **Class/Struct**     | PascalCase                       | `class VideoCapture`, `struct FrameData`     |
| **Function/Method**  | camelCase                        | `initDevice()`, `sendPacket()`               |
| **Variable (Local)** | snake_case                       | `frame_width`, `buffer_ptr`                  |
| **Member Variable**  | snake_case + trailing underscore | `is_running_`, `width_`, `encoder_ctx_`      |
| **Constant/Enum**    | kPascalCase                      | `kMaxBufferSize`, `kErrorNone`               |
| **Macro**            | UPPER_SNAKE_CASE                 | `MAX_RETRY_COUNT` (Avoid Macros if possible) |

## 3. Modern C++ Guidelines (Critical)

### 3.1. Memory Management

- **Strictly avoid manual `new`/`delete`.**
- Use `std::unique_ptr` for exclusive ownership.
- Use `std::shared_ptr` for shared resources (minimize usage due to overhead).
- **Zero Allocation in Hot Paths:** For large buffers (Video Frames), pre-allocate during initialization (Buffer Pool) and reuse them. Avoid `malloc` in the main loop.

### 3.2. Concurrency

- Use `std::thread` and `std::atomic` instead of raw `pthread` (unless setting specific thread priority/affinity for Real-time constraints).
- Use `std::lock_guard` or `std::unique_lock` for Mutex management to prevent deadlocks.

### 3.3. Error Handling

- **No C++ Exceptions (`try-catch`):** Due to runtime overhead and unpredictability in embedded environments.
- Use **Return Codes** (enum) or `std::optional` / `std::expected` patterns.

## 4. Logging

- Do not use `printf` or `std::cout`.
- Use the defined `LOG` macro (wraps spdlog or syslog).
- Format: `[LEVEL] [Time] [File:Line] Message`
  - Example: `[INFO] 10:00:00 [V4L2Capture.cpp:45] Device /dev/video0 opened.`

## 5. Git Workflow

### 5.1. Branching

- `main`: Stable, production-ready code.
- `develop`: Main development branch.
- `feature/feature-name`: Feature branches branched off from develop (e.g., `feature/add-srt-stats`).

### 5.2. Commit Messages (Conventional Commits)

Format: `<type>(<scope>): <subject>`

Types:

- `feat`: New feature.
- `fix`: Bug fix.
- `docs`: Documentation only changes.
- `refactor`: Code change that neither fixes a bug nor adds a feature.
- `chore`: Build process, tools, or dependencies changes.

Examples:

- `feat(capture): add support for MJPEG format`
- `fix(srt): resolve memory leak in connection timeout`
