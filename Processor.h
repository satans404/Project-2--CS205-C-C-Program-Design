#pragma once

#include "Layer.h"
#include "Matrix.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include <cstdarg>
#include <initializer_list>

template <typename T>
class Processor
{
private:
    vector<Layer<T>*> Queue;
    Matrix<T> result;
public:
    Processor();
    Processor(std::initializer_list<Layer<T>*> layers);
    void work();
    void clear();
    void push_back(Layer<T>* layer);
    void display();
    void structure();
    Matrix<T>& getResult();
};

template <typename T>
Processor<T>::Processor()
{

}

template <typename T>
Processor<T>::Processor(std::initializer_list<Layer<T>*> layers)
{
    for(auto& i: layers)
    {
        this->Queue.push_back(i);
    }
}

template <typename T>
void Processor<T>::clear()
{
    this->Queue.clear();
}

template <typename T>
void Processor<T>::push_back(Layer<T>* layer)
{
    this->Queue.push_back(layer);
}

template <typename T>
void Processor<T>::work()
{
    int l=this->Queue.size();
    for(int i=0;i<l;i++)
    {
        if(i==0)
        {
            this->Queue[i]->work();
        }
        else
        {
            this->Queue[i]->getResult().clear();
            this->Queue[i]->work(this->Queue[i-1]->getResult());
        }
    }
    this->result=this->Queue[l-1]->getResult();
}

template <typename T>
Matrix<T>& Processor<T>::getResult()
{
    return this->result;
}

template <typename T>
void Processor<T>::display()
{
    for(Layer<T>* i:this->Queue)
    {
        i->display();
    }
}

template <typename T>
void Processor<T>::structure()
{
    int l=this->Queue.size();
    cout<<"Processor: "<<endl;
    cout<<"Size: "<<l<<endl;
    for(int i=0;i<l;i++)
    {
        cout<<" Num = "<<i<<" : "<<endl;
        this->Queue[i]->structure();
    }
}
