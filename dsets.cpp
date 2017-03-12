/* Your code here! */
#include "dsets.h"
#This is a test edit
void DisjointSets::addelements(int num)
{
	for(int i = 0; i < num; i++)
	{
		elements.push_back(-1);
	}
}
int DisjointSets::find(int elem)
{
	if(elements[elem] < 0)
	{
		return elem;
	}
	else
	{
		return (elements[elem] = find(elements[elem]));
	}
}
void DisjointSets::setunion(int a, int b)
{
	int roota, rootb;
	roota = find(a);
	rootb = find(b);
	
	int newSize = elements[roota] + elements[rootb];
	
	if(elements[roota] <= elements[rootb])
	{
		elements[rootb] = roota;
		elements[roota] = newSize;
	}	
	else
	{
		elements[roota] = rootb;
		elements[rootb] = newSize;
	}
}
