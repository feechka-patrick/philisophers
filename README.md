# philosophers
RUN : make
<br>
./philo [number of philo] [time_to_die] [time_to_eat] [time_to_sleep] [(optional) number_of_times_each_philosopher_must_eat]]
<br>
<br>

ПОСТАНОВКА ЗАДАЧИ: [wiki]

TEST : 
  - Test with ./philo 1 800 200 200, the philosopher should not eat and should die
  - Test with ./philo 5 800 200 200, no one should die
  - Test with ./philo 5 800 200 200 7, no one should die and the simulation should stop when all the philosopher has eaten atleast 7 times each
  - Test with ./philo 4 410 200 200, no one should die
  - Test with ./philo 4 310 200 100, a philosopher should die

[wiki] : https://ru.wikipedia.org/wiki/%D0%97%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_%D0%BE%D0%B1_%D0%BE%D0%B1%D0%B5%D0%B4%D0%B0%D1%8E%D1%89%D0%B8%D1%85_%D1%84%D0%B8%D0%BB%D0%BE%D1%81%D0%BE%D1%84%D0%B0%D1%85#
