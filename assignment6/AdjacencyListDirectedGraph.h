#ifndef ASSIGNMENT6_ADJACENCYLISTDIRECTEDGRAPH_H
#define ASSIGNMENT6_ADJACENCYLISTDIRECTEDGRAPH_H

#include <iostream>
#include <list>
#include <stdexcept>

using namespace std;

template<typename V, typename E>
class AdjacencyListDirectedGraph {

  // ---------------------------------------------------------------------------------
  // You *cannot* add any additional public or private member functions in this class.
  // You *cannot* add any additional public or private member variables in this class.
  // ---------------------------------------------------------------------------------

public:

  // Define public data types of Vertex and Edge and the associated iterators.

  class Vertex;
  class Edge;

  typedef list<Vertex> VertexList;
  typedef list<Edge> EdgeList;
  typedef typename VertexList::iterator VertexItor;
  typedef typename EdgeList::iterator EdgeItor;
  typedef typename VertexList::const_iterator VertexConstItor;
  typedef typename EdgeList::const_iterator EdgeConstItor;

private:

  // Define private data types of VertexObject and EdgeObject and the associated iterators.
  // The type of IncidenceEdgesList and its iterator are defined as well.

  struct VertexObject;
  struct EdgeObject;

  typedef list<VertexObject> VertexObjectList;
  typedef list<EdgeObject> EdgeObjectList;
  typedef list<EdgeList> IncidenceEdgesList;

  typedef typename VertexObjectList::iterator VertexObjectItor;
  typedef typename EdgeObjectList::iterator EdgeObjectItor;
  typedef typename IncidenceEdgesList::iterator IncidenceEdgesItor;

  /*
   * VertexObject stores data of a vertex.
   */
  struct VertexObject {
    V elt;                             // the element stored at this vertex
    VertexObjectItor pos;              // position in vertex_collection
    IncidenceEdgesItor inc_edges_pos;  // position in inc_edges_collection

    VertexObject(V _elt) : elt(_elt) {}  // pos and inc_edges_pos are initially "NULL".
  };

  /*
   * EdgeObject stores data of an edge.
   */
  struct EdgeObject {
    E elt;                          // the element stored at this edge
    Vertex origin_vertex;           // the vertex at the origin
    Vertex dest_vertex;             // the vertex at the destination
    EdgeObjectItor pos;             // position in edge_collection
    EdgeItor origin_inc_edges_pos;  // position in an edge list in inc_edges_collection
    EdgeItor dest_inc_edges_pos;    // position in an edge list in inc_edges_collection

    EdgeObject(const Vertex& v, const Vertex& w, E _elt) : origin_vertex(v), dest_vertex(w), elt(_elt) {} // pos origin_inc_edges_pos, and dest_inc_edges_pos are initially "NULL".
  };

  // ---------------------------------------------------------------------------------
  // This class should contain the following three member variables only:
  // vertex_collection, edge_collection, and inc_edges_collection
  // You are not allowed to define any other member variables (public or private).
  // ---------------------------------------------------------------------------------

  VertexObjectList vertex_collection;
  EdgeObjectList edge_collection;
  IncidenceEdgesList inc_edges_collection;

public:

  /*
   * Vertex is a position class of a vertex in AdjacencyListDirectedGraph.
   * Internally, a vertex is a pointer to an entry in vertex_collection.
   */
  class Vertex {

    VertexObject *v_obj;

  public:

    /*
     * The constructor of Vertex. This subsumes the default constructor.
     *
     * v - a pointer to a VertexObject
     */
    Vertex(VertexObject* v = NULL) : v_obj(v) {}


    /*
     * Return the element stored at this vertex.
     */
    V& operator*() const {
	return v_obj->elt; //Just return the stored element.
    }

    /*
     * Return a list of edges incident to this vertex.
     */
    EdgeList incidentEdges() const {
	return *(v_obj->inc_edges_pos);//Easy return of the stored incident edges list 
    }

    /*
     * Check whether a vertex is adjacent to this vertex.
     * This means whether there is an edge that has this vertex
     * and the given vertex as the end points.
     *
     * v - the given vertex
     */
    bool isAdjacentTo(const Vertex& v) const {
	EdgeList& edgeListObj = *v_obj->inc_edges_pos;
	EdgeList& edgeListV = *v.v_obj->inc_edges_pos;
	int counter;//We will compare edges, to avoid seg. fault, we will take counter as least of the list size
	EdgeList comp;//Edges to compare, the least edge list among two
	if(edgeListObj.size()>edgeListV.size())
	{
		counter=edgeListV.size();
		comp=edgeListV;
	}
	else
	{
		counter=edgeListObj.size();
		comp=edgeListObj;
	}
	for(EdgeItor i = comp.begin(); i != comp.end(); i++)//Among the comp edges, if we find an edge satisfying the conintion, we return true, otherwise it will give false at the end of the function
	{
		if(((*i).origin()==(*this) && (*i).dest()==v) || (((*i).origin()==v && (*i).dest()==(*this))))
			{return true;
			}
	}
	return false;

    
}

    /*
     * C 	heck whether there is a directed edge connecting this vertex to the given vertex.
     *
     * v - the given vertex
     */
    bool isOutgoingTo(const Vertex& v) const {
	//This check is alomost the same as the isAdjacentTo, but now we need strictly v-destination, this-origin
	EdgeList& edges = *(v_obj->inc_edges_pos);
	for(EdgeItor i = edges.begin(); i != edges.end(); i++){//Consider all edges
		{
			if(((*i).origin()==(*this)) && ((*i).dest()==v))//Described above strict condition
				return true;
		}
	return false;//Otherwise
    }
}
    /*
     * Return a directed edge connecting this vertex to the given vertex.
     * If the directed edge does not exist, throw an exception.
     *
     * v - the given vertex
     * Return the directed edge connecting this vertex to the given vertex.
     */
    Edge outgoingEdge(const Vertex& v) const {
	//We will check the edges of this vertex as we did in bool isOutgoingTo and now retrun satisfying;
	EdgeList& edges = *v_obj->inc_edges_pos;
        for(EdgeItor i = edges.begin(); i != edges.end(); i++)//Consider all edges
                {
                        if((*i).origin()==(*this) && (*i).dest()==v)//Described above strict condition
                                return *i;
                }
        throw runtime_error("NO SUCH EDGE");//Otherwise
    }

    /*
     * Return the set of all directed edges connecting this vertex to any vertex.
     */


    EdgeList outgoingEdges() const {
	//Same as the outgoingEdge, but we will create a list and push_back new edges there;
	EdgeList outGoing;
	EdgeList& edges = *v_obj->inc_edges_pos;

        for(EdgeItor i = edges.begin(); i != edges.end(); i++)//Consider all edges
                {
                        if((*i).origin()==*(this))//Described above strict condition
                                outGoing.push_back(*i);
                }
	return outGoing;
    }
    /*
     * Check whether this vertex is the same as the given vertex
     *
     * v - the given vertex
     * Return true if this vertex is the same as the given vertex
     */
    bool operator==(const Vertex& v) const {
	if(v.v_obj==v_obj)//If the v_obj of both vertices is the same, they are equal
		return true;
	else 
		return false;
    }

    /*
     * Declare friend to AdjacencyListDirectedGraph so that
     * AdjacencyListDirectedGraph can access to the private
     * member variables of this class.
     */
    friend class AdjacencyListDirectedGraph<V,E>;
  };

  /*
   * Edge is a position class of an edge in AdjacencyListDirectedGraph.
   * Internally, an edge is a pointer to an entry in edge_collection.
   */
  class Edge {

    EdgeObject *e_obj;

  public:

    /*
     * The constructor of Edge. This subsumes the default constructor.
     *
     * v - a pointer to a EdgeObject
     */
    Edge(EdgeObject* e = NULL) : e_obj(e) {}

    /*
     * Return the element stored at this edge.
     */
    E& operator*() const {
	return e_obj->elt;//Return stored in e_obj element
    }

    /*
     * Return the vertices of this directed edge.
     * The first element of the vertex list is the vertex of the origin.
     * The second element of the vertex list is the vertex of the destination.
     */
    VertexList endVertices() const {
	VertexList endV;//Create empty list
	endV.push_back(e_obj->origin_vertex);//First push origin
	endV.push_back(e_obj->dest_vertex);//Then destination
	return endV;
    }

    /*
     * Return the vertex of this edge that is different from the given vertex.
     * If the given vertex is origin, return destination.
     * If the given vertex is destination, return origin.
     * If the given vertex is neither origin nor destination, throw an exception.
     *
     * v - the given vertex
     * Return the other vertex of this edge
     */
    Vertex opposite(const Vertex& v) const {
	if(v==e_obj->origin_vertex)
		return e_obj->dest_vertex;//If v is origin, then return destination
	else if(v==e_obj->dest_vertex)
		return e_obj->origin_vertex;//if v is destination, return origin
	else 
		throw runtime_error("NO SUCH VERTEX IN THE EDGE");//Exception
    }

    /*
     * Check whether a given edge is adjacent to this edge.
     * This means that whether the given edge and this edge
     * shared a vertex.
     *
     * edge - the given edge
     * Return true if the given edge is adjacent to this edge.
     */
    bool isAdjacentTo(const Edge& edge) const {
	//We can check two vertices of the edge, is one of  them incident to our edge
	return ((edge.isIncidentOn(e_obj->origin_vertex)) || (edge.isIncidentOn(e_obj->dest_vertex))); 
    }

    /*
     * Check whether a vertex is incident on this edge.
     * This means that whether the vertex is a vertex of this edge.
     *
     * v - the given vertex
     * Return true if the given vertex is incident to this edge.
     */
    bool isIncidentOn(const Vertex& v) const {
	if(e_obj->origin_vertex==v || e_obj->dest_vertex==v)//Direct check of the two options if they are equal to the v
		return true;
	else
		return false;
    }

    /*
     * Return the vertex at the origin of this edge.
     */
    Vertex origin() const {
	return e_obj->origin_vertex;//return origin vertex
    }

    /*
     * Return the vertex at the destination of this edge.
     */
    Vertex dest() const {
	return e_obj->dest_vertex;//return destination vertex
    }

    /*
     * Return true if this is a directed edge.
     * In this class, it should always return true.
     */
    bool isDirected() const {
	return true;//alsways true
    }

    /*
     * Check whether this edge is the same as the given edge.
     *
     * edge - the given edge
     * Return true if this edge is the same as the given edge.
     */
    bool operator==(const Edge& edge) const {
	return edge.e_obj==e_obj;//compare e_obj of two
    }

    /*
     * Declare friend to AdjacencyListDirectedGraph so that
     * AdjacencyListDirectedGraph can access to the private
     * member variables of this class.
     */
    friend class AdjacencyListDirectedGraph<V,E>;
  };


public:

  /*
   * Return the list of vertices in this graph.
   */

  VertexList vertices() {
	//they are almost the same as vertex_collection, but in vertex_collection we have VertexObject, we need to make them Vertices;
	VertexList answer;
	for(VertexObjectItor i = vertex_collection.begin(); i != vertex_collection.end(); i++)
	{
		Vertex v;
		v.v_obj=&(*i);
		answer.push_back(v);	//Here we will make vertex each VertexObject and add to answer
	}
	return answer; 
  
}
  /*
   * Return the list of edges in this graph.
   */
  EdgeList edges() {
	//Same as VertexList, but with edges
	EdgeList answer;
	for(EdgeObjectItor i = edge_collection.begin(); i != edge_collection.end();i++){
		Edge ed;
		ed.e_obj=&(*i);
		answer.push_back(ed);
	}
	return answer;
  }

  /*
   * Add a new vertex to this graph.
   *
   * x - the element to be stored in the new vertex.
   * Return the newly created vertex.
   */
  Vertex insertVertex(const V& x) {
	//Fist we need to create VertexObject for the new element;
	VertexObject verObj = VertexObject(x);
	vertex_collection.push_back(verObj);//Adding to the collection
	VertexObjectItor i  = vertex_collection.end();
	i--;//the pos of the new VertexObject
	VertexObject& newV=(*i);
	newV.pos=i;//Correcting pos;
	inc_edges_collection.push_back(EdgeList());//Adding to the collection, NULL 
	IncidenceEdgesItor ie = inc_edges_collection.end();
	ie--;//Position in the inc_edges_collection
	newV.inc_edges_pos=ie;//correcting pos
	Vertex v; //Creation of vertex
	v.v_obj=&newV;
	return v;// returning vertex
  }

  /*
   * Add a new edge to this graph. Throw an exception
   * if an edge has already existed between v and w.
   *
   * v - the vertex at the origin
   * w - the vertex at the destination
   * x - the element to be stored in the new edge.
   * Return the newly created edge.
   */

  Edge insertDirectedEdge(const Vertex& v, const Vertex& w, E x) {
	if(!v.isOutgoingTo(w))//Checking existance, if there is no, will do almost the same as insertVertex(), no need to explain similar analogue 
	{	EdgeObject newEdOb = EdgeObject(v, w, x);//creating new edge_object
		edge_collection.push_back(newEdOb);// adding to the edge_collect
		EdgeObjectItor i= edge_collection.end();
		i--;//pos of the edj_object
		EdgeObject &newEdObj=(*i);
		newEdObj.pos = i;//correcting pos

		VertexObject& vObj = *(v.v_obj);
		EdgeList & v_edges =    *(vObj.inc_edges_pos); //List of edges incident to the v
		VertexObject& W = *(w.v_obj);
		EdgeList & w_edges =	*(W.inc_edges_pos); //List of edges incident to the w

		Edge newEdge; 
		newEdge.e_obj=&newEdObj;//creating new edge for inserting
		w_edges.push_back(newEdge);//adding new edge to the incdient list for v
		v_edges.push_back(newEdge);//adding new edge to the incident list for w
		newEdObj.origin_inc_edges_pos=--(v_edges.end());//Correcting the origin_incident list position
		newEdObj.dest_inc_edges_pos=--(w_edges.end());//correcting the destination_ incident list position;
		return newEdge;
		
	}	
	else 
		throw runtime_error("Already exists");
  }
  /*
   * Remove a vertex from this graph. All edges that contain
   * v as one of their vertices are also removed.
   *
   * v - a vertex
   */
  void eraseVertex(const Vertex& v) {
	EdgeList& edgeList = *(*v.v_obj).inc_edges_pos;//list of edges which need to be deleted
	  for(EdgeItor i = edgeList.begin(); i != edgeList.end();){//deleting associated edges
		eraseEdge(*i);
	}
	vertex_collection.erase((*v.v_obj).pos);// erasing vertex from vertex_collection
	delete &v;//deleting the vertex itse;f
  }

  /*
   * Remove an edge from this graph.
   *
   * e - an edge
   */
  void eraseEdge(const Edge& e) {
	EdgeObject& edObj=*(e.e_obj);
	(*(edObj.origin_vertex.v_obj->inc_edges_pos)).erase(edObj.origin_inc_edges_pos);//Deleting origin pos form the collection
        (*(edObj.dest_vertex.v_obj->inc_edges_pos)).erase(edObj.dest_inc_edges_pos);//Deleting destination pos from the collection
        edge_collection.erase(edObj.pos);//deleting edge from the collection
        delete &e;//deleting edge e
  }

};


#endif //ASSIGNMENT6_ADJACENCYLISTDIRECTEDGRAPH_H
