#include "Layer.h"
#include "Matrix.h"

Layer::Layer()
{

}

Layer::Layer(Type type)
{
    this->type=type;
}

Layer::Type Layer::getType()
{
    return this->type;
}
Matrix& Layer::getResult()
{
    return this->result;
}
void Layer::work()
{

}

void Layer::setArgs(Matrix *bias, Matrix *kernal)
{

}

void Layer::structure() {}

void Layer::work(Matrix& input)
{

}

void Layer::display()
{

}
int Layer::getX()
{
    return 0;
}
int Layer::getY()
{
    return 0;
}
