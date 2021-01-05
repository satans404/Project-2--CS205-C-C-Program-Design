#include "Processor.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>
#include <cstdarg>
#include <initializer_list>

Processor::Processor()
{

}

Processor::Processor(std::initializer_list<Layer*> layers)
{
    for(auto& i: layers)
    {
        this->Queue.push_back(i);
    }
}
void Processor::clear()
{
    this->Queue.clear();
}

void Processor::push_back(Layer* layer)
{
    this->Queue.push_back(layer);
}

void Processor::work()
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
            this->Queue[i]->work(this->Queue[i-1]->getResult());
        }
    }
    this->result=this->Queue[l-1]->getResult();
}

template <typename T>
Matrix<T>& Processor::getResult()
{
    return this->result;
}

void Processor::display()
{
    for(Layer* i:this->Queue)
    {
        i->display();
    }
}

void Processor::structure()
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