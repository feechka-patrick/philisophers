# philosophers
RUN : make
./philo [number of philo] [time_to_die] [time_to_eat] [time_to_sleep] [(optional) number_of_times_each_philosopher_must_eat]]
<br>
TEST : 
  - Test with ./philo 1 800 200 200, the philosopher should not eat and should die
  - Test with ./philo 5 800 200 200, no one should die
  - Test with ./philo 5 800 200 200 7, no one should die and the simulation should stop when all the philosopher has eaten atleast 7 times each
  - Test with ./philo 4 410 200 200, no one should die
  - Test with ./philo 4 310 200 100, a philosopher should die
