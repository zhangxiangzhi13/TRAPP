//
// Created by 11131 on 2023/7/3.
//

#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MASTER_GRAPH_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MASTER_GRAPH_H
#include <vector>
#include "type.h"
#include <iostream>
#include "devide_car.h"
#include "all_shortcut.h"
#include "shortcut.h"
#include "upperlayer.h"
#include <limits>
#include "Bidirectional_Dijkstra.h"
#include <chrono>

#include "Dijkstra.h"
struct value{
    float road_length;
    float height;
    float width;
    float weight;
};


bool compareByPercent(const limit& a, const limit& b) {
    return a.percent < b.percent;
}
class  Graph {
public:

    Graph() {

    }

    ~Graph() {}


    void set(int x, int y, int z, std::vector<int> w,std::vector<int> v) {


        node_numbers = x;
        edge_numbers = y;
        cell_numbers = z;
        eachcell = w;



        node_positions = v;
        node_of_cell.resize(cell_numbers+1);
        for (int  i= 1; i < node_positions.size(); i++) {
            node_of_cell[node_positions[i]].push_back(i);
        }
        //  IA=new int[node_numbers+1];
        for (int i = 0; i <= node_numbers; i++)
        {
            IA.push_back(0);
        }

        A.push_back({0, 0, 0, 0});
        JA.push_back(0);



    }

    int get_nodenumbers() {
        return node_numbers;
    }

    int get_edgenumbers() {
        return edge_numbers;
    }

    int get_partnumbers() {
        return cell_numbers;
    }



    void add_edge(int x, int y, float z1, float z2, float z3, float z4) {
        A.push_back({z1, z2, z3, z4});
        JA.push_back(y);
        IA[x]++;
    }

    void final() {
        for (int i = 1; i <= node_numbers; i++) {
            IA[i] = IA[i] + IA[i - 1];
        }

        std::vector<std::vector<limit>> ls;


        for (int i = 1; i <=cell_numbers ; i++) {
            std::vector<float> tmp_height;
            std::vector<float> tmp_width;
            std::vector<float> tmp_weight;
            for (int j = 0; j <node_of_cell[i].size() ; j++) {
                for (int k =IA[node_of_cell[i][j]-1]+1; k <=IA[node_of_cell[i][j]] ; k++) {
                    if(node_positions[JA[k]]==i && JA[k]>node_of_cell[i][j])
                    {

                        tmp_height.push_back(A[k].height);
                        tmp_width.push_back(A[k].width);
                        tmp_weight.push_back((A[k].weight));
                      //  std::cout<<A[k].height<<" "<<A[k].width<<" "<<A[k].weight<<std::endl;
                    }
                }
            }

            std::sort(tmp_height.begin(), tmp_height.end());
            std::sort(tmp_width.begin(), tmp_width.end());
            std::sort(tmp_weight.begin(), tmp_weight.end());

            std::vector<limit> ls1;
            std::vector<limit> ls2;
            std::vector<limit> ls3;

            std::vector<std::vector<limit>> tmp_list;
            tmp_list.push_back(ls1);
            tmp_list.push_back(ls2);
            tmp_list.push_back(ls3);

            limit_of_cell.push_back(tmp_list);

            for (int j = 0; j < tmp_width.size(); j++) {

                bool tmp_decide;

                tmp_decide= false;
                for (int k = 0; k <limit_of_cell[i-1][0].size(); k++) {
                    if (tmp_height[j]==limit_of_cell[i-1][0][k].values)
                    {
                        tmp_decide= true;
                        limit_of_cell[i-1][0][k].time=limit_of_cell[i-1][0][k].time+1;
                        limit_of_cell[i-1][0][k].percent=(limit_of_cell[i-1][0][k].time*1.0)/(tmp_height.size()*1.0);
                    }
                }
                if (tmp_decide== false)
                {
                    limit ls;
                    ls.values=tmp_height[j];
                    ls.time=1;
                    ls.percent=(1.0)/(tmp_height.size()*1.0);
                    limit_of_cell[i-1][0].push_back(ls);

                }

                tmp_decide= false;
                for (int k = 0; k < limit_of_cell[i-1][1].size(); k++) {
                    if (tmp_width[j]==limit_of_cell[i-1][1][k].values)
                    {
                        tmp_decide= true;
                        limit_of_cell[i-1][1][k].time=limit_of_cell[i-1][1][k].time+1;
                        limit_of_cell[i-1][1][k].percent=(limit_of_cell[i-1][1][k].time*1.0)/(tmp_width.size()*1.0);
                    }
                }
                if (tmp_decide== false)
                {
                    limit ls;
                    ls.values=tmp_width[j];
                    ls.time=1;
                    ls.percent=(1.0)/(tmp_height.size()*1.0);
                    limit_of_cell[i-1][1].push_back(ls);

                }

                tmp_decide= false;
                for (int k = 0; k < limit_of_cell[i-1][2].size(); k++) {
                    if (tmp_weight[j]==limit_of_cell[i-1][2][k].values)
                    {
                        tmp_decide= true;
                        limit_of_cell[i-1][2][k].time=limit_of_cell[i-1][2][k].time+1;
                        limit_of_cell[i-1][2][k].percent=(limit_of_cell[i-1][2][k].time*1.0)/(tmp_height.size()*1.0);
                    }
                }
                if (tmp_decide== false)
                {
                    limit ls;
                    ls.values=tmp_weight[j];
                    ls.time=1;
                    ls.percent=(1.0)/(tmp_weight.size()*1.0);
                    limit_of_cell[i-1][2].push_back(ls);

                }

            }

        }

        for (int i = 0; i <limit_of_cell.size() ; i++) {
            std::sort(limit_of_cell[i][0].begin(),limit_of_cell[i][0].end(),[](const limit& a,const limit& b){return a.values<b.values;});
            std::sort(limit_of_cell[i][1].begin(),limit_of_cell[i][1].end(),[](const limit& a,const limit& b){return a.values<b.values;});
            std::sort(limit_of_cell[i][2].begin(),limit_of_cell[i][2].end(),[](const limit& a,const limit& b){return a.values<b.values;});

        }

        refine();
    }

    void entrance() {
        std::cout<<"cell_numbers:"<<cell_numbers<<std::endl;

        std::cout<<"entrance_node"<<std::endl;
        for (int i = 0; i <= cell_numbers; i++) {
            std::vector<int> ls;
            ls.push_back(0);
            entrance_node.push_back(ls);
        }
        for (int i = 1; i <= node_numbers; i++) {

            int a, b, c, d, e;
            e = 0;
            a = node_positions[i];

            b = IA[i - 1] + 1;
            c = IA[i];
            for (; b <= c; b++) {
                d = JA[b];
                if (node_positions[d] != a) {
                    e++;
                }
            }

            if (e >=1) {
                entrance_node[a].push_back(i);
                entrance_node[a][0]++;
            }
        }
        for (int i = 1; i < entrance_node.size(); i++) {
            for (int j = 1; j < entrance_node[i].size(); j++) {
                entrance_node_list.push_back(entrance_node[i][j]);
            }
        }
        upperlayers.set_entrancenode(entrance_node_list.size(), entrance_node_list);
        judge_entrance_node.resize(node_numbers+1);
        for (int i = 0; i < judge_entrance_node.size(); i++) {
            judge_entrance_node[i]=0;
        }
        for (int i = 0; i < entrance_node_list.size(); i++) {
            judge_entrance_node[entrance_node_list[i]]=1;
        }
        std::cout<<entrance_node_list.size()<<std::endl;
    }


    void Dijkstra(int start_node) {

        int start_cell;
        start_cell=node_positions[start_node];
        for (int i = 1; i < cars_divided[start_cell].size(); i++) {

            std::vector<int> update;//0可更新，1已更新
            std::vector<float> distance;
            std::vector<int> front_node;//前置点
            update.resize(node_numbers + 1);
            distance.resize(node_numbers + 1);
            front_node.resize(node_numbers + 1);


            for (int j = 0; j < node_numbers + 1; j++)
            {
                front_node[j]=-1;
                update[j] = 0;
                distance[j] = std::numeric_limits<float>::max();
            }


            int a;
            a = 1;
            distance[start_node] = 0;

            while (a) {
                int min_position,  start, end;
                float min_value;
                min_value = std::numeric_limits<float>::max();
                a = 0;

                for (int j = 1; j < node_numbers + 1; j++) {
                    if (start_cell==node_positions[j]&&distance[j] < min_value && update[j] == 0 ) {
                        min_value = distance[j];
                        min_position = j;
                        a = 1;
                    }
                }
                start = IA[min_position - 1] + 1;
                end = IA[min_position];

                update[min_position] = 1;

                for (int j = start; j <= end; j++) {
                    if (node_positions[JA[j]]==start_cell &&(distance[min_position] + A[j].road_length < distance[JA[j]]) && (A[j].height>=cars_divided[start_cell][i][0])&&(A[j].width>=cars_divided[start_cell][i][1])&&(A[j].weight>=cars_divided[start_cell][i][2])) {
                        distance[JA[j]] = distance[min_position] + A[j].road_length;
                        front_node[JA[j]] = min_position;
                    }
                }

            }
            int z1;
            for (int k = 0; k < entrance_node_list.size(); k++) {
                if(start_node==entrance_node_list[k])
                {
                    z1=k;
                }
            }
            for (int j = z1+1; j < entrance_node_list.size(); j++) {

                if ( node_positions[start_node]==node_positions[entrance_node_list[j]] ) {

                    float route_distance = distance[entrance_node_list[j]];

                    std::vector<int> route;
                    int c;
                    c = entrance_node_list[j];

                    route.insert(route.begin(), c);

                    while (1) {


                        route.insert(route.begin(), front_node[c]);

                        c = front_node[c];

                        if (c == start_node || c==-1) {
                            break;
                        }
                    }
                    bool available= true;
                    if(route_distance==std::numeric_limits<float>::max())
                    {
                        available= false;
                    }
                       // std::cout << " i:" << i << " " << start_node << " " << entrance_node_list[j] << " "<< route_distance << std::endl;
                       if(available) {
                           upperlayers.add_shortcut(i, start_node, entrance_node_list[j], route, route_distance);
                       }
                }
            }
        }

    }

    void compute_shortcut() {
        shortcuts=0;
        
        for (int i = 1; i <entrance_node.size() ; i++) {
            for (int j = 1; j <entrance_node[i].size() ; j++) {
                for (int k = j+1; k <entrance_node[i].size() ; k++) {
                    upperlayers.add_all_shortcuts(entrance_node[i][j],entrance_node[i][k],int(cars_divided[i].size()-1));
                    shortcuts=shortcuts+int(cars_divided[i].size()-1);
                }
            }
        }
        upperlayers.final();
        int a=0;
        for (int i = 1; i < entrance_node.size(); i++) {
            for (int j = 1; j <entrance_node[i].size() ; j++) {
                std::cout<<a<<std::endl;
                a++;
                Dijkstra(entrance_node[i][j]);
            }
        }


        upperlayers.make_order();
    }

    void query(int source_node,int end_node,float height,float width ,float weight)
    {
        auto start1 = std::chrono::high_resolution_clock::now();

        accurate_dijastra(source_node,end_node,height,width,weight);
        auto end1 = std::chrono::high_resolution_clock::now();
        // 计算时间差
        auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);
        std::cout << "time: " << duration1.count() << " microsecond" << std::endl;

        Bidirectional_Dijkstra_graph bidirectionalDijkstraGraph;
        Dijkstra_graph Dijkstra_Graph;

       int start_cell,end_cell;

        start_cell=node_positions[source_node];
        end_cell=node_positions[end_node];


        auto start2 = std::chrono::high_resolution_clock::now();


        for (int i = 0; i < node_of_cell[start_cell].size();i++) {
            for (int j = IA[node_of_cell[start_cell][i]-1]+1; j <=IA[node_of_cell[start_cell][i]] ; j++) {
                if (node_positions[JA[j]]==start_cell && A[j].height>=height && A[j].width>=width && A[j].weight>=weight && node_of_cell[start_cell][i]<JA[j])
                {
                   bidirectionalDijkstraGraph.push_back(node_of_cell[start_cell][i],JA[j],A[j].road_length);
                    Dijkstra_Graph.push_back(node_of_cell[start_cell][i],JA[j],A[j].road_length);
                }
            }
        }


        auto start3 = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < node_of_cell[end_cell].size();i++) {
            for (int j = IA[node_of_cell[end_cell][i]-1]+1; j <=IA[node_of_cell[end_cell][i]] ; j++) {
                if (node_positions[JA[j]]==end_cell && A[j].height>=height && A[j].width>=width && A[j].weight>=weight &&node_of_cell[end_cell][i]<JA[j])
                {
                    bidirectionalDijkstraGraph.push_back(node_of_cell[end_cell][i],JA[j],A[j].road_length);
                    Dijkstra_Graph.push_back(node_of_cell[end_cell][i],JA[j],A[j].road_length);
                }
            }
        }



        auto start4 = std::chrono::high_resolution_clock::now();

        for (int i = 1; i < entrance_node.size(); i++) {

            for (int j = 1; j <=entrance_node[i][0] ; j++) {


                for (int k = j+1; k <=entrance_node[i][0] ; k++) {

                int degree=-1;

                  std::vector<std::pair<int,float>> degree_order;
                if(cars_divided[node_positions[entrance_node[i][j]]].size()!=1) {
                    degree_order = upperlayers.get_order(entrance_node[i][j], entrance_node[i][k]);
                }


                  for (int l = 0; l < degree_order.size(); l++) {

                        if (cars_divided[node_positions[entrance_node[i][j]]][degree_order[l].first][0]>=height && cars_divided[node_positions[entrance_node[i][j]]][degree_order[l].first][1]>=width &&cars_divided[node_positions[entrance_node[i][j]]][degree_order[l].first][2]>=weight)
                        {
                            degree=degree_order[l].first;
                            break;
                        }
                    }
                    if(degree!=-1) {
                        float tmp = upperlayers.query_upperlayer(entrance_node[i][j], entrance_node[i][k], degree);

                        if (tmp != -1 ) {

                            bidirectionalDijkstraGraph.push_back(entrance_node[i][j], entrance_node[i][k], tmp);
                            Dijkstra_Graph.push_back(entrance_node[i][j], entrance_node[i][k], tmp);
                        }
                    }
                }


                for (int k = IA[entrance_node[i][j]-1]+1; k <= IA[entrance_node[i][j]] ; k++) {
                    if(node_positions[JA[k]]!=node_positions[entrance_node[i][j]] && A[k].height>=height && A[k].width>=width && A[k].weight>=weight)
                    {
                        bidirectionalDijkstraGraph.push_back(entrance_node[i][j],JA[k],A[k].road_length);
                        Dijkstra_Graph.push_back(entrance_node[i][j],JA[k],A[k].road_length);
                    }
                }

            }
        }



        auto start5 = std::chrono::high_resolution_clock::now();

        std::vector<int> pre_route = bidirectionalDijkstraGraph.compile(source_node, end_node,node_numbers,edge_numbers);


        std::vector<int> after_route;


        auto end2 = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);
        auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(start3 - start2);
        auto duration4 = std::chrono::duration_cast<std::chrono::microseconds>(start4 - start3);
        auto duration5 = std::chrono::duration_cast<std::chrono::microseconds>(start5 - start4);
        auto duration6 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start5);

        std::cout << "time: " << duration2.count() << " microsecond" << std::endl;

    std::cout << std::endl;

    }

    void accurate_dijastra(int start_node,int end_node,float height,float width,float weight)
    {


                std::vector<int> update;//0可更新，1已更新
                std::vector<int> distance;
                std::vector<int> front_node;//前置点
                update.resize(node_numbers + 1);
                distance.resize(node_numbers + 1);
                front_node.resize(node_numbers + 1);


                for (int j = 0; j < node_numbers + 1; j++)

                {
                    front_node[j]=-1;
                    update[j] = 0;
                //  distance[j] = std::numeric_limits<int>::max();
                distance[j] = -1;

                }

                int a;
                a = 1;
                distance[start_node] = 0;

                while (a) {

                    int min_position,  start, end;
                    float min_value;
                    min_value = std::numeric_limits<float>::max();
                    a = 0;

                    for (int j = 1; j < node_numbers + 1; j++) {
                        if ((distance[j] < min_value && distance[j]!=-1) && update[j] == 0) {
                            min_value = distance[j];
                            min_position = j;
                            a = 1;
                        }
                    }

                    start = IA[min_position - 1] + 1;
                    end = IA[min_position];

                    update[min_position] = 1;

                    for (int j = start; j <= end; j++) {

                        if (((distance[min_position] + A[j].road_length < distance[JA[j]])||distance[JA[j]]==-1) && (A[j].height>=height)&&(A[j].width>=width)&&(A[j].weight>=weight)) {
                            distance[JA[j]] = distance[min_position] + A[j].road_length;
                            front_node[JA[j]] = min_position;
                        }

                    }

                }



                        float route_distance = distance[end_node];
                        std::vector<int> route;
                        int c;
                        c = end_node;
                        route.insert(route.begin(), c);
                        while (1) {
                            route.insert(route.begin(), front_node[c]);

                            c = front_node[c];

                            if (c == start_node || c==-1) {
                                break;
                            }
                        }
    if(route_distance==std::numeric_limits<float>::max() ||route_distance<=0)
    {
        std::cout<<"no accurate_distance"<<std::endl;
    }
    else {
        std::cout << "accurate_distance: " << route_distance << std::endl;

    }
        }

    int get_cell(int node)
    {
        return node_positions[node];
    }

    void refine()
    {

        std::vector<std::vector<float>> cars_divided_initial0;

        cars_divided.push_back(cars_divided_initial0);


        cars_divided_initial = car_divided0(); //kmeans输出的结果



        for (int i = 0; i <limit_of_cell.size() ; i++) {


            std::vector<std::vector<float>> cars_divided_initial1;
            cars_divided_initial1=cars_divided_initial;
        
            cars_divided_initial1 = car_divided_precise(cars_divided_initial,limit_of_cell[i]);//实际道路限制进行分级精确化
            cars_divided_initial1 = car_divided_rematch(cars_divided_initial1);//rematch
            
            cars_divided_initial1.insert(cars_divided_initial1.begin(), {0.0, 0.0, 0.0});
            // for(int j=0; j<cars_divided_initial1.size();j++)
            // {
            //     std::cout<<"i "<<i<<"  "<<cars_divided_initial1[j][0]<<" "<< cars_divided_initial1[j][1]<<" "<<cars_divided_initial1[j][2]<<std::endl;
            // }
            cars_divided.push_back(cars_divided_initial1);


        }




    }



private:

    int node_numbers;//点数目
    int edge_numbers;//边数目
    int cell_numbers;//分类数目


    std::vector<int> eachcell;//各类含有多少点
    //int *eachcell;//各类含有多少点
    std::vector<std::vector<int>> node_of_cell;

    std::vector<int> node_positions;//每个点属于的cell


    std::vector<std::vector<float>> cars_divided_initial;//分类标准
    std::vector<std::vector<std::vector<float>>> cars_divided;//优化后分类标准


    std::vector<std::vector<int>> entrance_node;//
    std::vector<int> entrance_node_list;//
    std::vector<int> judge_entrance_node;
    int shortcuts=0;
    //std::vector<std::pair<int ,int>> entrance_node
    std::vector<value> A;//value
    //int *IA;//各行非零个数
    std::vector<int> IA;
    std::vector<int> JA;//column

    upperlayer upperlayers;
    std::vector<std::vector<std::vector<limit>>> limit_of_cell;

};

#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MASTER_GRAPH_H
