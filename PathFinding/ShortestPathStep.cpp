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

#include "ShortestPathStep.h"

USING_NS_CC;

namespace pathfinding {
    
    ShortestPathStep::ShortestPathStep():
    _gScore(0),
    _hScore(0),
    _parent(NULL)
    {
        
    }
    
    ShortestPathStep::~ShortestPathStep()
    {
        CC_SAFE_RELEASE_NULL(_parent);
    }
    
    ShortestPathStep* ShortestPathStep::create(const cocos2d::Vec2 &pos)
    {
        auto ret = new ShortestPathStep();
        if(ret && ret->init(pos)){
            ret->autorelease();
            return ret;
        }else{
            CC_SAFE_DELETE(ret);
            return nullptr;
        }
    }
    
    bool ShortestPathStep::init(const cocos2d::Vec2 &pos)
    {
        _position = pos;
        return true;
    }
}