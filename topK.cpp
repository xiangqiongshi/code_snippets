#include <eigen3/Eigen/Core>
#include <eigen3/unsupported/Eigen/CXX11/Core>
#include <eigen3/unsupported/Eigen/CXX11/Tensor>
#include <iostream>
#include <queue>

using namespace Eigen;
using namespace std;

void topK(Tensor<float, 3>& tensor_in, Tensor<float, 3>& tensor_out, int k, int dim, bool largest, bool sorted){
    const Eigen::Tensor<float, 3>::Dimensions& d = tensor_in.dimensions();
    
    if(dim == 0){
        if(k > d[0])
            return;
        tensor_out = Tensor<float, 3>(k, d[1], d[2]);
    }
    else if(dim == 1){
        if(k > d[1])
            return;
        tensor_out = Tensor<float, 3>(d[0], k, d[2]);
    }
    else{
        if(k > d[2])
            return;
        tensor_out = Tensor<float, 3>(d[0], d[1], k);
    }

    auto compare = [largest](pair<int, float>& a, pair<int, float>& b){
        if(largest)
            return a.second > b.second;
        else
            return a.second < b.second;
    };

    if(dim == 0){
        for(int i = 0; i < d[1]; i++){
            for(int j = 0; j < d[2]; j++){
                std::priority_queue<pair<int, float>, std::vector<pair<int, float>>, decltype(compare)> pq(compare);
                for(int m = 0; m < d[0]; m++){
                    pq.push({m, tensor_in(m,i,j)});
                    if(pq.size() > k)
                        pq.pop();
                }
                if(sorted){
                    for(int m = k-1; m >= 0; m--){
                        auto v = pq.top();
                        tensor_out(m,i,j) = v.second;
                        pq.pop();
                    }
                }
                else{
                    vector<pair<int, float>> vec;
                    while(!pq.empty()){
                        vec.push_back(pq.top());
                        pq.pop();
                    }
                    auto compare2 = [](pair<int, float>& a, pair<int, float>& b){
                        return a.first < b.first;
                    };
                    sort(vec.begin(), vec.end(), compare2);
                    for(int m = 0; m < k; m++){
                        tensor_out(m,i,j) = vec[m].second;
                    }
                }
            }
        }
        
    }
    if(dim == 1){
        for(int i = 0; i < d[0]; i++){
            for(int j = 0; j < d[2]; j++){
                std::priority_queue<pair<int, float>, std::vector<pair<int, float>>, decltype(compare)> pq(compare);
                for(int m = 0; m < d[1]; m++){
                    pq.push({m, tensor_in(i,m,j)});
                    if(pq.size() > k)
                        pq.pop();
                }
                if(sorted){
                    for(int m = k-1; m >= 0; m--){
                        auto v = pq.top();
                        tensor_out(i,m,j) = v.second;
                        pq.pop();
                    }
                }
                else{
                    vector<pair<int, float>> vec;
                    while(!pq.empty()){
                        vec.push_back(pq.top());
                        pq.pop();
                    }
                    auto compare2 = [](pair<int, float>& a, pair<int, float>& b){
                        return a.first < b.first;
                    };
                    sort(vec.begin(), vec.end(), compare2);
                    for(int m = 0; m < k; m++){
                        tensor_out(i,m,j) = vec[m].second;
                    }
                }
            }
        }
        
    }
    if(dim == 2){
        for(int i = 0; i < d[0]; i++){
            for(int j = 0; j < d[1]; j++){
                std::priority_queue<pair<int, float>, std::vector<pair<int, float>>,decltype(compare)> pq(compare);
                for(int m = 0; m < d[2]; m++){
                    pq.push({m, tensor_in(i,j,m)});
                    if(pq.size() > k)
                        pq.pop();
                }
                if(sorted){
                    for(int m = k-1; m >= 0; m--){
                        auto v = pq.top();
                        tensor_out(i,j,m) = v.second;
                        pq.pop();
                    }
                }
                else{
                    vector<pair<int, float>> vec;
                    while(!pq.empty()){
                        vec.push_back(pq.top());
                        pq.pop();
                    }
                    auto compare2 = [](pair<int, float>& a, pair<int, float>& b){
                        return a.first < b.first;
                    };
                    sort(vec.begin(), vec.end(), compare2);
                    for(int m = 0; m < k; m++){
                        tensor_out(i,j,m) = vec[m].second;
                    }
                }
            }
        }
        
    }
    
}

int main(int argc, char** argv){
    Tensor<float, 3> t_3d(2, 3, 4);
    
    // Initialize all elements to random values.
    int count = 0;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            for (int k = 0; k < 4; ++k) {
                t_3d(i, j, k) = count;
                count++;
            }
        }
    }

    int k = 1;
    int dim = 0;
    Tensor<float, 3> t_out;
    topK(t_3d, t_out, k, dim, true, true);
    const Eigen::Tensor<float, 3>::Dimensions& d = t_out.dimensions();
    for(int i = 0; i < d[0]; i++){
        for(int j = 0; j < d[1]; j++){
            for(int k = 0; k < d[2]; k++){
                std::cout<<t_out(i,j,k)<<",";
            }
            std::cout<<std::endl;
        }
        std::cout<<std::endl;
    }
}