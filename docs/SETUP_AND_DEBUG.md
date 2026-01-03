# Development Environment Setup & Debugging Guide

This document outlines the procedures for setting up the cross-compilation environment for Luckfox Pico and performing remote debugging using VS Code.

## 1. Prerequisites

### Host Machine (Ubuntu/Linux PC)
* **Docker:** Installed and configured (current user must be in the `docker` group).
* **VS Code:** With the following extensions installed:
    * C/C++ (Microsoft)
    * CMake Tools (Microsoft)
* **SSH Client:** OpenSSH client installed.

### Target Device (Luckfox Pico)
* **SSH Server:** Enabled and running.
* **GDB Server:** Installed (verify by running `gdbserver --version` on the device).
* **Network:** The device must be accessible from the Host PC (Default IP example: `192.168.7.2`).

## 2. One-Time Setup

### 2.1. SSH Passwordless Login (Critical)
VS Code automation requires non-interactive SSH access to the board. You must set up SSH keys to allow logging in without a password.

Run the following commands on your Host PC:

```bash
# Generate SSH key (if you haven't already)
ssh-keygen -t rsa -b 4096

# Copy the key to the target device
# Replace 192.168.7.2 with your actual board IP
ssh-copy-id root@192.168.7.2

# Verification:
# You should be able to log in without a password prompt:
ssh root@192.168.7.2
```
### 2.2. Docker Compiler Image
Ensure the compiler image is available locally:

```bash
docker images | grep luckfox-compiler
```

If missing, please refer to the project Dockerfile to build the image.

## 3. Configuration
The project includes pre-configured VS Code settings in the .vscode/ folder.

- settings.json: Defines target IP, user, and paths.

- tasks.json: Automates Docker build and SCP deployment.

- launch.json: Configures the GDB client.

Note: If your board IP changes, update embed.targetIP in .vscode/settings.json.

## 4. Workflow
### 4.1. Cross-Compilation (Build)
You can build the project for the ARM target directly from VS Code:

1. Press Ctrl + Shift + B.

2. Select "CMake Build".

3. Monitor the terminal. The build artifacts will be placed in build_arm/bin/.

Note: The task runs inside a Docker container but maps the file permissions to your local user, preventing "Permission Denied" issues.

### 4.2. Remote Debugging
To start a debugging session:

1. Open a source file (e.g., src/main.cpp) and set a breakpoint (F9).

2. Press F5 (or go to Run and Debug -> Select "GDB Remote Debug").

What happens automatically:

1. Build: Recompiles the code via Docker.

2. Deploy: SCPs the binary to the target (/usr/local/StreamFluxDevice).

3. GDB Server: Kills old instances and starts a new gdbserver on the target.

Connect: VS Code GDB connects to the target port.

## 5. Troubleshooting
Issue: "Permission denied" in build_arm folder
Cause: A previous build might have been run using root permissions inside Docker without the user mapping flag.

Fix:

```bash
sudo rm -rf build_arm/
# Run the build task again via VS Code
```

Issue: Debug session hangs at "Launching..."
- Cause: The scp or ssh command is waiting for a password input in the background.

- Fix: Repeat step 2.1 (SSH Passwordless Login).

Issue: "Connection refused" or GDB Timeout
- Cause: Wrong IP address or Firewall issues.

- Fix:

    - Check embed.targetIP in .vscode/settings.json.

    - Ping the device from your terminal.

    - Ensure port 2345 is not blocked.