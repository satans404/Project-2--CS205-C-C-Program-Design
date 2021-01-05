#include <iostream>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include "Pool.h"
#include "Matrix.h"

using namespace std;

void funcMin(Pool &pool,int dimX,int dimY,Matrix &input)
{
    int posX = 0, posY = 0, hashX = 0, hashY = 0,hashPos,x,y;
    float tmp;
    for (hashX = 0; hashX < pool.outX; hashX++)
    {
        for (hashY = 0; hashY < pool.outY; hashY++)
        {
            tmp=FLT_MAX;
            for (int i = 0; i < pool.poolX; i++)
            {
                for (int j = 0; j < pool.poolY; j++)
                {
                    x=(hashX*pool.poolX+i);
                    y=hashY*pool.poolY+j;
                    tmp=min(tmp,input.getNum(dimX,dimY,x,y));
                }
            }
            pool.result.setNum(dimX,dimY,hashX,hashY,tmp);
        }
    }
}
void funcMax(Pool &pool,int dimX,int dimY,Matrix &input)
{
    int posX = 0, posY = 0, hashX = 0, hashY = 0,hashPos,x,y;
    float tmp;
    for (hashX = 0; hashX < pool.outX; hashX++)
    {
        for (hashY = 0; hashY < pool.outY; hashY++)
        {
            tmp=-FLT_MAX;
            for (int i = 0; i < pool.poolX; i++)
            {
                for (int j = 0; j < pool.poolY; j++)
                {
                    x=(hashX*pool.poolX+i);
                    y=hashY*pool.poolY+j;
                    tmp=max(tmp,input.getNum(dimX,dimY,x,y));
                }
            }
            pool.result.setNum(dimX,dimY,hashX,hashY,tmp);
        }
    }
}
void funcAve(Pool &pool,int dimX,int dimY,Matrix &input)
{
    int posX = 0, posY = 0, hashX = 0, hashY = 0,hashPos,x,y;
    float tmp=0,base=(float)pool.poolX*(float)pool.poolY;
    for (hashX = 0; hashX < pool.outX; hashX++)
    {
        for (hashY = 0; hashY < pool.outY; hashY++)
        {
            tmp=0;
            for (int i = 0; i < pool.poolX; i++)
            {
                for (int j = 0; j < pool.poolY; j++)
                {
                    x=(hashX*pool.poolX+i);
                    y=hashY*pool.poolY+j;
                    tmp+=input.getNum(dimX,dimY,x,y);
                }
            }
            pool.result.setNum(dimX,dimY,hashX,hashY,tmp/base);
        }
    }
}
Pool::Pool(int x, int y, int poolX, int poolY,int DimX,int DimY, int pad=0,Type type = MAX):Layer(Layer::Type::Pool)
{
    this->inX = x;
    this->inY = y;
    this->poolX = poolX;
    this->poolY = poolY;
    this->outX = (x+2*pad) / poolX;
    if ((x+2*pad) % poolX)
        this->outX++;
    this->outY = (y+2*pad) / poolY;
    if ((y+2*pad) % poolY)
        this->outY++;
    this->DimX=DimX;
    this->DimY=DimY;
    this->pad=pad;
    this->result = Matrix(DimX,DimY,this->outX,this->outY);
    switch (type)
    {
        case MIN:
            this->func = funcMin;
            this->type = MIN;
            break;
        case MAX:
            this->func = funcMax;
            this->type = MAX;
            break;
        case AVE:
            this->func = funcAve;
            this->type = AVE;
            break;
        default:
            throw "Unknown Type of PoolFunction!";
            break;
    }
}

Pool::Pool():Layer(Layer::Type::Pool)
{
    this->inX = 0;
    this->inY = 0;
    this->poolX = 0;
    this->poolY = 0;
    this->outX = 0;
    this->outY = 0;
    this->DimX=1;
    this->DimY=1;
    this->pad=0;
    this->func = funcMax;
    this->type = MAX;
}

float Pool::getResultNum(int dimX,int dimY,int x,int y)
{
    return this->result.getNum(dimX,dimY,x,y);
}

void Pool::work(Matrix& input)
{
    input.setPad(this->pad);
    for(int i=0;i<this->DimX;i++)
    {
        for(int j=0;j<this->DimY;j++)
        {
            this->func(*this,i,j,input);
        }
    }
    input.setPad(0);
}

Matrix& Pool::getResult()
{
    return this->result;
}

void Pool::display()
{
    cout << "Pool: ";
    switch (this->type)
    {
        case MIN:
            cout << "MinPool" << endl;
            break;
        case MAX:
            cout << "MaxPool" << endl;
            break;
        case AVE:
            cout << "AvePool" << endl;
            break;
        default:
            cout << "UnknownPool" << endl;
            break;
    }
    cout << "Input Matrix Size: DimX=" <<this->DimX<<" DimY="<<this->DimY<<" Size="<<this->inX << " * " << this->inY << endl;
    cout << "Kernal Size: " << this->poolX << " * " << this->poolY << endl;
    cout << "Output Matrix Size: DimX=" <<this->result.Matrix::getDimX()<<" DimY="<<this->result.Matrix::getDimY()<<" Size="<<this->outX << " * " << this->outY << endl;
    for(int t=0;t<this->result.getDimX();t++)
    {
        for(int k=0;k<this->result.getDimY();k++)
        {
            cout<<"DimX="<<t<<" DimY="<<k<<endl;
            for(int i=0;i<this->outX;i++)
            {
                for(int j=0;j<this->outY;j++)
                {
                    cout<<this->getResultNum(t,k,i,j)<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
        }
    }
    cout<<endl;
}

void Pool::structure()
{
    cout << "Pool: ";
    switch (this->type)
    {
        case MIN:
            cout << "MinPool" << endl;
            break;
        case MAX:
            cout << "MaxPool" << endl;
            break;
        case AVE:
            cout << "AvePool" << endl;
            break;
        default:
            cout << "UnknownPool" << endl;
            break;
    }
    cout << "Input Matrix Size: DimX=" <<this->DimX<<" DimY="<<this->DimY<<" Size="<<this->inX << " * " << this->inY << endl;
    cout << "Kernal Size: " << this->poolX << " * " << this->poolY << endl;
    cout << "Output Matrix Size: DimX=" <<this->result.Matrix::getDimX()<<" DimY="<<this->result.Matrix::getDimY()<<" Size="<<this->outX << " * " << this->outY << endl;
}