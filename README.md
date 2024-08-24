# Algoritmo Dijkstra C
Pseudocodifica in C dell'algoritmo di Dijkstra con Esercizio di Default e Calcolo di **Tutti i Percorsi Minimi** e con **Archi Direzionabili**:


|Destra|Sinistra|Entrambe|
|---|---|---|


> [!NOTE]
> Il progetto è stato sviluppato a scuola per fini scolastici in funzione della consegna assegnata dal docente come lavoro individuale



> [!TIP]
> Corretto funzionamento garantito

> [!CAUTION] 
> `Fatal Error`: tra **2 Nodi** non ci devono essere più di un di **Massimo 2 Archi di Direzione Diversa**

#### Support Me

[<img width="200" src="https://github.com/vittorioPiotti/vittorioPiotti/blob/main/immagini/support.png"/>](https://ko-fi.com/vittoriopiotti)


## Screenshot

<img width="300" src="https://github.com/vittorioPiotti/Algoritmo-Dijkstra-C/blob/main/snap.png"/>


## Snippet Dijkstra Algorithm

```c

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

```

## Licenze

| Componente         | Versione  | Copyright                         | Licenza                                                       |
|--------------------|-----------|-----------------------------------|---------------------------------------------------------------|
| Algoritmo Dijkstra C | v1.0.0    | 2024 Vittorio Piotti              | [GPL-3.0 License](https://github.com/vittorioPiotti/Algoritmo-Dijkstra-C/blob/main/LICENSE.md) |
