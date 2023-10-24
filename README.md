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
The time complexity of SSSPA only consist of two parts, 

    first, the time complexity of edges access is O(|E|), 
    
    second, the time comlexity of inserting element into heap is O(|V|*log|V|).
    
SSSPA eliminates Heapify by delaying the expected dist[v] update or putting a new element into heap, which greatly increase its performance.

For more informations, you can visit https://bbs.huaweicloud.com/blogs/409181.

## performance test

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
    13 heap for implementation with make_heap , or memory for implementation without make_heap.

The fourth item corresponds to The execution time of Dijkstra / the execution time of SSSPA .
In linear model, the fourth item positively relates to the first and third terms, negatively relates to the second term. 
The more nodes visited and make_heap called, the greater the advantage of SSSPA has.

### records for implementation with make_heap

<img width="537" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/1edddb7d-595a-499e-8a54-c9aa0624fbb8">

<img width="537" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/5f25bab0-380d-4be1-b603-162fb3ad5e0e">

<img width="572" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/00b68819-4193-4aa4-a828-2bbe5734e8c3"> 

Take 12651312 as source-vertex, Dijkstra takes 9 hours, SSSPA takes 24 seconds.

<img width="567" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/2f55b900-1e4e-4453-9776-8f5602ee8c91">


<img width="558" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/5c3d64d6-f75c-47cc-bd6c-1116c412507f">


### records for implementation without make_heap


<img width="515" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/79d31b05-ba01-4e4e-b9a5-cf7069aab8f0">

<img width="515" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/e049937e-859a-4c7c-b6c3-a1dff315149e">

<img width="542" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/8fbe0887-ef22-4af7-b27c-f5f1154708ea">

<img width="542" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/7d456512-3792-49e3-bdd8-b320b0039015">

<img width="526" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/4dfc1a24-65ca-4cd4-aac8-a84c8da2d164">

<img width="553" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/442c3938-b927-4632-b04b-ecc1c3d3385e">

<img width="557" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/15ded079-ce1c-4e85-99eb-fa40851efabc">

<img width="581" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/df216acf-078f-4fcb-8b87-c8ceb2f11e03">


### records for both

<img width="547" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/0010dc6b-bf84-4055-9159-9480db845d85">

<img width="563" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/d265298b-2f8e-44d8-976d-ce6c3fc8c8cb">

<img width="558" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/9ed228e4-0c9a-4d2a-afae-63a634c30f18">


<img width="547" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/74e76b63-2073-4512-9adb-25c2c1ef78c2">

<img width="477" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/56916371-5dcd-414d-9f96-37edc814b126">

<img width="438" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/016309fc-5f6d-4f91-83f8-2ea6a2ec223b">

<img width="438" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/29626944-ab4f-4d01-bea7-3b691b5c5add">

<img width="426" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/8a0d1baa-1235-4435-8081-170e3885e74f">

<img width="507" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/58e874cb-8746-4d7c-8e1d-3849c483833a">

<img width="502" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/fffd733c-0a55-4c61-8128-fce6aa22b0c2">

<img width="455" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/27855e70-e731-41fb-9bf9-91911ef8e063">

    For more informations, you can visit https://bbs.huaweicloud.com/blogs/411649.






