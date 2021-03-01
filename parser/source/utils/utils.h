#ifndef VRPARSER_UTILS_H
#define VRPARSER_UTILS_H
#include <memory>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define _USE_MATH_DEFINES
#include <cmath>

#ifndef M_PI
#define M_PI (3.14159265358979323846264338)
#endif

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
        //file related
        bool exists(const std::string& p) const;
        int createDirectory(const std::string& file) const;
        int readFileToBuffer(const std::string& file, std::string& content) const;
        std::vector<std::string> readFileLines(const std::string& file) const;
        std::string getBrainVisionHeader(const std::string& dataFile, const std::string& markerFile) const;
        std::string join(const std::string p1, const std::string p2) const {
            if (p1.empty() || p2.empty()) {
                return p1.empty() ? p2 : p1;
            }
            if (p1.back() == '\\' || p1.back() == '/') {
                return p1 + p2;
            }
            return p1 + "/" + p2;
        }

        // debug related
        void logError(const std::string& msg) const {
            std::cerr << msg << std::endl;
        }

        // calculation related
        std::vector<float> quaternionToEuler(const std::vector<float>& quats) const noexcept;
        std::vector<float> quaternionToEuler(const float *const quats, const size_t items, const size_t padding) const noexcept;
    private:
        Utils() = default;
        void _quatToEulerIntern(const float* const q, float* const e) const noexcept {
            // roll (x-axis rotation)
            double sinr_cosp = 2 * (q[0] * q[3] + q[1] * q[2]);
            double cosr_cosp = 1 - 2 * (q[0] * q[0] + q[1] * q[1]);
            e[0] = std::atan2(sinr_cosp, cosr_cosp);

            // pitch (y-axis rotation)
            double sinp = 2 * (q[3] * q[1] - q[2] * q[0]);
            if (std::abs(sinp) >= 1)
                e[1] = std::copysign(M_PI / 2, sinp); // use 90 degrees if out of range
            else
                e[1] = std::asin(sinp);

            // yaw (z-axis rotation)
            double siny_cosp = 2 * (q[0] * q[3] + q[1] * q[2]);
            double cosy_cosp = 1 - 2 * (q[1] * q[1] + q[2] * q[2]);
            e[2] = std::atan2(siny_cosp, cosy_cosp);
        }
    };
}
#endif //VRPARSER_UTILS_H
