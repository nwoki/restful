#include "../src/resource.h"

class MyResource : public RESTFul::Resource
{

public:
    MyResource();
    ~MyResource();

    void restGet();
    void restDelete() {};
    void restPost() {};
    void restPut() {};

};
