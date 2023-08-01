#include <iostream>
#include <list>
#include "Command.h"



class Receiver_A : public algs::Receiver
{
public:
    void perfomAction() override {
        std::cout << "\tReceiver notifyded!\n";
    }
};

class Command_A: public algs::Command
{
private:
    //int value;
    Receiver_A *receiver;

public:
    int value;
    explicit Command_A(Receiver_A *rec, int val = 0) : 
        receiver(rec), 
        value(val)
    {
    }
    void execute() override {
        std::cout << "execute:\t" << value << " -> " << value + 1 << '\t';
        ++value;
        receiver->perfomAction();
    }
    void undo() override {
        std::cout << "undo:\t\t" << value << " -> " << value - 1<< '\t';
        --value;
        receiver->perfomAction();
    }
    void redo() override {
        std::cout << "redo:\t\t" << value << " -> " << value + 1 << '\t';
        ++value;
        receiver->perfomAction();
    }
};

class Invoker_A: public algs::Subject, public algs::Buffer
{
public:
    explicit Invoker_A(const int &size): 
        Subject(size)
    {
    }
    void run() override {
        for (auto *cmd: commands) {
            cmd->execute();
            buffer.push_back(cmd);
        }
        currentIndex = buffer.size() - 1;
    }
    void addCommand(algs::Command *cmd) override {
        commands.push_back(cmd);
    }
    void undoCommand() override {
        buffer[currentIndex]->undo();
        --currentIndex;
    }
    void redoCommand() override {
        ++currentIndex;
        buffer[currentIndex]->redo();
    }
};


int main()
{
    Receiver_A *receiver = new Receiver_A;
    Invoker_A *invoker = new Invoker_A(0);


    std::vector<Command_A*> cmds;
    cmds.push_back(new Command_A(receiver));
    cmds.push_back(new Command_A(receiver, 1));
    cmds.push_back(new Command_A(receiver, 2));
    cmds.push_back(new Command_A(receiver, 3));
    cmds.push_back(new Command_A(receiver, 4));
    cmds.push_back(new Command_A(receiver, 5));
    cmds.push_back(new Command_A(receiver, 6));
    cmds.push_back(new Command_A(receiver, 7));
    cmds.push_back(new Command_A(receiver, 8));
    cmds.push_back(new Command_A(receiver, 9));

    for (auto *i : cmds) {
        invoker->addCommand(i);
    }

    invoker->run();
    for (auto &i : cmds) {
        std::cout << i->value << ' ';
    }
    std::cout << '\n';

    for (int i = 0; i < 3; ++i) {
        invoker->undoCommand();
    }
    for (auto &i : cmds) {
        std::cout << i->value << ' ';
    }
    std::cout << '\n';

    for (int i = 0; i < 3; ++i) {
        invoker->redoCommand();
    }
    for (auto &i : cmds) {
        std::cout << i->value << ' ';
    }
    std::cout << '\n';

    for (int i = 0; i < 4; ++i) {
        invoker->undoCommand();
    }
    for (auto &i : cmds) {
        std::cout << i->value << ' ';
    }
    std::cout << '\n';
}

