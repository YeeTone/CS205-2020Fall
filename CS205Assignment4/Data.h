//
// Created by 16011 on 2020/11/24.
//

#ifndef A4_1_DATA_H
#define A4_1_DATA_H


class Data {
private:
    float* values= nullptr;
    int referenceTimes=0;
public:
    explicit Data(long size);
    ~Data();
    [[nodiscard]] int getReference()const;
    float* get_values_ptr();
    void addReference();
    void removeReference();
    void setDefaultRef();
};


#endif //A4_1_DATA_H
