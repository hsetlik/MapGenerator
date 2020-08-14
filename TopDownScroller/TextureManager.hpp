//
//  TextureManager.hpp
//  TopDownScroller
//
//  Created by Hayden on 8/14/20.
//  Copyright © 2020 Hayden Setlik. All rights reserved.
//

#ifndef TextureManager_hpp
#define TextureManager_hpp
#include "GameGlass.hpp"
#include <stdio.h>
class TextureManager{
public:
    static SDL_Texture * LoadTexture(const char * filePath, SDL_Renderer* texRenderer);
};
#endif /* TextureManager_hpp */
