


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

PElem returnError(PElem set)
{
	free(set);
	return NULL;
}
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
	if (NULL == vertexpointer) return  returnError(vertexpointer);
	vertexpointer->serialNumber = temp->serialNumber;

	return vertexpointer;

}
PElem cloneEdge(PElem edge) {
	Edge * temp;
	temp = (Edge*)edge;
	Edge * new_edge = (Edge*)malloc(sizeof(Edge));
	if (NULL == new_edge) return  returnError(new_edge);
	new_edge->nodeA = temp->nodeA;
	new_edge->nodeB = temp->nodeB;
	new_edge->weight = temp->weight;
	return new_edge;
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
typedef struct _Dijkstr
{
	int Vertex_id;
	int min_dist_source;
	int Prev_vertex;

}Dijkstr, *PDijkstr;
Bool compDijk(PElem first,PElem second)
{
	PDijkstr temp1;
	PDijkstr temp2;
	temp1 = (PDijkstr)first;
	temp2 = (PDijkstr)second;

	return (temp1->Vertex_id == temp2->Vertex_id);
}
PElem cloneDijk(PElem integer)
{
	PDijkstr temp1;
	PDijkstr temp2;
	temp1 = (PDijkstr)integer;
	
	
	temp2 = (PDijkstr)malloc(sizeof(Dijkstr));
	if (NULL == temp2) return  returnError(temp2);
	temp2->min_dist_source = temp1->min_dist_source;
	temp2->Prev_vertex = temp1->Prev_vertex;
	temp2->Vertex_id = temp1->Vertex_id;

	return temp2;

}
void destrucDijk(PElem integer)
{
	free(integer);
}
Bool FreeMen(PElem one, PElem two)
{
	free(one);
	free(two);
	return FALSE;
}
PDijkstr findMinDistanceVertex( PSet set)
{
	PDijkstr current_min;
	PDijkstr temp;
	temp = SetGetFirst(set);
	current_min = temp;
	
	while (NULL != (temp = SetGetNext(set)))
	{
		if (temp->min_dist_source == -1) continue;
		if (current_min->min_dist_source > temp->min_dist_source) 
		{
			current_min = temp;
		}
	}
	return current_min;
}


Bool GraphFindShortestPath(PGraph pGraph, int source, int * dist, int * prev) //this will probably use malloc need to che memory
{

	//basic checks
	if (pGraph == NULL || source > (pGraph->number_of_vertex) ||NULL == dist || NULL == prev)
	{
		return FALSE;
	}


	PSet unvisit_nodes;
	PSet visit_nodes;
	PVertex temp_vertex;
	Dijkstr temp_dij_elem;
	PDijkstr U_element;
	PDijkstr V_element;
	PDijkstr pointer_temp_dij;
	pointer_temp_dij = &temp_dij_elem;


	if (NULL == (unvisit_nodes = SetCreate(compDijk, cloneDijk, destrucDijk)))
	{
		free(unvisit_nodes);
		return FALSE;
	}
	if (NULL == (visit_nodes = SetCreate(compDijk, cloneDijk, destrucDijk)))
	{
		free(unvisit_nodes);
		free(visit_nodes);
		return FALSE;
	}

	
		

		temp_vertex = SetGetFirst(pGraph->vertex);
		pointer_temp_dij->Vertex_id = temp_vertex->serialNumber;
		pointer_temp_dij->min_dist_source = -1;
		pointer_temp_dij->Prev_vertex = -1;
		if (FALSE == SetAdd(unvisit_nodes, pointer_temp_dij)) return FreeMen(unvisit_nodes, visit_nodes);

		for (size_t i = 1; i < SetGetSize(pGraph->vertex); i++)
		{
			if (NULL == (temp_vertex = SetGetNext(pGraph->vertex))) break;
			pointer_temp_dij->Vertex_id = temp_vertex->serialNumber;
			pointer_temp_dij->min_dist_source = -1;
			pointer_temp_dij->Prev_vertex = -1;
			if (FALSE == SetAdd(unvisit_nodes, pointer_temp_dij)) return FreeMen(unvisit_nodes, visit_nodes);
		}

		temp_dij_elem.Vertex_id = source;
		pointer_temp_dij = SetFindElement(unvisit_nodes, &temp_dij_elem);
		pointer_temp_dij->min_dist_source = 0;
		pointer_temp_dij->Prev_vertex = 0;
	
	Bool awser;
	while (NULL != (SetGetFirst(unvisit_nodes)))
	{


		U_element = findMinDistanceVertex(unvisit_nodes);
		
		if (FALSE == (awser = SetRemoveElement(unvisit_nodes, U_element)))  return FreeMen(unvisit_nodes, visit_nodes);


	}
	//seting up the lists
	for (int i = 0; i < pGraph->number_of_vertex; i++)
	{
		dist[i] = -1; //flag to infinity
		prev[i] = -1; //flag to undefine
	}
	dist[source] = 0;
	prev[source] = 0;
	


return TRUE;
}

