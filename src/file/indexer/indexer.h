#include <vector>
#include <map>

struct indexEntry {
    std::vector<long> from;
    std::vector<long> to;
};

typedef std::map<long, indexEntry> indexMap;