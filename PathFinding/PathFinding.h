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

#ifndef __PathFinding__
#define __PathFinding__

#include "cocos2d.h"
#include "ShortestPathStep.h"

namespace pathfinding {

class PathFinding : public cocos2d::Ref {
    
public:
    typedef std::vector<std::vector<int>> WorldMap;
    
    PathFinding();
    virtual ~PathFinding();
    
    CREATE_FUNC(PathFinding);
    
    void setupMap(const WorldMap& map);
    
    std::vector<cocos2d::Vec2> getShortestPath(const cocos2d::Vec2& fromCoord,
                                               const cocos2d::Vec2& toCoord);
protected:
    virtual bool init();
    
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(cocos2d::Vector<ShortestPathStep *>, _openStep, OpenStep);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(cocos2d::Vector<ShortestPathStep *>, _closedStep, ClosedStep);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(WorldMap, _map, Map);
    CC_SYNTHESIZE_READONLY_PASS_BY_REF(cocos2d::Size, _mapSize, MapSize);
    
    void insertToOpenStep(ShortestPathStep *step);
    int computeHScore(const cocos2d::Vec2& fromCoord, const cocos2d::Vec2& toCoord);
    int computeCostToMove(ShortestPathStep *fromStep, ShortestPathStep* toStep);
    std::vector<cocos2d::Vec2> getNearbyTileCoord(const cocos2d::Vec2& tileCoord);
    
    inline cocos2d::Vector<ShortestPathStep *>::iterator
    getIte(cocos2d::Vector<ShortestPathStep *>& array, ShortestPathStep* step){
        for (auto ite = array.begin(); ite != array.end(); ite ++) {
            if((*ite)->getPosition().equals(step->getPosition())){
                return ite;
            }
        }
        return array.end();
    }
    
    inline bool contains(cocos2d::Vector<ShortestPathStep *>& array, ShortestPathStep* step){
        return getIte(array, step) != array.end();
    }

    inline bool isValidCoord(const cocos2d::Vec2& coord){
        return (coord.x >= 0 && coord.x < _mapSize.width &&
                coord.y >= 0 && coord.y < _mapSize.height);
    }
    inline bool canMoveAtCoord(const cocos2d::Vec2& coord){
        return (_map.at(coord.y).at(coord.x) == 0);
    }
};
}

#endif /* defined(__PathFinding__) */
