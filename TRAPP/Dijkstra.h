//
// Created by 11131 on 2023/9/12.
//

#ifndef READFILE_CRP_DIJKSTRA_H
#define READFILE_CRP_DIJKSTRA_H
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
//const float INF=std::numeric_limits<float >::max();
//struct  edge{
//    int source;
//    int target;
//    float distance;
//};
//struct Compare {
//    bool operator()(const std::pair<float, int>& a, const std::pair<float, int>& b) {
//        return a.first > b.first; // 使用 > 实现最小堆
//    }
//};
struct node_edge{
    int node;
    std::vector<int> edge;
    std::vector<float> distance;
};
class Dijkstra_graph
{
public:
    Dijkstra_graph()
    {
        edgenumbers=0;
        nodenumbers=0;
    }
    ~Dijkstra_graph()
    {

    }

    void push_back(int source,int tatget,float distance)
    {
        edgenumbers++;
        if(Graph.count(source)>0)
        {
            Graph[source].edge.push_back(tatget);
            Graph[source].distance.push_back(distance);
        } else{
            node_list.push_back(source);
            nodenumbers++;
            node_edge ls;
            ls.node=source;
            ls.edge.push_back(tatget);
            ls.distance.push_back(distance);
            Graph[source]=ls;
        }
        if(Graph.count(tatget)>0)
        {
            Graph[tatget].edge.push_back(source);
            Graph[tatget].distance.push_back(distance);
        } else{
            node_list.push_back(tatget);
            nodenumbers++;
            node_edge ls;
            ls.node=tatget;
            ls.edge.push_back(source);
            ls.distance.push_back(distance);
            Graph[tatget]=ls;
        }
    }
    void compile(int start_node,int end_node)
    {

     //   std::vector<int> update;//0可更新，1已更新
     //   std::vector<int> distance;
     //   std::vector<int> front_node;//前置点
        std::unordered_map<int,int> update;
        std::unordered_map<int,float> distances;
        std::unordered_map<int ,int> front_node;
        //update.resize(nodenumbers + 1);
        //distance.resize(nodenumbers + 1);
        //front_node.resize(nodenumbers + 1);


        for (int j = 0; j < node_list.size(); j++)
        {
            front_node[node_list[j]]=-1;
            update[node_list[j]] = 0;
            distances[node_list[j]] = -1;

        }

        int a;
        a = 1;
        distances[start_node] = 0;

        while (a) {
      //      std::cout<<"stack"<<std::endl;

            int min_position;
            float min_value;
            min_value = std::numeric_limits<float>::max();
            a = 0;

            for (int j = 0; j <node_list.size() ; j++) {
                if ((distances[node_list[j]] < min_value && distances[node_list[j]]!=-1) && update[node_list[j]] == 0) {
                    min_value = distances[node_list[j]];
                    min_position = node_list[j];
                    a = 1;
                }
            }

            update[min_position] = 1;
        //    std::cout<<min_position<<std::endl;
            for (int j =0; j <Graph[min_position].edge.size(); j++) {

                if (((min_value + Graph[min_position].distance[j] < distances[Graph[min_position].edge[j]])||distances[Graph[min_position].edge[j]]==-1) ) {
                    distances[Graph[min_position].edge[j]] = distances[min_position] + Graph[min_position].distance[j];
                    front_node[Graph[min_position].edge[j]] = min_position;
                }

            }

        }



        float route_distance = distances[end_node];
//        std::cout<<"distance"<<std::endl;
//        for (int i = 0; i < node_list.size(); i++) {
//            std::cout<<distances[node_list[i]]<<"   ";
//        }
        std::cout<<std::endl;
        std::vector<int> route;
        int c;
        c = end_node;
        route.insert(route.begin(), c);
        while (1) {
            //std::cout<<"hh"<<std::endl;
            route.insert(route.begin(), front_node[c]);

            c = front_node[c];

            if (c == start_node || c==-1) {
                break;
            }
        }
    //    std::cout<<"dsa"<<route_distance<<std::endl;
        if(route_distance==std::numeric_limits<float>::max() ||route_distance<=0)
        {
            std::cout<<"no distance"<<std::endl;
        }
        else {
            std::cout << "distance: " << route_distance << std::endl;
            // std::cout<<std::numeric_limits<int>::max()<<std::endl;
//            std::cout << "route:" << std::endl;
//            for (int i = 0; i < route.size(); i++) {
//                std::cout << route[i] << std::endl;
//            }
        }
    }




private:
    int nodenumbers,edgenumbers;
    std::unordered_map<int,node_edge> Graph;
    std::vector<int> node_list;
    std::vector<int> route;

};


#endif //READFILE_CRP_DIJKSTRA_H
