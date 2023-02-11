# ASSIGNMENT 5

- First line of input contains two integers no.of.students(N) and no.of.washing machines. Next N lines contains three integers arriving time, washing time, waiting time of a student.

- Array of structs is used to store the input, and it is sorted by arrival time(students with same arrival time are sorted by index).

- N threads are created(1 thread corresponding 1 student) and M semaphores represents M washing machines.

- Whenever a student arrives a thread is created, and in thread function if there is an empty washing machine the student starts washing and semaphore value is decreased by 1. If there is no empty washing machine the student waits. If waiting time exceeds patience of the student the student leaves without washing.

- dis_stu gives the no.of.students left without washing their clothes.

- If the percentage of students left without washing is greater than or equal to 25 then print "yes", else "no".

## SAMPLE INPUT

5 2  
6 3 5  
3 4 3  
6 5 2  
2 9 6  
8 5 2  

## SAMPLE OUTPUT

Student 4 arrives  
Student 4 starts washing  
Student 2 arrives  
Student 2 starts washing  
Student 1 arrives  
Student 3 arrives  
Student 2 leaves after washing  
Student 1 starts washing  
Student 5 arrives  
Student 3 leaves without washing  
Student 1 leaves after washing  
Student 5 starts washing  
Student 4 leaves after washing  
Student 5 leaves after washing  
1  
5  
No
