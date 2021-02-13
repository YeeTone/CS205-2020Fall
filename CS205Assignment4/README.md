# CS205Assignment4

CS205: C/C++ Program Design Assignment4

Please declare a class Matrix in file matrix.hpp and implement its member functions and friend functions (if any) in file matrix.cpp. How the matrix works is demonstrated in main.cpp with a main() function inside.

### Requirements:
1.(20 points) The class Matrix should be designed for a matrix with float elements. It should contain some members to describe its number of rows and columns, data and others. Please use private keyword to protect the data inside.

2.(35 points) Please design some constructors, destructor, operator =, operator << and some others as what Lecture Notes in Week 11 describe. Since the data of a matrix is normally large, please do not use data copy in constructors and operator =. You can follow the design of cv::Mat in OpenCV.

3.(25 points) Please implement operator * overloading such that the class can support: C= A * B, C = A * b, and C = a * B (Capital letters are for matrices. Small letters are for scalars).

4.(10 points) Compile and run your program on an ARM development board.

5.(5 points) Please host your source code at GitHub.com,

6.(5 points) Please use cmake to manage your source code.

### Rules:

1.Please submit your assignment report before its deadline. After the deadline (even 1 second), 0 score!

2.Please pay more attention to your code style. After all this is not ACM-ICPC contest. You have enough time to write code with both correct result and good code style. You will get deduction if your code style is terrible. You can read Google C++ Style Guide (http://google.github.io/styleguide/cppguide.html ) or some other guide for code style.
