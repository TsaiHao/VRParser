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
        std::string join(const std::string p1, const std::string p2) const {
            if (p1.empty() || p2.empty()) {
                return p1.empty() ? p2 : p1;
            }
            if (p1.back() == '\\' || p1.back() == '/') {
                return p1 + p2;
            }
            return p1 + "/" + p2;
        }

    private:
        Utils() = default;
    };
}
#endif //VRPARSER_UTILS_H
