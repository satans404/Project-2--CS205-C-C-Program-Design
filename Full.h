#pragma once

#include "Matrix.h"
#include "Layer.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>

using namespace std;

template <typename T>
class Full: public Layer<T>
{
private:
    Matrix<T>* kernal;
    Matrix<T>* bias;
    int inDimX,inDimY;
    int inX,inY;
    int outDimX,outDimY;
    int outX,outY;
    int pad;
public:
    Full();
    Full(int inDimX,int inDimY,int inX,int inY);
    void setArgs(Matrix<T>* bias,Matrix<T>* kernal);
    void work(Matrix<T>& input);
    void work(Matrix<T>& input,Matrix<T>& kernal,Matrix<T>& bias);
    void display();
    void structure();
    Matrix<T>& getResult();
};

template <typename T>
Full<T>::Full():Layer<T>(Layer::Type::Full)
{
    this->inX=0;
    this->inY=0;
    this->inDimX=0;
    this->inDimY=0;
    this->outX=0;
    this->outY=0;
    this->outDimX=0;
    this->outDimY=0;
    this->pad=0;
}

template <typename T>
Full<T>::Full(int inDimX,int inDimY,int inX,int inY):Layer<T>(Layer::Type::Full)
{
    this->inX=inX;
    this->inY=inY;
    this->inDimX=inDimX;
    this->inDimY=inDimY;
    this->outX=1;
    this->outY=1;
    this->outDimX=inDimX;
    this->outDimY=1;
    this->pad=0;
    this->result=Matrix<T>(this->outDimX,this->outDimY,1,1);
}

template <typename T>
void Full<T>::setArgs(Matrix<T>* bias, Matrix<T>* kernal)
{
    this->bias=bias;
    this->kernal=kernal;
}

template <typename T>
void Full<T>::work(Matrix<T>& input)
{
    if(this->bias== nullptr || this->kernal== nullptr)
    {
        throw "Error!";
    }
    else
    {
        this->work(input,*(this->kernal),*(this->bias));
    }
}

template <typename T>
void Full<T>::work(Matrix<T>& input,Matrix<T>& kernal,Matrix<T>& bias)
{
    int len=input.getLen(),start=0,len2=kernal.getLen();
    float ans=0;
    for(int t=0;t<this->inDimX;t++)
    {
        ans=0;
        for(int i=0;i<len;i++)
        {
            ans+=input.getNum(i)*kernal.getNum(t*len+i);
        }
        this->result.setNum(t,0,0,0,ans+bias.getNum(t));
    }
}

template <typename T>
Matrix<T>& Full<T>::getResult()
{
    return this->result;
}

template <typename T>
void Full<T>::display()
{
    cout<<"Full: "<<endl;
    this->result.display();
}

template <typename T>
void Full<T>::structure()
{
    cout<<"Full"<<endl;
}
