#include <iostream>
#include <vector>

#include "triangulate.hpp"

using namespace SH;

// Data wrapper for providing necessary getters --------------------------------
template <typename Type>
struct wrapperT{
public:
    using InnerType = Type;
    wrapperT(std::vector<std::pair<InnerType, InnerType>> data):data_(data){};
    InnerType x(int index){ return data_[index].first; };
    InnerType y(int index){ return data_[index].second; };
    int size(){ return data_.size(); };
private:
    std::vector<std::pair<InnerType, InnerType>> data_;
};
using wrapper = wrapperT<float>;
// -----------------------------------------------------------------------------

int main(){
    // Real data provided from user
    std::vector<std::pair<float, float>> data;

    data.push_back(std::make_pair(0.0, 0.0));
    data.push_back(std::make_pair(1.0, 1.0));
    data.push_back(std::make_pair(2.0, 0.0));
    data.push_back(std::make_pair(-1.0, -1.0));

    // Data wrapper to provide x(int idx) and y(int idx) getters
    wrapper wrappedData(data);
    TRI::InData<wrapper> input(wrappedData);

    // Process data
    std::vector<float> outData = input.GenerateTriangles();

    return 0;
}
