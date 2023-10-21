# SmallStepShortestPath
SSSPA, A new shortest path algorithm that completely avoids problems caused by relaxation operations of Dijkstra's algorithm

小步最短路径算法性能测试，及与Dijkstras最短路径算法对比，请参考 https://bbs.huaweicloud.com/blogs/411649。

另外，在更大规模数据集datagen-8_2、datagen-8_1、datagen-8_0、datagen-7_9（https://ldbcouncil.org/benchmarks/graphalytics/）等上的测试，其性能在1200倍以上。因为内存的限制（16G内存），只能测试一亿多条边的数据集（134,267,822    M    datagen-8_1-fb.tar.zst）。

小步最短路径算法的时间复杂度，可参考 https://bbs.huaweicloud.com/blogs/409181 。
