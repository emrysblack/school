/***********************************************************************
 * Program:
 *    Exploration 5, Awareness
 *    Brother Neff, CS237
 *
 * Author:
 *    Brady Field
 *
 * Summary:
 *    Check for Cliques and Anti-Cliques.
 *
 * NOTE: this code is highly UNcommented -- this is deliberate.
 *
 ***********************************************************************/

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <set>
using namespace std;

typedef unsigned int uint;

class Node
{
private:
   uint mNumber;

public:
   Node(uint inNumber)
   {
      mNumber = inNumber;
   }

   uint getNumber() const { return mNumber; }
};

ostream& operator<<(ostream& os, const Node& n)
{
   os << "Node[" << n.getNumber() << "]";
   return os;
}

class Edge
{
private:
   uint mFirst;
   uint mSecond;

public:
   Edge(uint first, uint second)
   {
      mFirst = first;
      mSecond = second;
   }

   uint first() const { return mFirst; }
   uint second() const { return mSecond; }
   bool operator ==(const Edge & rhs) const // added to simplify code elsewhere and make it more elegant
   { return mFirst == rhs.mFirst && mSecond == rhs.mSecond
         || mFirst == rhs.mSecond && mSecond == rhs.mFirst;}
};

ostream& operator<<(ostream& os, const Edge& e)
{
   os << "Edge[" << e.first() << ", " << e.second() << "]";
   return os;
}

class Graph
{
private:
   set<uint> mVertices;
   vector<Node> mNodes;
   vector<Edge> mEdges;
   map<uint, vector<Edge> > mAdjacencies;

public:
   const set<uint>& vertices() const { return mVertices; }

   const vector<Node>& nodes() const { return mNodes; }

   const vector<Edge>& edges() const { return mEdges; }

   Graph(const char* filename)
   {
      readFrom(filename);
   }

   virtual ~Graph()
   {
   }

   void readFrom(const char* filename)
   {
      uint v1;
      uint v2;
      ifstream file(filename, ios_base::in);
      if (file)
      {
         while (true)
         {
            file >> v1 >> v2;

            if (file.eof() || file.fail())
            {
               break;
            }
            addEdge(v1, v2);
         }
         file.close();
         addNodes();
      }
   }

   void addEdge(uint v1, uint v2)
   {
      Edge e(v1, v2);
      addEdge(e);
      addVertices(e);

      if (mAdjacencies.find(v1) != mAdjacencies.end())
      {
          vector<Edge> * adj = &mAdjacencies.find(v1)->second;
          adj->push_back(e);
      }
      else
      {
          vector<Edge> adj; adj.push_back(e);
          mAdjacencies.insert(pair<uint, vector<Edge> >(v1, adj));
      }
      if (mAdjacencies.find(v2) != mAdjacencies.end())
      {
          vector<Edge> * adj = &mAdjacencies.find(v2)->second;
          adj->push_back(e);
      }
      else
      {
          vector<Edge> adj; adj.push_back(e);
          mAdjacencies.insert(pair<uint, vector<Edge> >(v2, adj));
      }
   }

   void addEdge(const Edge& e)
   {
      mEdges.push_back(e);
   }

   void addVertices(const Edge& e)
   {
      mVertices.insert(e.first());
      mVertices.insert(e.second());
   }

   void addNodes()
   {
      addNodes(mVertices);
   }

   void addNodes(set<uint> vertices)
   {
      for (set<uint>::const_iterator it = vertices.begin();
           it != vertices.end(); it++)
      {
         uint v = *it;
         mNodes.push_back(Node(v));
      }
   }

   void addVertices(Graph& g)
   {
      addVertices(g.vertices());
   }

   void addVertices(set<uint> vertices)
   {
      for (set<uint>::const_iterator it = vertices.begin();
           it != vertices.end(); it++)
      {
         mVertices.insert(*it);
      }
   }

   bool contains(uint v) const
   {
      return (mVertices.find(v) != mVertices.end());
   }
   
   bool containsVertices(vector<uint>& vertices)
   {
      vector<uint>::const_iterator it = vertices.begin();
      while (it != vertices.end())
      {
         if (! contains(*it))
         {
            return false;
         }
         it++;
      }
      return true;
   }

   bool containsEdge(uint v1, uint v2)
   {
      // use adjacencies member variable to avoid redundant checks
      Edge e(v1,v2);
      vector<Edge>::const_iterator it = mAdjacencies[v1].begin();
      // go through all connections for current node
      for (; it != mAdjacencies[v1].end(); it++)
      {
         if (*it == e) // if edge is found, inform the caller function
         {
            return true;
         }
      }
      return false;
   }
};

ostream& operator<<(ostream& os, const Graph& g)
{
   os << "Graph[\n";

   vector<Edge> edges = g.edges();

   os << edges.size() << " edges:";
   for (vector<Edge>::const_iterator it = edges.begin();
        it != edges.end(); it++)
   {
      os << "\n\t" << *it;
   }

   vector<Node> nodes = g.nodes();
   int numNodes = nodes.size();

   os << "\n" << numNodes << " nodes:";

   for (vector<Node>::const_iterator it = nodes.begin();
        it != nodes.end(); it++)
   {
      os << "\n\t" << *it;
   }

   os << "\n]";

   return os;
}

/*************************************************************************
 * runs through a vector of vertices and checks for edges
 *************************************************************************/
bool checkClique(Graph & g, bool anti, vector<uint>& vertices)
{
   int size = vertices.size();
   for (int i = 0; i < size; i++)
   {
      for (int j = i + 1; j < size; j++)
      {
         if (anti == g.containsEdge(vertices[i], vertices[j]))
         {
            return false;
         }
      }
   }
   return true;
}

/*************************************************************************
 * The point of entry to a world of graph exploration.
 *************************************************************************/
bool checkCliqueOrAntiClique(const char * fileName, bool anti,
                             vector<uint>& vertices)
{
   Graph g(fileName);
   assert(g.containsVertices(vertices));
   return checkClique(g, anti, vertices);
}

/*************************************************************************
 * How to use this program to be implemented here.
 *************************************************************************/
void usage(const char* programName)
{
   cout << "usage: awareness filename\n e.g. awareness example.txt\n";
}

/*************************************************************************
 * What was learned, more granularly laid out via these 8 functions.
 *************************************************************************/
void howImasteredTheBasicTerminologyAndOperationsOfLogicSetsFunctionsAndGraphs()
{
   cout << "In short, I studied. I read about it and tried using the various things\n"
        << "talked about. Until one get one's hands dirty, that person will never become\n"
        << "as intimately familiar with concepts such as sets, functions, or graphs as one\n"
        << "needs to be to do anything useful with it. This is true of most concepts in life.\n\n";
}

void howIdemonstrateLogicalReasoningThroughSolvingProblems()
{
   cout << "I remember running into this principle while solving a Sudoku puzzle\n"
        << "as a matter of fact. I was new to them and I got stuck. I then proceeded\n"
        << "to stare at the page for about an hour before my brain came up with a new\n"
        << "logical way of looking at things. This applies with Discrete Mathematics as\n"
        << "well since the whole concept is to look at things in correct, yet novel ways.\n\n";
}

void howIinterpretedTheMeaningOfMathematicalStatementsInTheContextOfRealWorldApplications()
{
   cout << "Mathematical statements are a way for us to represent real-world ideas in a way\n"
        << "that a computer can understand. In other words they give us an algorithm or\n"
        << "an approach to solving problems that we encounter. This is not constrained to\n"
        << "computers. Take a simple example of sorting. When I was younger there was only one way\n"
        << "for me to sort things. Now I can select a sort based on criteria of what is to be sorted.\n"
        << "Then I can sort things much faster than using the one way for everything. I can do this\n"
        << "because I understand the Mathematical reasoning behind it.\n\n";
}

void howIdiscernedBetweenEffectiveAndIneffectiveApproachesToProblemSolving()
{
   cout << "Understanding the question or problem is the key to this one.\n"
        << "If one is taking a test, one must carefully read the question\n"
        << "before that person can select an appropriate answer. In problem\n"
        << "solving it's the same way. One must understand what the problem is\n"
        << "and what it means before they can select an appropriate solution.\n"
        << "One cannot \"Brute Force\" one's way through life or problems.\n\n";
}

void howIsolvedProblemsUsingLimitedOrConstrainedResources()
{
   cout << "It is important to take an inventory of the available tools for any problem.\n"
        << "Once this has been done often we find that we already have what we need.\n"
        << "Take this exploration for example. Once I figured out where the program was\n"
        << "spending most of its time running, I looked at the tools at my disposal. I\n"
        << "found a member variable that saved me great time in the completion of this code.\n"
        << "I didn't need to include another library to try to speed things up. I simply needed\n"
        << "to use what had been given to me more elegantly.\n\n";
}

void howIsynthesizedNewProblemSolvingConceptsByPuttingOldConceptsTogetherInNovelWays()
{
   cout << "Many times focussing on what one knows will lead that person to learn a new way\n"
        << "of thinking about things in a better way. Take Mathematics for instance. If one can learn\n"
        << "to do addition, that person has the ground work to learn multiplication and anything else\n"
        << "in mathematics because everything is an abstraction of addition.\n Similarly, in Pascal's\n"
        << "Triangle we find that the doing a choose function will give us appropriate numbers. For many\n"
        << "this may seem confusing or unrelated at first, but upon closer inspection the reasoning becomes clear.\n"
        << "Mathematics show up everywhere and follow patterns. By the same flip of the coin problem solving\n"
        << "can be built off of old methods until one arrives at a new avenue of understanding.\n\n";
}

void howIrecognizedTheRelativeImportanceOfDifferentElementsOfAComputerScienceProblem()
{
   cout << "One has to be able to step back and look at the big picture. If one can\n"
        << "determine the role of a program, one can determine the approach that should\n"
        << "be taken. For example, is this program supposed to run as quickly as possible,\n"
        << "or does readability and extensibility take precedence for this particular program?\n"
        << "With such questions answered, one can determine how to approach the problem.\n\n";
}

void howIknowHowDiscreteMathematicsAppliesToAllPartsOfComputerScience()
{
   cout << "Discrete Mathematics has proven that it's not strictly a hard science, but a mind-set.\n"
        << "When one runs up against a problem, sometimes the best solution is to change one's\n"
        << "perspective and tackle the problem in a completely different way.\n"
        << "It is this manner of thinking that formed the basis of the tools that we use\n"
        << "to address our needs as software developers. Everything from Data Types to Algorithms\n"
        << "are brought about using the principles from Discrete Mathematics.\n\n";
}
