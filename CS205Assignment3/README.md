# CS205Assignment3
CS205: C/C++ Program Design

### Requirements:

1.(50 points) Please implement a function which can compute the dot product of two vectors. The type of vector elements is float (not double). The function must be robust and cannot crash when you input something incorrectly. The definition is:
dot_product = v1[0]*v2[0]+v1[1]*v2[1]+…+v1[n-1]*v2[n-1] Hint: You can use float * v1 = new float[n]; to create a vector with n elements (4*n bytes).

2.(15 points) Please measure how many milliseconds (or seconds) for vectors which have
more than 200M elements. Hint: You can follow the example at https://en.cppreference.com/w/cpp/chrono/time_point to measure the time.

3.(20 points) Improve the efficiency of your source code. Can it be 10 times faster than your first version? Please report your methods and the improvements.

4.(15 points) Compare your implementation of dot product with OpenBLAS https://github.com/xianyi/OpenBLAS Please report if the two implementations return the same dot product if the input vectors are very long, and which implementation is faster and how faster it is. Hint: function cblas_sdot() in OpenBLAS.

5.You total score will also be affected by your source code quality and report quality.

6.To host your source code at GitHub.com is an option. You are strongly recommended to create a repository at GitHub.com to hold your source code for this assignment. If so, you can just put a link in the report of the assignment, and do not need to upload the source code to Blackboard. If you do not host your source code at GitHub.com, please upload your source with your report to Blackboard.

### Rules:

1.Please submit your assignment report before its deadline. After the deadline (even 1 second), 0 score!
2.Please pay more attention to your code style. After all this is not ACM-ICPC contest. You have enough time to write code with both correct result and good code style. You will get deduction if your code style is terrible. You can read Google C++ Style Guide (http://google.github.io/styleguide/cppguide.html ) or some other guide for code style.
