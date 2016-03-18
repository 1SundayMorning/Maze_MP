/* Your code here! */
#include <vector>
#include "png.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "dsets.h"

class SquareMaze
{
	private:
		class Square
		{
			private:
			public:
				Square()
				{
					down = true;
					right = true;
				};
				bool down;
				bool right;
			//true means wall exists, false means wall does not exist

		};
		class exploreInfo
		{
			private:
			public:
				exploreInfo()
				{
					parent = -1;
					distance = 0;
				}
				int parent;
				int distance;
		};
		DisjointSets  myMaze;
		vector<Square> mazeSquares;
		int mazeWidth;
		int mazeHeight;	
		int outX;
		int outY;
	public:

		SquareMaze();
		void makeMaze(int width, int height);
		bool canTravel(int x, int y, int dir) const;
		void setWall(int x, int y, int dir, bool exists);
		vector< int > solveMaze();
		PNG* drawMaze() const;
		PNG* drawMazeWithSolution();
		int getGridIdx(int x, int y);

};
