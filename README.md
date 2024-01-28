# ➡︎ PHILOSOPHERS ⬅︎

### Summary
The dining philosophers problem is a classic computer science scenario illustrating concurrency challenges. It involves five philosophers sitting around a table, alternating between thinking and eating. Each philosopher needs two adjacent forks to eat, and the problem arises when they attempt to pick up forks simultaneously, risking deadlock.

The solution requires synchronization mechanisms to prevent deadlock and starvation. Whether implemented with independent processes or threads within a single process, techniques like semaphores, monitors, or mutex are used for proper mutual exclusion and synchronization. The goal is to ensure philosophers share forks safely and efficiently.

### Usage
1) Compile the code & Execute
   ```makefile
   make
   ```
2) Compile the programa & execute:
   ```bash
   ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep (number_of_times_each_philosopher_must_eat)
   ```
   > Example: ./philo 5 600 500 400
   
### Info
◼️ Language: C
<br>
◼️ Compile: Makefile
<br>
◼️ Concepts: Mutex, Race Condition, Thread (Hilos), Cerrojos (Locks), Deadlock (Bloqueo Mutuo), <br>
&nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Locks, Concurrency, Paralelism, Process, Mutex (Mutual Exclusion).

### Diagram Image
🚧 Working on update image 🚧
![IMG MODEL](https://github.com/brayans22/Philosophers/assets/90729742/6a60f67b-c04c-456f-9de4-ebd81967c598)
