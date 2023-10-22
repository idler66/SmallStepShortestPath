# SmallStepShortestPath（SSSPA）
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
The time complexity of SSSPA also consist of two parts, the time complexity of edges access and the time complexity of Heapify when dist[u]+length(u,v) < dist[v].

For more informations, you can visit https://bbs.huaweicloud.com/blogs/409181 .

## performance test
For more informations, you can visit [https://bbs.huaweicloud.com/blogs/409181](https://bbs.huaweicloud.com/blogs/411649) .

 与Dijkstras最短路径算法对比.

另外，在更大规模数据集datagen-8_2、datagen-8_1、datagen-8_0、datagen-7_9（https://ldbcouncil.org/benchmarks/graphalytics/）等上的测试，其性能在数百倍。因为内存的限制（16G内存），只能测试一亿多条边的数据集（134,267,822    M    datagen-8_1-fb.tar.zst）。

