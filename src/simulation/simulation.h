class Bus {
    private:
        int id;
    public:
        bool operator==(Bus& other);

};
class Model {
    private:
        std::list<Bus*> connectedBusses;
        float calculate_self(bool);
    public:
        float calculate(bool);
        std::list<Model*> subModels;
        std::list<Bus*> getConnectedBusses();

};

struct simulationConfig{
    float stopTime;
    float stepSize;
    float multipassAccuracy;
};

struct busNet {
    Bus* bus;
    std::list<Model*> models;
};