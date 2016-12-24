


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
	SetDestroy(set);
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
/*this is a helper function that will check if one of the edges has the node we are looking for
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

	if (NULL == (graph->vertex = (PVertex)SetCreate(vertexComp, cloneVertex, freefunc)))
	{
		free(graph);
		return NULL;
	}
	if (NULL == (graph->edge = (PEdge)SetCreate(edgeComp, cloneEdge, freefunc))) {

		SetDestroy(graph->vertex);
		returnError(graph);
		return;
	}

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
	if (number > graph->number_of_vertex - 1) return NULL;
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
	SetDestroy(one);
	SetDestroy(two);
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

/*this will be use by Djisk_get_weith*/
PEdge find_dijk_edge(PSet edge_set, PVertex vertex1, PVertex vertex2)
{
	PEdge comp_edge;
	comp_edge = (PEdge)SetGetFirst(edge_set);
	while (TRUE)
	{
		if (comp_edge->nodeA == vertex1 && comp_edge->nodeB == vertex2 ||
			comp_edge->nodeB == vertex1 && comp_edge->nodeA == vertex2)
		{
			return comp_edge;
		}
		if (NULL == (comp_edge = (PEdge)SetGetNext(edge_set))) return NULL;
	}
}
int Djisk_get_weith(PGraph graph, int Current_vertex, int neighbor)
{
	PEdge temp_evaluate;
	Vertex vertx1, vertex2;
	PVertex temp1, temp2;

	vertx1.serialNumber = Current_vertex;
	vertex2.serialNumber = neighbor;

	temp1 = (PVertex)SetFindElement(graph->vertex, &vertx1);
	temp2 = (PVertex)SetFindElement(graph->vertex, &vertex2);

	temp_evaluate = find_dijk_edge(graph->edge, temp1, temp2);
	if (temp_evaluate == NULL) return (-2); // just for debuginf and cheking that all is working this means that didnt find that edge

	return temp_evaluate->weight;

}
Bool update_min_distance(PDijkstr U_elem, PGraph graph, PSet unvisit_nodes)
{
	// we will working with alocate memory we hace to be carefull
	PSet neigbors_of_u;
	PVertex temp_vertex;
	Dijkstr temp_neig;
	PDijkstr neib_elem_in_unv;


	int distance_u_v;
	int new_ditance;

	if (NULL == (neigbors_of_u = GraphNeighborVertices(graph, U_elem->Vertex_id))) return FreeMen(neigbors_of_u, NULL);
	if (NULL == (temp_vertex = (PVertex)SetGetFirst(neigbors_of_u))) return FreeMen(neigbors_of_u, NULL);
	while (TRUE)
	{
		temp_neig.Vertex_id = temp_vertex->serialNumber;
		if (NULL != (neib_elem_in_unv = (PDijkstr)SetFindElement(unvisit_nodes, &temp_neig)))
		{
			distance_u_v = Djisk_get_weith(graph, U_elem->Vertex_id, temp_vertex->serialNumber);
			new_ditance = U_elem->min_dist_source + distance_u_v;
			if (neib_elem_in_unv->min_dist_source == (-1) || new_ditance <neib_elem_in_unv->min_dist_source)
			{
				neib_elem_in_unv->min_dist_source = new_ditance;
				neib_elem_in_unv->Prev_vertex = U_elem->Vertex_id;
			}

		}
		if (NULL == (temp_vertex = (PVertex)SetGetNext(neigbors_of_u)))
		{
			SetDestroy(neigbors_of_u); ///<-- we free the memory here
			return TRUE;
		}
	}

}
void set_dijks_ele(PDijkstr elem, int serialNumber, int distance, int source)
{
	elem->Vertex_id = serialNumber;
	elem->min_dist_source = distance;
	elem->Prev_vertex = source;
}

Result copy_dist_prev(int* dist, int* prev, PSet visit_nodes)
{
	if (dist == NULL || prev == NULL || visit_nodes == NULL) return FAIL;
	PDijkstr temp;
	int i = 1;
	temp = SetGetFirst(visit_nodes);
	dist[0] = temp->min_dist_source;
	prev[0] = temp->Prev_vertex;
	while (NULL != (temp = SetGetNext(visit_nodes)))
	{
		dist[i] = temp->min_dist_source;
		prev[i] = temp->Prev_vertex;
//		printf("%d %d\n", dist[i], prev[i]);
		i++;
	}
	return TRUE;
}

Bool GraphFindShortestPath(PGraph pGraph, int source, int* dist, int* prev) //this will probably use malloc need to che memory
{

	//basic checks
	if (pGraph == NULL || source > (pGraph->number_of_vertex) || source < 0 ||NULL == dist || NULL == prev)
	{
		return FALSE;
	}


	PSet unvisit_nodes;
	PSet visit_nodes;
	Bool awser;

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
		SetDestroy(unvisit_nodes);
		free(visit_nodes);
		return FALSE;
	}

	
		

		temp_vertex = SetGetFirst(pGraph->vertex);
		set_dijks_ele(pointer_temp_dij, temp_vertex->serialNumber, INT_MAX, INT_MAX);

		if (FALSE == SetAdd(unvisit_nodes, pointer_temp_dij)) return FreeMen(unvisit_nodes, visit_nodes);

		for (size_t i = 1; i < SetGetSize(pGraph->vertex); i++)
		{
			if (NULL == (temp_vertex = SetGetNext(pGraph->vertex))) break;
			set_dijks_ele(pointer_temp_dij, temp_vertex->serialNumber, INT_MAX, INT_MAX);


			if (FALSE == SetAdd(unvisit_nodes, pointer_temp_dij)) return FreeMen(unvisit_nodes, visit_nodes);
		}

		temp_dij_elem.Vertex_id = source;
		pointer_temp_dij = SetFindElement(unvisit_nodes, &temp_dij_elem);
		pointer_temp_dij->min_dist_source = 0;
		pointer_temp_dij->Prev_vertex = 0;
	
	while (NULL != (SetGetFirst(unvisit_nodes)))
	{


		U_element = findMinDistanceVertex(unvisit_nodes);
		if (FALSE == (awser = update_min_distance(U_element, pGraph, unvisit_nodes)))  return FreeMen(unvisit_nodes, visit_nodes);
		if (FALSE == (awser = SetAdd(visit_nodes, U_element))) return FreeMen(unvisit_nodes, visit_nodes);
		
		if (FALSE == (awser = SetRemoveElement(unvisit_nodes, U_element)))  return FreeMen(unvisit_nodes, visit_nodes);


	}
	if (FALSE == (awser = copy_dist_prev(dist, prev, visit_nodes))) return FreeMen(unvisit_nodes, visit_nodes);
	awser = FreeMen(unvisit_nodes, visit_nodes);


return TRUE;
}

