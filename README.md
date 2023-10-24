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
    12 (The number of times dist[v] changes when dist[u]+length(u,v) < dist[v]) minus (the number of nodes that have found shortest path) (implementation without make_heap).

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


<img width="468" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/bf0b96a4-4232-448e-b240-5c354b1493b8">


<img width="479" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/176594a2-7ff2-448c-99ef-396b6e11aaa0">


<img width="473" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/df6b4357-ff45-4f3e-9d4b-f69ccb2870f2">


<img width="478" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/9b2064e1-e7c0-4673-84d3-f1aa4f923d28">


<img width="510" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/ee5af1c0-4d73-4a08-a979-5a8ff1b62720">


<img width="358" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/e18a57fc-1935-4f94-982d-a98523e492aa">


### records for implementation without make_heap


<img width="515" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/79d31b05-ba01-4e4e-b9a5-cf7069aab8f0">

<img width="515" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/e049937e-859a-4c7c-b6c3-a1dff315149e">

<img width="542" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/8fbe0887-ef22-4af7-b27c-f5f1154708ea">

<img width="542" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/7d456512-3792-49e3-bdd8-b320b0039015">

<img width="526" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/4dfc1a24-65ca-4cd4-aac8-a84c8da2d164">

<img width="553" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/442c3938-b927-4632-b04b-ecc1c3d3385e">

<img width="557" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/15ded079-ce1c-4e85-99eb-fa40851efabc">

<img width="581" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/df216acf-078f-4fcb-8b87-c8ceb2f11e03">

<img width="446" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/6c923e03-71b9-4b1b-b48a-b8bf46b28a55">

<img width="316" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/0ca396cb-d672-454e-a806-c5b8929054ee">


### records for data sets with degraded performance

### records for implementation with make_heap

<img width="445" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/70aab710-1279-4559-8be9-b5715d844a92">

<img width="445" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/a98b994b-2490-4516-beeb-9af8ffb4bfe3">

<img width="380" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/cd68eb64-a9b6-4412-8b0f-b90d4a65f632">


### records for implementation without make_heap

<img width="391" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/9bdbcb85-833e-4634-aaa2-6d73106b5244">

<img width="396" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/004e3b60-3115-4216-813b-cae011b69453">

<img width="371" alt="image" src="https://github.com/idler66/SmallStepShortestPath/assets/112096692/e99e12ac-3b12-4241-a3eb-b516ffc82bb0">


    For more informations, you can visit https://bbs.huaweicloud.com/blogs/411649.






