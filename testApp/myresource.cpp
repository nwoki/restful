#include "myresource.h"

MyResource::MyResource()
    : Resource("test")
{

}


MyResource::~MyResource()
{

}


void MyResource::restGet()
{
    qDebug("[MyResource::restGet]");
}
