/*
 * File: pathfinder.cpp
 * Assignment: PA4
 * Name: Connie Su
 * Date: 03/05/16
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

#define END_YEAR 2015
#define ARGS 5
#define PATH_TYPE 2
#define PAIR_FILE 3
#define OUT_FILE 4

using namespace std;

/*
 * prints path of starting actor to target actor 
 */ 
void printPath(ActorGraph& graph, ActorNode*& start, ActorNode*& end, 
               ofstream& out){
   stack<string> path;
   ActorNode* pathNode = end;
   while(pathNode != start){
      string actor = pathNode->getNameA();
      string movie = pathNode->getPrevEdge();
      path.push(actor);
      path.push(movie);
      pathNode = pathNode->getPrev();
   }

   path.push(pathNode->getNameA());
   bool isActor = true;
   while (!path.empty()){
      string toWrite = path.top();
      path.pop();
	     
      if (isActor && path.empty()) out << "(" << toWrite << ")" << "\n";
		     
      else if (isActor){
         out << "(" << toWrite << ")" << "--";
         isActor = false;
      }
		     
      else{
         int year = graph.movies[toWrite]->getYear();
         out << "[" << toWrite << "#@" << year << "]" << "-->";
         isActor = true;
      }
   }  
   return;
}

/*
 * Unweighted graph to find shortest path from one actor to another
 */ 
void unweightedPath(ActorGraph& graph, ActorNode*& start, ActorNode*& end, 
                    ofstream& out){
   queue<ActorNode*> explore;
   start->setDist(0);
   explore.push(start);

   while(!explore.empty()){
      ActorNode* next = explore.front();
      explore.pop();
      vector<string> edgesM = next->getMovies();
      for (int index = 0; index < edgesM.size(); index++){
         auto edge = graph.movies.find(edgesM[index]);
         vector<ActorNode*> nodesA = edge->second->getActors();
         for (int mark = 0; mark < nodesA.size(); mark++){
	    ActorNode* neighbor = nodesA[mark];
            if (neighbor->getDist() == numeric_limits<int>::max()){
	       neighbor->setDist(next->getDist() + 1);
	       neighbor->setPrev(next);
	       neighbor->setPrevEdge(edgesM[index]);
	       if (end == neighbor){
	          printPath(graph, start, end, out);
	          return;
	       }  
               explore.push(neighbor);
	    }
	 }
      }
   }
   return;
}

/*
 * Weighted graph to find path between actors by taking into account the years
 */ 
void weightedPath(ActorGraph& graph, ActorNode*& start, ActorNode*& end, 
                  ofstream& out){
   // shows
   priority_queue<pair<ActorNode*, int>, vector<pair<ActorNode*, int>>, Compare>
      actorQueue;
   start->setDist(0);
   actorQueue.push(make_pair(start, 0));

   while (!actorQueue.empty()){
      auto nextPair = actorQueue.top();
      actorQueue.pop();
      ActorNode* next = nextPair.first;
      
      if (!next->getVisited()){
         next->setVisited(true);
      
         if (end->getVisited()){
	    printPath(graph, start, end, out);
	    return;
	 }   
      
         vector<string> edgesM = next->getMovies();
         for (int index = 0; index< edgesM.size(); index++){
            auto edge = graph.movies.find(edgesM[index]);
            vector<ActorNode*> nodesA = edge->second->getActors();
            for (int mark = 0; mark < nodesA.size(); mark++){
	       ActorNode* neighbor = nodesA[mark];
	       int pathWeight = next->getDist() + 1 + 
	                        (END_YEAR - edge->second->getYear());
               if (pathWeight < neighbor->getDist()){
	          neighbor->setPrev(next);
	          neighbor->setDist(pathWeight);
	          neighbor->setPrevEdge(edgesM[index]); 
	          actorQueue.push(make_pair(neighbor, pathWeight));
	       }   
            }
         }
      }
   }  
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
 * Use to find a path between two actors using weighted or unweighted nodes
 */ 
int main(int argc, char * argv[]){
   // check if arguments are valid
   if (argc != ARGS) return -1;
   
   if ((strcmp(argv[PATH_TYPE], "u") != 0) && 
       (strcmp(argv[PATH_TYPE], "w") != 0)){
      cout << "wrong parameter " << "'" << argv[PATH_TYPE] << "'" 
           << ", must be u or w" << "\n";
      return -1; 
   }   
   
   if (!checkFile(argv[1])){
      cout << "Failed to read " << argv[1] << "!" << "\n";
      return -1;
   }   
   
   if (!checkFile(argv[PAIR_FILE])){
      cout << "Failed to read " << argv[PAIR_FILE] << "!" << "\n";
      return -1;
   }   

   // open files
   ifstream pairs;
   pairs.open(argv[PAIR_FILE], ios::in);
   
   ofstream out;
   out.open(argv[OUT_FILE], ios::out);

   // use to check if need to use weighted graph or unweighted
   bool weight = false;
   if (argv[PATH_TYPE] == "w") weight = true;

   // create graph
   ActorGraph graph;
   graph.loadFromFile(argv[1], weight);
   
   // use to see if movie and actor is in graph and to iterate
   unordered_map<string, ActorNode*>::const_iterator gotA;
   unordered_map<string, MovieEdge*>::const_iterator gotM;
      
   // use to skip header   
   bool have_header = false;
   
   // write header
   out << "(actor)--[movie#@year]-->(actor)--..." << "\n";

   // goes through pairs of actor and find a paht between them
   while(pairs){
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

      if (record.size() != PATH_TYPE) continue;

      string startActor(record[0]);
      string endActor(record[1]);

      // reset member variables to search through graph again
      for (gotA = graph.actors.begin(); gotA != graph.actors.end(); ++gotA){
         ActorNode* actor = gotA->second;
         actor->setDist(numeric_limits<int>::max());
         actor->setVisited(false);	 
      }

      // returns if can't find actors
      if (graph.actors[startActor] == NULL || graph.actors[endActor] == NULL) 
         return -1;

      // get actors
      ActorNode* start = graph.actors[startActor];
      ActorNode* end = graph.actors[endActor];
      
      // use unweighted graph
      if (strcmp(argv[PATH_TYPE], "u") == 0) 
         unweightedPath(graph, start, end, out);

      // use weighted graph
      else if (strcmp(argv[PATH_TYPE], "w") == 0) 
         weightedPath(graph, start, end, out); 
   }

   // close files
   pairs.close();
   out.close();
   return 0;
}
