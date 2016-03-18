/* Your code here! */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include "maze.h"
SquareMaze::SquareMaze()
{
	mazeWidth = 0;
	mazeHeight = 0;
	//DisjointSets myMaze;
}
void SquareMaze::makeMaze(int width, int height)
{
	//random number generator, will be used later to determine where
	//to randomly remove walls
	/*
	int vectSize = width*height;
	srand(time(NULL));
	int random = rand()%vectSize;
	*/
	DisjointSets  myMaze;
	
	int vectSize = width*height;
	mazeWidth = width;
	mazeHeight = height;
	//fills maze vector with -1, indicating that it is a root
	//entire maze is now full of unconnected squares
	//this vector will tell which square is connect to which
	//essentially it should contain each path
	myMaze.addelements(vectSize);
	//fills walls vector with 1, so there are walls everywhere
	//place walls on all sides of all squares of maze
	//this vector will contain as many entries as walls,
	//each index represents a square in the maze and the object
	//each entry contains contains information on walls
	//cout<<"I'm here"<<endl;
	for(int i = 0; i < vectSize; i++)
	{
		//cout<<"hello"<<endl;
		Square temp;
		temp.right = true;
		temp.down = true;
		mazeSquares.push_back(temp);
		//cout<<"here"<<endl;
		//cout<<mazeSquares[i].right<<endl;
	}
	
	srand(time(NULL));
	int count = 0; //will unions made.
	int whichWall;
	int mazeArrIdx = 0;
	int idxX = 0;
	int idxY = 0;
	
	while(count < (vectSize - 1))
	{
		idxX = rand()%width;//will generate a valid width index
		idxY = rand()%height;//will generate a valid height index
		whichWall = rand()%2;//choose which to remove (0, 1)
		mazeArrIdx = getGridIdx(idxX, idxY);//random index transferred to array index

		if(!whichWall)//we remove right
		{
			if((idxX != (width - 1))&&((myMaze.find(mazeArrIdx) != myMaze.find(mazeArrIdx + 1))))//valid index and no cycle
			{
				myMaze.setunion(mazeArrIdx, mazeArrIdx + 1);//set union
				setWall(idxX, idxY, 0, false);//right wall removed
				count++;
			}
		}
		else//we remove down
		{
			if((idxY != (height - 1))&&((myMaze.find(mazeArrIdx) != myMaze.find(mazeArrIdx + width))))//valid index and no cycle
			{						
				myMaze.setunion(mazeArrIdx, mazeArrIdx + width);//set union
				setWall(idxX, idxY, 1, false);//lower wall removed
				count++;
			}
		}	
	}	
}
bool SquareMaze::canTravel(int x, int y, int dir) const
{
	int arr_idx = ((y * mazeWidth) + x);
	if((x == 0)&&(dir == 2))//can't move off the map leftwards
	{
		return false;
	}
	if((y == 0)&&(dir == 3))//can't move off map upwards
	{
		return false;
	}
	if((x < 0)||(y < 0)||(x > (mazeWidth - 1))||(y > (mazeHeight - 1)))
	{
		return false;
	}
	if((x >= (mazeWidth - 1))&&(dir == 0))//can't move off map right
	{
		return false;
	}
	if((y >= (mazeHeight - 1))&&(dir ==1))//can't move off map down
	{
		return false;
	}
	else if(dir == 0)//direction right
	{
		if(mazeSquares[arr_idx].right == true)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if(dir == 1)//direction downwards
	{
		if(mazeSquares[arr_idx].down == true)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if(dir == 2)//direction left
	{
		if(mazeSquares[arr_idx - 1].right == true)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if(dir == 3)//direction upwards
	{
		if(mazeSquares[arr_idx - mazeWidth].down == true)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	
	return false;
}
int SquareMaze::getGridIdx(int x, int y)
{
	return ((y * mazeWidth) + x);
}
vector<int> SquareMaze::solveMaze()
{

	queue<int> neighbors;
	vector<exploreInfo> blockInfo;
	vector<int> solution;
	vector<bool> visited;
	int idxX = 0;
	int idxY = 0;
	int gridIdx = getGridIdx(idxX,idxY);
	
	for(int i = 0; i < (mazeWidth * mazeHeight); i++)
	{
		exploreInfo temp;
		temp.parent = -1;
		temp.distance = 0;
		blockInfo.push_back(temp);
		visited.push_back(false);
	}
	
	
	
	//implementation is a BFS algorithm
	neighbors.push(0);
	visited[0] = true;
	while(!neighbors.empty())
	{
		gridIdx = neighbors.front();
		neighbors.pop();//dequeue
		if((canTravel((gridIdx%mazeWidth),(gridIdx/mazeWidth), 0))&&(!visited[gridIdx + 1]))//new vertex
		{
				blockInfo[gridIdx + 1].parent = gridIdx;
				blockInfo[gridIdx + 1].distance = blockInfo[gridIdx].distance + 1;
				visited[gridIdx + 1] = true;
				neighbors.push(gridIdx + 1);//enqueue
		}
		if((canTravel((gridIdx%mazeWidth),(gridIdx/mazeWidth), 1))&&(!visited[gridIdx + mazeWidth]))//new vertex
		{
				blockInfo[gridIdx + mazeWidth].parent = gridIdx;
				blockInfo[gridIdx + mazeWidth].distance = blockInfo[gridIdx].distance + 1;
				visited[gridIdx + mazeWidth] = true;
				neighbors.push(gridIdx + mazeWidth);//enqueue
		}
		if((canTravel((gridIdx%mazeWidth),(gridIdx/mazeWidth), 2))&&(!visited[gridIdx - 1]))//new vertex
		{
				blockInfo[gridIdx - 1].parent = gridIdx;
				blockInfo[gridIdx - 1].distance = blockInfo[gridIdx].distance + 1;
				visited[gridIdx - 1] = true;
				neighbors.push(gridIdx - 1);//enqueue
		}
		if((canTravel((gridIdx%mazeWidth),(gridIdx/mazeWidth), 3))&&(!visited[gridIdx - mazeWidth]))//new vertex
		{
				blockInfo[gridIdx - mazeWidth].parent = gridIdx;
				blockInfo[gridIdx - mazeWidth].distance = blockInfo[gridIdx].distance + 1;
				visited[gridIdx - mazeWidth] = true;
				neighbors.push(gridIdx - mazeWidth);//enqueue
		}
		//visited[gridIdx] = true;
	}
	
	int bottomLeftIdx = getGridIdx(0, (mazeHeight - 1));
	//find largest distance at bottom of grid
	int currentBest = 0;
	int potential = 0;
	int exitIdx = bottomLeftIdx;
	for(int i = bottomLeftIdx; i < (mazeWidth*mazeHeight); i++)
	{
		potential = blockInfo[i].distance;
		if(potential > currentBest)
		{
			currentBest = potential;
			exitIdx = i;
		}
	}
	int j = exitIdx;
	outX = exitIdx%mazeWidth;
	outY = exitIdx/mazeWidth;
	vector<int> direction;
	while(blockInfo[j].parent != -1)
	{
		if(blockInfo[j].parent == (j - 1))
		{
			direction.push_back(0);
		}
		else if(blockInfo[j].parent == (j - mazeWidth))
		{
			direction.push_back(1);
		}
		else if(blockInfo[j].parent == (j + 1))
		{
			direction.push_back(2);
		}
		else if(blockInfo[j].parent == (j + mazeWidth))
		{
			direction.push_back(3);
		}
		else
		{
			cout<<"we have a huge problem"<<endl;
		}
		j = blockInfo[j].parent;
	}
	//flip vector
	for(size_t i = (direction.size()); i > 0; i--)
	{
		solution.push_back(direction[i - 1]);
	}
	
	return solution;
	
//	vector<int> ret;
//	return ret;
	
//	stack 
}
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
	int arr_idx = ((y * mazeWidth) + x);
	if(exists == true)
	{
		if(dir == 0)//0 is right wall
		{
			mazeSquares[arr_idx].right = true;
		}
		else
		{
			mazeSquares[arr_idx].down = true;
		}
	}
	else//wall does not exist
	{
		if(dir == 0)//0 is right wall
		{
			mazeSquares[arr_idx].right = false;
		}
		else
		{
			mazeSquares[arr_idx].down = false;
		}
	}
}
	

PNG * SquareMaze::drawMaze() const
{
	PNG * myMaze = new PNG(mazeWidth*10 + 1, mazeHeight*10 + 1);//make image
	RGBAPixel * blackPixel = new RGBAPixel(0, 0, 0);
	for(int i = 10; i < (mazeWidth*10 + 1); i++)//top wall minus entrance
	{
		*(*myMaze)(i,0) = *blackPixel;
	}
	for(int i = 0; i < (mazeHeight*10 + 1); i++)//left wall
	{
		*(*myMaze)(0,i) = *blackPixel;
	}
	for(int x = 0; x < mazeWidth; x++)
	{
		for(int y = 0; y < mazeHeight; y++)
		{
			for(int k = 0; k < 11; k ++)
			{
				if(canTravel(x, y, 0) == false)//right wall exists
				{
					*(*myMaze)((x + 1)*10, (y*10)+k) = *blackPixel;
				}
				if(canTravel(x, y, 1) == false)//down wall exists
				{
					*(*myMaze)((x*10) + k, (y + 1)*10) = *blackPixel;
				}            			
			}
		}
	}
	return myMaze;
}


PNG* SquareMaze::drawMazeWithSolution()
{
	
	PNG* finalImage = drawMaze();
	RGBAPixel* redPixel = new RGBAPixel(255, 0, 0);
	vector<int> directions = solveMaze();
	int moves = directions.size();
	//cout<<"moves: "<<moves<<endl;
	int x = 5;
	int y = 5;
	for(int i = 0; i < moves; i++)
	{
		if(directions[i] == 0)
		{
			for(int j = 0; j < 11; j++)
			{
				*(*finalImage)(x + j, y) = *redPixel;
			}
			x = x + 10;
		}
		if(directions[i] == 1)
		{
			for(int j = 0; j < 11; j++)
			{
				*(*finalImage)(x, y + j) = *redPixel;
			}
			y = y + 10;
		}
		if(directions[i] == 2)
		{
			for(int j = 0; j < 11; j++)
			{
				*(*finalImage)(x - j, y) = *redPixel;
			}
			x = x - 10;
		}
		if(directions[i] == 3)
		{
			for(int j = 0; j < 11; j++)
			{
				*(*finalImage)(x, y - j) = *redPixel;
			}
			y = y - 10;
		}
	}
	RGBAPixel * whitePixel = new RGBAPixel(255, 255, 255);
	for(int k = 1; k < 10; k++)
	{
		*(*finalImage)(outX*10 + k, (outY+1)*10) = *whitePixel;
	}
	return finalImage;
	
	
	//PNG * ret = new PNG();
	//return ret;
}
