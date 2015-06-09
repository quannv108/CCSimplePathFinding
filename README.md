# CCSimplePathFinding

Simple Path finding using for simple world using A* pathfinding algorithm. for cocos2dx v3
<h5>Document:</h5>
http://en.wikipedia.org/wiki/A*_search_algorithm

<h5>Thanks to Ray Wenderlich:</h5>
http://www.raywenderlich.com/4970/how-to-implement-a-pathfinding-with-cocos2d-tutorial

<h5>How to use:</h5>
1. Create a 2-dimension matrix world:
Example:
``` c++
std::vector<std::vector<int>> matrix
std::vector<int> row1 = {1,1,1,1,1};
std::vector<int> row2 = {1,0,1,0,1};
std::vector<int> row3 = {1,0,0,0,1};
std::vector<int> row4 = {1,0,1,0,1};
std::vector<int> row5 = {1,1,1,1,1};
matrix.push_back(row1);
matrix.push_back(row2);
matrix.push_back(row3);
matrix.push_back(row4);
matrix.push_back(row5);
```

2. Init PathFinding 
Example:
``` c++
_pathFinder = pathfinding::PathFinding::create();
_pathFinder->retain();
_pathFinder->setupMap(matrix);
```

3. Find the path:
Example: 
``` c++
Vec2 beginCoord = Vec2(1,1);
Vec2 endCoord = Vec2(3,3);
std::vector<Vec2> path = _pathFinder->getShortestPath(beginCoord, endCoord);
```

4. In PathFinding.cpp, you can enable debug print 
change
``` c++
#define DEBUG_PRINT 0
to 
#define DEBUG_PRINT 1
```
