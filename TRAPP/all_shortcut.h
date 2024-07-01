//
// Created by 11131 on 2023/7/29.
//
#ifndef GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MASTER_ALL_SHORTCUT_H
#define GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MASTER_ALL_SHORTCUT_H
#include <vector>
bool compare(const std::pair<int,float> &a,const std::pair<int,float> &b)
{
    return a.second<b.second;
}

class all_shortcuts
{
public:
    all_shortcuts(){}
    ~all_shortcuts(){}
    all_shortcuts(int input_source_node,int input_target_node,int type)
    {
        source_node=input_source_node;
        target_node=input_target_node;
        car_types=type;
        type_position1.resize(car_types+1);
        type_position2.resize(car_types+1);

        distances1.resize(type+1);
        distances2.resize(type+1);

        for (int i = 1; i <=car_types; i++) {
            type_position1[i]=-1;
            type_position2[i]=-1;
            distances1[i]=-1;
            distances2[i]=-1;

        }
    }
    void add_shortcut(int degree,const std::vector<int>& route,float distance)
    {
        add_shortcut1( degree, route, distance);
        add_shortcut2( degree, route, distance);
    }

    void add_shortcut1(int degree,const std::vector<int>& route,float distance)
    {

        int a;
        a=0;
        for (int i = 0; i < shortcut_record1.size(); i++) {
            if(route==shortcut_record1[i])
            {
                distances1[degree]=distance;
                type_position1[degree]=i;
                a=1;


            }
        }
        if(a==0)
        {


            shortcut_record1.push_back(route);
            type_position1[degree]=int(shortcut_record1.size()-1);
            distances1[degree]=distance;
        }
    }

    void add_shortcut2(int degree,const std::vector<int>& route,float distance)
    {

            shortcut_record2.push_back(route);
            type_position2[degree]=int(shortcut_record2.size()-1);
            distances2[degree]=distance;
        
    }

    int get_endnode()
    {
        return  target_node;
    }

    float get_distance(int degree)
    {

        return distances1[degree];
    }

    void test()
    {
    std::cout<<order1.size()<<std::endl;


    }
    std::vector<int> get_shortcut(int degree)
    {

        return shortcut_record1[type_position1[degree]];

    }

    void in_order()
    {
//            std::cout<<type_position.size()<<std::endl;
            for (int i = 1; i <type_position1.size(); i++) {
                if (type_position1[i] != -1) {
//                    std::cout<<"make it"<<std::endl;
//                    order.push_back(std::make_pair(i, distances[i]));
                    order1.emplace_back(i, distances1[i]);

                }
            }

            std::sort(order1.begin(), order1.end(), compare);
    }


    std::vector<std::pair<int,float>> get_order()
    {
        return order1;
    }

 int get_short_size1()
 {
    return shortcut_record1.size();
 }
  int get_short_size2()
 {
    return shortcut_record2.size();
 }
private:
    std::vector<std::pair<int,float>> order1;
    std::vector<std::pair<int,float>> order2;

    int source_node;
    int target_node;
    int car_types;

    std::vector<int> type_position1;
    std::vector<int> type_position2;
    
    std::vector<float> distances1;    
    std::vector<float> distances2;

    std::vector<std::vector<int>> shortcut_record1;
    std::vector<std::vector<int>> shortcut_record2;

};
#endif //GRAPH_PARTITIONING_WITH_NATURAL_CUTS_MASTER_ALL_SHORTCUT_H
