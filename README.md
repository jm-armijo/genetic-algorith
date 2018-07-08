# genetic-algorithm

This code implementats a Genetic Algorithm to indentify an equation by passing its parameters and expected results.

For instance, when converging, it should return `x1 + x2` if 2, 3 and 5 are passed (because 2 + 3 = 5). 

# Steps

This implementation follow the classical steps for a Genetic Algorithm, this is:

```
Generat initial Population
    |
    V
Calculate fitness  <-----------------------------+
    |                                            |
    V                                            |
Stop? Yes -----> End                             |
    | No                                         |
    V                                            |
Select best individuals                          |
    |                                            |
    V                                            |
Crossover                                        |
    |                                            |
    V                                            |
Mutate                                           |
    |                                            |
    +--------------------------------------------+
``` 

# Classes

There are 5 classes involved in this solution:

- Simulator: intialises the other classes and handles the execution of the algorithm
- Population: represents a group of Indiviual objects
- Individual: represents a single Individual made up of Genes
- Gene: a object that, in combination with other Genes, identifies an Individual.

The first two classes are quite generic and can be reused for another Genetic Algorithm withouth (significant) changes. On the other hand, classes Individual and Gene are ad-hoc for the problem at hand and should be re-implemented when solving different problems. I may add an abstract base classs in the future to better represent this fact.
