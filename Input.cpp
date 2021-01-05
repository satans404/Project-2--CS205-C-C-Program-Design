#include "Input.h"
#include "Matrix.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<vector>

Input::Input():Layer(Layer::Type::Input)
{
    this->dimX=0;
    this->dimY=0;
    this->x=0;
    this->y=0;
    this->type=cv::ImreadModes::IMREAD_COLOR;
}

Input::Input(int dimx, int dimy, int x, int y):Layer(Layer::Type::Input)
{
    this->dimX=dimx;
    this->dimY=dimy;
    this->x=x;
    this->y=y;
    this->type=cv::ImreadModes::IMREAD_COLOR;
    this->result=Matrix(dimx,dimy,x,y);
}

Input::Input(int dimx,int dimy,int x,int y,string path,cv::ImreadModes type):Layer(Layer::Type::Input)
{
    this->dimX=dimx;
    this->dimY=dimy;
    this->x=x;
    this->y=y;
    this->type=type;
    this->result=Matrix(dimx,dimy,x,y);
    this->loadFile(path,type);
}

bool Input::loadFile(string path, cv::ImreadModes type)
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

void Input::toMatrix()
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

int Input::getX()
{
    return this->x;
}

int Input::getY()
{
    return this->y;
}

int Input::getDimX()
{
    return this->dimX;
}

int Input::getDimY()
{
    return this->dimY;
}

Matrix& Input::getResult()
{
    return (this->result);
}

void Input::work()
{

}

void Input::display()
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

void Input::structure()
{
    cout<<"Input:"<<endl;
    cout<<"DimX: "<<this->dimX<<" DimY: "<<this->dimY<<endl;
    cout<<"x: "<<this->getX()<<" "<<"y: "<<this->getY()<<endl;
}