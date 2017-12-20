/*
 * Assignment:PA4
 * Name: Connie Su
 * Date: 03/04/16
 *
 * ActorGraph.hpp
 * Author: Adrian Guthals
 * Date: 2/24/2015
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_HPP
#define ACTORGRAPH_HPP

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <queue>

// Maybe include some data structures here

using namespace std;

/*
 * Nodes for graph
 */ 
class ActorNode{
public:
   ActorNode(string name, int dist, ActorNode* prev, string prevEdge, 
             bool isVisted);

   vector<string> getMovies();
   string getNameA();
   void insertMovie(string movie);
   int getDist();
   void setDist(int newDist);
   ActorNode* getPrev();
   void setPrev(ActorNode* prevActor);
   bool getVisited();
   void setVisited(bool newVisited);
   string getPrevEdge();
   void setPrevEdge(string setEdge);

private:
   string name;
   int dist;
   ActorNode* prev;
   string prevEdge;
   bool isVisited;
   vector<string> movies;
};

/*
 * Edges for graph
 */ 
class MovieEdge{
public:
   MovieEdge(string name, int year);
   string getNameM();
   int getYear();
   vector<ActorNode*> getActors();
   void insertActor(ActorNode* actor);

private:
   string name;
   int year;
   vector<ActorNode*> cast;
};

/*
 * Use in priority queues
 */ 
class Compare{
public:
   bool operator()(pair<ActorNode*, int> a1, pair<ActorNode*, int> a2);
   bool operator()(pair<MovieEdge*, int> m1, pair<MovieEdge*, int> m2);

};

/*
 * Graph use to connect actors with movies
 */ 
class ActorGraph {
protected:
  
  // Maybe add class data structure(s) here

public:
   unordered_map<string, ActorNode*> actors;
   unordered_map<string, MovieEdge*> movies;

   ActorGraph();
   ~ActorGraph();

  // Maybe add some more methods here
  
  /** You can modify this method definition as you wish
   *
   * Load the graph from a tab-delimited file of actor->movie relationships.
   *
   * in_filename - input filename
   * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
   *
   * return true if file was loaded sucessfully, false otherwise
   */
  bool loadFromFile(const char* in_filename, bool use_weighted_edges);
  
};

/*
 * Graph use to find earliest year that two actors are connected
 */ 
class ActorConGraph{
public:
   priority_queue<pair<MovieEdge*, int>, vector<pair<MovieEdge*, int>>, 
                       Compare> yearMovies;
   unordered_map<string, ActorNode*> actors;
   unordered_map<string, MovieEdge*> movies;
 
   bool loadFromFile(const char* in_filename, bool use_bfs);
   ~ActorConGraph();
   
};

#endif // ACTORGRAPH_HPP
