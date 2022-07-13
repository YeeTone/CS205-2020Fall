# CS205-2020Fall@C/C++
Course: CS205-C/C++ Program Design  
This repository is provided by YeeTone Wang, mainly for the course CS205 in 2020Fall by Prof.Shiqi Yu.       
The repo of Prof.Shiqi Yu about this course: https://github.com/ShiqiYu/CPP      

## SA Announcement

I will be the **SA(Student Assistance)** of C/C++ Program Design in 22Fall Semester.

Lab: Thursday 5-6, 3rd teaching building 509, by Prof.Shiqi Yu.

![image](https://user-images.githubusercontent.com/64548919/178712802-06967e10-a351-4878-aac2-aedd92dd748d.png)

## Comments on this course from the Author
Prof.Shiqi Yu is Excellent in C/C++, and it is highly recommended to take his C/C++ course!  

## (Extremely Important) Some Advice to get an EXCELLENT score in the C/C++ Assignments and Projects of Prof.Shiqu Yu
The importance is ranked from high to low:       
1. Guess and Meet the requirement of Prof.Shiqi Yu;        
2. Writing a high-quality Report so that Prof.Shiqi Yu can be happy to give you a high score;       
3. Presentation Skills (mainly for Project2) so that Prof.Shiqi Yu can give you a better score;        
4. The Code Style: if your code style is AWFUL, then you cannot get a high score of course;        
5. The Functionality of the Source Code;     

## Author Information
Name: YeeTone Wang  

SID: 11910104  

Semester: 2020Fall  

School: Southern University of Science and Technology  

Email: 11910104@mail.sustech.edu.cn  

Photos with Prof.Shiqi Yu:

(left: C/C++ course instructor Prof.Shiqi Yu, right: repo author YeeTone Wang)

（左：C/C++课程主讲老师于仕琪教授，右：仓库作者王奕童）

![IMG_20210525_174552](https://user-images.githubusercontent.com/64548919/122674746-17287c80-d209-11eb-94fb-ca0a7e59c326.jpg)

## Grade Policy of this Course
Lecture Attendance: 5%  

Lab Attendance: 5%  

Assignment: 30%(4 Assignments in total, but 3 are counted into the grade)  

Project1(Individual): 20%  

Project2(Individual): 40%  

## Some Scores and Comments of the Author's Assignments and Projects in this Course  
### Assignment1: BigInteger Multiplication           
**[Score]** 86/100   
**[Comment]** nice try!可以尝试在输入错误时不直接退出，而是继续输入直到输入正确  
  
### Assignment2: Multifunctional Calculator       
**[Score]** 95/100  
**[Comment]** excellent  
  
### Assignment3: Vector Dot Product and its Optimization    
**[Score]** 92/100  
**[Comment]** 函数参数float v1[]是指针，改为引用并不会提升效率。这点差别可完全忽略。io耗时跟计算无关。很好，继续努力。--Shiqi  
  
### Assignment4: Memory Management and Smart Pointer       
**[Score]** 93/100  
**[Comment]** 实现的很好，如果考虑到计算效率会更好。--于仕琪  
  
### Project1: Matrix Multiplication and its Optimization            
**[Score]** 88/100  
**[Comment]** 报告也不是越长越好，本次作业的重点是高效率的实现矩阵乘法。  
  
### Project2: CNN implemented by C/C++     
(Presentation Video on bilibili platform: https://www.bilibili.com/video/BV1aX4y1M7ga)  
**[Score]** 88/100  
**[Comment]** 本project的实现中数据类型为float指针数组，事实上应当定义一个矩阵类用于存储float元素。  
  
### Final Grade for this course: 91/100 -> A-  


## Couse Information
Instructor: Shiqi Yu  
Email: yusq@sustech.edu.cn  
Personal Website: https://faculty.sustech.edu.cn/yusq/  
Online course: https://www.bilibili.com/video/BV1U54y1C7vr?from=search&seid=17998358662680288929   

## Comments to all students from Prof.Shiqi Yu about the Project2
After reading all the source code of Project 2, I cannot help to say something.    
    
The features I expected from your source code and report for Project 2.    
    
1. I hoped you still remember your work on Assignment 4. **I expected you could design a class for the data structure (similar with Matrix in Assignment 4).** The class should have a mechanism for memory management. Do you still remember the default constructor and the assignment operator? Do you still remember how to avoid memory leak and a piece of memory is released twice? Few students did!      
2. If you think a little deeper on how the convolutional operation works, you can find that matrix multiplication can be used for convolutional operations. It can also be easily found by Google/Baidu. Then you can use the tricks learnt in Project 1 and Assignment 3 to optimize the implementation of a convolutional layer. **That is why I designed Project 1 and Assignment 3 for you.** You can use the tricks I introduced to speed up your program. Not so many students used all of them.     
3. Some principles can be found from the examples of the lecture notes. Header files should only be for declarations, and CPP files should be for definitions. What is the difference between declarations and definitions? **Do NOT put all source code into a single file.** It is not beautiful.     
4. **Modular programming** should always be one of the principles for programming in any languages. To avoid global variables. To make a function/class independent. How about your source code?    
5. Are you sure there is not memory leak in your program? If you call the function for face classification in a loop **1M times**, what will happen? Segmentation fault or out of memory?      
6. To finish **a good quality report** is the same important with to write good source code. You can learn how to express yourself and reach your target (a better score) through your report. It is not easy. To write a report is to train you on communication.    
     
Surely most of you will pass the exam of the course. But it is only the first step of your programming career. C and C++ are complex, flexible and powerful. Hope you can continue to improve your programming end enjoy the beauty of programming.    


Regards,

Shiqi

