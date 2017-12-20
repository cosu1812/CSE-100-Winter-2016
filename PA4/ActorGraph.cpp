/*
 * Name: Connie Su
 * Assignment: PA4
 * 03/04/16
 *
 * ActorGraph.cpp
 * Author: Adrian Guthals
 * Date: 2/24/2015
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */
 
#include "ActorGraph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <queue>
#include <stack>
#include <algorithm>
#define END_YEAR 2015

using namespace std;

/*
 * Create node for actor
 */ 
ActorNode::ActorNode(string name, int dist = 0, ActorNode* prev = 0, 
                     string prevEdge = "", bool isVisted = false):name(name),
		                                                  dist(dist),
								  prev(prev),
						           prevEdge(prevEdge),
							 isVisited(isVisited)
		                                                          {}

/*
 * Get name of actor
 */ 
string ActorNode::getNameA(){
   return name;
}

/*
 * get list of movies actor was in
 */ 
vector<string> ActorNode::getMovies(){
   return movies;
}

/*
 * insert movies to list
 */ 
void ActorNode::insertMovie(string movie){
   movies.push_back(movie);
}

/*
 * get distance between actors
 */ 
int ActorNode::getDist(){
   return dist;
}

/*
 * set distance between actors
 */ 
void ActorNode::setDist(int newDist){
   dist = newDist;
}

/*
 * get previous actor
 */
ActorNode* ActorNode::getPrev(){
   return prev;
}

/*
 * set previous actor to current actor
 */ 
void ActorNode::setPrev(ActorNode* prevActor){
   prev = prevActor;
}

/*
 * get status of node if visited or not
 */ 
bool ActorNode::getVisited(){
   return isVisited;
}

/*
 * set if node is visited or not
 */ 
void ActorNode::setVisited(bool newVisited){
   isVisited = newVisited;
}
/*
 * get previous edge
 */ 
string ActorNode::getPrevEdge(){
   return prevEdge;
}

/*
 * name edge that connects the two actors
 */ 
void ActorNode::setPrevEdge(string setEdge){
   prevEdge = setEdge;
}

/*
 * Create edges
 */ 
MovieEdge::MovieEdge(string name, int year):name(name), year(year){}

/*
 * get movie's name
 */
string MovieEdge::getNameM(){
   return name;
}

/*
 * get movie's year
 */ 
int MovieEdge::getYear(){
   return year;
}

/*
 * get movie's cast
 */ 
vector<ActorNode*> MovieEdge::getActors(){
   return cast;
}

/*
 * add actor to movie's cast
 */ 
void MovieEdge::insertActor(ActorNode* actor){
   cast.push_back(actor);
}

/* 
 * sort ActorNodes by weight in graph
 */ 
bool Compare::operator()(pair<ActorNode*, int> a1, pair<ActorNode*, int> a2){
      if (a1.second == a2.second) 
         return a1.first->getNameA() > a2.first->getNameA();
      return a1.second > a2.second;
}

/*
 * sort MovieEdges by year
 */ 
bool Compare::operator()(pair<MovieEdge*, int> m1, pair<MovieEdge*, int> m2){
      if (m1.second == m2.second) 
         return m1.first->getNameM() > m2.first->getNameM();
      return m1.second < m2.second;
}

/*
 * Creates ActorGraph
 */ 
ActorGraph::ActorGraph(){}

/*
 * Destructor for ActorGraph
 */ 
ActorGraph::~ActorGraph(){
   actors.clear();
   movies.clear();
}

/*
 * load movies and actor from files and add them to graph
 */ 
bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges)
{
  
  // Initialize the file stream
  ifstream infile(in_filename);

  bool have_header = false;
  
  // keep reading lines until the end of file is reached
  while (infile)
  {
    string s;
    
    // get the next line
    if (!getline( infile, s )) break;
    
    if (!have_header)
    {
      // skip the header
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> record;

    while (ss)
    {
      string next;
      
      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;
      
      record.push_back( next );
    }
    
    if (record.size() != 3)
    {
      // we should have exactly 3 columns
      continue;
    }
    
    string actor_name(record[0]);
    string movie_title(record[1]);
    int movie_year = stoi(record[2]);

    // use to check if actor and movie is in the graph
    unordered_map<string, ActorNode*>::const_iterator gotA = actors.find(actor_name);
    unordered_map<string, MovieEdge*>::const_iterator gotM = movies.find(movie_title);
        
    // add or update nodes and edges
    ActorNode* aNode;
    MovieEdge* mEdge;
    if (gotA == actors.end()){
       aNode = new ActorNode(actor_name);
       actors.insert(make_pair(actor_name, aNode));
    }   

    else{
       aNode = gotA->second;
    }
    
    if (gotM == movies.end()){
       mEdge = new MovieEdge(movie_title, movie_year);
       movies.insert(make_pair(movie_title, mEdge));
    }

    else{
       mEdge = gotM->second;
    }

    // add to graph
    mEdge->insertActor(aNode);
    aNode->insertMovie(movie_title);

  }
 
  // closes file
  if (!infile.eof())
  {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  infile.close();
  
  return true;
}

/*
 * Load info of actors and movies to create graph 
 */ 
bool ActorConGraph::loadFromFile(const char* in_filename, bool use_bfs){
  // Initialize the file stream
  ifstream infile(in_filename);

  bool have_header = false;
  
  // keep reading lines until the end of file is reached
  while (infile)
  {
    string s;
    
    // get the next line
    if (!getline( infile, s )) break;
    
    if (!have_header)
    {
      // skip the header
      have_header = true;
      continue;
    }

    istringstream ss( s );
    vector <string> record;

    while (ss)
    {
      string next;
      
      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( ss, next, '\t' )) break;
      
      record.push_back( next );
    }
    
    if (record.size() != 3)
    {
      // we should have exactly 3 columns
      continue;
    }
    
    string actor_name(record[0]);
    string movie_title(record[1]);
    int movie_year = stoi(record[2]);

    // use check if movie and actor are in graph
    unordered_map<string, ActorNode*>::const_iterator gotA = actors.find(actor_name);
    unordered_map<string, MovieEdge*>::const_iterator gotM = movies.find(movie_title);
    
    // add or update nodes and edges
    ActorNode* aNode;
    MovieEdge* mEdge;
    if (gotA == actors.end()){
       aNode = new ActorNode(actor_name);
       actors.insert(make_pair(actor_name, aNode));
    }   

    else{
       aNode = gotA->second;
    }
    
    if (gotM == movies.end()){
       mEdge = new MovieEdge(movie_title, movie_year);
       movies.insert(make_pair(movie_title, mEdge));
       
       // sort movies as it get added
       yearMovies.push(make_pair(mEdge, movie_year));
    }

    else{
       mEdge = gotM->second;
    }
    
    // add to graph
    mEdge->insertActor(aNode);
    aNode->insertMovie(movie_title);
  }
 
  // close file
  if (!infile.eof())
  {
    cerr << "Failed to read " << in_filename << "!\n";
    return false;
  }
  infile.close();
  
  return true;

}

/*
 * Destructor for ActorConGraph
 */ 
ActorConGraph::~ActorConGraph(){
   actors.clear();
   movies.clear();
}

