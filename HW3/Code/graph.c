


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"
#include "set.h"
#include "graph.h"




typedef struct _Graph 
{
	int number_of_vertex;

	struct _Set * vertex ;
	struct _Set * edge;

}Graph, *PGraph;


/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
			THIS FUNTIONS ARE USE TO MANAGE THE .H FUNTIONS
  ###################################################################################################*/

/*Here are the user funtions that will use to set our data base*/

Bool edgeComp(PElem id_vertex, PElem edge1)
{
	Edge * tenp1;
	Edge * tenp2;
	tenp1 = (Edge*)edge1;
	tenp2 = (Edge*)id_vertex;
	if ((tenp1->nodeA == tenp2->nodeA && tenp1->nodeB == tenp2->nodeB)||
		(tenp1->nodeB == tenp2->nodeA && tenp1->nodeA == tenp2->nodeB))
	{
		return TRUE;
	}
	return FALSE;
}
Bool vertexComp(PElem id_vertex, PElem vertex)
{
	Vertex * tenp1;
	Vertex * tenp2;
	tenp1 = (Vertex*)vertex;
	tenp2 = (Vertex*)id_vertex;
	if (tenp1->serialNumber == tenp2->serialNumber)
	{
		return TRUE;
	}
	return FALSE;
}

PElem cloneVertex(PElem vertexNumber) {
	PVertex temp;
	temp = (PVertex)vertexNumber;
	Vertex * vertexpointer = (Vertex *)malloc(sizeof(Vertex));
	vertexpointer->serialNumber = temp->serialNumber;

	return vertexpointer;

}
PElem cloneEdge(PElem edge) {
	Edge * temp;
	temp = (Edge*)edge;
	Edge * new_edge = (Edge*)malloc(sizeof(Edge));
	new_edge->nodeA = temp->nodeA;
	new_edge->nodeB = temp->nodeB;
	new_edge->weight = temp->weight;
	return new_edge;
}

PElem returnError(PElem set)
{
	free(set);
	return NULL;
}
void freefunc(PElem elem) {
	free(elem);
}
/*this is a helper funtion that will check if one of the eges have the node we are loking for
if it does it will add the pointer to the new set*/
Bool checkAndAdd(PEdge Edge_to_be_review, int Vertex_Serial_num, PSet new_set_of_vertix)
{
	if (Edge_to_be_review->nodeA->serialNumber == Vertex_Serial_num)
	{
		Bool awnser = SetAdd(new_set_of_vertix, Edge_to_be_review->nodeB);
		if (awnser == FALSE)
		{
			return FALSE;
		}
		return TRUE;
	}
	else if (Edge_to_be_review->nodeB->serialNumber == Vertex_Serial_num)
	{
		Bool awnser = SetAdd(new_set_of_vertix, Edge_to_be_review->nodeA);
		if (awnser == FALSE)
		{
			return FALSE;
		}
		return TRUE;

	}
	return TRUE;
}
//###################################################################################################




/*##################################################################################################
			PART 2 OF THE HOMEWORK
###################################################################################################*/

PGraph GraphCreate()

{
	PGraph graph = (PGraph)malloc(sizeof(Graph));
	if (graph == NULL) return returnError(graph);

	if (NULL == (graph->vertex = SetCreate(vertexComp, cloneVertex, freefunc))) return returnError(graph);
	if (NULL == (graph->vertex = SetCreate(edgeComp, cloneEdge, freefunc))) return returnError(graph);

	graph->number_of_vertex = 0;
	return graph;
}

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
	Bool anwser = SetAdd(graph->vertex, &new_element_vertex);
	if (anwser == TRUE)
	{
		graph->number_of_vertex = graph->number_of_vertex + 1;
	}

	return  anwser;
}

Bool GraphAddEdge(PGraph pGraph, int vertex1, int vertex2, int weight)
{
	Vertex identical_vertex;
	Edge  new_element_edge;

	if (vertex1 > pGraph->number_of_vertex ||
		vertex2 > pGraph->number_of_vertex || 
		vertex1 == vertex2)
	{
		return FALSE;
	}

	identical_vertex.serialNumber = vertex1;
	new_element_edge.nodeA = SetFindElement(pGraph->vertex, &identical_vertex);
	if (new_element_edge.nodeA == NULL) return FALSE;

	identical_vertex.serialNumber = vertex2;
	new_element_edge.nodeB = SetFindElement(pGraph->vertex, &identical_vertex);
	if (new_element_edge.nodeB == NULL) return FALSE;

	new_element_edge.weight = weight;

	

	return  SetAdd(pGraph->edge, &new_element_edge);
	
}

PSet GraphNeighborVertices(PGraph graph, int number) //<-- new memory alocation need to check for relese
{
	PSet new_set_of_vertix;
	new_set_of_vertix = SetCreate(edgeComp, cloneEdge, freefunc);
	if (new_set_of_vertix == NULL) returnError(new_set_of_vertix);
	
	Edge edge_morf;
	PEdge Pedge_morf;

	edge_morf.nodeA = NULL;
	edge_morf.nodeB = NULL;
	edge_morf.weight = 0;
	Pedge_morf = &edge_morf;

	Bool check;

	if (NULL == (Pedge_morf = SetGetFirst(graph->edge))) return returnError(new_set_of_vertix);
	
	if (FALSE == (check = checkAndAdd(Pedge_morf, number, new_set_of_vertix))) return returnError(new_set_of_vertix);
	while (TRUE)
	{
		if (NULL == (Pedge_morf = SetGetNext(graph->edge))) return new_set_of_vertix;
		if (FALSE == (check = checkAndAdd(Pedge_morf, number, new_set_of_vertix))) return returnError(new_set_of_vertix);
	}
}

int GraphGetNumberOfEdges(PGraph graph)
{
	return SetGetSize(graph->edge);
}

int GraphGetNumberOfVertices(PGraph something)
{
	return something->number_of_vertex;
	//return SetGetSize(something->vertex);
}

PSet GraphVerticesStatus(PGraph graph)
{
	return graph->vertex;
}

PSet GraphEdgesStatus(PGraph graph)
{
	return graph->edge;
}

/*########################################################################################
		PART 3 OF THE HOME WORK
##########################################################################################*/
/*
Bool GraphFindShortestPath(PGraph pGraph, int source, int * dist, int * prev)
{
return TRUE;
}
*/
