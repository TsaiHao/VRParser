//
// Created by zaijun on 2020/9/23.
//

#ifndef VRPARSER_MATRIX_H
#define VRPARSER_MATRIX_H

#include <vector>
#include <array>
#include <algorithm>
#include <utility>

namespace vrparser {
    template<size_t channel>
    class VrSignal {
        typedef float _elem_type;
        typedef std::array<_elem_type, channel> _sample_type;
        typedef std::vector<_sample_type> _mat_type;

    public:
        VrSignal() = default;
        size_t length() const {
            return _mat.size();
        }
        size_t size() const {
            return channel * _mat.size();
        }

        /*
        _sample_type &operator[](const size_t chan) const ;
        _elem_type &operator[](const std::pair<size_t, size_t> &pos) const ;
        void append(const _sample_type &data);
        */
        //void append(const _mat_type &mat);

    private:
        std::vector<_elem_type> _mat;
    };



}

#endif //VRPARSER_MATRIX_H
