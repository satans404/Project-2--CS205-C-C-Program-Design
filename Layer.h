#pragma once

#include "Matrix.h"
#include <string>
#include <opencv2/opencv.hpp>

template <typename T>
class Layer
{
public:
    Matrix<T> result;
    enum Type
    {
        Input,Pool,Conv,Full
    };
    Layer();
    Layer(Type type);
    virtual Matrix<T>& getResult();
    virtual void work();
    virtual void work(Matrix<T>& input);
    virtual void setArgs(Matrix<T>* bias,Matrix<T>* kernal);
    virtual void display();
    virtual int getX();
    virtual int getY();
    virtual bool loadFile(string path,cv::ImreadModes type);
    virtual void structure();
private:
    Type type;
};

template <typename T>
bool Layer<T>::loadFile(string path,cv::ImreadModes type)
{
    return false;
}

template <typename T>
Layer<T>::Layer()
{

}
template <typename T>
Layer<T>::Layer(Type type)
{
    this->type=type;
}

template <typename T>
Matrix<T>& Layer<T>::getResult()
{
    return this->result;
}

template <typename T>
void Layer<T>::work()
{

}

template <typename T>
void Layer<T>::setArgs(Matrix<T> *bias, Matrix<T> *kernal)
{

}

template <typename T>
void Layer<T>::structure() {}

template <typename T>
void Layer<T>::work(Matrix<T>& input)
{

}

template <typename T>
void Layer<T>::display()
{

}

template <typename T>
int Layer<T>::getX()
{
    return 0;
}

template <typename T>
int Layer<T>::getY()
{
    return 0;
}
