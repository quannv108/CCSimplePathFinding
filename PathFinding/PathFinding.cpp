/****************************************************************************
 Copyright (c) 2015 QuanNguyen
 
 http://quannguyen.info
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "PathFinding.h"

USING_NS_CC;

#define DEBUG_PRINT 0

namespace pathfinding{
    
    PathFinding::PathFinding()
    {
        
    }
    
    PathFinding::~PathFinding()
    {
        
    }
    
    bool PathFinding::init()
    {
        return true;
    }
    
    void PathFinding::setupMap(const WorldMap &map)
    {
        _map = map;
        
        _mapSize = Size::ZERO;
        _mapSize.height = _map.size();
        if(_mapSize.height > 0){
            _mapSize.width = _map.at(0).size();
        }
    }
    
    void PathFinding::insertToOpenStep(ShortestPathStep *step)
    {
        int stepFScore = step->getFScore(); // Compute the step's F score
        int count = _openStep.size();
        int i = 0; // This will be the index at which we will insert the step
        for (; i < count; i++) {
            if (stepFScore <= _openStep.at(i)->getFScore()) { // If the step's F score is lower or equals to the step at index i
                // Then we found the index at which we have to insert the new step
                // Basically we want the list sorted by F score
                break;
            }
        }
        
        // Insert the new step at the determined index to preserve the F score ordering
        _openStep.insert(i, step);
    }
    
    int PathFinding::computeHScore(const cocos2d::Vec2 &fromCoord, const cocos2d::Vec2 &toCoord)
    {
        // Here we use the Manhattan method, which calculates the total number of step moved horizontally and vertically to reach the
        // final desired step from the current step, ignoring any obstacles that may be in the way
        return abs(toCoord.x - fromCoord.x) + abs(toCoord.y - fromCoord.y);
    }
    
    int PathFinding::computeCostToMove(ShortestPathStep *from, ShortestPathStep *to)
    {
        // Because we can't move diagonally and because terrain is just walkable or unwalkable the cost is always the same.
        // But it have to be different if we can move diagonally and/or if there is swamps, hills, etc...
        return 1;
    }
    
    std::vector<Vec2> PathFinding::getNearbyTileCoord(const cocos2d::Vec2 &tileCoord)
    {
        std::vector<Vec2> result;
        //top
        Vec2 top = Vec2(tileCoord.x, tileCoord.y - 1);
        if(isValidCoord(top) && canMoveAtCoord(top)){
            result.push_back(top);
        }
        
        //bottom
        Vec2 bottom = Vec2(tileCoord.x, tileCoord.y + 1);
        if(isValidCoord(bottom) && canMoveAtCoord(bottom)){
            result.push_back(bottom);
        }
        
        //left
        Vec2 left = Vec2(tileCoord.x - 1, tileCoord.y);
        if(isValidCoord(left) && canMoveAtCoord(left)){
            result.push_back(left);
        }
        
        //right
        Vec2 right = Vec2(tileCoord.x + 1, tileCoord.y);
        if(isValidCoord(right) && canMoveAtCoord(right)){
            result.push_back(right);
        }
        
        return result;
    }
    
    std::vector<Vec2> PathFinding::getShortestPath(const cocos2d::Vec2 &fromCoord, const cocos2d::Vec2 &toCoord)
    {
        std::vector<Vec2> result;
        // Check that there is a path to compute ;-)
        if(fromCoord.equals(toCoord)){
            return result;
        }
        
        // Must check that the desired location is walkable
        // In our case it's really easy, because only wall are unwalkable
        if(!isValidCoord(toCoord) || !canMoveAtCoord(toCoord)){
            return result;
        }
        
        bool pathFound = false;
        _openStep.clear();
        _closedStep.clear();
        
        // Start by adding the from position to the open list
        insertToOpenStep(ShortestPathStep::create(fromCoord));
        
        do{
            // Get the lowest F cost step
            // Because the list is ordered, the first step is always the one with the lowest F cost
            ShortestPathStep *currentStep = _openStep.at(0);
            
            // Add the current step to the closed set
            _closedStep.pushBack(currentStep);
            
            // Remove it from the open list
            // Note that if we wanted to first removing from the open list, care should be taken to the memory
            _openStep.erase(_openStep.begin());
            
            // If the currentStep is the desired tile coordinate, we are done!
            if (currentStep->getPosition().equals(toCoord)){
                pathFound = true;
                ShortestPathStep *tmpStep = currentStep;
#if DEBUG_PRINT
                CCLOG("*** PATH FOUND :");
#endif
                do {
#if DEBUG_PRINT
                    CCLOG("%.0f %.0f", tmpStep->getPosition().x, tmpStep->getPosition().y);
#endif
                    result.push_back(tmpStep->getPosition());
                    tmpStep = tmpStep->getParent(); // Go backward
                } while (tmpStep != NULL); // Until there is not more parent
#if DEBUG_PRINT
                CCLOG("*** PATH END");
#endif
                std::reverse(result.begin(), result.end());
                _openStep.clear();
                _closedStep.clear();
                break;
            }
            
            // Get the adjacent tiles coord of the current step
            auto adjSteps = getNearbyTileCoord(currentStep->getPosition());
            for (Vec2 v : adjSteps) {
                ShortestPathStep *step = ShortestPathStep::create(v);
                
                // Check if the step isn't already in the closed set
                if (contains(_closedStep, step)){
                    step = NULL;
                    continue; // Ignore it
                }
                
                // Compute the cost from the current step to that step
                int moveCost = computeCostToMove(currentStep, step);
                
                // Check if the step is already in the open list
                auto openIte = getIte(_openStep, step);
                if (openIte == _openStep.end()) { // Not on the open list, so add it
                    
                    // Set the current step as the parent
                    step->setParent(currentStep);
                    
                    // The G score is equal to the parent G score + the cost to move from the parent to it
                    step->setGScore(currentStep->getGScore() + moveCost);
                    
                    // Compute the H score which is the estimated movement cost to move from that step to the desired tile coordinate
                    step->setHScore(computeHScore(step->getPosition(), toCoord));
                    
                    // Adding it with the function which is preserving the list ordered by F score
                    insertToOpenStep(step);
                }
                else { // Already in the open list
                    
                    step = *openIte; // To retrieve the old one (which has its scores already computed ;-)
                    
                    // Check to see if the G score for that step is lower if we use the current step to get there
                    if ((currentStep->getGScore() + moveCost) < step->getGScore()) {
                        
                        // The G score is equal to the parent G score + the cost to move from the parent to it
                        step->setGScore(currentStep->getGScore() + moveCost);
                        
                        // Because the G Score has changed, the F score may have changed too
                        // So to keep the open list ordered we have to remove the step, and re-insert it with
                        // the insert function which is preserving the list ordered by F score
                        
                        _openStep.erase(openIte);
                        
                        // Re-insert it with the function which is preserving the list ordered by F score
                        insertToOpenStep(step);
                    }
                }
            }
        }while (_openStep.size() > 0);
        
        return result;
    }
}
