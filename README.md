# Traveling Salesman Problem With Draft Limits

This repository contains implementations to solve the Traveling Salesman Problem With Draft Limits (TSP-DL).

1. The first implementation is a Tabu Search algorithm written in C. The graphs are represented as adjacency matrices.

## Problem Description

The Traveling Salesman Problem With Draft Limits is a variant of the classic Traveling Salesman Problem (TSP) that incorporates the concept of draft limits. In this problem, a ship needs to visit a set of ports exactly once and return to the starting one while adhering to draft limits. Each port is associated with a draft limit, which represents ------- can travel from that port before returning to it.

The objective is to find the shortest tour that satisfies the draft limits for each port. This problem is NP-hard, making it challenging to find an optimal solution for larger instances. Tabu Search is a heuristic algorithm commonly used to solve TSP and its variants efficiently.

## Instances

All the instances solved by our codes are available on:  <http://jgr.no/tspdl>.

Also, you can use our instances, that are already ready to use with our implementation.

The instances names are on the following format ```name#p_#d_#n``` where:

+ name: Name of the subset of instances.
+ \#p: Number of ports on the instances.
+ \#d: % of ports with restrictive draft limit
+ \#n: Id of the instance.

Possible combinations of name and #p are:

+ burma14
+ ulysses16, ulysses22
+ gr17, gr21, gr48
+ fri26
+ bayg29

\#d can assume values 10, 25, 50;
and \#n varies from 1 to 10.

There are other instances with more than one hundred ports, but they require special treatment to be addressed. So, for now, they won't be addressed in this repository.

## Implementation

### Tabu Search Algorithm

The Tabu Search algorithm is a metaheuristic that iteratively explores the solution space while maintaining a memory structure to avoid revisiting previously explored solutions. It uses various mechanisms to guide the search towards better solutions.

The C implementation in this repository provides a basic yet efficient Tabu Search algorithm for solving the TSP-DL. It incorporates features such as neighborhood exploration, tabu list management, and aspiration criteria to find high-quality solutions within a reasonable amount of time.

## Requirements for Development in C

To work on or modify this C implementation, you will need the following software tools and resources:

1. **C Compiler**: You'll need a C compiler to build and run the C code. [GCC](https://gcc.gnu.org/) is a popular and widely used compiler for C programming and is available on various platforms.

2. **Code Editor or IDE**: A code editor or integrated development environment (IDE) is essential for writing and editing the C source code. Some popular choices include [Visual Studio Code](https://code.visualstudio.com/), [Eclipse](https://www.eclipse.org/), and [Code::Blocks](http://www.codeblocks.org/).

3. **Git (optional)**: If you want to clone and manage the repository, you can use [Git](https://git-scm.com/), a version control system. Git allows you to track changes, collaborate with others, and maintain a history of your code.

## Usage

To use the Tabu Search implementation for solving the TSP-DL, follow these steps:

1. Clone the repository:

   ```shell
   git clone https://github.com/bruno-duart/TSPDL.git
   ```

2. Compile the C code:

    ```shell
    gcc file_name.c -o output
    ```

3. Run the executable with an input file:

    ```shell
    ./output input.txt
    ```

    Make sure to provide an input file with the necessary information, including the cities, distances between them, and draft limits.

## Input Format

The input file should be in a specific format, typically containing the following information:

- Number of ports.
- Adjacency matrix representing distances between ports.
- Demand of each port.
- Draft limits for each ports.
- Extra - If you plan to use the instances provided by our repository, take note that we provided the optimal cost of each instance

### Example input file

The below example is from ```burma14_10_1``` instance.

```txt
14

1 153 510 706 966 581 455 70 160 372 157 567 342 398 
153 1 422 664 997 598 507 197 311 479 310 581 417 376 
510 422 1 289 744 390 437 491 645 880 618 374 455 211 
706 664 289 1 491 265 410 664 804 1070 768 259 499 310 
966 997 744 491 1 400 514 902 990 1261 947 418 635 636 
581 598 390 265 400 1 168 522 634 910 593 19 284 239 
455 507 437 410 514 168 1 389 482 757 439 163 124 232 
70 197 491 664 902 522 389 1 154 406 133 508 273 355 
160 311 645 804 990 634 482 154 1 276 43 623 358 498 
372 479 880 1070 1261 910 757 406 276 1 318 898 633 761 
157 310 618 768 947 593 439 133 43 318 1 582 315 464 
567 581 374 259 418 19 163 508 623 898 582 1 275 221 
342 417 455 499 635 284 124 273 358 633 315 275 1 247 
398 376 211 310 636 239 232 355 498 761 464 221 247 1 

0 1 1 1 1 1 1 1 1 1 1 1 1 1 

13 13 13 13 13 12 13 13 13 13 13 13 1 13 

3416
```

## License

This project is licensed under the GPL-3.0 License. Feel free to use, modify, and distribute it according to the terms of the license.

## Acknowledgments

This implementation is inspired by research in the field of combinatorial optimization.

## Contribution

Contributions to this repository are welcome. If you have improvements or additional algorithms for solving TSP-DL or related problems, please create a pull request.

Happy solving! 🌍🧳🗺️
