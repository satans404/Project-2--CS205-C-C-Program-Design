#include "Full.h"
#include "Matrix.h"

using namespace std;

Full::Full():Layer(Layer::Type::Full)
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

Full::Full(int inDimX,int inDimY,int inX,int inY):Layer(Layer::Type::Full)
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
    this->result=Matrix(this->outDimX,this->outDimY,1,1);
}

void Full::setArgs(Matrix* bias, Matrix* kernal)
{
    this->bias=bias;
    this->kernal=kernal;
}

void Full::work(Matrix &input)
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

void Full::work(Matrix& input,Matrix& kernal,Matrix& bias)
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

Matrix& Full::getResult()
{
    return this->result;
}

void Full::display()
{
    cout<<"Full: "<<endl;
    this->result.display();
}

void Full::structure()
{
    cout<<"Full"<<endl;
}
