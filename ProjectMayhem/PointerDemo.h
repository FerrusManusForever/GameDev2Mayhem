#pragma once
#include "Cat.h"
#include <string>
class PointerDemo
{
public:
	void DoDemo();
	Cat demoCat;
private:
	void PassByValueDemo();
	void PassByReferenceDemo();
};

