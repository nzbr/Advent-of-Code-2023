#include "util.h"

vector<string> load_file(const string& filename) {
    auto file = std::ifstream(filename);
    if (!file) {
        std::cerr << "Could not open file" << std::endl;
        throw std::runtime_error("Could not open file");
    }

    string line;
    vector<string> result;

    while (std::getline(file, line)) {
        result.emplace_back(line);
    }

    file.close();

    return result;
}
