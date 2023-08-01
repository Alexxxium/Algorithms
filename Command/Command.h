#pragma once
#include <vector>


namespace algs
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void execute() = 0;
		virtual void undo() = 0;
		virtual void redo() = 0;
	};

	class Receiver
	{
	public:
		virtual ~Receiver() = default;
		virtual void perfomAction() = 0;
	};

	class Subject
	{
	protected:
		std::vector<Command*> commands;

	public:
		explicit Subject(const int &size): commands(size) 
		{
		}
		virtual ~Subject() { 
			for (Command *i : commands) {
				delete i;
			}
		}

		virtual void run() = 0;
		virtual void undoCommand() = 0;
		virtual void redoCommand() = 0;
		virtual void addCommand(Command *command) = 0;
		
	};

	class Buffer
	{
	protected:
		std::vector<Command*> buffer;
		int currentIndex;
		
		Buffer(): currentIndex(-1)
		{
		}
		~Buffer() {
			for (auto &i : buffer) {
				delete i;
			}
		}
	};
}