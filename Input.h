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
class Input: public Layer<T>
{
private:
    int dimX,dimY;
    int x,y;
    std::vector<cv::Mat> planes;
    cv::ImreadModes type;

public:
    Input();
    Input(int dimx,int dimy,int x,int y);
    Input(int dimx,int dimy,int x,int y,string path,cv::ImreadModes type);
    bool loadFile(string path,cv::ImreadModes type);
    void toMatrix();
    int getX();
    int getY();
    int getDimX();
    int getDimY();
    void display();
    Matrix<T>& getResult();
    void work();
    void structure();
};

template <typename T>
Input<T>::Input():Layer<T>(Layer::Type::Input)
{
    this->dimX=0;
    this->dimY=0;
    this->x=0;
    this->y=0;
    this->type=cv::ImreadModes::IMREAD_COLOR;
}

template <typename T>
Input<T>::Input(int dimx, int dimy, int x, int y):Layer<T>(Layer::Type::Input)
{
    this->dimX=dimx;
    this->dimY=dimy;
    this->x=x;
    this->y=y;
    this->type=cv::ImreadModes::IMREAD_COLOR;
    this->result=Matrix<T>(dimx,dimy,x,y);
}

template <typename T>
Input<T>::Input(int dimx,int dimy,int x,int y,string path,cv::ImreadModes type):Layer<T>(Layer::Type::Input)
{
    this->dimX=dimx;
    this->dimY=dimy;
    this->x=x;
    this->y=y;
    this->type=type;
    this->result=Matrix<T>(dimx,dimy,x,y);
    this->loadFile(path,type);
}

template <typename T>
bool Input<T>::loadFile(string path, cv::ImreadModes type)
{
    cv::Mat img= cv::imread(path, type);
    if(img.empty())
    {
        return false;
    }
    cv::split(img,this->planes);
    this->toMatrix();
    return true;
}

template <typename T>
void Input<T>::toMatrix()
{
    for(int t=0;t<this->dimY;t++)
    {
        for(int i=0;i<this->x;i++)
        {
            for(int j=0;j<this->y;j++)
            {
                this->result.setNum(0,t,i,j,(float)this->planes[2-t].at<uchar>(i, j)/(float)255);
            }
        }
    }
}

template <typename T>
int Input<T>::getX()
{
    return this->x;
}

template <typename T>
int Input<T>::getY()
{
    return this->y;
}

template <typename T>
int Input<T>::getDimX()
{
    return this->dimX;
}

template <typename T>
int Input<T>::getDimY()
{
    return this->dimY;
}

template <typename T>
Matrix<T>& Input<T>::getResult()
{
    return (this->result);
}

template <typename T>
void Input<T>::work()
{

}

template <typename T>
void Input<T>::display()
{
    cout<<"Input:"<<endl;
    cout<<"DimX: "<<this->dimX<<" DimY: "<<this->dimY<<endl;
    cout<<"x: "<<this->getX()<<" "<<"y: "<<this->getY()<<endl;
    for(int t=0;t<this->dimX;t++)
    {
        for(int k=0;k<this->dimY;k++)
        {
            cout<<"dimX: "<<t<<" dimY: "<<k<<endl;
            for(int i=0;i<this->x;i++)
            {
                for(int j=0;j<this->y;j++)
                {
                    cout<<this->result.getNum(t,k,i,j)<<",";
                }
                cout<<endl;
            }
        }
    }
    cout<<endl;
}

template <typename T>
void Input<T>::structure()
{
    cout<<"Input:"<<endl;
    cout<<"DimX: "<<this->dimX<<" DimY: "<<this->dimY<<endl;
    cout<<"x: "<<this->getX()<<" "<<"y: "<<this->getY()<<endl;
}