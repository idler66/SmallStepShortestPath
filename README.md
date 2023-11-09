# SmallStepShortestPath（SSSPA 小步最短路径算法）
SSSPA is a new shortest path algorithm that completely avoids problems caused by relaxation operations used by Dijkstra's algorithm .

## The problem of Dijkstra shortest path algorithm 

Relaxation operation is the essence of Dijkstra shortest path algorithm .

Let S be the set of nodes found the shortest path, and Q other nodes. 

Let u in S, v in S, When dist[u]+length(u,v) < dist[v], update dist[v] to dist[ u]+length(u,v).

Before v moved from V to S, it's path length dist[v] may be updated many times .

For every node u in S, the number of dist[u]+length(u,v) < dist[v] is proportional to u's out degree .

The above two points greatly increase the maintenance cost of the newly generated u in Q , time(time of Heapify) or memory(put a new element into heap when dist[u]+length(u,v) < dist[v]).

### u's out degree
For every v in Q, if there is a edge from u to v , u's out degree += 1.

## Time complexity
### Time complexity of Dijkstra binary heap implementation
The time complexity of Dijkstra consist of there parts, 

    first, the time complexity of edges access is O(|E|), 
    
    second, the time comlexity of inserting element into heap is O(|V|*log|V|),
    
    and third the time complexity of Heapify when dist[u]+length(u,v) < dist[v] is O(C*|V|), C is the number of heapify.
    
In parallel Dijkstra shortest path algorithm, heapify may be eliminated by putting a new element into heap when dist[u]+length(u,v) < dist[v].

### Time complexity of SSSPA binary heap implementation
The time complexity of SSSPA only consists of two parts, 

    first, the time complexity of edges access is O(|E|), 
    
    second, the time comlexity of inserting element into heap is O(|V|*log|V|).
    
SSSPA greatly increase its performance in two ways ,
     first, it eliminates Heapify by delaying the expected dist[v] update or putting a new element into heap;
     second, ...

For more informations, you can visit https://bbs.huaweicloud.com/blogs/409181.

## performance test

For Dijkstra shortest path algorithm with make_heap, 
it will be slightly better than SSSPA when there are very few nodes in some cases,
it's performance will drop sharply when the number of nodes increases.

For Dijkstra shortest path algorithm without make_heap, SSSPA universally outperforms it.
The greater the number of times dist[v] changes is , the bigger SSSPA outperforms Dijkstra shortest path algorithm.

### hardware
   Model name: MacBook Pro
   Model Identifier: MacBookPro11,4
   Processor name: Quad-core Intel Core i7
   Processor speed: 2.2 GHz
   Number of processors: 1
   Total number of cores: 4
   L2 cache (per core): 256 KB
   L3 cache: 6 MB
### platform 
    Stanford Network Analysis Project, SNAP
    
### data sets

    undirected graph, 
    datagen-8_3、datagen-8_2、datagen-8_1、datagen-8_0、datagen-7_9、datagen-7_8、datagen-7_7、datagen-7_6、datagen-7_5 
    from https://ldbcouncil.org/benchmarks/graphalytics/.
    
    undirected graph, 
    bio-CE-GN，bio-CE-CX，bio-DM-CX，bio-HS-CX，bio-SC-HT，bio-human-gene1，bio-human-gene2，bio-mouse-gene，bio-WormNet-v3 
    from https://networkrepository.com/.
    
    directed graph, 
    USairport500，OClinks_w_chars，OClinks_w , celegans_n306，Cross_Parker-Consulting_info，Cross_Parker-Consulting_value，Cross_Parker-Manufacturing_aware，Cross_Parker-Manufacturing_info，Freemans_EIES-1_n48，Freemans_EIES-2_n48 
    from https://toreopsahl.com/datasets/ and other links.

### result formats
    1 The number of nodes that have found shortest path,
    2 The number of edges visited by SSSPA / the number of nodes that have found shortest path,
    3 The number Dijkstra calls make_heap / the number of nodes that have found shortest path (for implementation with make_heap),
    4 The execution time of Dijkstra / the execution time of SSSPA,
    5 ID of source vertex,
    6 The number of edges visited by SSSPA,
    7 The number Dijkstra calls make_heap,
    8 The number of clock cycles occupied by SSSPA,
    9 The execution time of SSSPA (s),
    10 The number of clock cycles occupied by Dijkstra,
    11 The execution time of Dijkstra (s),
    12 (The number of times dist[v] changes when dist[u]+length(u,v) < dist[v]) minus (the number of nodes that have found shortest path) (implementation without make_heap),
    13 "heap" for implementation with make_heap , or "memory" for implementation without make_heap.

The fourth item corresponds to The execution time of Dijkstra / the execution time of SSSPA .
In linear model, the fourth item positively relates to the first and third terms, negatively relates to the second term. 
The more nodes visited and make_heap called, the greater the advantage of SSSPA has.

 
