This program will read numbers from a separate txt file and use those numbers in 4
different child processes, which are created by using “fork()”. Each child will then find all
prime numbers from 0 up to a given number from the txt file. When the process is
completed, each child will display a message stating the task is done and how long it took
to finish the task. After all child processes finish their tasks, the parent process then
displays the final message and, as an extra, we created a leaderboard of the top 3 fastest
child processes. 
