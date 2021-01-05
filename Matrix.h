#pragma once

#include <memory>
#include <iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>

using namespace std;
template <typename T>
class Matrix
{
private:
    shared_ptr<T[]> matrixs;
    int dimX,dimY;
    int x,y;
    int pad;

public:
    virtual ~Matrix();
    Matrix();
    Matrix(const Matrix<T>& other);
    Matrix(int dimX,int dimY,int x,int y);
    Matrix(int dimX,int dimY,int x,int y,shared_ptr<T[]> data);
    Matrix(int dimX,int dimY,int x,int y,int pad,shared_ptr<T[]> data);
    Matrix(int dimX,int dimY,int x,int y,T* data);
    Matrix(int dimX,int dimY,int x,int y,int pad,T* data);
    Matrix(int dimX,int dimY,int x,int y,int pad);
    Matrix operator=(const Matrix& other);
    void clear();
    int getPos(int dimX,int dimY,int x,int y);
    int getX();
    int getY();
    int getDimX();
    int getDimY();
    T getMax(int dimX,int dimY);
    T getMin(int dimX,int dimY);
    T getNum(int dimX,int dimY,int x,int y);
    T getNum(int pos);
    void setNum(int dimX,int dimY,int x,int y,T w);
    void add(int dimX,int dimY,int x,int y,T w);
    void minus(int dimX,int dimY,int x,int y,T w);
    void display();
    void setPad(int pad);
    int getLen();
};

template <typename T>
Matrix<T>::Matrix()
{
    this->matrixs= nullptr;
    this->dimX=0;
    this->dimY=0;
    this->x=0;
    this->y=0;
    this->pad=0;
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other)
{
    this->dimX=other.dimX;
    this->dimY=other.dimY;
    this->x=other.x;
    this->y=other.y;
    this->pad=other.pad;
    this->matrixs=other.matrixs;
}

template <typename T>
Matrix<T>::Matrix(int dimX,int dimY,int x,int y)
{
    this->dimX=dimX;
    this->dimY=dimY;
    this->x=x;
    this->y=y;
    this->pad=0;
    this->matrixs.reset(new float [dimX*dimY*x*y]);
    this->clear();
}

template <typename T>
Matrix<T>::Matrix(int dimX,int dimY,int x,int y,shared_ptr<T[]> data)
{
    this->dimX=dimX;
    this->dimY=dimY;
    this->x=x;
    this->y=y;
    this->pad=0;
    this->matrixs=data;
    this->matrixs=data;
}

template <typename T>
Matrix<T>::Matrix(int dimX,int dimY,int x,int y,int pad,shared_ptr<T[]> data)
{
    this->dimX=dimX;
    this->dimY=dimY;
    this->x=x;
    this->y=y;
    this->pad=pad;
    this->matrixs=data;
}

template <typename T>
Matrix<T>::Matrix(int dimX,int dimY,int x,int y,T* data)
{
    int len=dimX*dimY*x*y;
    this->dimX=dimX;
    this->dimY=dimY;
    this->x=x;
    this->y=y;
    this->pad=0;
    this->matrixs.reset(new T[len]);
    for(int i=0;i<len;i++)
    {
        this->matrixs[i]=data[i];
    }
}

template <typename T>
Matrix<T>::Matrix(int dimX,int dimY,int x,int y,int pad,T* data)
{
    int len=dimX*dimY*x*y;
    this->dimX=dimX;
    this->dimY=dimY;
    this->x=x;
    this->y=y;
    this->pad=0;
    this->matrixs.reset(new T[len]);
    this->pad=pad;
    for(int i=0;i<len;i++)
    {
        this->matrixs[i]=data[i];
    }
}

template <typename T>
Matrix<T>::Matrix(int dimX,int dimY,int x,int y,int pad)
{
    int len=dimX*dimY*x*y;
    this->dimX=dimX;
    this->dimY=dimY;
    this->x=x;
    this->y=y;
    this->pad=0;
    this->matrixs.reset(new T[len]);
    this->pad=pad;
    this->clear();
}

template <typename T>
void Matrix<T>::clear()
{
    int len=this->dimX*this->dimY*this->x*this->y;
    for(int i=0;i<len;i++)
    {
        this->matrixs[i]=0;
    }
}

template <typename T>
Matrix<T> Matrix<T>::operator=(const Matrix& other)
{
    this->dimX=other.dimX;
    this->dimY=other.dimY;
    this->x=other.x;
    this->y=other.y;
    this->pad=other.pad;
    this->matrixs=other.matrixs;
    return Matrix(*this);
}

template <typename T>
int Matrix<T>::getDimX()
{
    return this->dimX;
}

template <typename T>
int Matrix<T>::getDimY()
{
    return this->dimY;
}

template <typename T>
int Matrix<T>::getPos(int dimX,int dimY, int x, int y)
{
    if(dimX>=this->dimX||dimY>=this->dimY||dimX<0||dimY<0||x<0||y<0) return -1;
    if(this->pad==0)
    {
        if(x>=this->x||y>=this->y) return -1;
        return (dimX*this->dimY+dimY)*(this->x*this->y)+x*this->y+y;
    }
    else
    {
        if(x<this->pad||y<this->pad||x>=this->x+this->pad||y>=this->y+this->pad)
        {
            return -1;
        }
        return (dimX*this->dimY+dimY)*(this->x*this->y)+this->y*(x-this->pad)+(y-this->pad);
    }
}

template <typename T>
T Matrix<T>::getNum(int dimX,int dimY, int x, int y)
{
    int pos=this->getPos(dimX,dimY,x,y);
    if(pos==-1) return 0;
    return this->matrixs[pos];
}

template <typename T>
void Matrix<T>::setNum(int dimX, int dimY, int x, int y, T w)
{
    int pos=this->getPos(dimX,dimY,x,y);
    if(pos==-1) return;
    this->matrixs[pos]=w;
}

template <typename T>
void Matrix<T>::add(int dimX, int dimY, int x, int y, T w)
{
    int pos=this->getPos(dimX,dimY,x,y);
    if(pos==-1) return;
    this->matrixs[pos]+=w;
}

template <typename T>
void Matrix<T>::minus(int dimX, int dimY, int x, int y, T w)
{
    int pos=this->getPos(dimX,dimY,x,y);
    if(pos==-1) return;
    this->matrixs[pos]=-w;
}

template <typename T>
int Matrix<T>::getX()
{
    return this->x+2*this->pad;
}

template <typename T>
int Matrix<T>::getY()
{
    return this->y+2*this->pad;
}

template <typename T>
T Matrix<T>::getMax(int dimX,int dimY)
{
    float tmp=-FLT_MAX;
    for(int i=0;i<this->getX();i++)
    {
        for(int j=0;j<this->getY();j++)
        {
            tmp=max(tmp,this->getNum(dimX,dimY,i,j));
        }
    }
    return tmp;
}

template <typename T>
T Matrix<T>::getMin(int dimX,int dimY)
{
    float tmp=FLT_MAX;
    for(int i=0;i<this->getX();i++)
    {
        for(int j=0;j<this->getY();j++)
        {
            tmp=min(tmp,this->getNum(dimX,dimY,i,j));
        }
    }
    return tmp;
}

template <typename T>
void Matrix<T>::setPad(int pad)
{
    this->pad=pad;
}

template <typename T>
T Matrix<T>::getNum(int pos)
{
    return this->matrixs[pos];
}

template <typename T>
int Matrix<T>::getLen()
{
    return this->dimX*this->dimY*this->getX()*this->getY();
}

template <typename T>
void Matrix<T>::display()
{
    //cout<<"Matrix:"<<endl;
    //cout<<"DimX: "<<this->dimX<<" DimY: "<<this->dimY<<endl;
    //cout<<"x: "<<this->getX()<<" "<<"y: "<<this->getY()<<endl;
    for(int t=0;t<this->dimX;t++)
    {
        for(int k=0;k<this->dimY;k++)
        {
            //cout<<"dimX: "<<t<<" dimY: "<<k<<endl;
            for(int i=0;i<this->x+2*this->pad;i++)
            {
                for(int j=0;j<this->y+2*this->pad;j++)
                {
                    cout<<this->getNum(t,k,i,j)<<" ";
                }
                cout<<endl;
            }
        }
    }
    cout<<endl;
}

template <typename T>
Matrix<T>::~Matrix() {}
