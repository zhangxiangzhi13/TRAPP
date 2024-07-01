//
// Created by charles chen on 2023/6/27.
//

#ifndef CAR_CLASSIFICATION_VEHICLE_H
#define CAR_CLASSIFICATION_VEHICLE_H


class vehicle {

public:
    ~vehicle(){}

    vehicle(float new_height, float new_width, float new_weight){
        height = new_height;
        width = new_width;
        weight = new_weight;
    }

    float get_height(){
        return this->height;
    }

    float get_weight(){
        return this->weight;
    }

    float get_width(){
        return this->width;
    }



private:
    float height;
    float width;
    float weight;

};


#endif //CAR_CLASSIFICATION_VEHICLE_H
