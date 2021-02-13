# CS205Project1
CS205 Project1

Please implement a function to compute the multiplication of two matrices. The data type of matrix elements is float (not double). As shown in the following figure1, the resulting matrix C, known as the matrix product, has the number of rows of the first matrix A and the number of columns of the second matrix B.

![Image text](https://raw.githubusercontent.com/Yitong104/CS205Project1/main/1.png)

The definition of matrix multiplication is as follows2:

![Image text](https://raw.githubusercontent.com/Yitong104/CS205Project1/main/2.png)

### Requirements:

1.(20 points) Please define a Struct for matrices. The Struct should contain the property descriptions such as the number of rows, the number of columns, data, etc.

2.(30 points) Please implement a function which can compute the matrix product of two matrices. If the sizes of the two input matrices do not match, the function should report errors. The function must be robust and cannot crash when you input something incorrectly.

3.(10 points) Please measure how many milliseconds (or seconds) for the multiplication when the two matrices contain about 200M elements. Hint: You can follow the example at https://en.cppreference.com/w/cpp/chrono/time_point to measure the time.

4.(25 points) Improve the efficiency of your source code. Please report your methods and the improvements. Deep analysis and comparisons are expected in the report.

5.(10 points) Compare your implementation with OpenBLAS https://github.com/xianyi/OpenBLAS Please report the differences on results and speed. Hint: function cblas_sgemm() in OpenBLAS.

6.(5 points) Please host your source code at GitHub.com. you can just put a link in the report. If you do not host your source code at GitHub.com, please upload your source with your report to Blackboard.

7.Your total score will also be affected by your source code quality and report quality.

### Rules:

1.Please submit your assignment report before its deadline. After the deadline (even 1 second), 0 score!

2.Do not code your program unnecessarily complex. Simple is beautiful!

3.Please pay more attention to your code style. After all this is not ACM-ICPC contest. You have enough time to write code with both correct result and good code style. You will get deduction if your code style is terrible. You can read Google C++ Style Guide (http://google.github.io/styleguide/cppguide.html ) or some other guide for code style.
