# 🍽️ Philosophers
A implementation of the classic Dining Philosophers synchronization problem, developed as part of the 42 school curriculum. The project demonstrates concurrent programming concepts using threads, mutexes, processes, and semaphores.

## ⚠️ Notice to 42 Students
This repository serves as a reference implementation. Please note:
- **Do not copy code without understanding**
- Use this as a learning resource
- Implement your own solution to truly grasp the concepts
- Plagiarism violates 42's academic principles

## 🎯 Project Overview
The simulation involves philosophers sitting at a round table, each facing the challenge of coordinating their actions to survive. Between each philosopher is a fork, and they must acquire two forks to eat.

### Life Cycle
Each philosopher cycles through three states:
- **Eating** (requires two forks)
- **Sleeping** (after eating)
- **Thinking** (after sleeping)

The challenge is to prevent philosophers from starving while avoiding deadlocks and ensuring proper resource sharing.

## ✨ Features
- Thread-based simulation (mandatory part)
- Process-based simulation with semaphores (bonus part)
- Precise timestamp logging of philosopher actions
- Deadlock prevention mechanisms
- Starvation monitoring
- Configurable simulation parameters

## 🚀 Getting Started

### Prerequisites
- GCC compiler
- Make
- UNIX-based operating system

### Installation
```bash
# Clone the repository
git clone https://github.com/yourusername/philosophers.git

# Navigate to project directory
cd philosophers

# Compile the program
make
```

### Usage
Run the program with the following arguments:
```bash
./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

#### Parameters
| Parameter | Description | Type |
|-----------|-------------|------|
| number_of_philosophers | Number of philosophers and forks | Required |
| time_to_die | Maximum time (ms) without eating before death | Required |
| time_to_eat | Time (ms) taken to eat | Required |
| time_to_sleep | Time (ms) spent sleeping | Required |
| number_of_times_each_philosopher_must_eat | Optional limit for simulation end | Optional |

#### Example
```bash
./philosophers 5 800 200 200
```
This creates a simulation with:
- 5 philosophers
- Death occurs after 800ms without eating
- Eating takes 200ms
- Sleeping takes 200ms

## 📝 Output Format
The program logs actions with timestamps:
```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```
Where:
- `timestamp_in_ms` is the current time in milliseconds
- `X` is the philosopher number (1 to number_of_philosophers)

## 🔧 Technical Implementation
- Written in C
- Uses POSIX threads and mutexes (mandatory part)
- Uses processes and semaphores (bonus part)
- Implements proper resource cleanup
- Handles edge cases and error conditions
- Ensures accurate timing and synchronization

## 🤝 Contributing
Feel free to submit issues and enhancement requests.

## 📜 License
This project is open source and available under the [MIT License](LICENSE).

---
*Built with focus on concurrent programming principles* 💡
