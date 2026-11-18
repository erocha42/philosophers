*This project has been created as part of the 42 curriculum by erocha--.*

# Philosophers

## Description

**Philosophers** is a system programming project focused on thread management and process synchronization. The project is based on the famous "Dining Philosophers Problem," a classic illustration of resource allocation and synchronization issues in computer science.

### The Challenge
- Philosophers are sitting at a round table with a bowl of spaghetti.
- They can only do one of three things at a time: **eat**, **sleep**, or **think**.
- There are as many forks as there are philosophers, but a philosopher needs **two forks** to eat.
- The goal is to prevent philosophers from starving while avoiding **deadlocks** (mutual blocking) and **data races** (memory access conflicts).

## Instructions

### Compilation
The project uses a standard `Makefile` for compilation. From the project root, run:
```bash
make
```
This will generate the `philo` executable.

### Execution
The program accepts the following arguments:
```bash
./philo [nbr_philos] [time_to_die] [time_to_eat] [time_to_sleep] [nbr_meals_opt]
```

| Argument | Description |
| :--- | :--- |
| `number_of_philosophers` | The number of philosophers and forks. |
| `time_to_die` | Time (ms) after which a philosopher dies if they haven't eaten. |
| `time_to_eat` | The time (ms) it takes to eat. |
| `time_to_sleep` | The time (ms) spent sleeping. |
| `nbr_meals_opt` | (Optional) Number of meals before the simulation stops. |

**Example:**
```bash
./philo 5 800 200 200
```

## Technical Choices

- **Multi-threading**: Each philosopher runs in their own thread (`pthread_t`).
- **Mutex Synchronization**: Each fork is represented by a `pthread_mutex_t`. Additional mutexes (`print_lock`, `meal_lock`, `end_lock`) protect shared resources.
- **Deadlock Avoidance**: An **asymmetry** system based on the philosopher's index is used (odd-indexed philosophers pick up the right fork first, while even-indexed philosophers pick up the left fork first) to break the circular wait.
- **Monitoring (Reaper)**: A separate monitoring thread continuously checks the health of each philosopher and the global state of the simulation to ensure an immediate stop upon death or completion of required meals.
- **Timing Robustness**: Thinking delays (`think_action`) are calculated dynamically to avoid CPU overhead while maintaining high responsiveness to the `time_to_die` threshold.

## Resources

### Classic References
- **POSIX Threads Documentation**: [pthreads(7) — Linux manual page](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- **The Dining Philosophers Problem**: [Dijkstra's Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- **Data Race Detection**: [ThreadSanitizer (TSan) Manual](https://github.com/google/sanitizers/wiki/ThreadSanitizerCppManual)

### AI Usage Disclosure
Artificial Intelligence was used as a technical collaboration tool for the following tasks:
- **Structural Audit**: Validating mutex locking logic to ensure the absence of Data Races.
- **Reaper Optimization**: Assistance in implementing a non-blocking and precise monitoring routine.
- **Edge Case Handling**: Discussion regarding the single philosopher case (N=1) and the protection of `usleep` delays.