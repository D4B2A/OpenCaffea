#include "util/arguments/arguments.h"

int main(int argc, char* argv[]) {
    ArgumentParser parser = ArgumentParser();
    runConfig config = parser.parse(argc, argv);
    return 1;
}

