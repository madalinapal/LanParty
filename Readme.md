# Project title: LAN PARTY

## Description

This project implements a tournament management system designed to handle tasks such as team registration, match scheduling, and result processing. The program leverages various data structures, including singly linked lists, queues, stacks, binary search trees (BST), and AVL trees, to efficiently organize and process data.

## Features
### General workflow
* Reads requirements from a configuration file (c.in) and input data from a data file (d.in).
* Executes tasks based on the requirements using a menu-driven approach with conditional statements.

### Requirement 1: Team Registration
* Defines a Team structure that includes the number of players, team name, and a list of players.
* Players are defined using the Player structure, which contains the first name, last name, and score.
* Teams are added to the start of a singly linked list.
  
### Requirement 2: Team Filtering
* Calculates the smallest power of 2 less than or equal to the total number of teams.
* Removes teams with the lowest average score until the number of teams equals this power of 2.
  
### Requirement 3: Match Simulation
* Implements a queue to schedule matches and stacks for winners and losers.
* Simulates rounds of matches until the winner is determined and extracts the top 8 teams for ranking.

### Requirement 4: Creating a Binary Search Tree (BST)
* Inserts the top 8 teams into a BST.
* Displays the ranking in descending order based on scores.

### Requirement 5: Creating an AVL Tree
* Creates a balanced AVL tree using nodes from the BST.
* Displays nodes at a specific level of the AVL tree.

## Memory Management
* All resources (lists, queues, stacks, trees) are released at the end of execution to prevent memory leaks.

### Data Structures Used
* Singly Linked List for managing teams.
* Queues for scheduling matches.
* Stacks for separating winners and losers.
* Binary Search Tree (BST) for team ranking.
* AVL Tree for a balanced ranking system.

### Usage Instructions
1. Place the input file c.in in the main directory.
2. Compile and run the program.
3. Results will be saved in output files specific to each requirement.

## Technical Requirements
* Programming Language: C
* Input File: c.in d.in 
* Output: Specific files for each requirement.
