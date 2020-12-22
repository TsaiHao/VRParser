#ifndef VRPARSER_EXPERIMENT_H
#define VRPARSER_EXPERIMENT_H

#include <filesystem>
#include "dllmain.h"
#include "parsers/MarkerParser.h"
#include "utils/utils.h"
#include "parsers/ParserBase.h"

namespace VrParser {
    template <typename T>
    struct RawData {
        T* data;
        unsigned int length;
        std::string name;
        int channels;
    };

    struct Bias {
        int xbias;
        int ybias;
        std::string toString() const {
            std::string ret;
            if (ybias == 0) {
                ret = std::string("x")
                        + (xbias < 0 ? "n" : "p")
                        + std::to_string(abs(xbias));
            }
            else {
                ret = std::string("y")
                        + (ybias < 0 ? "n" : "p")
                        + std::to_string(abs(ybias));
            }
            return ret;
        }
    };

    class Experiment {
    public:
        explicit Experiment();
        Experiment(const std::string& rootPath, const int s, const int t) :
            _rootPath(rootPath), _subject(s), _trail(t) {}
        virtual void initialize() = 0;
        virtual ~Experiment() {}
        int& subject() {
            return _subject;
        }
        int& trail() {
            return _trail;
        }
        const MarkerParser& markers() const {
            return _markers;
        }
        virtual const std::string getDataPath() const = 0;

    protected:
        static std::unordered_map<std::string, int> Channels;
        static std::unordered_map<std::string, int> SampRate;
        std::filesystem::path _rootPath;
        int _subject;
        int _trail;
        MarkerParser _markers;
        std::unordered_map<std::string, std::unique_ptr<ParserBase>> _parsers;
        std::string dir;
        const std::string classify(const std::filesystem::path& path) const;
    };
}
#endif //VRPARSER_EXPERIMENT_H
