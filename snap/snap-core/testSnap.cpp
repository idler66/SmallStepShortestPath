// Small example testing basic functionality of SNAP

#include "Snap.h"

#include <time.h>
#include <cstdlib>
#include <fstream>

#include <streambuf>
#include <cmath>

void testHeap( IShortestPathGraph * Graph1, int nid,
          clock_t* time1 ,clock_t* time2,
          TSnap::TDijkstraStat& DijkstraStat,
          TSnap::TSmallStepStat& SmallStepStat) {
    TIntFltH NIdDistH2;
    clock_t startTime2,endTime2;
    startTime2 = clock();
    TSnap::GetWeightedShortestPathByDijkstraByHeap(Graph1, nid, NIdDistH2,
                                                   DijkstraStat);
//    GetWeightedShortestPathByDijkstraMemory
//    GetWeightedShortestPathByDijkstraByHeap
    endTime2 = clock();
    *time2 = (double)(endTime2 - startTime2) ;
    
   TIntFltH NIdDistH;
   clock_t startTime,endTime;
       startTime = clock();
   TSnap::GetWeightedShortestPathBySmallStepOnNGraph(Graph1, nid, NIdDistH,
                                                     SmallStepStat);
       endTime = clock();
    *time1 = (double)(endTime - startTime);
   
    for (TIntFltH::TIter It = NIdDistH2.BegI(); It < NIdDistH2.EndI(); It++) {
      int node_id = It.GetKey();//node id
      double centr = It.GetDat();//distanc to source node
        if (centr != __DBL_MAX__) {
            double centr2 = NIdDistH.GetDat(node_id);
            assert(centr == centr2);
        }
    }

    for (TIntFltH::TIter It = NIdDistH.BegI(); It < NIdDistH.EndI(); It++) {
      int node_id = It.GetKey();//node id
      double centr = It.GetDat();//distanc to source node
        if (centr != __DBL_MAX__) {
            double centr2 = NIdDistH2.GetDat(node_id);
            assert(centr == centr2);
        }

    }
}
void testMemory( IShortestPathGraph * Graph1, int nid,
          clock_t* time1 ,clock_t* time2,
          TSnap::TDijkstraStat& DijkstraStat,
          TSnap::TSmallStepStat& SmallStepStat) {
    TIntFltH NIdDistH2;
    clock_t startTime2,endTime2;
    startTime2 = clock();
    TSnap::GetWeightedShortestPathByDijkstraMemory(Graph1, nid, NIdDistH2,
                                                   DijkstraStat);
//    GetWeightedShortestPathByDijkstraMemory
//    GetWeightedShortestPathByDijkstraByHeap
    endTime2 = clock();
    *time2 = (double)(endTime2 - startTime2) ;
    
   TIntFltH NIdDistH;
   clock_t startTime,endTime;
       startTime = clock();
   TSnap::GetWeightedShortestPathBySmallStepOnNGraph(Graph1, nid, NIdDistH,
                                                     SmallStepStat);
       endTime = clock();
    *time1 = (double)(endTime - startTime);
   
    for (TIntFltH::TIter It = NIdDistH2.BegI(); It < NIdDistH2.EndI(); It++) {
      int node_id = It.GetKey();//node id
      double centr = It.GetDat();//distanc to source node
        if (centr != __DBL_MAX__) {
            double centr2 = NIdDistH.GetDat(node_id);
            assert(centr == centr2);
        }
    }

    for (TIntFltH::TIter It = NIdDistH.BegI(); It < NIdDistH.EndI(); It++) {
      int node_id = It.GetKey();//node id
      double centr = It.GetDat();//distanc to source node
        if (centr != __DBL_MAX__) {
            double centr2 = NIdDistH2.GetDat(node_id);
            assert(centr == centr2);
        }

    }
}
void compairSmallStepAndDijkstras(std::string name, bool dir) {

    std::string bstr = "/Users/jufanwang/SmallStepShortestPath/snap/dataset/u-w/";
    std::string cstr = name + "/" + name;
    
    std::string dbstr = "/Users/jufanwang/SmallStepShortestPath/snap/dataset/d-w/";
    std::string dcstr = name;
    
    std::string istr = ".edges";
    
    
    PNGraph Graph1;
    PUNGraph UGraph1;
    if (dir) {
        Graph1 = TSnap::LoadAttrEdgeList<PNGraph>((dbstr+dcstr+istr).c_str(), 0, 1, 2);
        Graph1->sortEdgeByAttr();
    }else {
        UGraph1 = TSnap::LoadAttrEdgeList<PUNGraph>((bstr+cstr+istr).c_str(), 0, 1, 2);
        UGraph1->sortEdgeByAttr();
    }
        

        srand((unsigned)time(NULL));
      int *randomNodeIDIndex;
    if (dir) {
        randomNodeIDIndex= (int*)malloc(sizeof(int)*Graph1->GetNodes());
        memset(randomNodeIDIndex,0, sizeof(int)*Graph1->GetNodes());
    }else {
        randomNodeIDIndex= (int*)malloc(sizeof(int)*UGraph1->GetNodes());
        memset(randomNodeIDIndex,0, sizeof(int)*UGraph1->GetNodes());
    }
    
        
        int count = 0;
       int account = 0;
    int rindex ;
        while (count < 10 && account < 2000) {
            if (dir) {
                rindex = (rand()%Graph1->GetNodes());
            }else {
                rindex = (rand()%UGraph1->GetNodes());
            }
            if (randomNodeIDIndex[rindex] ==0) {
                randomNodeIDIndex[rindex] = 1;
                count++;
            }
            account++;
        }

        clock_t smallStepTime = 0;
        clock_t DijkstraTime = 0;
        TSnap::TDijkstraStat DijkstraStat;
        TSnap::TSmallStepStat SmallStepStat;
        std::ofstream oFile;
    std::string genbase = "/Users/jufanwang/SmallStepShortestPath/snap/dataset/gen/";
    std::string ostr = ".csv";
    oFile.open((genbase+name+ostr).c_str(), std::ios::out | std::ios::trunc);

    int index = 0;
    if (dir) {
        for (TNGraph::TNodeI NI = Graph1->BegNI(); NI < Graph1->EndNI(); NI++) {
            if(randomNodeIDIndex[index] == 1){
                int nid = NI.GetId();
                DijkstraStat.restat();
                SmallStepStat.restat();

                testMemory(Graph1(), nid,
                     &smallStepTime, &DijkstraTime,
                     DijkstraStat, SmallStepStat);
           oFile<< DijkstraStat.getNodeCount() << ","
                << (double)SmallStepStat.getVisitedEdgeNum()/DijkstraStat.getNodeCount() << ","
                << (double)DijkstraStat.getReHeapCount()/DijkstraStat.getNodeCount() << ","
                << (double)DijkstraTime/smallStepTime<< ","
                << nid << ","
                << (double)SmallStepStat.getVisitedEdgeNum() << ","
                << (double)DijkstraStat.getReHeapCount() << ","
                << smallStepTime << "," << (double)smallStepTime/CLOCKS_PER_SEC << ","
                << DijkstraTime << "," << (double)DijkstraTime/CLOCKS_PER_SEC<<","
                << (double)DijkstraStat.getUpdateNum()<<","
                << "memory"
                << std::endl;
                
                DijkstraStat.restat();
                SmallStepStat.restat();
                testHeap(Graph1(), nid,
                     &smallStepTime, &DijkstraTime,
                     DijkstraStat, SmallStepStat);
           oFile<< DijkstraStat.getNodeCount() << ","
                << (double)SmallStepStat.getVisitedEdgeNum()/DijkstraStat.getNodeCount() << ","
                << (double)DijkstraStat.getReHeapCount()/DijkstraStat.getNodeCount() << ","
                << (double)DijkstraTime/smallStepTime<< ","
                << nid << ","
                << (double)SmallStepStat.getVisitedEdgeNum() << ","
                << (double)DijkstraStat.getReHeapCount() << ","
                << smallStepTime << "," << (double)smallStepTime/CLOCKS_PER_SEC << ","
                << DijkstraTime << "," << (double)DijkstraTime/CLOCKS_PER_SEC <<","
                << (double)DijkstraStat.getUpdateNum()<<","
                << "heap"
                << std::endl;
            }
            index++;
        }
    }else {
        for (TUNGraph::TNodeI NI = UGraph1->BegNI(); NI < UGraph1->EndNI(); NI++) {
            if(randomNodeIDIndex[index] == 1){
                int nid = NI.GetId();
                DijkstraStat.restat();
                SmallStepStat.restat();
                
                testMemory(UGraph1(), nid,
                     &smallStepTime, &DijkstraTime,
                     DijkstraStat, SmallStepStat);
           oFile<< DijkstraStat.getNodeCount() << ","
                << (double)SmallStepStat.getVisitedEdgeNum()/DijkstraStat.getNodeCount() << ","
                << (double)DijkstraStat.getReHeapCount()/DijkstraStat.getNodeCount() << ","
                << (double)DijkstraTime/smallStepTime<< ","
                << nid << ","
                << (double)SmallStepStat.getVisitedEdgeNum() << ","
                << (double)DijkstraStat.getReHeapCount() << ","
                << smallStepTime << "," << (double)smallStepTime/CLOCKS_PER_SEC << ","
                << DijkstraTime << "," << (double)DijkstraTime/CLOCKS_PER_SEC<<","
                << (double)DijkstraStat.getUpdateNum()<<","
                << "memory"
                << std::endl;
                
                DijkstraStat.restat();
                SmallStepStat.restat();
                testHeap(UGraph1(), nid,
                     &smallStepTime, &DijkstraTime,
                     DijkstraStat, SmallStepStat);
           oFile<< DijkstraStat.getNodeCount() << ","
                << (double)SmallStepStat.getVisitedEdgeNum()/DijkstraStat.getNodeCount() << ","
                << (double)DijkstraStat.getReHeapCount()/DijkstraStat.getNodeCount() << ","
                << (double)DijkstraTime/smallStepTime<< ","
                << nid << ","
                << (double)SmallStepStat.getVisitedEdgeNum() << ","
                << (double)DijkstraStat.getReHeapCount() << ","
                << smallStepTime << "," << (double)smallStepTime/CLOCKS_PER_SEC << ","
                << DijkstraTime << "," << (double)DijkstraTime/CLOCKS_PER_SEC <<","
                << (double)DijkstraStat.getUpdateNum() <<","
                << "heap"
                << std::endl;
            }
            index++;
        }
    }
   
    oFile.close();
}

//y = 23.46945 - 11.2186*x1 +  23.44935*x2

//y = 118.50312 − 98.83127*x1 + 13.89933*x2 + 20.41228*x1*x1
//y = 118.50312 − 98.83127*2.15711 + 13.89933*0.113037 + 20.41228*2.15711*2.15711
////y = 118.50312 − 98.83127*2.48039 + 13.89933*0.127451 + 20.41228*2.48039∗2.48039
//y=17.18604 − 8.39503⋅x1 + 26.81102⋅x2
//y=1.81804 −1.16118⋅x1+17.78196⋅x2− 0.00012⋅x3− 43.95885⋅x2∗x2+0.00307⋅x2∗x3+0⋅x3∗x3 正态性不好
//y = 2.23583 − 1.19747 ⋅ x 1 + 20.46337 ⋅ x 2 − 0.00036 ⋅ x 3 − 55.43522 ⋅ x 2 ∗ x 2 + 0.00347 ⋅ x 2 ∗ x 3
//y=0.85274−0.20355⋅x1+2.84067⋅x2+0.00024⋅x3−9.66391⋅x2∗x2+0.005⋅x2∗x3
 
int main(int argc, char* argv[]) {
        
    compairSmallStepAndDijkstras("bio-CE-GN", false);
    compairSmallStepAndDijkstras("bio-CE-CX", false);//11
    compairSmallStepAndDijkstras("bio-DM-CX", false);//3.6
    compairSmallStepAndDijkstras("bio-HS-CX", false);//3.6
    compairSmallStepAndDijkstras("bio-SC-HT", false);//2.2

    compairSmallStepAndDijkstras("bio-human-gene1", false);
    compairSmallStepAndDijkstras("bio-human-gene2", false);
    compairSmallStepAndDijkstras("bio-mouse-gene", false);//5.x
    compairSmallStepAndDijkstras("bio-WormNet-v3", false);//11
    
//    compairSmallStepAndDijkstras("datagen-8_0-fb", false);//
//    compairSmallStepAndDijkstras("datagen-8_1-fb", false);//2
//    compairSmallStepAndDijkstras("datagen-8_2-zf", false);//
//    compairSmallStepAndDijkstras("datagen-8_3-zf", false);//

//    compairSmallStepAndDijkstras("datagen-7_5-fb", false);//11
//    compairSmallStepAndDijkstras("datagen-7_6-fb", false);//11
//    compairSmallStepAndDijkstras("datagen-7_7-zf", false);//11
//    compairSmallStepAndDijkstras("datagen-7_8-zf", false);//11
//    compairSmallStepAndDijkstras("datagen-7_9-fb", false);//11

    compairSmallStepAndDijkstras("USairport500", true);//11
    compairSmallStepAndDijkstras("OClinks_w_chars", true);//11
    compairSmallStepAndDijkstras("OClinks_w", true);//11
//
    compairSmallStepAndDijkstras("celegans_n306", true);//11
    compairSmallStepAndDijkstras("Cross_Parker-Consulting_info", true);//11
    compairSmallStepAndDijkstras("Cross_Parker-Consulting_value", true);//11
    compairSmallStepAndDijkstras("Cross_Parker-Manufacturing_aware", true);//11
    compairSmallStepAndDijkstras("Cross_Parker-Manufacturing_info", true);//11
    compairSmallStepAndDijkstras("Freemans_EIES-1_n48", true);//11
    compairSmallStepAndDijkstras("Freemans_EIES-2_n48", true);//11


  // create a graph and save it
  { PNGraph Graph = TNGraph::New();
  for (int i = 0; i < 10; i++) {
    Graph->AddNode(i); }
  for (int i = 0; i < 10; i++) {
    Graph->AddEdge(i, TInt::Rnd.GetUniDevInt(10)); }
  TSnap::SaveEdgeList(Graph, "graph.txt", "Edge list format"); }
  // load a graph
  PNGraph Graph;
  Graph = TSnap::LoadEdgeList<PNGraph>("graph.txt", 0, 1);
  // traverse nodes
  for (TNGraph::TNodeI NI = Graph->BegNI(); NI < Graph->EndNI(); NI++) {
    printf("NodeId: %d, InDegree: %d, OutDegree: %d\n", NI.GetId(), NI.GetInDeg(), NI.GetOutDeg());
    printf("OutNodes: ");
    for (int e = 0; e < NI.GetOutDeg(); e++) { printf("  %d", NI.GetOutNId(e)); }
    printf("\nInNodes: ");
    for (int e = 0; e < NI.GetInDeg(); e++) { printf("  %d", NI.GetInNId(e)); }
    printf("\n\n");
  }
  // graph statistic
  TSnap::PrintInfo(Graph, "Graph info");
  PNGraph MxWcc = TSnap::GetMxWcc(Graph);
  TSnap::PrintInfo(MxWcc, "Largest Weakly connected component");
  // random graph
  PNGraph RndGraph = TSnap::GenRndGnm<PNGraph>(100, 1000);
  TGStat GraphStat(RndGraph, TSecTm(1), TGStat::AllStat(), "Gnm graph");
  GraphStat.PlotAll("RndGraph", "Random graph on 1000 nodes");
  // Forest Fire graph
  { TFfGGen ForestFire(false, 1, 0.35, 0.30, 1.0, 0.0, 0.0);
  ForestFire.GenGraph(100);
  PNGraph FfGraph = ForestFire.GetGraph(); }
  // network
  TPt<TNodeEDatNet<TStr, TStr> > Net = TNodeEDatNet<TStr, TStr>::New();
  Net->AddNode(0, "zero");
  Net->AddNode(1, "one");
  Net->AddEdge(0, 1, "zero to one");

  const PNGraph DirectedGraph = TNGraph::New();
  for (int i = 0; i < 10; i++) {
    DirectedGraph->AddNode(i);
  }

  DirectedGraph->AddEdge(0, 1);
  DirectedGraph->AddEdge(1, 2);
  DirectedGraph->AddEdge(2, 3);
  DirectedGraph->AddEdge(3, 4);
  DirectedGraph->AddEdge(4, 5);
  DirectedGraph->AddEdge(5, 6);
  DirectedGraph->AddEdge(6, 7);
  DirectedGraph->AddEdge(7, 2);
  DirectedGraph->AddEdge(8, 9);

  TIntFltH nodeBtwH;
  TIntPrFltH edgeBtwH;


  printf("Testing Betweenness Centrality Calculation \n");
  TSnap::GetBetweennessCentr<PNGraph> (DirectedGraph, nodeBtwH, edgeBtwH, true);
  for (TIntFltH::TIter It = nodeBtwH.BegI(); It < nodeBtwH.EndI(); It++) {
    int node_id = It.GetKey();
    double centr = It.GetDat();
    printf("NodeId: %d, Centr: %f \n", node_id, centr);
  }

//   printf("Testing Closeness Centrality Calculation \n");
//   for (TNGraph::TNodeI NI = DirectedGraph->BegNI(); NI < DirectedGraph->EndNI(); NI++) {
//     int id = NI.GetId();
//     double centr = TSnap::GetClosenessCentr<PNGraph>(DirectedGraph, id, true);
//     printf("NodeId: %d, Centr: %f \n", id, centr);
//   }

  return 0;
}
