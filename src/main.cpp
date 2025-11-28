#include "gc_controller.hpp"
#include <iostream>

int main() {
    GCController gc;

    gc.setMode(GCMode::Auto);

    std::cout << "\n=== GC Control Script Demo ===\n\n";

    gc.suggest("realtime");
    gc.freezeRegion("parser_heap");
    gc.collectNow();

    gc.unfreezeRegion("parser_heap");
    gc.suggest("batch");
    gc.collectNow();

    const GCStats& s = gc.stats();
    std::cout << "\nGC Stats:\n";
    std::cout << "  Cycles      : " << s.cycles << "\n";
    std::cout << "  Last Pause  : " << s.last_pause.count() << "us\n";

    return 0;
}
