//
//  GameObjects.cpp
//  TopDownScroller
//
//  Created by Hayden on 8/14/20.
//  Copyright © 2020 Hayden Setlik. All rights reserved.
//

#include "GameObjects.hpp"

Tile::Tile(){
}
Tile::~Tile(){
}
void Tile::init(int xSet, int ySet){
    xPos = xSet;
    yPos = ySet;
    isLand = false;
    landWeight = 1;
    numAdjacent = 0;
    numWithinThree = 0;
    setIndex(0);
}
void Tile::setIndex(int setting){
    textureIndex = setting;
}

void Tile::isClicked(){
    printf("Tile clicked at: %d, %d\n", xPos, yPos);
}
Tile memberTiles[80][43];

Map::Map(){
}
Map::~Map(){
}

void Map::initMemberTiles(){
    for(int x = 0; x < 80; x++){
        for(int y = 0; y < 43; y++){
            memberTiles[x][y].init(x, y);
        }
    }
}
void Map::assignTexture(Tile tile){
    int x = tile.xPos;
    int y = tile.yPos;
            int texIndex = memberTiles[x][y].textureIndex;
            switch(texIndex){
                case 0:{
                    memberTiles[x][y].currentTexture = oceanBase;
                    break;
                }
                case 1:{
                    //printf("texture 1 assigned at: %d, %d\n", x, y);
                    memberTiles[x][y].currentTexture = grassBase;
                    //printf("grass texture assigned at: %d, %d\n", x, y);
                    break;
                }
                case 2:{
                    //printf("texture 2 assigned at: %d, %d\n", x, y);
                    memberTiles[x][y].currentTexture = desertBase;
                    break;
                }
            }
    if(texIndex != 0){
       // printf("Texture index is %d at: %d, %d\n", texIndex, x, y);
    }
        }

void Map::loadAllTextures(SDL_Renderer * renderer){
    SDL_Surface * tempSurface1 = IMG_Load("/Users/SFMAdmin/Desktop/Programming/SDL_projects/TopDownScroller/Tiles/Tile_0000_Ocean_Default.png");
    oceanBase = SDL_CreateTextureFromSurface(renderer, tempSurface1);
    SDL_FreeSurface(tempSurface1);
    SDL_Surface * tempSurface2 = IMG_Load("/Users/SFMAdmin/Desktop/Programming/SDL_projects/TopDownScroller/Tiles/Tile_0001_Grass_Default.png");
    grassBase = SDL_CreateTextureFromSurface(renderer, tempSurface2);
    SDL_FreeSurface(tempSurface2);
    SDL_Surface * tempSurface3 = IMG_Load("/Users/SFMAdmin/Desktop/Programming/SDL_projects/TopDownScroller/Tiles/Tile_0002_Sand_Default.png");
    desertBase = SDL_CreateTextureFromSurface(renderer, tempSurface3);
    SDL_FreeSurface(tempSurface3);
}

void Map::renderMap(SDL_Renderer *renderer){
    //printf("renderMap Started\n");
    for(int x = 0; x < 80; x++){
        for(int y = 0; y < 43; y++){
            assignTexture(memberTiles[x][y]);
            SDL_Texture *texture = memberTiles[x][y].currentTexture;
            SDL_Rect destRect;
            destRect.w = 15;
            destRect.h = 15;
            destRect.x = 15 * x;
            destRect.y = 15 * y;
            SDL_RenderCopy(renderer, texture, NULL, &destRect);
            
        }
    }
}

void Map::sendClick(){
    double _clickX;
    double _clickY;
    int xClickPx;
    int yClickPx;
    SDL_GetMouseState(&xClickPx, &yClickPx);
    _clickX = xClickPx / 15;
    _clickY = yClickPx / 15;
    int clickX = round(_clickX);
    int clickY = round(_clickY);
    memberTiles[clickX][clickY].isClicked();
    
}

Tile Map::tileClicked(){
    //assignTextures();
    double _clickX;
    double _clickY;
    int xClickPx;
    int yClickPx;
    SDL_GetMouseState(&xClickPx, &yClickPx);
    _clickX = xClickPx / 15;
    _clickY = yClickPx / 15;
    int clickX = round(_clickX);
    int clickY = round(_clickY);
    return memberTiles[clickX][clickY];
}

void Map::printTextures(){
    printf("starting texture printing...\n");
    for(int x = 0; x < 80; x++){
        for(int y = 0; y < 43; y++){
            int thisTexture = memberTiles[x][y].textureIndex;
            if(thisTexture != 0){
                printf("Texture is %d at: %d, %d\n", thisTexture, x, y);
            }
        }
    }
    printf("texture printing finished\n");
}

Landmass::Landmass(){
}
Landmass::~Landmass(){
}
void Landmass::init(Map chosenMap){
    map = chosenMap;
    memberCount = 0;
    optionCount = 0;
    firstRound = true;
    printf("Landmass initialized\n");
}

int Landmass::xInLimits(int xIn){
    if(xIn < 78){
        return 79;
    } else if(xIn < 1){
        return 0;
    } else{
        return xIn;
    }
}
int Landmass::yInLimits(int yIn){
    if(yIn < 41){
        return 42;
    } else if(yIn < 1){
        return 0;
    } else{
        return yIn;
    }
}


Tile* Landmass::adjacentTiles(Tile tile){
    printf("adjacent tiles started\n");
    static Tile adjacents[4];
    int x = tile.xPos;
    printf("x = %d\n", x);
    int y = tile.yPos;
    printf("y = %d\n", y);
    if(y > 0){
        adjacents[0] = memberTiles[x][y - 1];//top
        memberTiles[x][y].numAdjacent++;
        printf("Top neighbor: %d,%d\n", memberTiles[x][y - 1].xPos, memberTiles[x][y - 1].yPos);
        printf("top tile added\n");
    }
    if(x < 79){
    adjacents[1] = memberTiles[x + 1][y];//left
        memberTiles[x][y].numAdjacent++;
        printf("Left neighbor: %d,%d\n", memberTiles[x + 1][y].xPos, memberTiles[x + 1][y].yPos );
        printf("left tile added\n");
    }
    if(y < 43){
    adjacents[2] = memberTiles[x][y + 1];//bottom
        memberTiles[x][y].numAdjacent++;
        printf("Bottom neighbor : %d,%d\n", memberTiles[x][y + 1].xPos, memberTiles[x][y + 1].yPos);
        printf("bottom tile added\n");
    }
    if(x > 0){
        adjacents[3] = memberTiles[x - 1][y];//right
        memberTiles[x][y].numAdjacent++;
        printf("Right neighbor: %d,%d\n", memberTiles[x - 1][y].xPos, memberTiles[x - 1][y].yPos);
        printf("right tile added\n");
    }
    printf("number of adajcent: %d\n", memberTiles[x][y].numAdjacent);
    printf("adjacentTiles finished\n");
    return adjacents;
}

bool yInRange(int input){
    if(input < 0 || input > 42 ){
        return false;
    } else {
        return true;
    }
}

bool xInRange(int input){
    if(input < 0 || input > 79){
        return false;
    } else {
        return true;
    }
}


Tile* Landmass::withinThree(Tile inputTile){
    int xIn = inputTile.xPos;
    int yIn = inputTile.yPos;
    Tile tile = memberTiles[xIn][yIn];
    Tile* pNeighbors = adjacentTiles(tile);
    Tile neighbors[4];
    for(int i = 0; i < 4; ++i){
        int x = pNeighbors[i].xPos;
        int y = pNeighbors[i].yPos;
        neighbors[i] = memberTiles[x][y];
    }
    int maxNeighbors;
    if(tile.numAdjacent > 4){
        maxNeighbors = 4;
    } else{
        maxNeighbors = tile.numAdjacent;
    }
    for(int i = 0; i < maxNeighbors; i++){
        int tempX = pNeighbors[i].xPos;
        int tempY = pNeighbors[i].yPos;
        neighbors[i] = memberTiles[tempX][tempY];
    }
    //4 in second order, 12 in third
    static Tile inRange[16];
    int assignedInRange = 0;
    for(int i = 0; i < maxNeighbors; i++){
        Tile* pIterNeighbors = adjacentTiles(neighbors[i]);
        Tile iterNeighbors[4];
        for(int i = 0; i < 4; ++i){
            int xIter = pIterNeighbors[i].xPos;
            int yIter = pIterNeighbors[i].yPos;
            iterNeighbors[i] = memberTiles[xIter][yIter];
        }
        
        int iterMax = neighbors[i].numAdjacent;
        for(int n = 0; n < iterMax; n++){
            iterNeighbors[i] = pIterNeighbors[i];
            int x = iterNeighbors[i].xPos;
            int y = iterNeighbors[i].yPos;
            if((yInRange(y))&&(xInRange(x))){
            if(assignedInRange == 0){
                inRange[0] = memberTiles[x][y];
                assignedInRange++;
                tile.numWithinThree++;
            } else{
                inRange[assignedInRange] = memberTiles[x][y];
                assignedInRange++;
                tile.numWithinThree++;
            }
            }}
    }
    return inRange;
}

int Landmass::numNeighbors(Tile tile){
    printf("numNeighbors started\n");
    Tile* pTiles = adjacentTiles(tile);
    Tile tiles[4];
    int startX = tile.xPos;
    int startY = tile.yPos;
    int maxNumber = memberTiles[startX][startY].numAdjacent;
    int neighborCount = 0;
    for(int i = 0; i < maxNumber; i++){
        tiles[i] = pTiles[i];
        printf("pointer to tile at: %d, %d\n", pTiles[i].xPos, pTiles[i].yPos);
        int x = tiles[i].xPos;
        int y = tiles[i].xPos;
        if(memberTiles[x][y].isLand){
            neighborCount++;
        }
    }
    return neighborCount;
}

void Landmass::addOptionsFrom(Tile tile){
    printf("Adding Options from: %d, %d\n", tile.xPos, tile.yPos);
    Tile* pTiles = adjacentTiles(memberTiles[tile.xPos][tile.yPos]);
    Tile tiles[4];
    for(int i = 0; i < 4; ++i){
        tiles[i] = pTiles[i];
    }
    int maxNumber;
    if(memberTiles[tile.xPos][tile.yPos].numAdjacent > 4){
        maxNumber = 4;
    } else{
        maxNumber = memberTiles[tile.xPos][tile.yPos].numAdjacent;
    }
    //printf("checking for %d options\n", maxNumber);
    for(int i = 0; i < maxNumber; i++){
        bool valid = true;
        tiles[i] = pTiles[i];
        //printf("Pointed to coOrds: %d,%d\n", pTiles[i].xPos, pTiles[i].yPos);
        int x = tiles[i].xPos;
        int y = tiles[i].yPos;
        if(memberTiles[x][y].isLand){
            valid = false;
        }
        for(int n = 0; n < optionCount; n++){
            int optX = _optionTiles[n].xPos;
            int optY = _optionTiles[n].yPos;
            if((optX ==x)&&(optY == y)){
                valid = false;
            }
        }
        if(valid){
            _optionTiles[optionCount] = tiles[i];
            int x = _optionTiles[optionCount].xPos;
            int y = _optionTiles[optionCount].yPos;
            printf("Options updated from: %d,%d\n", x, y);
            //updateLandWeight(memberTiles[x][y]);
            optionCount++;
        }
    }
}

void Landmass::updateLandWeight(Tile tile){
    int testX = tile.xPos;
    int testY = tile.yPos;
    int adjConstant = 8;
    Tile* pTileA = adjacentTiles(memberTiles[testX][testY]);
    Tile adjacentTiles[4];
    for(int z = 0; z < 4; ++z){
        int x = pTileA[z].xPos;
        int y = pTileA[z].yPos;
        adjacentTiles[z] = memberTiles[x][y];
    }
    int numAdjRounds;
    if(memberTiles[testX][testY].numAdjacent > 4){
        numAdjRounds = 4;
    } else {
        numAdjRounds = memberTiles[testX][testY].numAdjacent;
    }
    int numW3Rounds;
    if(memberTiles[testX][testY].numWithinThree > 16){
        numW3Rounds = 16;
    } else {
        numW3Rounds = memberTiles[testX][testY].numWithinThree;
    }
    for(int i = 0; i < numAdjRounds; i++){
        if(i == 0){
        printf("\nbeginning update iteration\n\n");
        }

        int x = adjacentTiles[i].xPos;
        printf("X set to %d\n",x);
        int y = adjacentTiles[i].yPos;
        printf("Y set to %d\n",y);
        if(memberTiles[x][y].isLand){
            memberTiles[x][y].landWeight += adjConstant;
            int roundWeight = memberTiles[x][y].landWeight;
            printf("weight at %d,%d updated to %d\n", x, y, roundWeight);
        }
    }
    int inThreeConstant = 3;
    Tile* pTileB = withinThree(tile);
    Tile withinThree[20];
    for(int i = 0; i < 20; ++i){
        int x = pTileB[i].xPos;
        int y = pTileB[i].yPos;
        withinThree[i] = memberTiles[x][y];
    }
    for(int n = 0; n < numW3Rounds; n++){
        int x = withinThree[n].xPos;
        int y = withinThree[n].yPos;
        if(memberTiles[x][y].isLand){
            memberTiles[x][y].landWeight += inThreeConstant;
        }
    }
}
void Landmass::addMember(int xPos, int yPos, int texIndex){
    if(firstRound){
        printf("\n FIRST ROUND\n \n");
    } else {
        printf("\nROUND BEGIN\n\n");
    }
    memberTiles[xPos][yPos].setIndex(texIndex);
    memberTiles[xPos][yPos].isLand = true;
    addOptionsFrom(memberTiles[xPos][yPos]);
    updateLandWeight(memberTiles[xPos][yPos]);
    if(firstRound){
        printf("\n FIRST ROUND ENDED\n\n");
    } else {
        printf("\nROUND ENDED\n\n");
    }
}

int Landmass::randomOpenIndex(){
    printf("rOI started\n");
    int landWeightSum = 0;
    //printf("option count: %d\n", optionCount);
    for(int i = 0; i < optionCount; i++){
        int x = _optionTiles[i].xPos;
        int y = _optionTiles[i].yPos;
       
        int weight = memberTiles[x][y].landWeight;
        landWeightSum += weight;
    }
    printf("landWeightSum: %d\n", landWeightSum);
    printf("current options: %d\n", optionCount);
    int random = rand() % landWeightSum;
    for(int i = 0; i < optionCount; i++){
        //printf("Current random: %d\n", random);
        int x = _optionTiles[i].xPos;
        int y = _optionTiles[i].yPos;
        printf("checking weight from %d,%d...\n", x, y);
        int weight = memberTiles[x][y].landWeight;
        printf("Comparing random %d with weight %d\n", random, weight);
        bool land = memberTiles[x][y].isLand;
        if(random < weight && land == false){
            return i;
        } else {
            random -= weight;
        }
    }
    return 0;
}
void Landmass::build(int xOrigin, int yOrigin, int texStart, int size){
    addMember(xOrigin, yOrigin, texStart);
    firstRound = false;
    printf("\nFIRST TILE PLACED WITH %d OPTIONS\n\n", optionCount);
    Tile firstTile = memberTiles[xOrigin][yOrigin];
    printf("landmass started at: %d, %d\n", firstTile.xPos, firstTile.yPos);
    int toFill = size - 1;
    for(int i = 0; i < toFill; i++){
        printf("ready to fill space #%d\n", i);
        int index = randomOpenIndex();
        printf("Chosen index: %d\n", index);
        int x = _optionTiles[index].xPos;
        int y = _optionTiles[index].yPos;
        addMember(x, y, texStart);
    }
    printf("landmass built\n");
    
    
}
