#include <eigen3/Eigen/Dense>
#include <iostream>

struct Size {
    Size(int h_, int w_): height(h_), width(w_){}
    int height, width;
};

Eigen::MatrixXf max_pool2d(Eigen::MatrixXf& mat_in, Size sz, int stride = 1){
    
    int rows = mat_in.rows();
    int cols = mat_in.cols();
    int height = sz.height;
    int width = sz.width;
    int final_rows = (rows-height)/stride;
    if(stride*final_rows+height <= rows)
        final_rows++;
    int final_cols = (cols-width)/stride;
    if(stride*final_cols+width <= cols)
        final_cols++;
    // std::cout<<final_rows<<","<<final_cols<<std::endl;
    Eigen::MatrixXf mat_tmp(rows, final_cols);
    for(int i = 0; i < rows; i++){
        for(int j = 0; j <  final_cols; j++){
            float max_val = std::numeric_limits<float>::min();
            for(int m = 0; m < width; m++){
                // float val = mat_in(i,j+m);
                float val = mat_in(i,j*stride+m);
                if(val > max_val)
                    max_val = val;
            }
            mat_tmp(i,j) = max_val;
        }
    }
    
    // std::cout<<mat_tmp<<std::endl<<std::endl;
    Eigen::MatrixXf mat_out(final_rows, final_cols);
    for(int j = 0; j < final_cols; j++){
        for(int i = 0; i < final_rows; i++){
            float max_val = std::numeric_limits<float>::min();
            for(int m = 0; m < height; m++){
                // float val = mat_tmp(i+m,j);
                float val = mat_tmp(i*stride+m,j);
                if(val > max_val)
                    max_val = val;
            }
            mat_out(i,j) = max_val;
        }
    }
    return mat_out;
}

int main (int argc, char** argv)
{
    Eigen::MatrixXf mat(4,5);
    mat<<9,7,8,2,4,
         5,3,1,4,5,
         6,2,4,5,3,
         3,4,5,6,7;
    std::cout<<max_pool2d(mat, Size(3,3), 2)<<std::endl;

    return 1;
}