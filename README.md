# philosophers
make : gcc *.c -pthread -o philo\n
run : ./philo 

test : 
  - Test with ./philo 1 800 200 200, the philosopher should not eat and should die
  - Test with ./philo 5 800 200 200, no one should die
  - Test with ./philo 5 800 200 200 7, no one should die and the simulation should 
  stop when all the philosopher has eaten atleast 7 times each
  - Test with ./philo 4 410 200 200, no one should die
  - Test with ./philo 4 310 200 100, a philosopher should die
