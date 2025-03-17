
struct runConfig {
    bool verbose;
};

class ArgumentParser{
    public:
        runConfig parse(int argc, char** argv);
};

