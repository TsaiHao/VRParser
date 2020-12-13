#ifndef VRPARSER_UTILS_H
#define VRPARSER_UTILS_H

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace VrParser
{
    class Utils {
    public:
        static const std::unique_ptr<Utils>& instance() {
            static std::unique_ptr<Utils> _inst = nullptr;
            if (!_inst) {
                std::unique_ptr<Utils> temp(new Utils());
                _inst = std::move(temp);
            }
            return _inst;
        }
        bool exists(const std::string& p) const;
        int createDirectory(const std::string& file) const;
        int readFileToBuffer(const std::string& file, std::string& content) const;
        std::vector<std::string> readFileLines(const std::string& file) const;

    private:
        Utils() = default;
    };
}
#endif //VRPARSER_UTILS_H
