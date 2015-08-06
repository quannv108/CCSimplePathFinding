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

#ifndef __ShortestPathStep__
#define __ShortestPathStep__

#include "cocos2d.h"

namespace pathfinding{
    
    class ShortestPathStep {
        
    public:
        ShortestPathStep(const cocos2d::Vec2& pos);
        ShortestPathStep();
        virtual ~ShortestPathStep();
        
        CC_SYNTHESIZE_PASS_BY_REF(cocos2d::Vec2, _position, Position);
        CC_SYNTHESIZE(int, _gScore, GScore);
        CC_SYNTHESIZE(int, _hScore, HScore);
        CC_SYNTHESIZE(ShortestPathStep *, _parent, Parent);
        
        inline int getFScore(){
            return _gScore + _hScore;
        }
    protected:
        virtual bool init(const cocos2d::Vec2& pos);
        
    };
}

#endif /* defined(__ShortestPathStep__) */
