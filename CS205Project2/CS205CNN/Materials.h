#pragma once
#include<iostream>
#include<opencv2/opencv.hpp>
#include<math.h>

typedef struct conv_param {
	int pad;
	int stride;
	int kernel_size;
	int in_channels;
	int out_channels;
	float* p_weight;
	float* p_bias;
} conv_param;

typedef struct fc_param {
	int in_features;
	int out_features;
	float* p_weight;
	float* p_bias;
} fc_param;

