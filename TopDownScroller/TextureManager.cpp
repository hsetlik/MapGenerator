//
//  TextureManager.cpp
//  TopDownScroller
//
//  Created by Hayden on 8/14/20.
//  Copyright © 2020 Hayden Setlik. All rights reserved.
//

#include "TextureManager.hpp"

SDL_Texture * TextureManager::LoadTexture(const char *filePath, SDL_Renderer* texRenderer){
    SDL_Surface *tempSurface = IMG_Load(filePath);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(texRenderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}
