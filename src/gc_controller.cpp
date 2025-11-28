#include "gc_controller.hpp"
#include <thread>

GCController::GCController() {
    currentMode = GCMode::Auto;
}

void GCController::setMode(GCMode mode) {
    currentMode = mode;
    std::cout << "[GC] Mode changed: ";

    switch (mode) {
        case GCMode::Auto: std::cout << "Auto\n"; break;
        case GCMode::LowLatency: std::cout << "LowLatency\n"; break;
        case GCMode::HighThroughput: std::cout << "HighThroughput\n"; break;
        case GCMode::Manual: std::cout << "Manual\n"; break;
    }
}

void GCController::collectNow() {
    auto start = std::chrono::high_resolution_clock::now();

    std::cout << "[GC] Manual collection triggered.\n";
    stat.cycles += 1;

    std::this_thread::sleep_for(std::chrono::milliseconds(3)); // mock delay

    auto end = std::chrono::high_resolution_clock::now();
    stat.last_pause = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "[GC] Finished collection. Pause = "
              << stat.last_pause.count() << "us\n";
}

void GCController::freezeRegion(const std::string& name) {
    regionFrozen[name] = true;
    std::cout << "[GC] Region frozen: " << name << "\n";
}

void GCController::unfreezeRegion(const std::string& name) {
    regionFrozen[name] = false;
    std::cout << "[GC] Region unfrozen: " << name << "\n";
}

void GCController::suggest(const std::string& hint) {
    std::cout << "[GC] Hint received: " << hint << "\n";

    if (hint == "realtime") {
        setMode(GCMode::LowLatency);
    } 
    else if (hint == "batch") {
        setMode(GCMode::HighThroughput);
    }
}

const GCStats& GCController::stats() const {
    return stat;
}
