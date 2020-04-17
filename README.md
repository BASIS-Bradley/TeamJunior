Josh and Shariq, add stuff wherever I wrote stuff in // // and then delete what is in the // //(delete this line after too)

# Graphs

Throughout this project our team implemented the graph data structure consisting of series of points that share relation to one another, represented by edges. We also implemented many functions utilizing the properties of graphs that explored through this project.

## Prerequisites

In order to run the Markov Clustering algorithm the Eigen 3 Library, in which version 3.3.7 is the latest stable version. This can be downloaded from [Eigen Main Page](http://eigen.tuxfamily.org/index.php?title=Main_Page). //Josh if you want you can add more about the library itself//This is the only necessary library that must be downloaded in order to run our code.

## [Data](TeamJunior/data/)

All the data we used were various types of graphs such as directed and weighted, undirected and unweighted, etc. We imported all our data from [SNAP Database](https://snap.stanford.edu/data/). //Shariq add what data we tested, like why it is and what we can get from running oure functions on it//

## Code

Our code is made up of various hpp files:

#### [edge.hpp](TeamJunior/edge.hpp)
  *//Shariq add the functionality//

#### [node.hpp](TeamJunior/node.hpp)
  *Most basic object for each point in the graph containing the number of the node
  
#### [point.hpp](TeamJunior/point.hpp)
  *Object representing each point of the graph that creates a node as well as retrieves it and its weight
  
#### [graph.hpp](TeamJunior/graph.hpp)
  *Object that creates and prints a collection of the points in the graph interrelated by edges as well as retrieves its properties
  
#### [analyser.hpp](TeamJunior/analyser.hpp)
  *Contains all but one of the analysis funtions that can be run on the graphs, which writes the results to text files 
  
#### [mcl.hpp](TeamJunior/mcl.hpp)
  *Contains our Markov Clustering Algorithm
  
#### [main.hpp](TeamJunior/main.hpp)
  *Contains the method to create and import graphs as well as run funtions on those graphs

## Running the Code

Create an executable of our [main.hpp file](TeamJunior/main.hpp) by typing and then run that executable. This will write the results of the analysis functions on the graphs into multiple text files.

## Authors

Shariq Butt, Sreevatsa Nukala, Joshua Tensuan
