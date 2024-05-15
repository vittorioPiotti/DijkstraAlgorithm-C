//
//  main.c
//  DijkstraCodifica
//
//  Created by Vittorio Piotti on 25/04/23.
//


#include <stdio.h>
#include <string.h>

#define MAX_PATHS 10

#define MAX_NODES 10
#define MAX_EDGES MAX_NODES * (MAX_NODES - 1)   //numero massimo combinazione di archi dato che per ogni 2 nodi ci sono 2 archi
#define USED 1
#define NOT_USED 0

#define NOT_DIRECTED 0 //freccia non direzionata
#define DIRECTED 1  //freccia direzionata (from-to)



#define MIN_COST 1
#define MAX_COST 99

#define MAX_CHAR 20

struct Path{
    int id;
    int cost;
};

struct Paths{
    struct Path path[MAX_NODES];
    int length;
    int used;
};


struct RoutingTable{
    int id;
    int prec;
    int cost;
    int used;
};

struct RoutingTables{
    struct RoutingTable routingTable[MAX_NODES];
    int used;
};

struct Node {
    int id;     // identificatore univoco del nodo (valore da 0 - 24)
    int label;  // nome nodo (valore da A - Y)
    int used;   // flag che indica se il nodo è stato utilizzato (valore 0 non usato, 1 usato)
};

struct Edge {
    int id;     // identificatore univoco dell'arco
    int cost;   // costo dell'arco (valore da 0 a 99)
    int from;   // id nodo di partenza dell'arco
    int to;     // id nodo di arrivo dell'arco
    int verso;  // direzione dell'arco (0 per non orientato, 2 destra, 3 sinistra)
    int used;   // flag che indica se l'arco è stato utilizzato (valore 0 non usato, 1 usato)
};
struct Connection{
    int id;
    int cost;
};
struct ConnectedNodes{
    int id;
    int length;
    struct Connection connections[MAX_NODES];
};



const struct Node NODES[MAX_NODES]= {
    {0,  'A', 0},  {1,  'B', 0}, {2,  'C', 0},  {3,  'D', 0},  {4,  'E', 0},
    {5,  'F', 0},  {6,  'G', 0}, {7,  'H', 0},  {8,  'I', 0},  {9,  'J', 0},
};

const struct Edge EDGES[MAX_EDGES] = {
    {0, 0, 0, 1, 0,  0}, {1, 0, 1, 0, 0,  0}, {2, 0, 0, 2, 0,  0}, {3, 0, 2, 0, 0,  0},
    {4, 0, 0, 3, 0,  0}, {5, 0, 3, 0, 0,  0}, {6, 0, 0, 4, 0,  0}, {7, 0, 4, 0, 0,  0},
    {8, 0, 0, 5, 0,  0}, {9, 0, 5, 0, 0,  0}, {10, 0, 0, 6, 0, 0}, {11, 0, 6, 0, 0, 0},
    {12, 0, 0, 7, 0, 0}, {13, 0, 7, 0, 0, 0}, {14, 0, 0, 8, 0, 0}, {15, 0, 8, 0, 0, 0},
    {16, 0, 0, 9, 0, 0}, {17, 0, 9, 0, 0, 0}, {18, 0, 1, 2, 0, 0}, {19, 0, 2, 1, 0, 0},
    {20, 0, 1, 3, 0, 0}, {21, 0, 3, 1, 0, 0}, {22, 0, 1, 4, 0, 0}, {23, 0, 4, 1, 0, 0},
    {24, 0, 1, 5, 0, 0}, {25, 0, 5, 1, 0, 0}, {26, 0, 1, 6, 0, 0}, {27, 0, 6, 1, 0, 0},
    {28, 0, 1, 7, 0, 0}, {29, 0, 7, 1, 0, 0}, {30, 0, 1, 8, 0, 0}, {31, 0, 8, 1, 0, 0},
    {32, 0, 1, 9, 0, 0}, {33, 0, 9, 1, 0, 0}, {34, 0, 2, 3, 0, 0}, {35, 0, 3, 2, 0, 0},
    {36, 0, 2, 4, 0, 0}, {37, 0, 4, 2, 0, 0}, {38, 0, 2, 5, 0, 0}, {39, 0, 5, 2, 0, 0},
    {40, 0, 2, 6, 0, 0}, {41, 0, 6, 2, 0, 0}, {42, 0, 2, 7, 0, 0}, {43, 0, 7, 2, 0, 0},
    {44, 0, 2, 8, 0, 0}, {45, 0, 8, 2, 0, 0}, {46, 0, 2, 9, 0, 0}, {47, 0, 9, 2, 0, 0},
    {48, 0, 3, 4, 0, 0}, {49, 0, 4, 3, 0, 0}, {50, 0, 3, 5, 0, 0}, {51, 0, 5, 3, 0, 0},
    {52, 0, 3, 6, 0, 0}, {53, 0, 6, 3, 0, 0}, {54, 0, 3, 7, 0, 0}, {55, 0, 7, 3, 0, 0},
    {56, 0, 3, 8, 0, 0}, {57, 0, 8, 3, 0, 0}, {58, 0, 3, 9, 0, 0}, {59, 0, 9, 3, 0, 0},
    {60, 0, 4, 5, 0, 0}, {61, 0, 5, 4, 0, 0}, {62, 0, 4, 6, 0, 0}, {63, 0, 6, 4, 0, 0},
    {64, 0, 4, 7, 0, 0}, {65, 0, 7, 4, 0, 0}, {66, 0, 4, 8, 0, 0}, {67, 0, 8, 4, 0, 0},
    {68, 0, 4, 9, 0, 0}, {69, 0, 9, 4, 0, 0}, {70, 0, 5, 6, 0, 0}, {71, 0, 6, 5, 0, 0},
    {72, 0, 5, 7, 0, 0}, {73, 0, 7, 5, 0, 0}, {74, 0, 5, 8, 0, 0}, {75, 0, 8, 5, 0, 0},
    {76, 0, 5, 9, 0, 0}, {77, 0, 9, 5, 0, 0}, {78, 0, 6, 7, 0, 0}, {79, 0, 7, 6, 0, 0},
    {80, 0, 6, 8, 0, 0}, {81, 0, 8, 6, 0, 0}, {82, 0, 6, 9, 0, 0}, {83, 0, 9, 6, 0, 0},
    {84, 0, 7, 8, 0, 0}, {85, 0, 8, 7, 0, 0}, {86, 0, 7, 9, 0, 0}, {87, 0, 9, 7, 0, 0},
    {88, 0, 8, 9, 0, 0}, {89, 0, 9, 8, 0, 0},
};



//inserire qui input
const int ADJ_MATRIX[MAX_NODES][MAX_NODES] = {
        {0, 2, 1, 1, 0, 0, 0, 0, 0, 0},
        {3, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
const int START = 0;
const int END = 1;



//gestione network
int changeState(int);
int checkNodo(struct Node [],int );
void newNode(struct Node [],int);
void newEdge(struct Edge [],int,int,int,int);
void delateNode(struct Node [],struct Edge [], int);
void delateEdge(struct Edge [],int);
void updateEdges(struct Edge [], int [][MAX_NODES]);
void updateNodes(struct Node [], int [][MAX_NODES]);
int getNodeLabel(struct Node [],int );
int getNodes(struct Node[]);

//gestione strutture per dijsktra
void initConnectedNodes(struct Node[],struct Edge[],struct ConnectedNodes[]);
void initRoutingTable(struct Node [],struct ConnectedNodes [], struct RoutingTables []);
int dijkstra(struct ConnectedNodes [], struct Paths [], struct RoutingTables [],int , int ,int );
int allExplored(struct RoutingTable [],int);
int getMinCostNotExplored(struct RoutingTable [],int);
int getInxNotExplored(struct RoutingTable [],int);
int getInxRoutingTable(struct RoutingTable [],int,int);
void fixRoutingTable(struct RoutingTables [],int ,int );
int getInxMinCostNotExplored(struct RoutingTable [], int );
void initPaths(struct RoutingTables [],struct Paths [],int, int, int, int);
void fixResults(struct RoutingTables [],struct Paths [],int ,int );
int getPaths(struct Paths [],int );

int main(int argc, const char * argv[]) {
    
    struct Node nodes[MAX_NODES] = {0};
    struct Edge edges[MAX_EDGES] = {0};
    int start = START;
    int end = END;
    int adj_matrix[MAX_NODES][MAX_NODES];
    struct ConnectedNodes connectedNodes[MAX_NODES];
    struct RoutingTables routingTables[MAX_PATHS];
    struct Paths paths[MAX_PATHS];
    int nPaths = 0;
    int i = 0;
    int j = 0;
    
    memcpy(adj_matrix, ADJ_MATRIX, sizeof(adj_matrix));
    memcpy(nodes, NODES, sizeof(nodes));
    memcpy(edges, EDGES, sizeof(edges));
    
    
    
    updateNodes( nodes,  adj_matrix);
    updateEdges( edges,  adj_matrix);

    
    initConnectedNodes(nodes, edges, connectedNodes);
    
    
    initRoutingTable(nodes,connectedNodes, routingTables);
    
    
    nPaths = dijkstra(connectedNodes, paths, routingTables,start,end,getNodes(nodes));
    
    
    
    printf("\n\tNodes = {");
    for(i = 0; i < MAX_NODES; i ++){
        if(nodes[i].used == USED)printf("\n\t\t{id: %d, label: %c}, ",nodes[i].id,nodes[i].label);
    }
    printf("\n\t}\n");
    char verso[MAX_CHAR] = "";
    char used[MAX_CHAR] = "";
    char prec[MAX_CHAR] = "";
    char cost[MAX_CHAR] = "";
    printf("\n\tEdges = {");
    for(i = 0; i < MAX_EDGES; i ++){
        if(edges[i].used == USED){
            strcpy(verso, "non direzionato");
            strcpy(used, "usato");
            if(edges[i].verso == DIRECTED)strcpy(verso,"direzionato");
            if(edges[i].verso == USED)strcpy(verso,"direzionato");
            printf("\n\t\t{id: %d,  from: %c, to: %c, cost: %d, used: %s, verso: %s}, ",edges[i].id,getNodeLabel(nodes, edges[i].from),getNodeLabel(nodes, edges[i].to),edges[i].cost,used,verso);
        }
    }
    printf("\n\t}\n");
    printf("\n\tConnectedNodes = {");
    for(i = 0; i < getNodes(nodes); i ++){
        printf("\n\t\t{id: %c, connections: [",getNodeLabel(nodes, connectedNodes[i].id));
        for(j = 0; j < connectedNodes[i].length; j ++){
            printf("{id: %c, cost: %d}, ",getNodeLabel(nodes,connectedNodes[i].connections[j].id),connectedNodes[i].connections[j].cost );
        }
        printf("]},");
    }
    printf("\n\t}\n");
    for(j = 0; j < nPaths; j ++){
        if(routingTables[j].used == USED){
            printf("\n\tRoutingTable.%d = {",j + 1);
            for(i = 0; i < getNodes(nodes); i ++){
                strcpy(used, "usato");
                strcpy(prec, "nessuno");
                if(routingTables[j].routingTable[i].used == NOT_USED) strcpy(used, "non usato");
                
                if(routingTables[j].routingTable[i].prec == - 1){
                    if(routingTables[j].routingTable[i].cost == MAX_COST + 1){
                        strcpy(cost, "infinito");
                        printf("\n\t\t{id: %c, prec: %s, cost: %s, used: %s},",getNodeLabel(nodes, routingTables[j].routingTable[i].id),prec,cost,used );
                    }else{
                        printf("\n\t\t{id: %c, prec: %s, cost: %d, used: %s},",getNodeLabel(nodes, routingTables[j].routingTable[i].id),prec,routingTables[j].routingTable[i].cost,used );
                    }
                    
                }else{
                    if(routingTables[j].routingTable[i].cost == MAX_COST + 1){
                        strcpy(cost, "infinito");
                        printf("\n\t\t{id: %c, prec: %c, cost: %s, used: %s},",getNodeLabel(nodes, routingTables[j].routingTable[i].id),getNodeLabel(nodes, routingTables[j].routingTable[i].prec),cost,used );
                    }else{
                        printf("\n\t\t{id: %c, prec: %c, cost: %d, used: %s},",getNodeLabel(nodes, routingTables[j].routingTable[i].id),getNodeLabel(nodes, routingTables[j].routingTable[i].prec),routingTables[j].routingTable[i].cost,used );
                    }
                    
                }
            }
            printf("\n\t}\n");
        }
    }

 
    for(i = 0; i < nPaths; i ++){
        if(paths[i].used == USED){
            printf("\n\tPath.%d = {",i + 1);
            for(j = 0; j < paths[i].length; j ++){
                printf("\n\t\t{id: %c, cost: %d},",getNodeLabel(nodes,paths[i].path[j].id),paths[i].path[j].cost);
            }
            printf("\n\t}\n");
        }
    }
    

    
    printf("\n\tsono stati rilevati %d cammini minimi da %c a %c con spesa %d\n\n",getPaths(paths, nPaths),getNodeLabel(nodes, start),getNodeLabel(nodes, end),paths[0].path[0].cost);

    return 0;
}
int getPaths(struct Paths paths[],int nPaths){
    int c = 0;
    int i = 0;
    for( i = 0; i < nPaths; i ++){
        if(paths[i].used == USED)c++;
    }
    return c;
}
void fixRoutingTable(struct RoutingTables routingTable[],int paths,int nNodes){
    int i = 0;
    int j = 0;
    for( i = 1; i < paths; i ++){
        for( j = 0; j < nNodes; j ++){
            if(routingTable[i].routingTable[j].prec == -1){
                routingTable[i].routingTable[j].prec = routingTable[0].routingTable[j].prec;
                routingTable[i].routingTable[j].cost = routingTable[0].routingTable[j].cost;
                routingTable[i].routingTable[j].used = USED;
            }
        }
    }
}
void fixResults(struct RoutingTables routingTables[],struct Paths paths[],int nPaths,int nNodes){
    int i = 0;
    int j = 0;
    int k = 0;
    int c = 0;
    for( i = 0; i < nPaths; i ++){
        for( j = 0; j < nPaths; j ++){
            if(i != j && paths[i].length == paths[j].length && paths[i].used == USED && paths[j].used == USED){
                c = 0;
                for( k = 0; k < paths[i].length ; k ++){
                    if(paths[i].path[k].id == paths[j].path[k].id )c++;
                }
                if(c == paths[i].length){
                    paths[j].used = NOT_USED;
                    routingTables[j].used = NOT_USED;
                }else routingTables[j].used = USED;
                
                
            }
        }
    }
}
void initPaths(struct RoutingTables routingTables[],struct Paths paths[],int nPaths,int nNodes,int start,int end){
    int i = 0;
    int inx = 0;
    int flag = 0;
    for( i = 0; i < nPaths; i ++){
        flag = 0;
        inx = getInxRoutingTable(routingTables[i].routingTable, end, nNodes);
        paths[i].length = 0;
        do{
            if(inx == start)flag = 1;
            paths[i].path[paths[i].length].id = routingTables[i].routingTable[inx].id;
            paths[i].path[paths[i].length].cost = routingTables[i].routingTable[inx].cost;
            inx = routingTables[i].routingTable[inx].prec;
            paths[i].used = USED;
            paths[i].length++;
          
        }while(flag == 0);
    }
}
int allExplored(struct RoutingTable routingTable[],int nNodes){
    int i = 0;
    int c = 0;
    int flag = NOT_USED;
    for( i = 0; i < nNodes;i++){
        if(routingTable[i].used == USED )c++;
    }
    if(c == nNodes) flag = USED;
    return flag;
}
int getMinCostNotExplored(struct RoutingTable routingTable[],int nNodes){
    int minCost = routingTable[getInxNotExplored(routingTable,nNodes)].cost;
    int i = 0;
    for(i = 0; i < nNodes; i++){
        if(routingTable[i].used == NOT_USED && minCost > routingTable[i].cost )minCost = routingTable[i].cost;
    }
    return minCost;
}
int getInxNotExplored(struct RoutingTable routingTable[],int nNodes){
    int inx = -1;
    int i = 0;
    for(i = 0; i < nNodes; i++){
        if(routingTable[i].used == NOT_USED){
            inx = i;
            break;
        }
    }
    return inx;
}
int getInxMinCostNotExplored(struct RoutingTable routingTable[], int nNodes){

    int minCost = getMinCostNotExplored(routingTable,nNodes);
    int inx = getInxNotExplored(routingTable,nNodes);
    int i = 0;
    for(i = 1; i < nNodes; i++){
        
        if(routingTable[i].used == NOT_USED && minCost == routingTable[i].cost ){
            inx = i;
            break;
        }
    }

    return inx;
}
    

int dijkstra(struct ConnectedNodes connectedNodes[], struct Paths paths[], struct RoutingTables routingTables[],int start, int end,int nNodes){
    int i = 0;
    int j = 0;
    int inx = 0;
    int cost = 0;
    int nPaths = 1;
    for(i = 0; i < nNodes; i ++){
        if(routingTables[0].routingTable[i].id == start)routingTables[0].routingTable[i].cost = 0;
    }
    do{
        i = getInxMinCostNotExplored(routingTables[0].routingTable,nNodes);
        routingTables[0].routingTable[i].used = USED;
        if(routingTables[0].routingTable[i].cost == MAX_COST + 1)cost = 0;
        else cost = routingTables[0].routingTable[i].cost;
        if(connectedNodes[i].length != 0){
            for(j = 0; j < connectedNodes[i].length; j ++){
                inx = getInxRoutingTable(routingTables[0].routingTable,connectedNodes[i].connections[j].id,nNodes );
                if(connectedNodes[i].connections[j].cost + cost < routingTables[0].routingTable[inx].cost){
                    routingTables[0].routingTable[inx].cost = connectedNodes[i].connections[j].cost + cost;
                    routingTables[0].routingTable[inx].prec = connectedNodes[i].id;
                }else if(connectedNodes[i].connections[j].cost + cost == routingTables[0].routingTable[inx].cost){
                    routingTables[nPaths].routingTable[inx].cost = connectedNodes[i].connections[j].cost + cost;
                    routingTables[nPaths].routingTable[inx].prec = connectedNodes[i].id;
                    nPaths++;
                }
            }
        }
    }while(allExplored(routingTables[0].routingTable,nNodes) == NOT_USED);
    if(nPaths > 1)fixRoutingTable(routingTables, nPaths, nNodes);
    initPaths(routingTables, paths, nPaths, nNodes, start, end);
    fixResults(routingTables, paths, nPaths, nNodes);
    return nPaths;
}
int getInxRoutingTable(struct RoutingTable routingTable[],int id,int nNodes){
    int inx = -1;
    int i = 0;
    for(i = 0; i < nNodes; i ++){
        if(id == routingTable[i].id){
            inx = i;
            break;
        }
    }
    return inx;
}
void initRoutingTable(struct Node nodes[],struct ConnectedNodes connectedNodes[], struct RoutingTables routingTables[]){
    int i = 0;
    int j = 0;
    for(j = 0; j < MAX_PATHS; j++){
        routingTables[i].used = USED;
        for(i = 0; i < getNodes(nodes); i ++){
            routingTables[j].routingTable[i].id = connectedNodes[i].id;
            routingTables[j].routingTable[i].prec = -1;
            routingTables[j].routingTable[i].cost = MAX_COST + 1;
            routingTables[j].routingTable[i].used = NOT_USED;
        }
    }
    
}
void initConnectedNodes(struct Node nodes[],struct Edge edges[], struct ConnectedNodes connectedNodes[]){
    int i = 0;
    int j = 0;
    int k = 0;
    int c = 0;
    for( i = 0; i < MAX_NODES; i ++){
        if(nodes[i].used == USED){
            connectedNodes[c].id = nodes[i].id;
            connectedNodes[c].length = 0;
            c++;
        }
    }
    for( i = 0; i < MAX_EDGES; i ++){
        for( j = 0; j < getNodes(nodes); j ++){
            if(edges[i].used == USED && edges[i].from == connectedNodes[j].id){
                if(edges[i].verso == NOT_DIRECTED){
                    connectedNodes[j].connections[connectedNodes[j].length].id = edges[i].to;
                    connectedNodes[i].connections[connectedNodes[j].length].cost = edges[i].cost;
                    connectedNodes[j].length++;
                    for( k = 0; k < getNodes(nodes); k ++){
                        if(connectedNodes[k].id ==  edges[i].to){
                            connectedNodes[k].connections[connectedNodes[k].length].id = edges[i].from;
                            connectedNodes[k].connections[connectedNodes[k].length].cost = edges[i].cost;
                            connectedNodes[k].length++;
                        }
                    }
                }else{
                    connectedNodes[j].connections[connectedNodes[j].length].id = edges[i].to;
                    connectedNodes[j].connections[connectedNodes[j].length].cost = edges[i].cost;
                    connectedNodes[j].length++;
                }
                
            }
        }
    }
}


int getNodes(struct Node nodes[]){
    int c = 0;
    int i = 0;
    for( i = 0; i < MAX_NODES; i ++){
        if(nodes[i].used == USED)c++;
    }
    return c;
}
int changeState(int state){
    if(state == USED)return NOT_USED;
    return USED;
}
void newNode(struct Node nodes[],int id){
    int i = 0;
    for( i = 0; i < MAX_NODES; i ++){
        if(nodes[i].id == id && nodes[i].used == NOT_USED){
            nodes[i].used = changeState(nodes[i].used);
            break;
        }
    }
}
void delateNode(struct Node nodes[],struct Edge edges[], int id){
    int i = 0;
    for( i = 0; i < MAX_NODES; i ++){
        if(nodes[i].id == id && nodes[i].used == USED)nodes[i].used = changeState(nodes[i].used);
    }
    for( i = 0; i < MAX_EDGES; i ++){
        if((edges[i].from == id && edges[i].used == USED) || (edges[i].to == id && edges[i].used == USED)){
            delateEdge(edges, edges[i].id);
        }
    }
    
}
void updateNodes(struct Node nodes[], int adj_matrix[][MAX_NODES]){
    int i = 0;
    int j = 0;
    for(i = 0; i < MAX_NODES; i++){
        for(j = 0; j < MAX_NODES; j++){
            if(i != j && adj_matrix[i][j] != 0){
                newNode(nodes, i);
                newNode(nodes, j);
            }
        }
    }
}
void updateEdges(struct Edge edges[], int adj_matrix[][MAX_NODES]){
    int i = 0;
    int j = 0;
    for(i = 0; i < MAX_NODES; i++){
        for(j = 0; j < MAX_NODES; j++){
            if(adj_matrix[i][j] != 0 )newEdge(edges, i, j, adj_matrix[i][j], DIRECTED);
        }
    }
    for(i = 0; i < MAX_EDGES; i++){
        for(j = 0; j < MAX_EDGES; j++){
            if(edges[i].id != edges[j].id && edges[i].from == edges[j].to && edges[i].to == edges[j].from && edges[i].used == USED && edges[j].used == USED){
                
                if(edges[i].cost == edges[j].cost ){
                    edges[i].verso = NOT_DIRECTED;
                    delateEdge(edges, edges[j].id);
                }
                else{
                    edges[i].verso = DIRECTED;
                    edges[j].verso = DIRECTED;
                }
                
            }
        }
    }
}

int getNodeLabel(struct Node nodes[],int id){
    int label = -1;
    int i = 0;
    for( i = 0; i < MAX_NODES; i ++){
        if(nodes[i].id == id)label = nodes[i].label;
    }
    return label;
}

void delateEdge(struct Edge edges[], int id){
    int i = 0;
    for( i = 0; i < MAX_EDGES; i ++){
        if(edges[i].id == id && edges[i].used == USED)edges[i].used = changeState(edges[i].used);
    }
}
int checkNodo(struct Node nodes[MAX_NODES],int id){
    int i = 0;
    for( i = 0; i < MAX_NODES; i ++){
        if(nodes[i].id == id && nodes[i].used == USED)return id;
    }
    return -1;
}
void newEdge(struct Edge edges[],int from, int to,int cost,int verso){
    int i = 0;
    for( i = 0; i < MAX_EDGES; i ++){
        if(edges[i].used == NOT_USED && edges[i].from == from && edges[i].to == to && cost >= MIN_COST && cost <= MAX_COST){
            edges[i].used = changeState(edges[i].used);
            edges[i].from = from;
            edges[i].to = to;
            edges[i].cost = cost;
            edges[i].verso = verso;
            break;
        }
    }
}

