#include "gc_controller.hpp"
#include <iostream>

int main(int argc, char** argv) {
    GCController gc;

    if (argc < 2) {
        std::cout << "GC Runtime Usage:\n";
        std::cout << "  gc-runtime setmode <auto|low|high|manual>\n";
        std::cout << "  gc-runtime collect\n";
        std::cout << "  gc-runtime freeze <name>\n";
        std::cout << "  gc-runtime unfreeze <name>\n";
        std::cout << "  gc-runtime suggest <hint>\n";
        return 0;
    }

    std::string cmd = argv[1];

    if (cmd == "setmode" && argc >= 3) {
        std::string m = argv[2];
        if (m == "auto") gc.setMode(GCMode::Auto);
        else if (m == "low") gc.setMode(GCMode::LowLatency);
        else if (m == "high") gc.setMode(GCMode::HighThroughput);
        else if (m == "manual") gc.setMode(GCMode::Manual);
    }

    else if (cmd == "collect") {
        gc.collectNow();
    }

    else if (cmd == "freeze" && argc >= 3) {
        gc.freezeRegion(argv[2]);
    }

    else if (cmd == "unfreeze" && argc >= 3) {
        gc.unfreezeRegion(argv[2]);
    }

    else if (cmd == "suggest" && argc >= 3) {
        gc.suggest(argv[2]);
    }

    return 0;
}

