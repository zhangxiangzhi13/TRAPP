//
// Created by charles chen on 2023/7/26.
//

#ifndef CAR_CLASSIFICATION_UPPERLAYER_H
#define CAR_CLASSIFICATION_UPPERLAYER_H
#include <iostream>
#include <vector>
#include "shortcut.h"
#include "all_shortcut.h"

class upperlayer{

public:

    upperlayer(){}

    ~upperlayer(){}
    void set_entrancenode(int entrancenode,const std::vector<int>& old_entrance_node_list)
    {
        row.resize(entrancenode+1);
        row[0]=0;
        for (int i = 1; i<=entrancenode ; i++) {
            row[i]=0;
        }
        entrance_node_list=old_entrance_node_list;
        shortcut_value.emplace_back(1,1,1);
        column.push_back(0);
    }


    void add_all_shortcuts(int start ,int end ,int types  )
    {
        shortcut_value.emplace_back(start,end,types);
        for (int i = 0; i < entrance_node_list.size(); i++) {
            if(entrance_node_list[i]==end)
            {
                column.push_back(i);
            }
            if (entrance_node_list[i]==start)
            {
                row[i+1]=row[i+1]+1;
            }
        }
    }
    void final()
    {
        for (int i = 1; i < row.size(); i++) {
            row[i]=row[i-1]+row[i];
        }
    }

    void add_shortcut(int degree ,int start_node,int end_node,const std::vector<int>& route,float  distance)
    {


        int en_start_node,en_end_node;
        for (int i = 0; i < entrance_node_list.size(); i++)
        {
            if(start_node==entrance_node_list[i])
            {
                en_start_node=i+1;
            }
            if (end_node==entrance_node_list[i])
            {
                en_end_node=i+1;
            }
        }
        if (en_start_node>en_end_node)
        {
            int tmp;
            tmp=en_start_node;
            en_start_node=en_end_node;
            en_end_node=tmp;

        }


        for (int i = row[en_start_node-1]+1; i <=row[en_start_node] ; i++)
        {
            if(shortcut_value[i].get_endnode()==end_node)
            {
                shortcut_value[i].add_shortcut(degree,route,distance);
            }
        }


    }


    float query_upperlayer(int start_node,int end_node,int degree)
    {

        float distance;

        int p_start_node,p_end_node;
        for (int i = 0; i < entrance_node_list.size(); i++) {
            if(entrance_node_list[i]==start_node)
            {
                p_start_node=i+1;
            }
            if(entrance_node_list[i]==end_node)
            {
                p_end_node=i+1;
            }
        }
        if (p_start_node>p_end_node)
        {
            p_start_node=p_end_node;
        }
        for (int i = row[p_start_node-1]+1; i <=row[p_start_node] ; i++) {
            if (end_node==shortcut_value[i].get_endnode())
            {
                distance=shortcut_value[i].get_distance(degree);
                break;
            }
        }

        return distance;
    }

    std::vector<int> get_shortcut(int source_node,int end_node,int degree)
    {
        int tmp1,tmp2;
        for (int i = 0; i < entrance_node_list.size(); i++) {
            if(entrance_node_list[i]==source_node)
            {
                tmp1=i+1;
            }
            if(entrance_node_list[i]==end_node)
            {
                tmp2=i+1;
            }
        }
        if (tmp1>tmp2)
        {
            tmp1=tmp2;
        }
        std::vector<int> tmp_route;
        for (int i = row[tmp1-1]+1; i <=row[tmp1] ; i++) {
            if (shortcut_value[i].get_endnode()==end_node)
            {
                tmp_route =shortcut_value[i].get_shortcut(degree);
                break;
            }
        }

        return tmp_route;
    }

    std::vector<std::pair<int,float>> get_order(int source_node,int end_node)
    {
        int tmp1,tmp2;
        for (int i = 0; i < entrance_node_list.size(); i++) {
            if(entrance_node_list[i]==source_node)
            {
                tmp1=i+1;
            }
            if(entrance_node_list[i]==end_node)
            {
                tmp2=i+1;
            }
        }
       // std::cout<<tmp1<<" "<<tmp2<<std::endl;
        if (tmp1>tmp2)
        {
            tmp1=tmp2;
            end_node=source_node;
        }

        int tmp;
        for (int i = row[tmp1-1]+1; i <=row[tmp1] ; i++) {
            if (shortcut_value[i].get_endnode()==end_node)
            {
                tmp=i;
            }
        }
        return shortcut_value[tmp].get_order();
    }

    void make_order()
    {
        for (int i = 1; i < shortcut_value.size(); i++) {
            shortcut_value[i].in_order();
        }
    }

    void test()
{
//        std::cout<<"row:"<<row.size()<<std::endl;
//    for (int i = 0; i <row.size() ; i++) {
//        std::cout<<row[i]<<std::endl;
//    }
    for (int i = 1; i < shortcut_value.size(); i++) {
        shortcut_value[i].test();
    }
}
void get_shortcut_size()
{   int z1=0,z2=0;
    for (int i = 1; i < shortcut_value.size(); i++) {
        
        z1=z1+shortcut_value[i].get_short_size1();
        z2=z2+shortcut_value[i].get_short_size2();  
    }
    std::cout<<"z1: "<<z1<<std::endl;
    std::cout<<"z2: "<<z2<<std::endl;
}
private:
    std::vector<int> entrance_node_list;
    std::vector<all_shortcuts> shortcut_value;
    std::vector<int> column;
    std::vector<int> row;

};

#endif //CAR_CLASSIFICATION_UPPERLAYER_H
