// memento.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cliext/vector> 
using namespace std;
using namespace System;


ref class Memento {
private:
	String^ state;

public:
	Memento(String^ state){
		this->state = state;
	}

	String^ getState(){
		return state;
	}	
};


ref class Originator {
private:
	String^ state;

public:
	void setState(String^ state){
		this->state = state;
	}

	String^ getState(){
		return state;
	}

	Memento^ saveStateToMemento(){
		return gcnew Memento(state);
	}

	void getStateFromMemento(Memento^ Memento){
		state = Memento->getState();
	}
};

ref class CareTaker {
private:
	cliext::vector<Memento^>^ mementoList;

public:
	CareTaker(){
		mementoList = gcnew cliext::vector<Memento^>();
	}
	void add(Memento^ state){
		mementoList->push_back(state);
	}

	Memento^ get(int index){
		return mementoList->at(index);
	}
};



int _tmain(int argc, _TCHAR* argv[])
{
	Originator^ originator = gcnew Originator();
	CareTaker^ careTaker = gcnew CareTaker();
	originator->setState("State #1");
	originator->setState("State #2");
	careTaker->add(originator->saveStateToMemento());
	originator->setState("State #3");
	careTaker->add(originator->saveStateToMemento());
	originator->setState("State #4");

	Console::WriteLine("Current State: " + originator->getState());		
	originator->getStateFromMemento(careTaker->get(0));
	Console::WriteLine("First saved State: " + originator->getState());
	originator->getStateFromMemento(careTaker->get(1));
	Console::WriteLine("Second saved State: " + originator->getState());
	Console::ReadLine();
	return 0;
}

