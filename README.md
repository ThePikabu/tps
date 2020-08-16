# Travelling salesman problem

My solution of [travelling salesman problem](https://en.wikipedia.org/wiki/Travelling_salesman_problem) using simulated annealing method.

## How it works

The program inputs a file in the format: in the first line, enter number n - the number of cities, then in the n lines - the coordinates of
the cities written as two numbers. (see **data** folder for more examples). 

Next, the algorithm tries to reduce the initial route length (which is chosen randomly). The difference from gradient descent is that the system 
has a certain "temperature", which determines the probability of going to a less optimal state with a longer route length (This is necessary so that the algorithm
can "get out" of the local minimum with some probability).

As a result, the algorithm outputs two numbers - the total length it came to (if it converged, or if a given number of iterations was passed) and the minimum length
for all time (in case the algorithm from the" smaller "local minimum turned out to be" larger")
