#pragma once
#include "Materials.h"
#include "Materials.cpp"
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
class CNN_Tools{
private:
	CNN_Tools() {

	}
public:
	static void read_start(string s);
	static Mat reshape(Mat& image);
	static float* bgr2rgb(Mat& image);
	static float* conv_RELU(int channels, int rows, int cols, float* input, conv_param& conv_p);
	static float* max_pooling(int channels, int rows, int cols, float* input);
	static void matrix_Production(float* out, float* mat1, int r, int col, int c, float* mat2);
};

