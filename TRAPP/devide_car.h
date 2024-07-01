//
// Created by charles chen on 2023/9/7.
//


#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "vehicle.h"
#include <sstream>
#include <algorithm>
#include "type.h"



/*
 * 此系统主要分为以下几个部分：、
 * PUNCH算法、车辆分级算法、shortcut建立算法、路线规划部分
 * */

void read_files_partition(){
//此函数用于读取分区文件(punch后的文件)
//to read partition files

}


void read_files_road(){
//此函数用于读取道路文件
//to read road files


}

void read_car_file(std::vector<vehicle> &vehicle_set){
//此函数用于读取车辆数据
//to read car files

    //std::cout<<"reading car files"<<std::endl;

    std::ifstream infile;
    infile.open("./car_data.txt");  //使用相对路径有问题 使用绝对路径ok
    if(!infile){
        std::cout<<"no file find"<<std::endl;
    }
    std::string line;
    //std::vector<std::string> vectorLines;
    //std::vector<vehicle> vehicle_set;


    float height = 0;
    float width = 0;
    float weight = 0;

    int num_count = 0;//用于区分高宽重 0是高 1是宽 2是重

    while (std::getline(infile,line)){
        //std::cout<<line<<std::endl;

        std::istringstream temp_iss(line);
        float temp_car_data;

        while(temp_iss >> temp_car_data){
            //std::cout<<temp_car_data;
            //std::cout<<"\n";
            num_count %= 3;
            if(num_count==0){
                //高
                height = temp_car_data;
            }
            if(num_count==1){
                //宽
                width = temp_car_data;
            }
            if(num_count==2){
                //重
                weight = temp_car_data;
            }
            num_count++;
        }

        //std::cout<<"new:"<<height<<" "<<width<<" "<<weight<<std::endl;
        vehicle_set.push_back(vehicle(height,width,weight));   //更新车辆set

    }

    // std::cout<<"reading car files finished"<<std::endl;

}




int get_vehicle_group_num(std::vector<float>& vehicle_height, std::vector<float>& vehicle_width, std::vector<float>& vehicle_weight){
    float alpha = 0.05; //from 0.01 to 0.2

    float min_height = 1.2;
    float min_width = 1.4;
    float min_weight = 0.9;



    float max_height = 4.0;
    float max_width = 2.5;
    float max_weight = 49.0;

    int max_step_num = 0;

    float increment_step = 0.1; //步长 可以随意设置

    int height_count = 0;
    int width_count = 0;
    int weight_count = 0;

    float previous_height = 1.2;
    float previous_width = 1.4;
    float previous_weight = 0.9;

    float current_height = 0;
    float current_width = 0;
    float current_weight = 0;



    for(int i=0;i<vehicle_height.size();i++){
        //vehicle_height[i]>previous_height&&vehicle_height[i]<=previous_height+increment_step就计数
        //std::cout<<vehicle_weight[i]<<std::endl;

        if(vehicle_height[i]>previous_height+increment_step){
            ///如果该高度大于previous_height+步长 那么重新计数
            if(max_step_num < height_count){
                max_step_num = height_count;
            }

            height_count = 1; //更新height_count 因为当前的height要算入下一个组里
            previous_height += increment_step;

        }

        if(vehicle_width[i]>previous_width+increment_step){
            ///如果该高度大于previous_height+步长 那么重新计数
            if(max_step_num < width_count){
                max_step_num = width_count;
            }

            width_count = 1; //更新height_count 因为当前的height要算入下一个组里
            previous_width += increment_step;

        }

        if(vehicle_weight[i]>previous_weight+increment_step){
            ///如果该高度大于previous_height+步长 那么重新计数
            if(max_step_num < weight_count){
                max_step_num = weight_count;
            }

            weight_count = 1; //更新height_count 因为当前的height要算入下一个组里
            previous_weight += increment_step;

        }

        height_count++;
        width_count++;
        weight_count++;

    }

    // std::cout<<alpha*max_step_num<<std::endl;
    return alpha*max_step_num;

}



void split(int *array,std::string line ,char split_word){

}


void make_shortcut(){
//此函数用于建立shortcut
//to make shortcut


}

void find_shortest_road(){
//此函数用于找到最短路径  dijkstra
//to find the shortest road


}




void car_divided_height(std::vector<float>& vehicle_height , std::vector<float>& vehicle_height_level, int level_group_num){
//此函数用于进行车辆高度分级
//to devide the cars in height
    //std::sort(vehicle_height.begin(),vehicle_height.end()); //由小到大排序
    //int level_group_num = 2000; ///每个组的车辆的个数 自由设定 （具体怎么设置待定）
    int level_group_count = 0; //记录每个组当前的个数

    for(int i=0;i<vehicle_height.size();i++){

        level_group_count++;
        if(level_group_count % level_group_num == level_group_num - 1 ){
            ///每group_num个元素 分割一次 可能出现以下情况：
            ///可能这个分割线和之后下一个分割线值相等，这个无所谓， 在后面三个分割聚合再进行处理

            ///尾部处理 如果最后一组不满分组成员个数 则：
            /// 若其个数小于1/2分组成员个数则并入前组
            /// 若其个数大于1/2分组成员个数正常分组
            /// 理论上是这样 实际上可以在设置group_num时就使得最后一个分组数目尽量小或者尽量大 依据情况而定

            /// 若按组元素个数来分的步长太小怎么办？ 增大到一个步长？  待定

            if((vehicle_height.size()-i)<(level_group_num/2) && i != vehicle_height.size()-1){
                //个数小于1/2分组成员个数则并入前组
                vehicle_height_level.push_back(vehicle_height[vehicle_height.size()-1]);
                break;
            }

            if((vehicle_height.size()-i)>=(level_group_num/2) && (vehicle_height.size()-i)<level_group_num && i != vehicle_height.size()-1){
                //个数大于1/2分组成员个数正常分组
                vehicle_height_level.push_back(vehicle_height[i]);
                vehicle_height_level.push_back(vehicle_height[vehicle_height.size()-1]);
                break;
            }

            vehicle_height_level.push_back(vehicle_height[i]);

        }

//        if(i%level_group_num==level_group_num-1){

//            vehicle_height_level.push_back(vehicle_height[i]); //刚好取到分组最大值
//
//        }


    }


}

void car_divided_width(std::vector<float>& vehicle_width , std::vector<float>& vehicle_height_level, int level_group_num){
//此函数用于进行车辆宽度分级
//to devide the cars in width
    //std::sort(vehicle_width.begin(),vehicle_width.end());//由小到大排序
    //int level_group_num = 2000; //每个组的车辆的个数 自由设定 （具体怎么设置待定）
    int level_group_count = 0; //记录每个组当前的个数

    for(int i=0;i<vehicle_width.size();i++){

        level_group_count++;
        if(level_group_count % level_group_num == level_group_num - 1 ){

            if((vehicle_width.size()-i)<(level_group_num/2) && i != vehicle_width.size()-1){
                //个数小于1/2分组成员个数则并入前组
                vehicle_height_level.push_back(vehicle_width[vehicle_width.size()-1]);
                break;
            }

            if((vehicle_width.size()-i)>=(level_group_num/2) && (vehicle_width.size()-i)<level_group_num && i != vehicle_width.size()-1){
                //个数大于1/2分组成员个数正常分组
                vehicle_height_level.push_back(vehicle_width[i]);
                vehicle_height_level.push_back(vehicle_width[vehicle_width.size()-1]);
                break;
            }

            vehicle_height_level.push_back(vehicle_width[i]);

        }

    }

}

void car_divided_weight(std::vector<float>& vehicle_weight , std::vector<float>& vehicle_height_level, int level_group_num){
//此函数用于进行车辆重量分级
//to devide the cars in weight
    //std::sort(vehicle_weight.begin(),vehicle_weight.end());//由小到大排序
    //int level_group_num = 2000; //每个组的车辆的个数 自由设定 （具体怎么设置待定）
    int level_group_count = 0; //记录每个组当前的个数

    for(int i=0;i<vehicle_weight.size();i++){

        level_group_count++;
        if(level_group_count % level_group_num == level_group_num - 1 ){

            if((vehicle_weight.size()-i)<(level_group_num/2) && i != vehicle_weight.size()-1){
                //个数小于1/2分组成员个数则并入前组
                vehicle_height_level.push_back(vehicle_weight[vehicle_weight.size()-1]);
                break;
            }

            if((vehicle_weight.size()-i)>=(level_group_num/2) && (vehicle_weight.size()-i)<level_group_num && i != vehicle_weight.size()-1){
                //个数大于1/2分组成员个数正常分组
                vehicle_height_level.push_back(vehicle_weight[i]);
                vehicle_height_level.push_back(vehicle_weight[vehicle_weight.size()-1]);
                break;
            }

            vehicle_height_level.push_back(vehicle_weight[i]);
        }

    }



}


int count_level_group_num(std::vector<vehicle>& vehicle_set , float height_lower_bound, float height_upper_bound, float width_lower_bound, float width_upper_bound, float weight_lower_bound, float weight_upper_bound){
    int count = 0;
    for(int i=0;i<vehicle_set.size();i++){
        if(vehicle_set[i].get_height() > height_lower_bound && vehicle_set[i].get_height() <= height_upper_bound){
            if(vehicle_set[i].get_width() > width_lower_bound && vehicle_set[i].get_width() <= width_upper_bound){
                if(vehicle_set[i].get_weight() > weight_lower_bound && vehicle_set[i].get_weight() <= weight_upper_bound){

                    count++; ///满足条件就计数
                }
            }
        }

    }

    return count;

}


int count_level_increment_num(std::vector<vehicle>& vehicle_set , float height_lower_bound, float height_upper_bound, float width_lower_bound, float width_upper_bound, float weight_lower_bound, float weight_upper_bound){


    if(height_upper_bound==height_lower_bound&&width_upper_bound==width_lower_bound){
        int count = 0;
        for(int i=0;i<vehicle_set.size();i++){
            if(vehicle_set[i].get_height()==height_upper_bound&&vehicle_set[i].get_width()==width_upper_bound){

                if(vehicle_set[i].get_weight()>weight_lower_bound&&vehicle_set[i].get_weight()<=weight_upper_bound){
                    count++;
                }
            }
        }
        return count;
    }

    if(height_upper_bound==height_lower_bound&&weight_upper_bound==weight_lower_bound){
        int count = 0;
        for(int i=0;i<vehicle_set.size();i++){
            if(vehicle_set[i].get_height()==height_upper_bound&&vehicle_set[i].get_weight()==weight_upper_bound){

                if(vehicle_set[i].get_width()>width_lower_bound&&vehicle_set[i].get_width()<=width_lower_bound){
                    count++;
                }
            }
        }

        return count;
    }

    if(width_upper_bound==width_lower_bound&&weight_upper_bound==weight_lower_bound){
        int count=0;
        for(int i=0;i<vehicle_set.size();i++){
            if(vehicle_set[i].get_width()==width_lower_bound&&vehicle_set[i].get_weight()==weight_upper_bound){

                if(vehicle_set[i].get_height()>height_lower_bound&&vehicle_set[i].get_height()<=height_upper_bound){
                    count++;
                }
            }

        }
        return count;
    }

    return -1;

}


int count_level_group_num_new(std::vector<vehicle>& vehicle_set , float height_lower_bound, float height_upper_bound, float width_lower_bound, float width_upper_bound, float weight_lower_bound, float weight_upper_bound){
    int count_high = 0;
    int count_low = 0;
    for(int i=0;i<vehicle_set.size();i++){
        if(vehicle_set[i].get_height() > 0 && vehicle_set[i].get_height() <= height_upper_bound){
            if(vehicle_set[i].get_width() > 0 && vehicle_set[i].get_width() <= width_upper_bound){
                if(vehicle_set[i].get_weight() > 0 && vehicle_set[i].get_weight() <= weight_upper_bound){
                    count_high++; ///满足条件就计数
                }
            }
        }
    }

    for(int i=0;i<vehicle_set.size();i++){
        if(vehicle_set[i].get_height() > 0 && vehicle_set[i].get_height() <= height_lower_bound){
            if(vehicle_set[i].get_width() > 0 && vehicle_set[i].get_width() <= width_lower_bound){
                if(vehicle_set[i].get_weight() > 0 && vehicle_set[i].get_weight() <= weight_lower_bound){
                    count_low++; ///满足条件就计数
                }
            }
        }
    }

    return count_high - count_low;

}





std::vector<std::vector<float>> car_divided(){
//此函数用于进行车辆分级
//to devide the cars

    std::vector<vehicle> vehicle_set;
    std::vector<float> vehicle_height;
    std::vector<float> vehicle_width;
    std::vector<float> vehicle_weight;
    std::vector<std::vector<float>> vehicle_level_vector; //车辆分级向量

    //以下容器储存各个分量分级的结果
    std::vector<float> vehicle_height_level;
    std::vector<float> vehicle_width_level;
    std::vector<float> vehicle_weight_level;


    read_car_file(vehicle_set);  //read car_data files
    //std::cout<<vehicle_set[5].get_height()<<std::endl;

    for(int i=0;i<vehicle_set.size();i++){
        //把 高 宽 重  分别放到一个容器内
        vehicle_height.push_back(vehicle_set[i].get_height());
        vehicle_width.push_back(vehicle_set[i].get_width());
        vehicle_weight.push_back(vehicle_set[i].get_weight());
    }

    std::sort(vehicle_height.begin(),vehicle_height.end());//由小到大排序
    std::sort(vehicle_width.begin(),vehicle_width.end());//由小到大排序
    std::sort(vehicle_weight.begin(),vehicle_weight.end());//由小到大排序

    int vehicle_group_num = get_vehicle_group_num(vehicle_height,vehicle_width,vehicle_weight); ///具体数量怎么取 还要思考一下

    //完成各个分量的初步排序
    car_divided_height(vehicle_height , vehicle_height_level, vehicle_group_num);
    car_divided_width(vehicle_width , vehicle_width_level, vehicle_group_num);
    car_divided_weight(vehicle_weight , vehicle_weight_level, vehicle_group_num);





    int vehicle_group_count = 0;

    float previous_height = 1.2;
    float previous_width = 1.4;
    float previous_weight = 0.9;

    float current_height = 0;
    float current_width = 0;
    float current_weight = 0;

    float increment_step = 0.1; //步长 可以随意设置

    int height_increment = 0;
    int width_increment = 0;
    int weight_increment = 0;

    float min_height = 1.2;
    float min_width = 1.4;
    float min_weight = 0.9;

    float max_height = 4.0;
    float max_width = 2.5;
    float max_weight = 49.0;

    int total_vehicle_num = 0;

    for(int i = 0; i < vehicle_height_level.size();i++){


        ///给当前分组的分割点赋值
        current_height = vehicle_height_level[i];
        current_width = vehicle_width_level[i];
        current_weight = vehicle_weight_level[i];

        vehicle_group_count = count_level_group_num_new(vehicle_set , previous_height , current_height , previous_width ,
                                                        current_width , previous_weight , current_weight);

        // std::cout<<"i="<<i<<std::endl;

        while(vehicle_group_count < vehicle_group_num){
            ///分的组数量不够 就继续循环





            ///具体逻辑还有待思考 是用减法还是直接算增量
            ///此处还可以再进行优化 有重复计算
            height_increment = count_level_group_num_new(vehicle_set , current_height , current_height+increment_step ,
                                                         current_width ,current_width , current_weight , current_weight);

            width_increment = count_level_group_num_new(vehicle_set, current_height , current_height, current_width, current_width+increment_step ,
                                                        current_weight , current_weight) ;

            weight_increment = count_level_group_num_new(vehicle_set, current_height , current_height , current_width, current_width,
                                                         current_weight, current_weight+5*increment_step);

            // std::cout<<"height_increment:"<<height_increment<<" width_increment:"<<width_increment<<" weight_increment:"<<weight_increment<<std::endl;

            ///此处发现BUG ！

            if(std::max(std::max(height_increment,width_increment),weight_increment)==height_increment && height_increment > 0){
                ///如果随步长增量最大的是高度
//                if(i < vehicle_height_level.size()-1 && vehicle_height_level[i+1] <= current_height+increment_step){
//                    for(int j=i;j<vehicle_height_level.size();j++){
//                        if(vehicle_height_level[j] <= current_height+increment_step){
//                            vehicle_height_level[j] = current_height+increment_step; ///此处从i开始赋值！！！注意
//                        }
//                    }
//                }

                for(int j=i; j<vehicle_height_level.size();j++){
                    if(vehicle_height_level[j] <= current_height+increment_step){
                        vehicle_height_level[j] = current_height+increment_step; ///此处从i开始赋值！！！注意
                    }
                }

//                 std::cout<<"new height level:"<<std::endl;
//                 for(int k=0; k<vehicle_height_level.size();k++){
//                     std::cout<<vehicle_height_level[k]<<" ";
//
//                 }
                current_height = current_height+increment_step;

                // std::cout<<"current height:"<<current_height<<std::endl;

            }
            else if(std::max(std::max(height_increment,width_increment),weight_increment)==width_increment && width_increment > 0){
                ///如果随步长增量最大的是宽度

                for(int j=i; j<vehicle_height_level.size();j++){  ///size都相等
                    if(vehicle_width_level[j] <= current_width+increment_step){
                        vehicle_width_level[j] = current_width+increment_step; ///此处从i开始赋值！！！注意
                    }
                }
                current_width = current_width+increment_step;

            }

            else if(std::max(std::max(height_increment,width_increment),weight_increment)==weight_increment && weight_increment > 0){
                ///如果随步长增量最大的是重量

                for(int j=i; j<vehicle_height_level.size();j++){  ///size都相等
                    ///此处步长改大成5倍
                    if(vehicle_weight_level[j] <= current_weight+5*increment_step){
                        vehicle_weight_level[j] = current_weight+5*increment_step; ///此处从i开始赋值！！！注意
                    }
                }
                current_weight = current_weight+5*increment_step;

            }

            else if(std::max(std::max(height_increment,width_increment),weight_increment)==0){
                ///按照当前分量占的比例来选择哪一个分量进行增加
                ///利用该公式： (current_height-min_height)/(max_height-min_height)的大小来判断哪个分量该增加
                ///或者是最后一个分组了 但是达不到要求的数目 这种情况就直接break就行

                float height_rate = (current_height-min_height)/(max_height-min_height);
                float width_rate = (current_width-min_width)/(max_width-min_width);
                float weight_rate = (current_weight-min_weight)/(max_weight-min_weight);


                if(height_rate >= 1 && width_rate >= 1 && weight_rate >= 1){
                    ///说明已经划分结束了 应该break

                    break;

                }

                if(std::min(std::min(height_rate,width_rate) , weight_rate) == height_rate){
                    ///如果是当前高度占总高度比最低
                    for(int j=i; j<vehicle_height_level.size();j++){
                        if(vehicle_height_level[j] <= current_height+increment_step){
                            vehicle_height_level[j] = current_height+increment_step; ///此处从i开始赋值！！！注意
                        }
                    }
                    current_height = current_height+increment_step;
                }
                else if(std::min(std::min(height_rate,width_rate) , weight_rate) == width_rate){
                    ///如果是当前宽度占总宽度比最低
                    for(int j=i; j<vehicle_height_level.size();j++){  ///size都相等
                        if(vehicle_width_level[j] <= current_width+increment_step){
                            vehicle_width_level[j] = current_width+increment_step; ///此处从i开始赋值！！！注意
                        }
                    }
                    current_width = current_width+increment_step;
                }
                else if(std::min(std::min(height_rate,width_rate) , weight_rate) == weight_rate){
                    ///如果是当前重量占总重量比最低
                    for(int j=i; j<vehicle_height_level.size();j++){  ///size都相等
                        if(vehicle_weight_level[j] <= current_weight+5*increment_step){
                            vehicle_weight_level[j] = current_weight+5*increment_step; ///此处从i开始赋值！！！注意
                        }
                    }
                    current_weight = current_weight+5*increment_step;
                }






            }

            vehicle_group_count = count_level_group_num_new(vehicle_set , previous_height , current_height , previous_width ,
                                                            current_width , previous_weight , current_weight);

            // std::cout<<"temp vehicle num:"<<vehicle_group_count<<std::endl;


        }

        total_vehicle_num += vehicle_group_count;



        // std::cout<<"final vehicle num: "<<vehicle_group_count<<std::endl;
        // std::cout<<"total vehicle num: "<<total_vehicle_num<<std::endl;



        //vehicle_level_vector.push_back(std::vector<float>{vehicle_height_level[i],vehicle_width_level[i],vehicle_weight_level[i]});
        vehicle_level_vector.push_back(std::vector<float>{current_height,current_width,current_weight});
        previous_height = current_height;
        previous_width = current_width;
        previous_weight = current_weight;

        if(total_vehicle_num>=vehicle_set.size()){
            break;
        }

        vehicle_group_count = 0;

    }

    for(int i=0;i<vehicle_level_vector.size();i++){
        // std::cout<<vehicle_level_vector[i][0]<<" "<<vehicle_level_vector[i][1]<<" "<<vehicle_level_vector[i][2]<<std::endl;
    }

    // std::cout<<vehicle_level_vector.size()<<std::endl;


    return vehicle_level_vector;









    //分别对高宽重进行从大到小的排序
//    std::sort(vehicle_height.begin(),vehicle_height.end());
//    std::sort(vehicle_width.begin(),vehicle_width.end());
//    std::sort(vehicle_weight.begin(),vehicle_weight.end());




}


std::vector<std::vector<float>> car_divided0() {
    std::vector<std::vector<float>> data;
    //std::ifstream infile("C:\\Users\\11131\\Desktop\\k-means\\max_values_clusters.txt"); // 假设数据存储在名为"data.txt"的文件中
    std::ifstream infile("./max_values_clusters.txt"); // 假设数据存储在名为"data.txt"的文件中

    if (!infile) {
        std::cout << "无法打开文件" << std::endl;
        return data;
    }

    std::string line;
    while (std::getline(infile, line)) {
        std::vector<float> row;
        std::istringstream iss(line);

        float value;
        while (iss >> value) {
            row.push_back(value);
        }

        if (row.size() == 3) {  // 检查是否有三个浮点数
            data.push_back(row);
        } else {
            std::cout << "警告：找到不完整的行" << std::endl;
        }
    }

    return data;
}


void init(){
    //用于初始化



}



/*
 * 对照组实验：以0.1为步长来设置分组 重量步长设置为0.5
 *
 */


std::vector<std::vector<float>> car_divided_original(){
    //原始的分组方式 作为实验的对照组
    float min_height = 1.2;
    float min_width = 1.4;
    float min_weight = 0.9;

    float max_height = 4.0;
    float max_width = 2.5;
    float max_weight = 49.0;

    float increment_step = 0.1; //步长 可以随意设置 , 重量用5倍步长

    float current_height = min_height - increment_step;
    float current_width = min_width- increment_step;
    float current_weight = min_weight- increment_step*5;

    std::vector<std::vector<float>> vehicle_level_vector_original;

    while(current_height<max_height){
        current_height += increment_step;
        //std::cout<<"now height:"<<current_height<<std::endl;

        while(current_width<max_width){
            current_width += increment_step;
            //std::cout<<"now width:"<<current_width<<std::endl;

            if(current_width>max_width){
                current_width = max_width;
            }

            while(current_weight<max_weight){
                current_weight += 5 * increment_step;
                //std::cout<<"now weight:"<<current_weight<<std::endl;

                if(current_weight>max_weight){
                    //current_weight = max_weight;
                    vehicle_level_vector_original.push_back(std::vector<float>{current_height , current_width , max_weight});
                    current_weight = min_weight;
                    break;
                }

                vehicle_level_vector_original.push_back(std::vector<float>{current_height , current_width , current_weight});
            }

        }
        current_width = min_width;
    }

//    while(!(current_height>=max_height && current_width>=max_width && current_weight>=max_weight)){
//
//        if(current_height<max_height){
//            current_height += increment_step;
//        }
//
//        if(current_width<max_width){
//            current_width += increment_step;
//        }
//
//        if(current_weight<max_weight){
//            current_weight += 5 * increment_step;
//        }
//
//        vehicle_level_vector_original.push_back(std::vector<float>{current_height , current_width , current_weight});
//
//
//
//    }

    for(int i=0; i<vehicle_level_vector_original.size();i++){

        //std::cout<<vehicle_level_vector_original[i][0]<<" "<<vehicle_level_vector_original[i][1]<<" "<<vehicle_level_vector_original[i][2]<<std::endl;

    }

    //std::cout<<vehicle_level_vector_original.size()<<std::endl;


    return vehicle_level_vector_original;

}






//这里会对分组再进行细分
std::vector<std::vector<float>> car_divided_fine_grained(){

    std::vector<float> vehicle_height;
    std::vector<float> vehicle_width;
    std::vector<float> vehicle_weight;




    float min_height = 1.2;
    float min_width = 1.4;
    float min_weight = 0.9;

    float max_height = 4.0;
    float max_width = 2.5;
    float max_weight = 49.0;

    float increment_step = 0.1; //步长 可以随意设置 , 重量用5倍步长
    std::vector<vehicle> vehicle_set; //车辆数据集合

    read_car_file(vehicle_set);

    for(int i=0;i<vehicle_set.size();i++){
        //把 高 宽 重  分别放到一个容器内
        vehicle_height.push_back(vehicle_set[i].get_height());
        vehicle_width.push_back(vehicle_set[i].get_width());
        vehicle_weight.push_back(vehicle_set[i].get_weight());
    }

    std::sort(vehicle_height.begin(),vehicle_height.end());//由小到大排序
    std::sort(vehicle_width.begin(),vehicle_width.end());//由小到大排序
    std::sort(vehicle_weight.begin(),vehicle_weight.end());//由小到大排序





    int vehicle_group_num = get_vehicle_group_num(vehicle_height,vehicle_width,vehicle_weight);


    std::vector<std::vector<float>> pre_vehicle_level = car_divided0();

    std::vector<std::vector<float>> fine_grained_vehicle_level;

    for(int i = 0 ; i < pre_vehicle_level.size() - 1 ; i++){

        fine_grained_vehicle_level.push_back(pre_vehicle_level[i]);
        // std::cout<<"i:"<<i<<std::endl;



        for(int j = 0 ; j <= 2 ; j++){

            if(j == 0){//处理车高
                if(pre_vehicle_level[i][j] + 3*increment_step <= pre_vehicle_level[i+1][j]){//如果差距较大就要细化处理 大于3倍步长
                    float start = 0;
                    float end = 0;
                    int is_continuous = 0;
                    float car_density_average = (float)count_level_group_num_new(vehicle_set , pre_vehicle_level[i][0] , pre_vehicle_level[i+1][0] ,
                                                                                 pre_vehicle_level[i][1] ,  pre_vehicle_level[i][1] ,
                                                                                 pre_vehicle_level[i][2] , pre_vehicle_level[i][2])
                                                / (pre_vehicle_level[i+1][0]-pre_vehicle_level[i][0]);

                    float check_start = pre_vehicle_level[i][0];
                    float check_end = check_start;
                    float check_interval_density;

                    while(check_end < pre_vehicle_level[i+1][j]){
                        ///处理前置条件
                        check_start = check_end;
                        if((check_end + increment_step) > pre_vehicle_level[i+1][j]){
                            check_end = pre_vehicle_level[i+1][j];
                        } else{
                            check_end += increment_step;
                        }

                        check_interval_density = (float)count_level_group_num_new(vehicle_set , check_start , check_end ,
                                                                                  pre_vehicle_level[i][1] ,  pre_vehicle_level[i][1] ,
                                                                                  pre_vehicle_level[i][2] , pre_vehicle_level[i][2])/increment_step;

                        if(check_interval_density < car_density_average * 0.5){//如果是小于平均密度的0.3 那么就可视为0

                            if(is_continuous == 0){//0说明是第一次遇到低密度区间
                                is_continuous = 1;
                                start = check_start;
                                end = check_end;
                            }
                            else if(is_continuous == 1){//1说明不是第一次遇到了低密度区间
                                end = check_end;
                            }

                        }

                        else if(check_interval_density >= car_density_average * 0.5 && check_interval_density <= car_density_average * 0.8){
                            //
                            if(is_continuous == 1){
                                end = check_end;
                            }

                        }

                        else if(check_interval_density > car_density_average * 0.8){
                            if(is_continuous == 1){
                                end = check_end;
                                is_continuous = 0;//重新置位

                                if(start != pre_vehicle_level[i][0]){

                                    fine_grained_vehicle_level.push_back(std::vector<float>{start , pre_vehicle_level[i][1] , pre_vehicle_level[i][2]});

                                }

                            }
                        }




                    }

                    if(is_continuous == 1){
                        //说明后面是有连续的低密度区间
                        if(start != pre_vehicle_level[i][0]){

                            fine_grained_vehicle_level.push_back(std::vector<float>{start , pre_vehicle_level[i][1] , pre_vehicle_level[i][2]});
                        }

                        is_continuous = 0;

                    }

                }

            }
            else if(j==1){//处理车宽

                if(pre_vehicle_level[i][j] + 3*increment_step <= pre_vehicle_level[i+1][j]){//如果差距较大就要细化处理 大于3倍步长
                    float start = 0;
                    float end = 0;
                    int is_continuous = 0;
                    float car_density_average = (float)count_level_group_num_new(vehicle_set , pre_vehicle_level[i][0] , pre_vehicle_level[i][0] ,
                                                                                 pre_vehicle_level[i][1] ,  pre_vehicle_level[i+1][1] ,
                                                                                 pre_vehicle_level[i][2] , pre_vehicle_level[i][2])
                                                / (pre_vehicle_level[i+1][1]-pre_vehicle_level[i][1]);

                    float check_start = pre_vehicle_level[i][1];
                    float check_end = check_start;
                    float check_interval_density;

                    while(check_end < pre_vehicle_level[i+1][j]){
                        ///处理前置条件
                        check_start = check_end;
                        if((check_end + increment_step) > pre_vehicle_level[i+1][j]){
                            check_end = pre_vehicle_level[i+1][j];
                        } else{
                            check_end += increment_step;
                        }

                        check_interval_density = (float)count_level_group_num_new(vehicle_set , pre_vehicle_level[i][0] , pre_vehicle_level[i][0] ,
                                                                                  check_start ,  check_end ,
                                                                                  pre_vehicle_level[i][2] , pre_vehicle_level[i][2])/increment_step;

                        if(check_interval_density < car_density_average * 0.5){//如果是小于平均密度的0.3 那么就可视为0

                            if(is_continuous == 0){//0说明是第一次遇到低密度区间
                                is_continuous = 1;
                                start = check_start;
                                end = check_end;
                            }
                            else if(is_continuous == 1){//1说明不是第一次遇到了低密度区间
                                end = check_end;
                            }

                        }

                        else if(check_interval_density >= car_density_average * 0.5 && check_interval_density <= car_density_average * 0.8){
                            //
                            if(is_continuous == 1){
                                end = check_end;
                            }

                        }

                        else if(check_interval_density > car_density_average * 0.8){
                            if(is_continuous == 1){
                                end = check_end;
                                is_continuous = 0;//重新置位

                                if(start != pre_vehicle_level[i][1]){

                                    fine_grained_vehicle_level.push_back(std::vector<float>{pre_vehicle_level[i][0] , start , pre_vehicle_level[i][2]});
                                }

                            }
                        }




                    }

                    if(is_continuous == 1){
                        //说明后面是有连续的低密度区间

                        if(start != pre_vehicle_level[i][1]){

                            fine_grained_vehicle_level.push_back(std::vector<float>{pre_vehicle_level[i][0] , start , pre_vehicle_level[i][2]});
                        }

                        is_continuous = 0;

                    }







//                    float low_boundary = pre_vehicle_level[i][j];
//                    float high_boundary = pre_vehicle_level[i+1][j];
//                    float mid = (high_boundary + low_boundary) / 2;
//                    int interval_increment = count_level_group_num_new(vehicle_set , low_boundary , high_boundary ,
//                                                 pre_vehicle_level[i][1] ,  pre_vehicle_level[i][1] , pre_vehicle_level[i][2] , pre_vehicle_level[i][2]);
//
//                    int low_mid_increment = count_level_group_num_new(vehicle_set , low_boundary , mid ,
//                                                                      pre_vehicle_level[i][1] ,  pre_vehicle_level[i][1] , pre_vehicle_level[i][2] , pre_vehicle_level[i][2]);
//                    int mid_high_increment = count_level_group_num_new(vehicle_set , mid , high_boundary ,
//                                                                       pre_vehicle_level[i][1] ,  pre_vehicle_level[i][1] , pre_vehicle_level[i][2] , pre_vehicle_level[i][2]);
//
//                    while((high_boundary>=low_boundary+2*increment_step) && (interval_increment>vehicle_group_num * 0.1)){///判断条件需要改
//
//                        if(low_mid_increment > mid_high_increment ){
//
//
//                        }
//
//
//
//
//
//                    }

//                    //while()
//                    float low_boundary = pre_vehicle_level[i][j];
//                    float high_boundary = pre_vehicle_level[i+1][j];
//                    float mid = (high_boundary + low_boundary) / 2;
//
//                    if(count_level_group_num_new(vehicle_set , low_boundary , high_boundary ,
//                                                 pre_vehicle_level[i][1] ,  pre_vehicle_level[i][1] , pre_vehicle_level[i][2] , pre_vehicle_level[i][2])==0){
//                        continue;
//                    }
//
//                    int low_mid_increment = count_level_group_num_new(vehicle_set , low_boundary , mid ,
//                                                                      pre_vehicle_level[i][1] ,  pre_vehicle_level[i][1] , pre_vehicle_level[i][2] , pre_vehicle_level[i][2]);
//                    int mid_high_increment = count_level_group_num_new(vehicle_set , mid , high_boundary ,
//                                                                       pre_vehicle_level[i][1] ,  pre_vehicle_level[i][1] , pre_vehicle_level[i][2] , pre_vehicle_level[i][2]);
//
//                    if(low_mid_increment * mid_high_increment == 0){//如果有一部分是0
//
//                    }


                }

            }
            else if(j==2){//处理车重

                if(pre_vehicle_level[i][j] + 3*increment_step*5 <= pre_vehicle_level[i+1][j]){//如果差距较大就要细化处理 大于3倍步长
                    // std::cout<<"process weight"<<std::endl;

                    float start = 0;
                    float end = 0;
                    int is_continuous = 0;
                    float car_density_average = (float)count_level_group_num_new(vehicle_set , pre_vehicle_level[i][0] , pre_vehicle_level[i][0] ,
                                                                                 pre_vehicle_level[i][1] ,  pre_vehicle_level[i][1] ,
                                                                                 pre_vehicle_level[i][2] , pre_vehicle_level[i+1][2])
                                                / (pre_vehicle_level[i+1][2]-pre_vehicle_level[i][2]);


                    float check_start = pre_vehicle_level[i][2];
                    float check_end = check_start;
                    float check_interval_density;

                    while(check_end < pre_vehicle_level[i+1][j]){
                        ///处理前置条件
                        check_start = check_end;
                        if((check_end + increment_step*5) > pre_vehicle_level[i+1][j]){
                            check_end = pre_vehicle_level[i+1][j];
                        } else{
                            check_end += increment_step*5;
                        }

                        check_interval_density = (float)count_level_group_num_new(vehicle_set , pre_vehicle_level[i][0] , pre_vehicle_level[i][0] ,
                                                                                  pre_vehicle_level[i][1] ,  pre_vehicle_level[i][1] ,
                                                                                  check_start , check_end);

                        if(check_interval_density < car_density_average * 0.5){//如果是小于平均密度的0.3 那么就可视为0

                            if(is_continuous == 0){//0说明是第一次遇到低密度区间
                                is_continuous = 1;
                                start = check_start;
                                end = check_end;
                            }
                            else if(is_continuous == 1){//1说明不是第一次遇到了低密度区间
                                end = check_end;
                            }

                        }

                        else if(check_interval_density >= car_density_average * 0.5 && check_interval_density <= car_density_average * 0.8){
                            //
                            if(is_continuous == 1){
                                end = check_end;
                            }

                        }

                        else if(check_interval_density > car_density_average * 0.8){
                            if(is_continuous == 1){
                                end = check_end;
                                is_continuous = 0;//重新置位

                                if(start != pre_vehicle_level[i][2]){

                                    fine_grained_vehicle_level.push_back(std::vector<float>{pre_vehicle_level[i][0] , pre_vehicle_level[i][1] , start});
                                }

                            }
                        }




                    }

                    if(is_continuous == 1){
                        //说明后面是有连续的低密度区间
                        if(start != pre_vehicle_level[i][2]){

                            fine_grained_vehicle_level.push_back(std::vector<float>{pre_vehicle_level[i][0] , pre_vehicle_level[i][1] , start});
                        }

                        is_continuous = 0;

                    }

                    // std::cout<<"finished process weight!"<<std::endl;


                }

            }





        }






    }

    fine_grained_vehicle_level.push_back(pre_vehicle_level[pre_vehicle_level.size()-1]);

    return fine_grained_vehicle_level;



}






int find_element_index(std::vector<float> vec , float element){
    //返回某一元素在vector中的位置
    int index=-1;

    for(int i=0;i<vec.size();i++){
        if(vec[i]==element){
            index = i;
        }
    }

    //std::cout<<"finished finding index: "<<index<<std::endl;
    return index;


}

std::vector<std::vector<float>> car_divided_rematch(std::vector<std::vector<float>> precise_vehicle_level){//stage 4

    //预处理
    std::vector<float> height;
    std::vector<float> width;
    std::vector<float> weight;

    std::vector<std::vector<float>> rematch_vehicle_level;

    if(precise_vehicle_level.size()==0){

        // std::cout<<"empty precise_vehicle_level"<<std::endl;
        return rematch_vehicle_level;
    }

    std::vector<vehicle> vehicle_set; //车辆数据集合
    read_car_file(vehicle_set);

    for(int i=0;i<precise_vehicle_level.size();i++){
        //处理高
        height.push_back(precise_vehicle_level[i][0]);
        //处理宽
        width.push_back(precise_vehicle_level[i][1]);
        //处理重
        weight.push_back(precise_vehicle_level[i][2]);
    }

    std::sort(height.begin() , height.end());
    std::sort(width.begin() , width.end());
    std::sort(weight.begin() , weight.end());

    //去重
    height.erase(std::unique(height.begin() , height.end()) , height.end());
    width.erase(std::unique(width.begin() , width.end()) , width.end());
    weight.erase(std::unique(weight.begin() , weight.end()) , weight.end());

    for(int i=0;i<precise_vehicle_level.size();i++){
        rematch_vehicle_level.push_back(precise_vehicle_level[i]);


        if(i < precise_vehicle_level.size()-1){
            int height_save = 0;   //置位
            int width_save = 0;
            int weight_save = 0;

            for(int j=1;j<=2;j++){

                //处理高
                ///要考虑去重
                //std::cout<<"finding height index: "<<precise_vehicle_level[i][0]<<std::endl;
                int height_index = find_element_index(height , precise_vehicle_level[i][0]);

                if(height_index+j<height.size()&&height_index!=-1){

                    if(height_save==0){
                        int interval_vehicle_num = count_level_group_num_new(vehicle_set , precise_vehicle_level[i][0] , height[height_index+j],
                                                                             precise_vehicle_level[i][1] , precise_vehicle_level[i][1],
                                                                             precise_vehicle_level[i][2] , precise_vehicle_level[i][2]);

//                        std::cout<<"interval_v_num: "<<interval_vehicle_num<<std::endl;
//                        std::cout<<precise_vehicle_level[i][0]<<" "<<precise_vehicle_level[i][1]<<" "<<precise_vehicle_level[i][2]<<std::endl;
//                        std::cout<<height[height_index+j]<<" "<<precise_vehicle_level[i][1]<<" "<<precise_vehicle_level[i][2]<<std::endl;
                        if((float)interval_vehicle_num > 0.02*vehicle_set.size()){
                            if(std::count(precise_vehicle_level.begin(), precise_vehicle_level.end(),
                                          std::vector<float>{height[height_index+j],precise_vehicle_level[i][1],precise_vehicle_level[i][2]})<=0){
                                ///没有重复就插入

                                height_save =1;//置位
                                rematch_vehicle_level.push_back(std::vector<float>{height[height_index+j], precise_vehicle_level[i][1] , precise_vehicle_level[i][2]});
                            }
                        }

                    }

                    else if(height_save==1){

                        int interval_vehicle_num = count_level_group_num_new(vehicle_set , height[height_index+1] , height[height_index+j],
                                                                             precise_vehicle_level[i][1] , precise_vehicle_level[i][1],
                                                                             precise_vehicle_level[i][2] , precise_vehicle_level[i][2]);

//                        std::cout<<"interval_v_num: "<<interval_vehicle_num<<std::endl;
//                        std::cout<<height[height_index+1]<<" "<<precise_vehicle_level[i][1]<<" "<<precise_vehicle_level[i][2]<<std::endl;
//                        std::cout<<height[height_index+j]<<" "<<precise_vehicle_level[i][1]<<" "<<precise_vehicle_level[i][2]<<std::endl;
                        if((float)interval_vehicle_num > 0.02*vehicle_set.size()){
                            if(std::count(precise_vehicle_level.begin(), precise_vehicle_level.end(),
                                          std::vector<float>{height[height_index+j],precise_vehicle_level[i][1],precise_vehicle_level[i][2]})<=0){
                                ///没有重复就插入

                                height_save =1;//置位
                                rematch_vehicle_level.push_back(std::vector<float>{height[height_index+j], precise_vehicle_level[i][1] , precise_vehicle_level[i][2]});
                            }
                        }
                    }



                }

                //处理宽
                //std::cout<<"finding width index: "<<precise_vehicle_level[i][1]<<std::endl;
                int width_index = find_element_index(width , precise_vehicle_level[i][1]);

                if(width_index+j<width.size()&&width_index!=-1){

                    if(width_save==0){

                        int interval_vehicle_num = count_level_group_num_new(vehicle_set , precise_vehicle_level[i][0] , precise_vehicle_level[i][0],
                                                                             precise_vehicle_level[i][1] , width[width_index+j],
                                                                             precise_vehicle_level[i][2] , precise_vehicle_level[i][2]);

//                        std::cout<<"interval_v_num: "<<interval_vehicle_num<<std::endl;
//                        std::cout<<precise_vehicle_level[i][0]<<" "<<precise_vehicle_level[i][1]<<" "<<precise_vehicle_level[i][2]<<std::endl;
//                        std::cout<<precise_vehicle_level[i][0]<<" "<<width[width_index+j]<<" "<<precise_vehicle_level[i][2]<<std::endl;

                        if((float)interval_vehicle_num > 0.02*vehicle_set.size()){
                            if(std::count(precise_vehicle_level.begin(), precise_vehicle_level.end(),
                                          std::vector<float>{precise_vehicle_level[i][0],width[width_index+j],precise_vehicle_level[i][2]})<=0){
                                ///没有重复就插入

                                width_save=1;
                                rematch_vehicle_level.push_back(std::vector<float>{precise_vehicle_level[i][0],width[width_index+j],precise_vehicle_level[i][2]});
                            }
                        }
                    }

                    else if(width_save==1){

                        int interval_vehicle_num = count_level_group_num_new(vehicle_set , precise_vehicle_level[i][0] , precise_vehicle_level[i][0],
                                                                             width[width_index+1] , width[width_index+j],
                                                                             precise_vehicle_level[i][2] , precise_vehicle_level[i][2]);

//                        std::cout<<"interval_v_num: "<<interval_vehicle_num<<std::endl;
//                        std::cout<<precise_vehicle_level[i][0]<<" "<<width[width_index+1]<<" "<<precise_vehicle_level[i][2]<<std::endl;
//                        std::cout<<precise_vehicle_level[i][0]<<" "<<width[width_index+j]<<" "<<precise_vehicle_level[i][2]<<std::endl;

                        if((float)interval_vehicle_num > 0.02*vehicle_set.size()){
                            if(std::count(precise_vehicle_level.begin(), precise_vehicle_level.end(),
                                          std::vector<float>{precise_vehicle_level[i][0],width[width_index+j],precise_vehicle_level[i][2]})<=0){
                                ///没有重复就插入

                                width_save=1;
                                rematch_vehicle_level.push_back(std::vector<float>{precise_vehicle_level[i][0],width[width_index+j],precise_vehicle_level[i][2]});
                            }
                        }
                    }



                }

                //std::cout<<"finding weight index: "<<precise_vehicle_level[i][2]<<std::endl;
                int weight_index = find_element_index(weight , precise_vehicle_level[i][2]);

                if(weight_index+j<weight.size()&&weight_index!=-1){

                    if(weight_save==0){

                        int interval_vehicle_num = count_level_group_num_new(vehicle_set , precise_vehicle_level[i][0] , precise_vehicle_level[i][0],
                                                                             precise_vehicle_level[i][1] , precise_vehicle_level[i][1],
                                                                             precise_vehicle_level[i][2] , weight[weight_index+j]);

//                        std::cout<<"interval_v_num: "<<interval_vehicle_num<<std::endl;
//                        std::cout<<precise_vehicle_level[i][0]<<" "<<precise_vehicle_level[i][1]<<" "<<precise_vehicle_level[i][2]<<std::endl;
//                        std::cout<<precise_vehicle_level[i][0]<<" "<<precise_vehicle_level[i][1]<<" "<<weight[weight_index+j]<<std::endl;

                        if((float)interval_vehicle_num > 0.02*vehicle_set.size()){
                            if(std::count(precise_vehicle_level.begin(), precise_vehicle_level.end(),
                                          std::vector<float>{precise_vehicle_level[i][0],precise_vehicle_level[i][1],weight[weight_index+j]})<=0){
                                ///没有重复就插入

                                weight_save = 1;
                                rematch_vehicle_level.push_back(std::vector<float>{precise_vehicle_level[i][0],precise_vehicle_level[i][1],weight[weight_index+j]});
                            }
                        }
                    }

                    else if(weight_save==1){

                        int interval_vehicle_num = count_level_group_num_new(vehicle_set , precise_vehicle_level[i][0] , precise_vehicle_level[i][0],
                                                                             precise_vehicle_level[i][1] , precise_vehicle_level[i][1],
                                                                             weight[weight_index+1] , weight[weight_index+j]);

//                        std::cout<<"interval_v_num: "<<interval_vehicle_num<<std::endl;
//                        std::cout<<precise_vehicle_level[i][0]<<" "<<precise_vehicle_level[i][1]<<" "<<weight[weight_index+1]<<std::endl;
//                        std::cout<<precise_vehicle_level[i][0]<<" "<<precise_vehicle_level[i][1]<<" "<<weight[weight_index+j]<<std::endl;

                        if((float)interval_vehicle_num > 0.02*vehicle_set.size()){
                            if(std::count(precise_vehicle_level.begin(), precise_vehicle_level.end(),
                                          std::vector<float>{precise_vehicle_level[i][0],precise_vehicle_level[i][1],weight[weight_index+j]})<=0){
                                ///没有重复就插入

                                weight_save = 1;
                                rematch_vehicle_level.push_back(std::vector<float>{precise_vehicle_level[i][0],precise_vehicle_level[i][1],weight[weight_index+j]});
                            }
                        }
                    }



                }





            }


        }



    }


    for(int i = precise_vehicle_level.size()-1;i>=0;i--){
        for(int k=0;k<weight.size();k++){
            // std::cout<<weight[k]<<std::endl;
        }
        // std::cout<<"stage 2 in rematch: "<<i<<std::endl;

        if(i>=1){

            int height_save_stage2 = 0;
            int width_save_stage2 = 0;
            int weight_save_stage2 = 0;

            //std::cout<<"stage 2 in loop: "<<i<<std::endl;
            for(int j=1;j<=2;j++){
                //处理高
                //std::cout<<"stage 2 in loop: "<<i<<std::endl;
                //std::cout<<"stage 2 in loop: "<<i<<std::endl;
                //std::cout<<"finding height index: "<<precise_vehicle_level[i][0]<<std::endl;
                int height_index = find_element_index(height , precise_vehicle_level[i][0]);
                int width_index = find_element_index(width , precise_vehicle_level[i][1]);
                int weight_index = find_element_index(weight , precise_vehicle_level[i][2]);

                // std::cout<<"height index: "<<height_index<<std::endl;

                if(height_index-j>=0&&height_index!=-1&&width_index-1>=0&&width_index!=-1&&weight_index-1>=0&&weight_index!=-1){
                    if(height_save_stage2==0){//还没插入新的分级

//                        int interval_vehicle_num = count_level_group_num_new(vehicle_set , height[height_index-j] , precise_vehicle_level[i][0],
//                                                                             precise_vehicle_level[i][1] , precise_vehicle_level[i][1],
//                                                                             precise_vehicle_level[i][2] , precise_vehicle_level[i][2]);

                        int interval_vehicle_num = count_level_group_num_new(vehicle_set, height[height_index-j], height[height_index-j],
                                                                             width[width_index-1], precise_vehicle_level[i][1],
                                                                             weight[weight_index-1], precise_vehicle_level[i][2]);


                        // std::cout<<"interval_v_num: "<<interval_vehicle_num<<std::endl;
                        //std::cout<<"interval_v_num: "<<interval_vehicle_num<<std::endl;
                        // std::cout<<height[height_index-j]<<" "<<precise_vehicle_level[i][1]<<" "<<precise_vehicle_level[i][2]<<std::endl;
                        // std::cout<<precise_vehicle_level[i][0]<<" "<<precise_vehicle_level[i][1]<<" "<<precise_vehicle_level[i][2]<<std::endl;

                        if((float)interval_vehicle_num > 0.03*vehicle_set.size()){
                            if((std::count(precise_vehicle_level.begin(), precise_vehicle_level.end(),
                                           std::vector<float>{height[height_index-j],precise_vehicle_level[i][1],precise_vehicle_level[i][2]})<=0)
                               &&(std::count(rematch_vehicle_level.begin(), rematch_vehicle_level.end(),
                                             std::vector<float>{height[height_index-j],precise_vehicle_level[i][1],precise_vehicle_level[i][2]}))<=0){

                                ///插入需要置位
                                // std::cout<<"insert"<<std::endl;
                                height_save_stage2 = 1;
                                rematch_vehicle_level.push_back(std::vector<float>{height[height_index-j],precise_vehicle_level[i][1],precise_vehicle_level[i][2]});
                            }

                        }
                    }

                    else if(height_save_stage2==1){//之前插入过了

//                        int interval_vehicle_num = count_level_group_num_new(vehicle_set , height[height_index-j] , height[height_index-1],
//                                                                             precise_vehicle_level[i][1] , precise_vehicle_level[i][1],
//                                                                             precise_vehicle_level[i][2] , precise_vehicle_level[i][2]);

                        int interval_vehicle_num = count_level_group_num_new(vehicle_set, height[height_index-j], height[height_index-j],
                                                                             width[width_index-1], precise_vehicle_level[i][1],
                                                                             weight[weight_index-1], precise_vehicle_level[i][2]);

                        // std::cout<<"interval_v_num: "<<interval_vehicle_num<<std::endl;
                        // std::cout<<height[height_index-j]<<" "<<precise_vehicle_level[i][1]<<" "<<precise_vehicle_level[i][2]<<std::endl;
                        // std::cout<<height[height_index-1]<<" "<<precise_vehicle_level[i][1]<<" "<<precise_vehicle_level[i][2]<<std::endl;

                        if((float)interval_vehicle_num > 0.03*vehicle_set.size()){
                            if((std::count(precise_vehicle_level.begin(), precise_vehicle_level.end(),
                                           std::vector<float>{height[height_index-j],precise_vehicle_level[i][1],precise_vehicle_level[i][2]})<=0)
                               &&(std::count(rematch_vehicle_level.begin(), rematch_vehicle_level.end(),
                                             std::vector<float>{height[height_index-j],precise_vehicle_level[i][1],precise_vehicle_level[i][2]}))<=0){

                                ///插入需要置位
                                // std::cout<<"insert"<<std::endl;
                                height_save_stage2 = 1;
                                rematch_vehicle_level.push_back(std::vector<float>{height[height_index-j],precise_vehicle_level[i][1],precise_vehicle_level[i][2]});
                            }

                        }

                    }


                }
                //std::cout<<"stage 2 in rematch: "<<i<<"finish height"<<std::endl;




                if(width_index-j>=0&&width_index!=-1){

                    if(width_save_stage2==0){

                        int interval_vehicle_num = count_level_group_num_new(vehicle_set , height[height_index-1], precise_vehicle_level[i][0],
                                                                             width[width_index-j] , width[width_index-j],
                                                                             weight[weight_index-1] , precise_vehicle_level[i][2]);

                        // std::cout<<"interval_v_num: "<<interval_vehicle_num<<std::endl;
                        // std::cout<<precise_vehicle_level[i][0]<<" "<<width[width_index-j]<<" "<<precise_vehicle_level[i][2]<<std::endl;
                        // std::cout<<precise_vehicle_level[i][0]<<" "<<precise_vehicle_level[i][1]<<" "<<precise_vehicle_level[i][2]<<std::endl;

                        if((float)interval_vehicle_num > 0.03*vehicle_set.size()){
                            if((std::count(precise_vehicle_level.begin(), precise_vehicle_level.end(),
                                           std::vector<float>{precise_vehicle_level[i][0],width[width_index-j],precise_vehicle_level[i][2]})<=0)
                               &&(std::count(rematch_vehicle_level.begin(), rematch_vehicle_level.end(),
                                             std::vector<float>{precise_vehicle_level[i][0],width[width_index-j],precise_vehicle_level[i][2]}))<=0){

                                ///插入 置位
                                // std::cout<<"insert"<<std::endl;
                                width_save_stage2=1;
                                rematch_vehicle_level.push_back(std::vector<float>{precise_vehicle_level[i][0],width[width_index-j],precise_vehicle_level[i][2]});
                            }

                        }
                    }

                    else if(width_save_stage2==1){

                        int interval_vehicle_num = count_level_group_num_new(vehicle_set , height[height_index-1], precise_vehicle_level[i][0],
                                                                             width[width_index-j] , width[width_index-j],
                                                                             weight[weight_index-1] , precise_vehicle_level[i][2]);

                        // std::cout<<"interval_v_num: "<<interval_vehicle_num<<std::endl;
                        // std::cout<<precise_vehicle_level[i][0]<<" "<<width[width_index-j]<<" "<<precise_vehicle_level[i][2]<<std::endl;
                        // std::cout<<precise_vehicle_level[i][0]<<" "<<width[width_index-1]<<" "<<precise_vehicle_level[i][2]<<std::endl;

                        if((float)interval_vehicle_num > 0.03*vehicle_set.size()){
                            if((std::count(precise_vehicle_level.begin(), precise_vehicle_level.end(),
                                           std::vector<float>{precise_vehicle_level[i][0],width[width_index-j],precise_vehicle_level[i][2]})<=0)
                               &&(std::count(rematch_vehicle_level.begin(), rematch_vehicle_level.end(),
                                             std::vector<float>{precise_vehicle_level[i][0],width[width_index-j],precise_vehicle_level[i][2]}))<=0){

                                ///插入 置位

                                // std::cout<<"insert"<<std::endl;
                                width_save_stage2=1;
                                rematch_vehicle_level.push_back(std::vector<float>{precise_vehicle_level[i][0],width[width_index-j],precise_vehicle_level[i][2]});
                            }

                        }
                    }



                }
                //std::cout<<"stage 2 in rematch: "<<i<<"finish width"<<std::endl;


                //std::cout<<"weight index: "<<weight_index<<std::endl;

                if(weight_index-j>=0&&weight_index!=-1){

                    if(weight_save_stage2==0){

                        int interval_vehicle_num = count_level_group_num_new(vehicle_set , height[height_index-1], precise_vehicle_level[i][0],
                                                                             width[width_index-1] , precise_vehicle_level[i][1],
                                                                             weight[weight_index-j] , weight[weight_index-j]);

                        // std::cout<<"interval_v_num: "<<interval_vehicle_num<<std::endl;
                        // std::cout<<precise_vehicle_level[i][0]<<" "<<precise_vehicle_level[i][1]<<" "<<weight[weight_index-j]<<std::endl;
                        // std::cout<<precise_vehicle_level[i][0]<<" "<<precise_vehicle_level[i][1]<<" "<<precise_vehicle_level[i][2]<<std::endl;

                        if((float)interval_vehicle_num > 0.02*vehicle_set.size()){
                            if((std::count(precise_vehicle_level.begin(), precise_vehicle_level.end(),
                                           std::vector<float>{precise_vehicle_level[i][0],precise_vehicle_level[i][1],weight[weight_index-j]})<=0)
                               &&(std::count(rematch_vehicle_level.begin(), rematch_vehicle_level.end(),
                                             std::vector<float>{precise_vehicle_level[i][0],precise_vehicle_level[i][1],weight[weight_index-j]}))<=0){

                                ///插入 置位
                                weight_save_stage2=1;
                                // std::cout<<"insert"<<std::endl;
                                rematch_vehicle_level.push_back(std::vector<float>{precise_vehicle_level[i][0],precise_vehicle_level[i][1],weight[weight_index-j]});
                            }

                        }
                    }

                    else if(weight_save_stage2==1){

                        int interval_vehicle_num = count_level_group_num_new(vehicle_set , height[height_index-1], precise_vehicle_level[i][0],
                                                                             width[width_index-1] , precise_vehicle_level[i][1],
                                                                             weight[weight_index-j] , weight[weight_index-j]);

                        // std::cout<<"interval_v_num: "<<interval_vehicle_num<<std::endl;
                        // std::cout<<precise_vehicle_level[i][0]<<" "<<precise_vehicle_level[i][1]<<" "<<weight[weight_index-j]<<std::endl;
                        // std::cout<<precise_vehicle_level[i][0]<<" "<<precise_vehicle_level[i][1]<<" "<<weight[weight_index-1]<<std::endl;

                        if((float)interval_vehicle_num > 0.03*vehicle_set.size()){
                            if((std::count(precise_vehicle_level.begin(), precise_vehicle_level.end(),
                                           std::vector<float>{precise_vehicle_level[i][0],precise_vehicle_level[i][1],weight[weight_index-j]})<=0)
                               &&(std::count(rematch_vehicle_level.begin(), rematch_vehicle_level.end(),
                                             std::vector<float>{precise_vehicle_level[i][0],precise_vehicle_level[i][1],weight[weight_index-j]}))<=0){

                                ///插入 置位
                                // std::cout<<"insert"<<std::endl;
                                weight_save_stage2=1;
                                rematch_vehicle_level.push_back(std::vector<float>{precise_vehicle_level[i][0],precise_vehicle_level[i][1],weight[weight_index-j]});
                            }

                        }
                    }


                }
                //std::cout<<"stage 2 in rematch: "<<i<<"finish weight"<<std::endl;





            }

        }



    }

    return rematch_vehicle_level;


}


int find_element_range_in_limit(std::vector<limit> limit_single_dimension, float element){
    //返回limit中第一个比给定元素大的或者相等的
    int index=-1;

    for(int i=0;i<limit_single_dimension.size();i++){

        if(limit_single_dimension[i].values>=element){
            index = i;
            return index;
        }
    }

    return index;
}

std::vector<std::vector<float>> car_divided_precise(std::vector<std::vector<float>> refined_vehicle_level,std::vector<std::vector<limit>> limit_of_cell){//stage 3


    std::vector<std::vector<float>> precise_vehicle_level;
    // std::cout<<"precise stage:"<<std::endl;

    if(limit_of_cell.empty()==1||limit_of_cell[0].empty()==1||limit_of_cell[1].empty()==1||limit_of_cell[2].empty()==1){
        ///空limit_of_cell 返回空vector
        // std::cout<<"empty refined_vehicle_level"<<std::endl;
        return precise_vehicle_level;
    }

    ///index返回值为-1的情况需要考虑
    for(int i=0;i<refined_vehicle_level.size();i++){

        //处理比较小的数据
        //limit_of_cell[0]高限制   limit_of_cell[1]宽限制    limit_of_cell[3]重限制
        //处理高
        // std::cout<<i<<": get precise height:"<<std::endl;
        // std::cout<<"refined height:"<<refined_vehicle_level[i][0]<<std::endl;
        if(refined_vehicle_level[i][0] <= limit_of_cell[0][0].values){
            refined_vehicle_level[i][0] = limit_of_cell[0][0].values;
        }
        else if(refined_vehicle_level[i][0] > limit_of_cell[0][0].values){
            int height_index = find_element_range_in_limit(limit_of_cell[0], refined_vehicle_level[i][0]);
            //std::cout<<"precise height: "<<limit_of_cell[0][height_index].values<<std::endl;
            if(height_index==-1){
                //说明比cell内最大的限制都大
                refined_vehicle_level[i][0] = limit_of_cell[0][limit_of_cell[0].size()-1].values;
            } else{

                if(refined_vehicle_level[i][0] < limit_of_cell[0][height_index].values){


                    if((refined_vehicle_level[i][0] - limit_of_cell[0][height_index-1].values) >=
                       (limit_of_cell[0][height_index].values - refined_vehicle_level[i][0])){

                        refined_vehicle_level[i][0] = limit_of_cell[0][height_index].values;
                    }

                    else if((refined_vehicle_level[i][0] - limit_of_cell[0][height_index-1].values) <
                            (limit_of_cell[0][height_index].values - refined_vehicle_level[i][0])){

                        refined_vehicle_level[i][0] = limit_of_cell[0][height_index-1].values;


                    }

                }

            }

        }

        //处理宽
        if(refined_vehicle_level[i][1] <= limit_of_cell[1][0].values){
            refined_vehicle_level[i][1] = limit_of_cell[1][0].values;
        }
        else if(refined_vehicle_level[i][1] > limit_of_cell[1][0].values){
            int width_index = find_element_range_in_limit(limit_of_cell[1], refined_vehicle_level[i][1]);

            if(width_index==-1){
                refined_vehicle_level[i][1] = limit_of_cell[1][limit_of_cell[1].size()-1].values;
            } else{

                if(refined_vehicle_level[i][1] < limit_of_cell[1][width_index].values){
    

                    if((refined_vehicle_level[i][1] - limit_of_cell[1][width_index-1].values) >=
                       (limit_of_cell[1][width_index].values - refined_vehicle_level[i][1])){

                        refined_vehicle_level[i][1] = limit_of_cell[1][width_index].values;
                    }

                    else if((refined_vehicle_level[i][1] - limit_of_cell[1][width_index-1].values) <
                            (limit_of_cell[1][width_index].values - refined_vehicle_level[i][1])){

                        refined_vehicle_level[i][1] = limit_of_cell[1][width_index-1].values;

//                        if(std::count(refined_vehicle_level.begin(),refined_vehicle_level.end(),
//                                      std::vector<float>{refined_vehicle_level[i][0],limit_of_cell[1][width_index].values,refined_vehicle_level[i][2]})<=0){
//
//                            refined_vehicle_level.push_back(std::vector<float>{refined_vehicle_level[i][0],limit_of_cell[1][width_index].values,refined_vehicle_level[i][2]});
//                        }
                    }

//                    else if((refined_vehicle_level[i][1] - limit_of_cell[1][width_index-1].values) ==
//                            (limit_of_cell[1][width_index].values - refined_vehicle_level[i][1])){
//
//                        //refined_vehicle_level[i][0] = limit_of_cell[0][height_index-1].values;
//                        if(limit_of_cell[1][width_index-1].percent>0.05){
//                            refined_vehicle_level[i][1] = limit_of_cell[1][width_index-1].values;
//                            if(std::count(refined_vehicle_level.begin(),refined_vehicle_level.end(),
//                                          std::vector<float>{refined_vehicle_level[i][0],limit_of_cell[1][width_index].values,refined_vehicle_level[i][2]})<=0){
//
//                                refined_vehicle_level.push_back(std::vector<float>{refined_vehicle_level[i][0],limit_of_cell[1][width_index].values,refined_vehicle_level[i][2]});
//                            }
//                        }
//                        else{
//                            refined_vehicle_level[i][1] = limit_of_cell[1][width_index].values;
//                        }
//                    }

                }

            }



        }


        //处理重
        if(refined_vehicle_level[i][2] <= limit_of_cell[2][0].values){
            refined_vehicle_level[i][2] = limit_of_cell[2][0].values;
        }
        else if(refined_vehicle_level[i][2] > limit_of_cell[2][0].values){
            int weight_index = find_element_range_in_limit(limit_of_cell[2], refined_vehicle_level[i][2]);
            if(weight_index==-1){
                refined_vehicle_level[i][2] = limit_of_cell[2][limit_of_cell[2].size()-1].values;
            } else{

                if(refined_vehicle_level[i][2] < limit_of_cell[2][weight_index].values){
                    //如果相等，什么都不做
                    //如果小于就需要判断了怎么取值
                    ///随机游走？

                    if((refined_vehicle_level[i][2] - limit_of_cell[2][weight_index-1].values) >=
                       (limit_of_cell[2][weight_index].values - refined_vehicle_level[i][2])){

                        refined_vehicle_level[i][2] = limit_of_cell[2][weight_index].values;

                    }

                    else if((refined_vehicle_level[i][2] - limit_of_cell[2][weight_index-1].values) <
                            (limit_of_cell[2][weight_index].values - refined_vehicle_level[i][2])){

                        refined_vehicle_level[i][2] = limit_of_cell[2][weight_index-1].values;

//                        if(std::count(refined_vehicle_level.begin(),refined_vehicle_level.end(),
//                                      std::vector<float>{refined_vehicle_level[i][0],refined_vehicle_level[i][1],limit_of_cell[2][weight_index].values})<=0){
//
//                            refined_vehicle_level.push_back(std::vector<float>{refined_vehicle_level[i][0],refined_vehicle_level[i][1],limit_of_cell[2][weight_index].values});
//                        }
                    }

//                    else if((refined_vehicle_level[i][2] - limit_of_cell[2][weight_index-1].values) ==
//                            (limit_of_cell[2][weight_index].values - refined_vehicle_level[i][2])){
//
//                        //refined_vehicle_level[i][0] = limit_of_cell[0][height_index-1].values;
//                        if(limit_of_cell[2][weight_index-1].percent>0.05){
//                            refined_vehicle_level[i][2] = limit_of_cell[2][weight_index-1].values;
//                            if(std::count(refined_vehicle_level.begin(),refined_vehicle_level.end(),
//                                          std::vector<float>{refined_vehicle_level[i][0],refined_vehicle_level[i][1],limit_of_cell[2][weight_index].values})<=0){
//
//                                refined_vehicle_level.push_back(std::vector<float>{refined_vehicle_level[i][0],refined_vehicle_level[i][1],limit_of_cell[2][weight_index].values});
//                            }
//                        }
//                        else{
//                            refined_vehicle_level[i][2] = limit_of_cell[2][weight_index].values;
//                        }
//                    }

                }

            }


        }

    }

    for(int i=0;i<refined_vehicle_level.size();i++){
        if(std::count(precise_vehicle_level.begin(),precise_vehicle_level.end(),refined_vehicle_level[i])<=0){
            precise_vehicle_level.push_back(refined_vehicle_level[i]);
        }

    }

    return precise_vehicle_level;

}





