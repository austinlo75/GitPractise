#include <iostream>
#include <vector>
using namespace std;

class Handler
{
public:
    virtual Handler* setNext(Handler* handler) = 0;
    virtual string Handle(string request) = 0;
};


class AbstractHandler : public Handler
{
private:
    Handler *next_handler;

public:
    Handler *setNext(Handler *handler) override {
        next_handler = handler;
        return handler;
    }

    string Handle(string request) override {
        if (next_handler)
            return next_handler->Handle(request);
        return {};
    }
};

class MonkeyHandler : public AbstractHandler
{
public:
    string Handle(string request) override {
        if (request == "Bannana")
            return "Monkey: I'll eat the " + request + ".\n";
        else
            return AbstractHandler::Handle(request);
    }
};

class SquirrelHandler : public AbstractHandler
{
public:
    string Handle(string request) override {
        if (request == "Nut")
            return "Squirrel: I'll eat the " + request + ".\n";
        else
            return AbstractHandler::Handle(request);
    }
};

class DogHandler : public AbstractHandler
{
public:
    string Handle(string request) override {
        if (request == "Meat")
            return "Dog: I'll eat the " + request + ".\n";
        else
            return AbstractHandler::Handle(request);
    }
};


void ClientCode(Handler &handler)
{
    vector<string> food = {"Nut", "Bannana", "Meat", "Coffee"};

    for (const string &f : food)
    {
        cout << "Client: Who wants a " << f << "? \n";
        const string result = handler.Handle(f);
        if (!result.empty())
            cout << " " << result;
        else
            cout << f << " was left untouched \n";
    }
}

int main()
{
    MonkeyHandler *monkey = new MonkeyHandler;
    SquirrelHandler *squi = new SquirrelHandler;
    DogHandler *dog = new DogHandler;

    monkey->setNext(squi)->setNext(dog);

    cout << "Chain monkey->squirrel->dog \n";
    ClientCode(*monkey);
    cout << endl;

    cout << "Chain squirrel->dog \n";
    ClientCode(*squi);
    cout << endl;

}
