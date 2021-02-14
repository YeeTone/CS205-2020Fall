# CS205Project2  
### Project Presentation Video  
Link: https://www.bilibili.com/video/BV1aX4y1M7ga  
![Image text](https://github.com/YeeTone/CS205-2020Fall/blob/main/CS205Project2/Images/like.jpg)  
  
This is a trial of implementation of Simple CNN.  
This is mainly for CS205:C/C++ Program Design Project2.  
If you think this is a nice Project, please do not hesitate to give me a ★!  
  
### Contact us   
Author Name: YeeTone Wang(王奕童)  
Author ID:11910104  
Author Email: 11910104@mail.sustech.edu.cn  
  
Course Instructor Name:Shiqi Yu(于仕琪)  
Course Instructor Email: yusq@sustech.edu.cn  

### Project Topic  
![Image text](https://github.com/YeeTone/CS205-2020Fall/blob/main/CS205Project2/Images/topic.png)  

## Catalogue
There are 8 parts, 10 pages in the report in total.  
Part 0. How to use it and test?  
Part 1. Description  
Part 2. Result& Verification  
Part 3. Implementation of the Optimization  
Part 4. Memory management  
Part 5. Test on Different Platform  
Part 6. To Dos in the future  
Part 7. Summary  
  
### Part 0.How to use it and test on VS2017  
First open the git-Bash and input like this to clone the repository.  
![Image text](https://github.com/YeeTone/CS205-2020Fall/blob/main/CS205Project2/Images/gitclone.png)  
  
If you don’t install VS2017 on your computer, please download and follow the instructions on LAB1 of CS205 2020 Fall.   
  
If you don’t install OpenCV on your computer, please download and follow the instructions on LAB14 of CS205 2020 Fall.   
  
Then Open the VS2017(try to install if you don’t have VS2017!) and choose the corresponding sln file.  
![Image text](https://github.com/YeeTone/CS205Project2/blob/main/Images/open.png)
  
Then you can just change the name of file in the main.cpp and start test!
  
### Part 1.Description  
There are 5 code files for this project in total:  
![Image text](https://github.com/YeeTone/CS205-2020Fall/blob/main/CS205Project2/Images/open.png)  
1.main.cpp： The entry of the project, using very few lines of codes;//code lines:5  
2.Material.h：Mainly for the definition of the struct for convolution core and full-connected layer, using very simple codes;//code lines:22  
3.Material.cpp：Nothing, since no definition of methods in the convolution cores and full-connected layer;//code lines:3  
4.Tools.h：Mainly for the tool class——CNN_Tools. All operations for CNN is implemented by this class. And this class cannot be instantiated;//code lines:20  
5.Tools.cpp：Mainly for the trained data and the implementation of the methods defined in the class CNN_Tools;//code lines:287
#### Total code lines:5+22+3+20+287=337, simple and beautiful!
  
【Implementation for the Requirements】   
1.The 3x3 convolution core is correctly implemented, which supports the case when stride=1 or stride=2; it also support the case when padding=1;   
2.For the 128x128 images, it can output the confidence scores of faces and background correctly; For the images not 128x128. it can be reshaped to 128x128 then output the correct confidence scores;  
3.For the efficiency of the computation, it is improved in many aspects, such as compilation option, loop structure, memory access, etc. And some comparison and analysis is aslo shown in the report.  
4.The programme is nicely supported in many platforms, such as Win10, X86 and ARM etc.;  
5.Github Repository Link：https://github.com/YeeTone/CS205Project2.git  
6.This project report is neither too long nor too short, and it is a pleasure reading this report. 

### Part 2.Result& Verification  
Test Environment：Windows 10  
Compiler：mingw-gcc/g++  
Development IDE：Visual Studio 2017  
There are 8 images for test cases(4 faces and 4 background), which are also uploaded with the Report.  
You can find the images in the folder CS205CNN as well.  
![Image text](https://github.com/YeeTone/CS205-2020Fall/blob/main/CS205Project2/Images/dialogue1.jpg)  
![Image text](https://github.com/YeeTone/CS205-2020Fall/blob/main/CS205Project2/Images/dialogue2.jpg)  
From these 8 test cases, the result is generally in line with our expectations, so we can verify the correctness of the implementation of this simple CNN.  
  
### Part 3. Implementation of the Optimization  
#### （1）The core class of the CNN Implementation: CNN_Tools  
Core methods and their effects:  
  
[Method Definition]  
```C++
static void read_start(string s);
```
[Parameter List]  
```C++
(string s)  
```
[Method Effect]It provides a good external access, and only needs to pass in a string to complete CNN image reading and convolution calculation.   
  
[Method Definition]
```C++
static Mat reshape(Mat& image);  
```
[Parameter List]  
```C++
(Mat& image)  
```
[Method Effect]If the input image is 128x128, there is no need to do with it; otherwise, it can be reshape by CV::resize function, so that it can be changed to the size of 128x128 again, therefore to enhance the versatility of the program.    
  
[Method Definition]  
```C++
static float* bgr2rgb(Mat& image);  
```
[Parameter List]  
```C++
(Mat& image)  
```
[Method Effect]It is noticed that the initial data type of CV::Mat is an unsigned char type arranged in BGR order, which does not conform to our subsequent definition of convolution layer and full connection layer. This method is used to convert uchar data type to float type and BGR to RGB format.   
[Method Definition]  
```C++
static float* conv_RELU (int channels, int rows, int cols, float* input, conv_param& conv_p);  
```
[Parameter List] 
```C++
(int channels, int rows, int cols, float* input, conv_param& conv_p)  
```
[Method Effect]This method integrates convolution operation and RELU operation to reduce the cost of function call and the space cost of memory development.   
  
[Method Definition]  
```C++
static float* max_pooling (int channels, int rows, int cols, float* input);  
```
[Parameter List]  
```C++
(int channels, int rows, int cols, float* input)  
```
[Method Effect]This method is mainly for maximum pooling operation.   
  
[Method Definition]  
```C++
static void matrix_Production(float* out, float* mat1, int r, int col, int c, float* mat2);  
```
[Parameter List]
```C++
(float* out, float* mat1, int r, int col, int c, float* mat2)  
```
[Method Effect]This method is mainly matrix multiplication, which is used in the last step of full connection layer operation.   

#### （2）Calculation time line chart of optimization process   
The following line chart shows the operation time for the 128x128 picture:  
![Image text](https://github.com/YeeTone/CS205-2020Fall/blob/main/CS205Project2/Images/picture.png)  
Horizontal axis: optimization debugging times, unit: times  
Vertical axis unit: running time, unit: ms  
Efficiency improvement: 235%  

#### （3）Optimization Process of BGR2RGB
[Optimization Strategy]Increase the loop steps to reduce the number of cycles  
[Improvement Record]The wrong judgment of cyclic boundary conditions always leads to ArrayOutOfBound!  
[Optimization Method]After Shiqi Yu's introduction in the lectures, considering that the input image must be 128x128 after reshape operation, we can try to change the loop step of col from 1 to 4, so as to reduce the number of comparison operations in the loop condition, improve the memory access hit rate, and save the operation time.  
The simplified code is shown as follows:  
```C++
for (int i = 0; i < row; i++){
	for (int j = 0; j < col - 1; j += 4){
		//calculation
       		...
	}
}
```
[Optimization Strategy]Use #pragma omp to implement the parallel calculation.  
[Improvement Record]It may leads to negative improvement if it is used in the outside for-loop; If OpenMP is not selected in VS2017, then the improvement cannot come into effect.  
[Usage Requirement]You need to select the "Yes (/ OpenMP)" option in the upper left corner of vs2017, which is project --> Properties --> C/C++ --> language --> OpenMP support, to call the parallel optimization scheme of OMP.  
[Optimization Method]Three kinds of OMP are used to optimize the parallel statements inside and outside the double nested for loop:  
Outer:#pragma omp parallel  
Loop:#pragma omp single  
Calculation:#pragma omp task  
The simplified code is shown as follows:  
```C++
#pragma omp parallel                            
{                                                 
    #pragma omp single                          
	for (int i = 0; i < row; i++){             
		...                                       
		for (int j = 0; j < col - 1; j += 4){  
		#pragma omp task                         
			{                                     
            //calculation                        
				...                               
			}                                     
		}                                         
	}                                             
}  
```
   
#### （4）Optimization Process of Conv_RELU  
[Optimization Strategy]Local variables are created to record values to reduce the time cost for multiplication.  
[Improvement Record]For a single multiplication, it is not necessary to record the value, because the time of accessing local variables may be higher than the cost of multiplication, which leads to negative optimization; the time of multiple multiplication should be recorded, so as to reduce the cost of multiple multiplication.  
[Optimization Method]Local variables are created to record the calculation results of multiple multiplication / division as follows:  
```C++
int for_num = i_channel * kernel_size * kernel_size * i;
int fnumber = for_num + (j - 1) * kernel_size * kernel_size;
int fnumber2 = (j - 1) * (rows) * (cols)+ k * (cols) + l;
```

[Optimization Strategy]Using # pragma omp to realize parallel operation  
[Improvement Record]The same as before, it is still the loop order of OMP statement;  
[Optimization Method]After repeated debugging, the optimal strategy of pragma loop is determined as follow:  
```C++
for (int i = 0; i < o_cha; i++){
	int f_num = i * ks * ks * i_cha;
	for (int j = 1; j <= channels; j++){
		int fn = f_num + (j - 1) * ks * ks;
#pragma omp parallel for
		for (int k = 1; k <= rows - 2; k += conv_p.stride){
			for (int l = 1; l <= cols - 2; l += conv_p.stride){
				...
			}
		}
	}
}
```
If I try to add OMP statements in the inner or outer layer on the local computer, it will lead to longer running time. The reason is that the number of CPU cores on the local computer is limited. If I continue to add OMP statements, it will lead to too many CPU threads, as shown below:  
![Image text](https://github.com/YeeTone/CS205-2020Fall/blob/main/CS205Project2/Images/thread.png)  
The communication between threads also needs extra time, resulting in the slow operation speed.  

#### （5）Part 4.Memory management
In the implementation of CNN algorithm, one of the most annoying things is memory management and release. Although we have implemented a CMatrix class for automatic memory management in assignment 4, memory management is still a difficulty in this project. The following similar pages appear many times in the production of this project, and most of them appear at system("pause") or return 0:  
![Image text](https://github.com/YeeTone/CS205-2020Fall/blob/main/CS205Project2/Images/error1.png)
![Image text](https://github.com/YeeTone/CS205-2020Fall/blob/main/CS205Project2/Images/error2.png)
![Image text](https://github.com/YeeTone/CS205-2020Fall/blob/main/CS205Project2/Images/error3.png)  
For this reason, the following flow chart of data transfer and memory management in convolution operation is designed to facilitate understanding:     
![Image text](https://github.com/YeeTone/CS205-2020Fall/blob/main/CS205Project2/Images/Data_Graph.png)  
Flow chart of memory management and data flow  
In short, it is to recycle the incoming data immediately after it is used up, so as to avoid the problem of subsequent memory management and realize efficient data management.   

### Part 5.Test on Different Platform  
【Linux System】The running results of two standard test cases on ARM development board are as follows  
Test File: 0.jpg（face.jpg）  
![Image text](https://github.com/YeeTone/CS205-2020Fall/blob/main/CS205Project2/Images/arm1.png)  
Test File: 1.jpg（bg.jpg）  
![Image text](https://github.com/YeeTone/CS205-2020Fall/blob/main/CS205Project2/Images/arm2.png)  
From the above standard test images provided by SimpleCNNbyCPP, we conclude that  
1.The running results of the two test files are the same as that of WIN10 platform, which verifies the correctness of the cross platform operation of the program;  
2.After many times of time measurement, it is found that the running time of the test file in ARM development board is longer than that in Win10 System. This part comes from the fact that the memory of ARM development board is not as large as that of windows 10 system, which leads to the limitation of computing performance.   

### Part 6.To Dos in the future  
As the project is approaching the end of the term, there is a lot of pressure and time is tight, so many ideas in mind have not been shown in the project implemented by CNN. Now the to do list in the future is as follows:  
1. Add a more perfect self-defined memory reference recycling mechanism to realize the reasonable application and release of memory space; (this idea has been implemented in assignment 4, but it has not been merged yet.)  
2. Increase the use of instruction sets (such as AVX, SSE, etc.) on different platforms to improve the efficiency of operation while maintaining platform compatibility;  
3. Add the JNI interface implementation of this program, so that we can take advantage of the cross platform advantages of Java language and the high efficiency of C / C + + language, and it may be transplanted to Android platform in the future;  
4. Increase the use of CUDA interface to call GPU to calculate data more efficiently;  
  
### Part 7.Summary
The final project of CS205:C/C++ Program Design is the C++ implementation of simple CNN. At the first of this project, I felt that it was difficult to do with it. After the introduction in the instructor Shiqi Yu in the Lecture 14 and the videos on bilibili, I found that the implementation of CNN was not as difficult as I thought. As the course instructor Yu said: the previous assignments and mid-term projects are all for the implementation of CNN; this project is not so difficult, but it well reflects the characteristics of C++ language. In the process of doing the final project, I think I learned a lot that I didn't have previously:  
1.C++'s characteristic: pointers point to the memory;  
2.C++'s local variables' deep understanding;  
3.C++'s memory use and free;  
4.C++'s high efficiency for calculation;  
5.C++'s calculation efficiency's difference under different platforms;  
6.C++'s Instruction set under different platforms;  
7.C++'s class and objects' understanding;  
8.opencv library's installation and use;  
9.Basic Algorithm of CNN's Implementation;  
10.Ability to solve various kinds of ERRORs of VS2017;  
11.Patience for bugs and Patience for Debugging;  
   
Semester summary: In this semester, Shiqi Yu's teaching of C / C + + course is quite unique, which is a major innovation of CS205 course. This course has well cultivated the students' practical ability and greatly expanded their knowledge, involving many aspects of knowledge, such as Computer Operating System, Computer Composition Principle and so on.
### Finally, I believe that this semester's C/C++ course will be of great benefit to my future study in the computer department!  
