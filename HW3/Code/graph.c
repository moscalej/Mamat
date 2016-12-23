


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "graph.h"
#include "set.h"
#include "list.h"


typedef struct _Graph 
{
	int number_of_vertex;
	PSet vertex ;
	PSet edge;
	
	

}Graph, *PGraph;

Bool edgeComp(PElem id_vertex, PElem edge1)
{
	Edge * tenp1;
	int  tenp2;
	tenp1 = (Edge*)edge1;
	tenp2 = (int)id_vertex;
	if (tenp1->nodeA==tenp2 || tenp1->nodeB ==tenp2)
	{
		return TRUE;
	}
	return FALSE;
}

Bool vertexComp(PElem id_vertex, PElem vertex)
{
	Vertex * tenp1;
	int  tenp2;
	tenp1 = (Vertex*)vertex;
	tenp2 = (int)id_vertex;
	if (tenp1->serialNumber == tenp2)
	{
		return TRUE;
	}
	return FALSE;
}

/*
PGraph GraphCreate()

{
	
	PGraph graph = (PGraph)malloc(sizeof(Graph));
	graph->vertex = SetCreate(vertexComp, CLONE_FUNC, free);
	graph->edge	= SetCreate(edgeComp, CLONE_FUNC, free);
	
	graph->number_of_vertex = 0;
	return graph;
}
*/

void GraphDestroy(PGraph graph)
{
	SetDestroy(graph->vertex);
	SetDestroy(graph->edge);
	free(graph);
}

Bool GraphAddVertex(PGraph graph, int vertex_number)
{
	Vertex new_element_vertex;
	new_element_vertex.serialNumber = vertex_number;

	if (vertex_number != graph->number_of_vertex)
	{
		return FALSE;
	}
	
	return  SetAdd(graph->vertex, &new_element_vertex);
}

Bool GraphAddEdge(PGraph pGraph, int vertex1, int vertex2, int weight)
{
	Edge  new_element_edge;
	new_element_edge.nodeA = vertex1;
	new_element_edge.nodeB = vertex2;
	new_element_edge.weight = weight;

	if (vertex1 > pGraph->number_of_vertex || vertex2 > pGraph->number_of_vertex || vertex1 == vertex2)
	{
		return FALSE;
	}

	return  SetAdd(pGraph->edge, &new_element_edge);
	
}
/*
PSet GraphNeighborVertices(PGraph graph, int number) //<-- new memory alocation need to check for relese
{
	PSet new_set_of_vertix;
	Edge vertix_mover;
	PVertex vertix_mover_pointer;
	

	new_set_of_vertix = SetCreate(edgeComp, CLONE_FUNC, DESTROY_FUNC);
	while (TRUE)
	{
		graph->vertex->
	}


	return PSet();
}
*/
Bool GraphFindShortestPath(PGraph pGraph, int source, int * dist, int * prev)
{
	return TRUE;
}

int GraphGetNumberOfEdges(PGraph somethin)
{
	return 0;
}

int GraphGetNumberOfVertices(PGraph something)
{
	return 0;
}
/*
PSet GraphVerticesStatus(PGraph)
{
	return PSet();
}

PSet GraphEdgesStatus(PGraph)
{
	return PSet();
}

*/
