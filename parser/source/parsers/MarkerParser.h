#ifndef VRPARSER_MARKERPARSER_H
#define VRPARSER_MARKERPARSER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace VrParser {
    class MarkerParser {
    public:
        struct Marker {
        public:
            bool hasName(const std::string &name) const {
                return (_ms.find(name) != _ms.end());
            }

            int getCounter(const std::string &name) const {
                if (hasName(name)) {
                    return _ms.find(name)->second;
                }
                return -1;
            }

            void addCounter(const std::string &name, const int value) {
                _ms[name] = value;
            }

            void comment(const std::string& com) {
                _comment = com;
            }

            const std::string comment() const {
                return _comment;
            }

            void clear() {
                _ms.clear();
                _comment.clear();
            }

        private:
            std::unordered_map<std::string, int> _ms;
            std::string _comment;
        };

        MarkerParser() = default;
        MarkerParser(const std::string &mfile);
        MarkerParser(MarkerParser&& rhs) {
            _names = std::move(rhs._names);
            _markers = std::move(rhs._markers);
        }
        MarkerParser& operator=(MarkerParser&& rhs) {
            _names = std::move(rhs._names);
            _markers = std::move(rhs._markers);
            return *this;
        }

        void generateMatlabClass(const std::string &fname);
        void parseFile(const std::string &mfile);
        void removeUncommonMarkers();

        std::vector<Marker>& Markers() {
            return _markers;
        }
        const std::unordered_set<std::string>& Names() const {
            return _names;
        }

    private:
        std::unordered_set<std::string> _names;
        std::vector<Marker> _markers;
    };
}

#endif //VRPARSER_MARKERPARSER_H
