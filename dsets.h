#ifndef DSETS
#define DSETS

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;


class DisjointSets
{
	public:
		void addelements(int num);
		int find(int elem);
		void setunion(int a, int b);
	private:
		vector<int> elements;
};
#endif
