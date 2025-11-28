#pragma once
#include <string>
#include <unordered_map>
#include <chrono>
#include <iostream>

enum class GCMode {
    Auto,
    LowLatency,
    HighThroughput,
    Manual,
};

struct GCStats {
    uint64_t total_alloc = 0;
    uint64_t total_freed = 0;
    uint64_t cycles = 0;
    std::chrono::microseconds last_pause{0};
};

class GCController {
public:
    GCController();

    void setMode(GCMode mode);
    void collectNow();
    void freezeRegion(const std::string& name);
    void unfreezeRegion(const std::string& name);
    void suggest(const std::string& hint);

    const GCStats& stats() const;

private:
    GCMode currentMode;
    std::unordered_map<std::string, bool> regionFrozen;
    GCStats stat;
};
