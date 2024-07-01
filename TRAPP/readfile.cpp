//
// Created by 11131 on 2023/7/2.
//
#include "graph.h"
#include <string>
#include <sstream>
#include <fstream>
#include <random>
//#include "devide_car.h"
#include "vehicle.h"

Graph sumGraph;

void readfile(std::string add1, std::string add2) {
    std::ifstream inputFile1;//读取分类数据
    inputFile1.open(add1);
    std::ifstream inputFile2;//读取边数据
    inputFile2.open(add2);

    std::string line;
    getline(inputFile2, line);
    int edgenumbers = stoi(line);

    getline(inputFile1, line);
    std::istringstream iss(line);
    std::string ls;
    iss >> ls;
    iss >> ls;
    iss >> ls;
    iss >> ls;
    int partitionsnumbers = stoi(ls);
    iss >> ls;
    iss >> ls;
    iss >> ls;
    iss >> ls;
    int nodenumbers = stoi(ls);

    std::vector<int> nodeposition;
    nodeposition.resize(nodenumbers + 1);

    std::vector<int> eachparts;
    eachparts.resize(partitionsnumbers + 1);
    getline(inputFile1, line);
    //读取分区域数据
    for (int i = 1; i <= partitionsnumbers; i++) {
        getline(inputFile1, line);
        std::istringstream iss0(line);
        iss0 >> ls;
        iss0 >> ls;
        iss0 >> ls;
        int ls0;
        ls0 = stoi(ls);

        eachparts[i] = ls0;

        for (int ii = 1; ii <= ls0; ii++) {
            getline(inputFile1, line);
            std::istringstream iss1(line);
            iss1 >> ls;
            int ls1;
            ls1 = stoi(ls);

            nodeposition[ls1] = i;
        }
    }

    sumGraph.set(nodenumbers, edgenumbers, partitionsnumbers, eachparts, nodeposition);


    getline(inputFile2, line);
    for (int i = 1; i <= edgenumbers; i++) {
        getline(inputFile2, line);
        std::istringstream iss2(line);
        std::string ls2;
        iss2 >> ls2;


        int a1, a2;
        float a3, a4, a5, a6;
        iss2 >> ls2;

        a1 = stoi(ls2);

        iss2 >> ls2;

        a2 = stoi(ls2);

        iss2 >> ls2;

        a3 = stof(ls2);

        iss2 >> ls2;

        a4 = stof(ls2);

        iss2 >> ls2;

        a5 = stof(ls2);

        iss2 >> ls2;

        a6 = stof(ls2);

        sumGraph.add_edge(a1, a2, a3, a4, a5, a6);
    }


    sumGraph.final();


}

int main() {
    

    std::string add1 = "./node_clusters.txt";

    std::string add2 = "./edge_new.gr";
    readfile(add1, add2);
    sumGraph.entrance();

   sumGraph.compute_shortcut();

    std::ifstream file("./query_point.txt");
        // 定义变量来存储读取的数据
    int intData1, intData2;
    float floatData1, floatData2, floatData3;
    
    // 用于存储每行的数据
    std::vector<int> intValues1;
    std::vector<int> intValues2;

    std::vector<float> floatValues1;
    std::vector<float> floatValues2;
    std::vector<float> floatValues3;
    
    // 逐行读取数据
    while (file >> intData1 >> intData2 >> floatData1 >> floatData2 >> floatData3) {
        // 将读取的数据存入对应的向量中
        intValues1.push_back(intData1);
        intValues2.push_back(intData2);
        floatValues1.push_back(floatData1);
        floatValues2.push_back(floatData2);
        floatValues3.push_back(floatData3);
    }

    int count = 0;

    for (int i = 0; i <30; i++) {
        count++;
        std::cout << "test node: " << intValues1[i] << " ->" << intValues2[i] << std::endl;
        std::cout << "data: " << floatValues1[i] << " " << floatValues2[i] << " " << floatValues3[i] << std::endl;
        sumGraph.query(intValues1[i], intValues2[i], floatValues1[i], floatValues2[i], floatValues3[i]);
    }
    std::cout << "final count: " << count << std::endl;


}

