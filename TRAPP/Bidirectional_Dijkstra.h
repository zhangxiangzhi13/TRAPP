//
// Created by 11131 on 2023/8/8.
//
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MASTER_BIDIRECTIONAL_DIJKSTRA_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MASTER_BIDIRECTIONAL_DIJKSTRA_H
const float INF=std::numeric_limits<float >::max();
struct  edge{
    int source;
    int target;
    float distance;
};
struct Compare {
    bool operator()(const std::pair<float, int>& a, const std::pair<float, int>& b) {
        return a.first > b.first; // 使用 > 实现最小堆
    }
};

class Bidirectional_Dijkstra_graph
{
public:
    Bidirectional_Dijkstra_graph()
    {
        edgenumbers=0;
        nodenumbers=0;
    }
    ~Bidirectional_Dijkstra_graph()
    {

    }
    void relax1(int u,int x,float weight)
    {
        if(sf[x]== false && df[x]>df[u]+weight)
        {
            df[x]=df[u]+weight;
            pref[x]=u;
            qf.push(std::make_pair(df[x],x));
        }
    }
    void relax2(int v,int x,float weight)
    {
        if(sb[x]== false && db[x]>db[v]+weight)
        {
            db[x]=db[v]+weight;
            preb[x]=v;
            qb.push(std::make_pair(db[x],x));

        }

    }
    void push_back(int source,int tatget,float distance)
    {
        Graph.push_back({source,tatget,distance});
        Graph.push_back({tatget,source,distance});
        edgenumbers++;
        edgenumbers++;

    }
    std::vector<int> compile(int pre_source,int pre_target ,int pre_nodeumber,int pre_edgenumber)
    {
      //  edgenumbers=pre_edgenumber;
        nodenumbers=pre_nodeumber;



        source=pre_source;
        target=pre_target;
        df.resize(nodenumbers+1);
        db.resize(nodenumbers+1);
        sf.resize(nodenumbers+1);
        sb.resize(nodenumbers+1);
        pref.resize(nodenumbers+1);
        preb.resize(nodenumbers+1);


        qf.push(std::make_pair(0,source));
        qb.push(std::make_pair(0,target));



        for (int i = 0; i < nodenumbers; i++) {
            df[i]=INF;
            db[i]=INF;
            sf[i]= false;
            sb[i]= false;
        }


        df[source]=0;
        db[target]=0;
        pref[source]=-1;
        preb[target]=-1;
        int u,v;
        distance=INF;


        while (!qf.empty() && !qb.empty())
        {

            u=qf.top().second;
            qf.pop();
            v=qb.top().second;
            qb.pop();

            sf[u]= true;
            sb[v]= true;
            for (int i = 0; i <edgenumbers ; i++) {
                if(Graph[i].source==u)
                {
                    relax1(u,Graph[i].target,Graph[i].distance);
                    if(sb[Graph[i].target]== true && df[u]+Graph[i].distance+db[Graph[i].target]<distance)
                    {
                        distance=df[u]+Graph[i].distance+db[Graph[i].target];

                        route.clear();
                        int z;
                        z=u;
                        while (z!=-1)
                        {


                            route.insert(route.begin(),z);
                            z=pref[z];
                        }
                        z=Graph[i].target;
                        while(z!=-1)
                        {
                            route.push_back(z);
                            z=preb[z];
                        }
                    }
                }
                if(Graph[i].target==u)
                {
                    relax1(u,Graph[i].source,Graph[i].distance);
                    if(sb[Graph[i].source]== true && df[u]+Graph[i].distance+db[Graph[i].source]<distance)
                    {
                        distance=df[u]+Graph[i].distance+db[Graph[i].source];

                        route.clear();
                        int z;
                        z=u;
                        while (z!=-1)
                        {
                            //std::cout<<"here20"<<std::endl;

                            route.insert(route.begin(),z);
                            z=pref[z];
                        }
                        z=Graph[i].source;
                        while(z!=-1)
                        {



                            route.push_back(z);
                            z=preb[z];
                        }
                    }
                }
            }

            for (int i = 0; i <edgenumbers ; i++) {
                if(Graph[i].source==v)
                {
                    relax2(v,Graph[i].target,Graph[i].distance);
                    //if(sf[Graph[i].target]== true && df[v]+Graph[i].distance+db[Graph[i].target]<distance)
                    if(sf[Graph[i].target]== true && db[v]+Graph[i].distance+df[Graph[i].target]<distance)

                    {
                        distance=db[v]+Graph[i].distance+df[Graph[i].target];
                        route.clear();
                        int z;
                        z=v;
                        while (z!=-1)
                        {

                            route.insert(route.begin(),z);
                            z=pref[z];
                        }
                        z=Graph[i].target;
                        while(z!=-1)
                        {
                            route.push_back(z);
                            z=preb[z];
                        }

                    }
                }
                if(Graph[i].target==v)
                {
                    relax2(v,Graph[i].source,Graph[i].distance);
//                    if(sf[Graph[i].source]== true && df[v]+Graph[i].distance+db[Graph[i].source]<distance)
                    if(sf[Graph[i].source]== true && db[v]+Graph[i].distance+df[Graph[i].source]<distance)

                    {
                        distance=db[v]+Graph[i].distance+df[Graph[i].source];

                        route.clear();
                        int z;
                        z=v;
                        while (z!=-1)
                        {


                            route.insert(route.begin(),z);
                            z=pref[z];
                        }
                        z=Graph[i].source;
                        while(z!=-1)
                        {


                            route.push_back(z);
                            z=preb[z];
                        }
                    }
                }
            }


            if (df[u]+db[v]>=distance)
            {
                break;
            }

        }



        if(distance==INF){
            route.push_back(-1);
        }
        else {
            std::cout<<"distance:"<<distance<<std::endl;
        }


        return route;
    }

    void test()
    {
        std::cout<<Graph.size()<<std::endl;
        for (int i = 0; i < Graph.size(); i++) {
            std::cout<<"source:"<<Graph[i].source<<std::endl;
            std::cout<<"target:"<<Graph[i].target<<std::endl;
            std::cout<<"distance:"<<Graph[i].distance<<std::endl;
        }


    }

private:
    int  source,target;
    int nodenumbers,edgenumbers;

    std::vector<edge> Graph;
    std::priority_queue<std::pair<float, int>,std::vector<std::pair<float, int>>, Compare> qf;
    std::priority_queue<std::pair<float, int>,std::vector<std::pair<float, int>>, Compare> qb;

    std::vector<float> df;
    std::vector<float> db;

    std::vector<bool> sf;
    std::vector<bool> sb;

    std::vector<int> pref;
    std::vector<int> preb;

    std::vector<int> route;
    float distance;
};
#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MASTER_BIDIRECTIONAL_DIJKSTRA_H
