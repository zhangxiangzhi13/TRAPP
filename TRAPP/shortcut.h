//
// Created by charles chen on 2023/7/25.
//

#ifndef CAR_CLASSIFICATION_SHORTCUT_H
#define CAR_CLASSIFICATION_SHORTCUT_H




#include <vector>
#include <iostream>


class shortcut{

public:
    shortcut(){}

    ~shortcut(){}

    void set_shortcut_limit(float height,float width,float weight){

    }


    float get_distance()
    {
        return distance;
    }


    std::vector<int> get_shortcut_record()
    {
        return shortcut_record;
    }

    void set_shortcut(int start,int end,int in_degree,std::vector<int> route,float pre_distance,bool pre_available)
    {
        distance=pre_distance;
        shortcut_record=route;
    }

    void test()
    {
        std::cout<<distance<<std::endl;
        for (int i = 0; i < shortcut_record.size(); i++) {
            std::cout<<shortcut_record[i]<<std::endl;
        }
    }

private:


    float distance;
    std::vector<int> shortcut_record; ///具体用string还是int还需要考虑 看图的节点用什么表示
    ///用于记录具体路线




};



#endif //CAR_CLASSIFICATION_SHORTCUT_H