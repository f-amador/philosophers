
![assets_task_01jwk7p0t0em59pqyzjqszzwsv_1748697364_img_0](https://github.com/user-attachments/assets/cfe4bf6a-c73d-43ba-96e9-0ea8ae5268d5)

# 🍽️ 42 Philosophers - Multithreaded Dining Simulation

A multithreading solution to the classic Dining Philosophers problem, demonstrating synchronization with mutexes and threads.

## 🌟 Features

| **Category**       | **Details**                                                                 |
|--------------------|-----------------------------------------------------------------------------|
| **Threading**      | Full multithreaded implementation with `pthread`                            |
| **Synchronization**| Mutex-protected shared resources (forks, status, print)                    |
| **Time Management**| Precise microsecond sleeping with `usleep`                                  |
| **Error Handling** | Comprehensive mutex/thread cleanup on exit                                  |
| **Monitoring**     | Dedicated monitor thread for philosopher health checks                      |

---

## 🖥️ System Architecture

### Thread Interaction Flowchart

```mermaid
graph TD
    MAIN[Main Thread] --> INIT[Initialize Mutexes]
    INIT --> SPAWN[Spawn Philosopher Threads]
    SPAWN --> MONITOR[Spawn Monitor Thread]
    
    subgraph Philosopher Threads
        P1[Philosopher 1] -->|Lock Left Fork| MUTEX1[Mutex 1]
        P1 -->|Lock Right Fork| MUTEX2[Mutex 2]
        P2[Philosopher 2] -->|Lock Left Fork| MUTEX2
        P2 -->|Lock Right Fork| MUTEX3[Mutex 3]
        PN[...] -->|Lock Forks| MUTEXN[Mutex N]
    end
    
    MONITOR --> CHECK[Check Meal Times]
    CHECK -->|If starved| KILL[Set Death Flag]
    KILL --> CLEANUP[Trigger Program End]
    
    MAIN -->|Cleanup| JOIN[Join All Threads]
    JOIN --> DESTROY[Destroy Mutexes]
```

### Key Interactions Explained:
1. **Main Thread**  
   - Initializes all mutexes (`fork`, `print`, etc.)
   - Spawns N philosopher threads + 1 monitor thread

2. **Philosopher Threads**  
   - Try to lock **left fork** (current index mutex)
   - Try to lock **right fork** (next index mutex)
   - If both acquired:  
     ```
     EAT → update last_meal → SLEEP → THINK
     ```

3. **Monitor Thread**  
   - Continuously checks `last_meal` times
   - If `(current_time - last_meal) > time_to_die`:  
     - Locks `print` mutex
     - Announces death
     - Sets `dead` flag to terminate program

4. **Termination**  
   - Main thread joins all threads
   - Destroys mutexes in reverse initialization order


## 🏗️ Project Structure

```c
/* Philosopher individual data */
typedef struct s_philo {
    bool            forks;      // Flag indicating if forks are available
    int             n;          // Philosopher's unique ID (1 to n_philo)
    long            lastmeal;   // Timestamp (ms) of last meal start
    int             meals;      // Meals consumed count (for optional meal limit)
    pthread_t       thread;     // Thread handle for this philosopher
    pthread_mutex_t fork;       // Mutex representing a fork (shared with neighbor)
} t_philo;

/* Shared simulation control data */
typedef struct s_vars {
    /* Simulation parameters */
    int             n_philo;    // Total number of philosophers
    long            tteat;      // Time (ms) required to eat
    long            ttdie;      // Time (ms) before starving
    long            ttsleep;    // Time (ms) spent sleeping
    long            status;     // Program state flag (running/ended)
    
    /* Meal tracking */
    int             nmeals;     // Optional meal limit (-1 if infinite)
    int             mealcount;  // Global meals eaten counter
    
    /* Utility fields */
    int             i;          // Loop counter
    long            stime;      // Simulation start timestamp (ms)
    bool            dead;       // Death flag (true if any philosopher died)
    
    /* Mutexes */
    pthread_mutex_t var;        // Protects shared variables
    pthread_mutex_t print;      // Synchronizes output printing
    pthread_mutex_t inc;        // Protects meal counters
    pthread_mutex_t time;       // Protects time-sensitive operations
    pthread_mutex_t m_philo;    // Protects philosopher array access
    
    /* Threads */
    pthread_t       monitor;    // Health check thread
    t_philo         **philo;    // Array of philosopher pointers
} t_vars;
```

## 🚀 Quick Start

### Prerequisites
- GCC compiler
- Make
- pthread library

### Compilation
```bash
make
```

### Usage
```bash
./philo <number_of_philos> <time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_meals]
```

**Example:**
```bash
./philo 5 800 200 200 7  # 5 philos, die after 800ms, eat for 200ms, etc.
```

## 🧠 The Dining Problem

Simulates philosophers who:
1. Alternate between thinking and eating
2. Must share forks (resources) with neighbors
3. Can starve if they don't eat in time
4. May enter deadlock if improperly synchronized

## 🔧 Key Functions

| **Function**         | **Purpose**                                  |
|----------------------|---------------------------------------------|
| `init_philo()`       | Initialize philosopher threads               |
| `init_mutexs()`      | Create mutexes for shared resources         |
| `*monitor()`         | Health-check thread                         |
| `eating_msg()`       | Thread-safe status printing                 |
| `ft_usleep()`        | Precision microsecond sleeping              |
| `get_time()`         | Timestamp in milliseconds                   |

## 🎨 Sample Output

```
[timestamp_ms] Philosopher 1 has taken a fork
[timestamp_ms] Philosopher 2 is eating
[timestamp_ms] Philosopher 3 is sleeping
[timestamp_ms] Philosopher 4 died 💀
```

## 🛠️ Error Handling

The program gracefully handles:
- Invalid input values
- Mutex initialization failures
- Thread creation errors
- Resource leaks (full cleanup on exit)

## 📚 Resources

1. [Dining Philosophers Problem (Wikipedia)](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
2. [pthread Manual](https://man7.org/linux/man-pages/man7/pthreads.7.html)
3. [Mutex Locking Patterns](https://riptutorial.com/c/example/31615/introduction-to-mutexes)

---
