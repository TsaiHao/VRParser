#ifndef VRPARSER_UTILS_H
#define VRPARSER_UTILS_H

#include <memory>
#include <string>
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

        int createDirectory(const std::string& file) const;
    private:
        Utils() = default;
    };
}
#endif //VRPARSER_UTILS_H
