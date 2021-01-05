#pragma once

#include "Matrix.h"
#include "Layer.h"

template <typename T>
class Conv: public Layer<T>
{
private:
    //typedef void (*ConvFunc)(Conv<T>&);
    //friend void funcReLU(Conv<T>&);
    //friend void funcdReLU(Conv<T>& conv);
    //ConvFunc func;
    void funcReLU(Conv<T>&);
    void funcdReLU(Conv<T>& conv);
public:
    enum Type
    {
        ReLU,dReLU
    };
    //Matrix result;
    Matrix<T>* bias= nullptr;
    Matrix<T>* kernal= nullptr;
    int inX,inY;
    int convX,convY;
    int outX,outY;
    int stride,pad;
    int inDimX,inDimY;
    int outDimX,outDimY;

    Type type;
    Conv (int inX,int inY,int convX,int convY,int inDimX,int inDimY,int outDimX,int outDimY,int stride=1,int pad=0,Type type=ReLU);
    Conv ();
    void display();
    void structure();
    void normalization();
    void convolution(Conv& conv,int dimX,int dimY,Matrix<T>& input,Matrix<T>& kernal,Matrix<T>& bias);
    void setArgs(Matrix<T>* bias,Matrix<T>* kernal);
    void work(Matrix<T> &input,Matrix<T>& kernal,Matrix<T> &bias);
    void work(Matrix<T> &input);
    Matrix<T>& getResult();

};
//template <typename T>
//void funcReLU(Conv<T>& conv);
//template <typename T>
//void funcdReLU(Conv<T>& conv);

template <typename T>
Conv<T>::Conv():Layer<T>(Layer::Type::Conv)
{
    this->inX = 0;
    this->inY = 0;
    this->convX = 0;
    this->convY = 0;
    this->outX = 0;
    this->outY = 0;
    this->type = ReLU;
    this->type = ReLU;
    this->stride=1;
    this->pad=0;
    this->inDimX=1;
    this->outDimX=1;
    this->inDimY=1;
    this->outDimY=1;
}

template <typename T>
Conv<T>::Conv(int inX, int inY, int convX, int convY,int inDimX,int inDimY,int outDimX,int outDimY, int stride, int pad, Type type):Layer<T>(Layer::Type::Conv)
{
    this->inX=inX;
    this->inY=inY;
    this->convX=convX;
    this->convY=convY;
    this->stride=stride;
    this->pad=pad;
    this->type=type;
    this->inDimX=inDimX;
    this->inDimY=inDimY;
    this->outDimX=outDimX;
    this->outDimY=outDimY;
    switch (type)
    {
        case ReLU:
            this->type = type;
            break;
        case dReLU:
            this->type=type;
            break;
        default:
            throw "Unknown Type of ConvFunction!";
            break;
    }
    this->outX=(inX+2*pad-convX)/stride+1;
    this->outY=(inY+2*pad-convY)/stride+1;
    this->result=Matrix<T>(outDimX,outDimY,this->outX,this->outY);
}

template <typename T>
void Conv<T>::setArgs(Matrix<T> *bias, Matrix<T> *kernal)
{
    this->bias=bias;
    this->kernal=kernal;
}

template <typename T>
void Conv<T>::work(Matrix<T> &input)
{
    if(this->bias== nullptr||this->kernal== nullptr)
    {
        throw "Error";
    }
    this->work(input,*(this->kernal),*(this->bias));
}

template <typename T>
void Conv<T>::work(Matrix<T>& input,Matrix<T>& kernal,Matrix<T>& bias)
{
    input.setPad(this->pad);
    for(int i=0;i<this->outDimY;i++)
    {
        for(int j=0;j<this->inDimY;j++)
        {
            //input.display();
            this->convolution(*this,i,j,input,kernal,bias);
            //if(input.getX()==17) this->result.display();
            //result[0][i]=sum(input[0][j]*kernal[i][j]+bias[0][i])
            /*
输入1个128*128*3的矩阵   dimX=1.dimY=3,x=128,y=128
卷积层:16个3层3*3矩阵  dimX=16,dimY=3,out:dimX=1,dimY=16,x=64,y=64
卷积层:32个16层3*3矩阵

 */
        }
    }
    input.setPad(0);
    //this->normalization();
    //this->func(*this);
    switch (this->type)
    {
        case dReLU:
            this->funcdReLU(*this);
            break;
        case ReLU:
            this->funcReLU(*this);
            break;
        default:
            throw "Error";
            break;

    }
}

template <typename T>
void Conv<T>::convolution(Conv<T>& conv,int I,int J,Matrix<T>& input,Matrix<T>& kernal,Matrix<T>& bias)
{
    int x,y;
    float tmp;
    for(int hashX=0;hashX*conv.stride+conv.convX<=input.getX();hashX++)
    {
        for(int hashY=0;hashY*conv.stride+conv.convY<=input.getY();hashY++)
        {
            tmp=0;
            for(int i=0;i<conv.convX;i++)
            {
                for(int j=0;j<conv.convY;j++)
                {
                    x=hashX*conv.stride+i;
                    y=hashY*conv.stride+j;
                    tmp+=input.getNum(0,J,x,y)*kernal.getNum(I,J,i,j);
                    //if(input.getX()==17)cout<<"0 "<<J<<" "<<x<<" "<<y<<" "<<input.getNum(0,J,x,y)<<endl;
                }
            }
            if(J==0) tmp+=bias.getNum(0,I,0,0);
            conv.result.add(0,I,hashX,hashY,tmp);
        }
    }
}

template <typename T>
void Conv<T>::normalization()
{
    float maxNum,minNum,num,tmp;
    for(int t=0;t<this->outDimX;t++)
    {
        for(int k=0;k<this->outDimY;k++)
        {
            maxNum=this->result.getMax(t,k);
            minNum=this->result.getMin(t,k);
            for(int i=0;i<this->outX;i++)
            {
                for(int j=0;j<this->outY;j++)
                {
                    num=this->result.getNum(t,k,i,j);
                    tmp=(num-minNum)/(maxNum-minNum);
                    this->result.setNum(t,k,i,j,tmp);
                }
            }
        }
    }
}

template <typename T>
void Conv<T>::funcReLU(Conv<T> &conv)
{
    float num;
    for(int t=0;t<conv.outDimX;t++)
    {
        for(int k=0;k<conv.outDimY;k++)
        {
            for(int i=0;i<conv.result.getX();i++)
            {
                for(int j=0;j<conv.result.getY();j++)
                {
                    num=conv.result.getNum(t,k,i,j);
                    if(num<=0) num=0;
                    conv.result.setNum(t,k,i,j,num);
                }
            }
        }
    }
}

template <typename T>
void Conv<T>::funcdReLU(Conv<T> &conv)
{
    float num;
    for(int t=0;t<conv.outDimX;t++)
    {
        for(int k=0;k<conv.outDimY;k++)
        {
            for(int i=0;i<conv.result.getX();i++)
            {
                for(int j=0;j<conv.result.getY();j++)
                {
                    num=conv.result.getNum(t,k,i,j);
                    if(num<=0) num=0;
                    else num=1;
                    conv.result.setNum(t,k,i,j,num);
                }
            }
        }
    }
}

template <typename T>
Matrix<T>& Conv<T>::getResult()
{
    return this->result;
}

template <typename T>
void Conv<T>::display()
{
    cout << "Conv: ";
    switch (this->type)
    {
        case ReLU:
            cout << "ReLU Function" << endl;
            break;
        case dReLU:
            cout<<"dReLU Function"<<endl;
            break;
    }
    cout << "Input Matrix Size: DimX=" <<this->inDimX<<" DimY="<<this->inDimY<<" Size="<<this->inX << " * " << this->inY << endl;
    cout << "Kernal Size: " << this->convX << " * " << this->convY << endl;
    cout << "Output Matrix Size: DimX=" <<this->outDimX<<" DimY="<<this->outDimY<<" Size="<<this->outX << " * " << this->outY << endl;
    for(int t=0;t<this->result.getDimX();t++)
    {
        for(int k=0;k<this->result.getDimY();k++)
        {
            cout<<"DimX="<<t<<" DimY="<<k<<endl;
            for(int i=0;i<this->result.getX();i++)
            {
                for(int j=0;j<this->result.getY();j++)
                {
                    cout<<this->result.getNum(t,k,i,j)<<" ";
                }
                cout<<endl;
            }
            cout<<endl;
        }
    }
    cout<<endl;
}

template <typename T>
void Conv<T>::structure()
{
    cout << "Conv: ";
    switch (this->type)
    {
        case ReLU:
            cout << "ReLU Function" << endl;
            break;
        case dReLU:
            cout<<"dReLU Function"<<endl;
            break;
    }
    cout << "Input Matrix Size: DimX=" <<this->inDimX<<" DimY="<<this->inDimY<<" Size="<<this->inX << " * " << this->inY << endl;
    cout << "Kernal Size: " << this->convX << " * " << this->convY << endl;
    cout << "Output Matrix Size: DimX=" <<this->outDimX<<" DimY="<<this->outDimY<<" Size="<<this->outX << " * " << this->outY << endl;
}