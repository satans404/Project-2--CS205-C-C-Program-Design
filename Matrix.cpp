#include "Matrix.h"

#include <iostream>

Matrix::Matrix()
{
    this->matrixs= nullptr;
    this->dimX=0;
    this->dimY=0;
    this->x=0;
    this->y=0;
    this->pad=0;
}

Matrix::Matrix(const Matrix& other)
{
    this->dimX=other.dimX;
    this->dimY=other.dimY;
    this->x=other.x;
    this->y=other.y;
    this->pad=other.pad;
    this->matrixs=other.matrixs;
}

Matrix::Matrix(int dimX,int dimY,int x,int y)
{
    this->dimX=dimX;
    this->dimY=dimY;
    this->x=x;
    this->y=y;
    this->pad=0;
    this->matrixs.reset(new float [dimX*dimY*x*y]);
    this->clear();
}

Matrix::Matrix(int dimX,int dimY,int x,int y,shared_ptr<float[]> data)
{
    this->dimX=dimX;
    this->dimY=dimY;
    this->x=x;
    this->y=y;
    this->pad=0;
    this->matrixs=data;
}

Matrix::Matrix(int dimX,int dimY,int x,int y,int pad,shared_ptr<float[]> data)
{
    this->dimX=dimX;
    this->dimY=dimY;
    this->x=x;
    this->y=y;
    this->pad=pad;
    this->matrixs=data;
}

Matrix::Matrix(int dimX,int dimY,int x,int y,float* data)
{
    int len=dimX*dimY*x*y;
    this->dimX=dimX;
    this->dimY=dimY;
    this->x=x;
    this->y=y;
    this->pad=0;
    this->matrixs.reset(new float[len]);
    for(int i=0;i<len;i++)
    {
        this->matrixs[i]=data[i];
    }
}

Matrix::Matrix(int dimX,int dimY,int x,int y,int pad,float* data)
{
    int len=dimX*dimY*x*y;
    this->dimX=dimX;
    this->dimY=dimY;
    this->x=x;
    this->y=y;
    this->pad=0;
    this->matrixs.reset(new float[len]);
    this->pad=pad;
    for(int i=0;i<len;i++)
    {
        this->matrixs[i]=data[i];
    }
}

Matrix::Matrix(int dimX,int dimY,int x,int y,int pad)
{
    int len=dimX*dimY*x*y;
    this->dimX=dimX;
    this->dimY=dimY;
    this->x=x;
    this->y=y;
    this->pad=0;
    this->matrixs.reset(new float[len]);
    this->pad=pad;
    this->clear();
}

void Matrix::clear()
{
    int len=this->dimX*this->dimY*this->x*this->y;
    for(int i=0;i<len;i++)
    {
        this->matrixs[i]=0;
    }
}

Matrix Matrix::operator=(const Matrix& other)
{
    this->dimX=other.dimX;
    this->dimY=other.dimY;
    this->x=other.x;
    this->y=other.y;
    this->pad=other.pad;
    this->matrixs=other.matrixs;
    return Matrix(*this);
}

int Matrix::getDimX()
{
    return this->dimX;
}

int Matrix::getDimY()
{
    return this->dimY;
}

int Matrix::getPos(int dimX,int dimY, int x, int y)
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

float Matrix::getNum(int dimX,int dimY, int x, int y)
{
    int pos=this->getPos(dimX,dimY,x,y);
    if(pos==-1) return 0;
    return this->matrixs[pos];
}

void Matrix::setNum(int dimX, int dimY, int x, int y, float w)
{
    int pos=this->getPos(dimX,dimY,x,y);
    if(pos==-1) return;
    this->matrixs[pos]=w;
}

void Matrix::add(int dimX, int dimY, int x, int y, float w)
{
    int pos=this->getPos(dimX,dimY,x,y);
    if(pos==-1) return;
    this->matrixs[pos]+=w;
}

void Matrix::minus(int dimX, int dimY, int x, int y, float w)
{
    int pos=this->getPos(dimX,dimY,x,y);
    if(pos==-1) return;
    this->matrixs[pos]=-w;
}

int Matrix::getX()
{
    return this->x+2*this->pad;
}

int Matrix::getY()
{
    return this->y+2*this->pad;
}

float Matrix::getMax(int dimX,int dimY)
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

float Matrix::getMin(int dimX,int dimY)
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

void Matrix::setPad(int pad)
{
    this->pad=pad;
}

float Matrix::getNum(int pos)
{
    return this->matrixs[pos];
}

int Matrix::getLen()
{
    return this->dimX*this->dimY*this->getX()*this->getY();
}

void Matrix::display()
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
Matrix::~Matrix() {}