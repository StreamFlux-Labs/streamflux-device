/*
 * StreamFlux Device - Main Entry Point
 */

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

#include "utils/Logger.h"

int main(int argc, char* argv[]) {
    (void)argc; // Suppress unused warning
    (void)argv;

    LOG_INFO("========================================");
    LOG_INFO("   StreamFlux Device - v0.1.0 Init      ");
    LOG_INFO("========================================");

    #ifdef TARGET_ROCKCHIP
        LOG_INFO("Platform: Rockchip Embedded (ARM64)");
    #else
        LOG_INFO("Platform: PC Development (x86_64)");
    #endif

    LOG_INFO("Initializing modules...");
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    
    LOG_DEBUG("This is a debug message (visible in Debug build)");
    LOG_WARN("Camera module not connected (Simulation Mode)");

    LOG_INFO("Entering Main Loop...");
    int frame_count = 0;
    const int max_frames = 5;

    while (frame_count < max_frames) {
        auto start = std::chrono::steady_clock::now();
        
        std::this_thread::sleep_for(std::chrono::milliseconds(33));

        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        LOG_INFO("Processed Frame " << frame_count << " in " << duration << "ms");
        frame_count++;
    }

    LOG_INFO("Shutting down safely...");
    return 0;
}