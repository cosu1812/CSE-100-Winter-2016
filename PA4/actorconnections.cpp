/**
 * File: actorconnections.cpp
 * Name: Connie Su
 * Assignment: PA4
 * 03/08/16
 */ 
#include "ActorGraph.hpp"
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>
#include <limits>
#include <stack>
#include <string.h>
#include <algorithm>

#define GRAPH_TYPE 4
#define ARGS 5
#define PAIR_FILE 2
#define OUT_FILE 3

/*
 * Find the year where the two actors become connected
 */ 
void BFSMode(ActorConGraph& graph, ActorNode*& start, ActorNode*& end, 
             ofstream& out){
   // use to get back sorted movies
   priority_queue<pair<MovieEdge*, int>, vector<pair<MovieEdge*, int>>, 
                  Compare> returnEdges;

   // use to traverse graph
   queue<ActorNode*> explore;
   start->setDist(0);
   explore.push(start);
   
   // get earliest year
   auto moviePair = graph.yearMovies.top();
   int year = moviePair.second;

   // traverse through graph by adding earliest movies
   while (!graph.yearMovies.empty()){    
      // removes movies from current year
      while(year == moviePair.second){
         auto movie = moviePair.first;
	 returnEdges.push(moviePair);
         if (!graph.yearMovies.empty()){
	    graph.yearMovies.pop();
	    moviePair = graph.yearMovies.top();
	 }   
      }
      moviePair = graph.yearMovies.top();
      year = moviePair.second;

      // use BFS to get to target actor while ignoring movies from other years
      while(!explore.empty()){
         ActorNode* next = explore.front();
         vector<string> edgesM = next->getMovies();
         for (int index = 0; index < edgesM.size(); index++){
            auto edge = graph.movies.find(edgesM[index]);
	    if (edge->second->getYear() > year) continue;
            explore.pop();
            vector<ActorNode*> nodesA = edge->second->getActors();
            for (int mark = 0; mark < nodesA.size(); mark++){
	       ActorNode* neighbor = nodesA[mark];
               if (neighbor->getDist() == numeric_limits<int>::max()){
	          neighbor->setDist(next->getDist() + 1);
	          neighbor->setPrev(next);
	          neighbor->setPrevEdge(edgesM[index]);
	          
		  // if found target actor traverse up the graph to get earliest
		  // year
		  if (end == neighbor){
	             ActorNode* pathNode = end;
		     auto minMov = graph.movies.find(end->getPrevEdge());
		     int minYear = minMov->second->getYear();
		     while(pathNode != start){
		        auto nextMov = graph.movies.find(pathNode->getPrevEdge());
			int mYear = nextMov->second->getYear();
		        if (mYear < minYear) minYear = mYear;
			pathNode = pathNode->getPrev();
		     }
		     out << start->getNameA() << "\t" << end->getNameA() << 
		          "\t" << minYear << "\n";
	             return;
	          }  
                  explore.push(neighbor);
	       }
	    } 
         }
      }
   }  

   // restore the priority queue with popped movies
   while (!returnEdges.empty()){
      auto edge = returnEdges.top();
      returnEdges.pop();
      graph.yearMovies.push(edge);
   }

   // writes to file if can't find path to target
   out << start->getNameA() << "\t" << end->getNameA() << "\t" << "9999" 
       << "\n";
   return;
}


/*
 * check if file is empty
 */ 
bool checkFile(const char* filename){
   ifstream file(filename);
   
   //Check if input file was actually opened
   if(!file.is_open()) return false;

   //Check for empty file
   file.seekg(0, ios_base::end); 
   unsigned int len = file.tellg();
	
   if(len==0) return false;

   file.close();

   return true;
}

/*
 * Use to create graph and find actor connections based on actor pairs
 */ 
int main(int argc, char * argv[]){
   // check if we have valid arguments
   if (argc != ARGS && argc != GRAPH_TYPE) return -1;
   
   if (!checkFile(argv[1])){
      cout << "Failed to read " << argv[1] << "!" << "\n";
      return -1;
   }  
  
   if (!checkFile(argv[2])){
      cout << "Failed to read " << argv[1] << "!" << "\n";
      return -1;
   }  

   bool use_bfs = true;
   if (argc == GRAPH_TYPE){
      use_bfs = false;
   }

   else if ((strcmp(argv[GRAPH_TYPE], "bfs") != 0) && 
       (strcmp(argv[GRAPH_TYPE], "unfind") != 0)){
      cout << "wrong parameter " << "'" << argv[GRAPH_TYPE] << "'" 
           << ", must be bfs or unfind" << "\n";
      return -1; 
   }
 
   // open files
   ifstream pairs;
   pairs.open(argv[PAIR_FILE], ios::in);
   
   ofstream out;
   out.open(argv[OUT_FILE], ios::out);
   
   // create graph
   ActorConGraph graph;
   graph.loadFromFile(argv[1], use_bfs);

   // use to check if we have actor
   unordered_map<string, ActorNode*>::const_iterator gotA;
   unordered_map<string, MovieEdge*>::const_iterator gotM;
      
   // skips header in file
   bool have_header = false;
   
   // write header
   out << "Actor1\tActor2\tYear" << "\n";

   // get actor connection based on actor pairs
   while(pairs){
      // get actor pairs
      string s;
      if (!getline(pairs, s)) break;

      if (!have_header){
         have_header = true;
	 continue;
      }

      istringstream ss(s);
      vector<string> record;

      while (ss){
         string next;
	 if (!getline(ss, next, '\t')) break;
	 record.push_back(next);
      }

      if (record.size() != PAIR_FILE) continue;

      string startActor(record[0]);
      string endActor(record[1]);
      
      // reset variables for searching through graph again
      for (gotA = graph.actors.begin(); gotA != graph.actors.end(); ++gotA){
         ActorNode* actor = gotA->second;
         actor->setDist(numeric_limits<int>::max());
         actor->setVisited(false);	 
      }

      if (graph.actors[startActor] == NULL || 
          graph.actors[endActor] == NULL) 
         return -1;

      ActorNode* start = graph.actors[startActor];
      ActorNode* end = graph.actors[endActor];
      
      // run bfs on graph to find actor connection
      if (strcmp(argv[GRAPH_TYPE], "bfs") == 0) 
         BFSMode(graph, start, end, out);

    //  else if (argc == GRAPH_TYPE || (strcmp(argv[GRAPH_TYPE], "unionfind") == 0)) 
      //   weightedPath(graph, start, end, out); 
   }
   pairs.close();
   out.close();
   return 0;
 
}
