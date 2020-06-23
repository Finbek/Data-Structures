#include <iostream>
#include <string>
#include <stdexcept>
#include <queue>
#include <list>
#include <vector>
#include <map>
#include <limits>
#include "AdjacencyListDirectedGraph.h"
#include "FlightMap.h"
#include <unordered_map>

double FlightMap::calcRouteDistance(const list<string> route) {
	//We will check the three conditions( existence of the airports and the edge between them), then find an edge between aitports and add distance to the answer through loop
	double answer=0;
	for(list<string>::const_iterator iter = route.begin(); iter != route.end();)
		{FlightGraph::Vertex v1, v2;
		if (!findAirport(v1, *iter)) {
  			  throw runtime_error(*iter + " does not exist.");
		 }
 	        if (!findAirport(v2, *(++iter))) {
   			 throw runtime_error(*(iter) + " does not exist.");
 		 }
 	        if (!v1.isOutgoingTo(v2)) {
   			 throw runtime_error(*v1 + " does not connect to " + *v2 + ".");

   		 }
		FlightGraph::Edge edge = v1.outgoingEdge(v2);
		answer+=*(edge);
	}
	return answer;
	}


list<string> FlightMap::findShortestRoute(const string &airport1, const string &airport2) {
	if(!isAirportExist(airport1))
		throw runtime_error(airport1 + " does not exist.");
	if(!isAirportExist(airport2))
                throw runtime_error(airport2 + " does not exist.");
	FlightGraph::Vertex src, dst;
	FlightGraph::VertexList vlist = flight_graph.vertices();
	src=airport_db.at(airport1);
	dst=airport_db.at(airport2);
	int a = std::numeric_limits<int>::max();
	typedef std::pair<int, string> cur;//closest graph and distance
	priority_queue<cur, vector<cur>, greater<cur>> unvisited;//unvisited
	map<string, cur> D;
	for (FlightGraph::VertexItor iter = vlist.begin(); iter != vlist.end(); iter) 
        {
		D[**iter].first=a;       
        }

	unvisited.push(std::make_pair(0, *src));
	D[*src].first=0;
	bool check=true;
	while(!unvisited.empty())
	{
		FlightGraph::Vertex tmp = airport_db.at(unvisited.top().second);
		unvisited.pop();
		FlightGraph::EdgeList elist = tmp.outgoingEdges();
		for(FlightGraph::EdgeItor iter = elist.begin(); iter != elist.end(); ++iter)
		{
      				int weight =**iter;
				 if (D[*(iter->dest())].first > D[*tmp].first + weight)
           			 {
					D[*(iter->dest())].first = D[*tmp].first + weight;
					D[*(iter->dest())].second = *tmp;
               				unvisited.push(make_pair(D[*(iter->dest())].first, *(iter->dest())));
			   	 }
				if(*(iter->dest())==*dst)
				{
					check=false;
				}
		
					
   		 }
	}

	list<string> ans;
	string dest=*dst;
	if(!check)
	{	while(dest==(*src))
			{	
				ans.push_front(dest);
				dest=D[dest].second;
			}
	}
	ans.push_front(*src);
	return ans;
	
  }
	
			
	

void FlightMap::printAllShortestRoutes(const string &airport) {
	if(!isAirportExist(airport))
                throw runtime_error(airport + " does not exist.");
	FlightGraph::VertexList vlist = flight_graph.vertices();
	for(FlightGraph::VertexItor iter = vlist.begin(); iter != vlist.end(); ++iter)
	{	if(**iter!=airport)
		{
			list<string> route=findShortestRoute(airport, **iter);
			if(route.size()>0)
				{
					 printRoute(route);
					 cout << "  (Distance = " << calcRouteDistance(route) << ")" << endl;
				}
		}
	}
}
