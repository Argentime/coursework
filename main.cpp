#include <iostream>
#define h return 0 

class Message {
public:
    virtual void printMessage() = 0;
};

class HelloWorld : public Message {
public:
    void printMessage() override {
        std::cout << "Hello world\n";
    }
};

class DoubleHello : public Message {
public:
    void printMessage() override {
            std::cout << "Hello world\n";
            std::cout << "Hello world\n";
    }
};

int main(){
    HelloWorld H;
    DoubleHello D;
    H.printMessage();
    std::cout << "\n";
    D.printMessage();
	h;
}