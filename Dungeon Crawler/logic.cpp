#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
  
   //happy path
    ifstream thefile(fileName);
    //if it is empty
    if(!thefile.is_open()){
        return nullptr;
    }

    //if it is empty and not numerical
    if(!(thefile>>maxRow>>maxCol)){
        return nullptr; 
    }
    //less than 1
    if(maxRow<1 || maxCol <1){
        return nullptr;
    }

    //INT32_MAX AND MIN
    if(INT32_MAX/ maxRow <= maxCol){
        return nullptr;
    }

    //if it is empty and not numerical
    if(!(thefile>> player.row>> player.col)){
        return nullptr;
    }

    //not  less than 0
    if(player.row < 0 || player.col < 0){
        return nullptr;
    }

    //out of bounds
    if(player.row >= maxRow || player.col >= maxCol){
        return nullptr;
    }
    //2D array
    char** Level = createMap(maxRow, maxCol);
    
    //able to access my create map
    if(Level == nullptr){
        return nullptr;
    }



    //allocating items
    // checking for !
    int iteration = 0; 
    for(int i = 0; i<maxRow; i++){
        for(int j = 0; j<maxCol; j++){
            //if it is empty
            thefile>>Level[i][j];

            // too few values
            if(thefile.fail()){
                deleteMap(Level, maxRow);
                return nullptr;
            }
           if(Level[i][j] == '!' || Level[i][j] == '?'){
               iteration = iteration + 1;
           }
           //checking for characters
           if(Level[i][j] != TILE_OPEN && Level[i][j] != TILE_PLAYER && Level[i][j] != TILE_TREASURE && Level[i][j] != TILE_AMULET && Level[i][j] != TILE_MONSTER && Level[i][j] != TILE_PILLAR && Level[i][j] != TILE_DOOR && Level[i][j] != TILE_EXIT){
                deleteMap(Level, maxRow);
                return nullptr;
           }
        }
    }

    //If there '!'?
    if(iteration <= 0){
        deleteMap (Level, maxRow);
        return nullptr;
    }
    //too many values
    char temp;
    if(thefile>>temp){
        deleteMap(Level, maxRow);
        return nullptr;
    }


    //player replacement:
    Level[player.row][player.col] = 'o';

    return Level;


}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    //nextRow and nextCol are set to the appropriate values depending on the input direction
    //Input other than MOVE_UP, MOVE_DOWN, MOVE_LEFT, or MOVE_RIGHT is ignored (don’t move)
    switch(input){
        case MOVE_DOWN:
            nextRow += 1;
            break;

        case MOVE_UP:
            nextRow -= 1;
            break;
        
        case MOVE_LEFT:
            nextCol -= 1;
            break;
        
        case MOVE_RIGHT:
            nextCol += 1;
            break;
    }   
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    //Allocate the 2D map array.
    char** map = new char*[maxRow];

    //Initialize each cell to TILE_OPEN    
    for(int i = 0; i < maxRow; i ++){
        map[i] = new char[maxCol];
        for(int j = 0; j < maxCol; j++){
            map[i][j] = TILE_OPEN;
        }
    }
    
    return map;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    // 2a) deleteMap - memory error test (0.0/1.0)
    // 2b) deleteMap - updates values (0.0/1.0)
    
    //Memory Error check points are given in this one
    if(map == nullptr){
        maxRow = 0;
        return;
    }
    for (int row = 0; row < maxRow; row++) {
        delete[] map[row];
      
    }
    maxRow = 0;
    delete[] map;
    map = nullptr;
    
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {

    if(map == nullptr){
        return nullptr;
    }
    if(maxCol<1 || maxRow<1){
        return nullptr;
    }

    //3a) resizeMap - updates row and column size (0.0/1.0)
    int maxRow_two = maxRow * 2;
    int maxCol_two = maxCol * 2;

    // 3d) resizeMap - valgrind memory leak check (0.0/1.0)


    // 3e) resizeMap - player not duplicated (same dimension) (0.0/1.0)
   
    char** resize_map = new char* [maxRow_two];
    for(int i = 0; i< maxRow_two; i++){
        resize_map[i] = new char [maxCol_two];
        //making sure to keep the old map intact:
        if( i< maxRow){
            for(int j = 0; j < maxCol; j++){
                resize_map[i][j] = map[i][j];
            }
        }
    }

    

    //3g) resizeMap - contents correct (same dimensions) (0.0/1.0)
    for( int i = 0; i < maxRow; i++){
        for(int j = 0; j < maxCol; j++){
            resize_map[i][j+maxCol] = map[i][j];
            resize_map[i + maxRow][j] = map[i][j];
            resize_map[i + maxRow][j + maxCol] = map[i][j];


        }
    }


    // 3f) resizeMap - player not duplicated (different dimensions) (0.0/1.0)
    for(int i = 0; i < maxRow; i++){
        for(int j = 0; j < maxCol; j++){
            if(map[i][j] == TILE_PLAYER){
            //replace player by tile open '-' everywhere except the original player placement
            // we do not change the [i][j] as we need at least one player            
            resize_map[i][j + maxCol] = '-';
            resize_map[i + maxRow][j] = '-';
            resize_map[i + maxRow][j + maxCol] = '-';
            }
        }
    }


    
    // 3h) resizeMap - contents correct (different dimensions 2x5) (0.0/1.0)
    // 3i) resizeMap - contents correct (different dimensions 4x2) (0.0/1.0)
    
    deleteMap(map, maxRow);

    //3 a)
    maxRow = maxRow_two;
    maxCol = maxCol_two;

    return resize_map;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    // 4c) doPlayerMove - general movement (0.0/1.0)
//   cout<<"do Player Move"<<endl;


    //moving out of bondaries
    //col boundaries
    if(nextCol >= maxCol || nextCol < 0){
        nextRow = player.row;
        nextCol = player.col;
        return 0;
    }
    
    
    //row boundaries
    if(nextRow >= maxRow || nextRow < 0){
        nextRow = player.row;
        nextCol = player.col;
        return 0;
    }

    // cout<<" after checking ROw and Col"<<endl;



    //cannot move into a Monster or pillar
    if(map[nextRow][nextCol] == TILE_PILLAR || map[nextRow][nextCol] == TILE_MONSTER){
        nextRow = player.row;
        nextCol = player.col;
        return 0;
    }

    // cout<<"cannot move into a Monster pillar"<<endl;


    // 4d) doPlayerMove - treasure (0.0/1.0)
    if(map[nextRow][nextCol] == TILE_TREASURE){
        player.treasure ++;
        //original player position changed to '-'
        map[player.row][player.col] = TILE_OPEN;
        //change the player position to the new position
        map[nextRow][nextCol] = TILE_PLAYER;

        //update for next change
        player.row = nextRow;
        player.col = nextCol;

        return STATUS_TREASURE;
    }

    // cout<<"treausre"<<endl;
    // 4e) doPlayerMove - amulet and door status (0.0/1.0)
    //AMULET
    if(map[nextRow][nextCol] == TILE_AMULET){
        //original player position changed to '-'
        map[player.row][player.col] = TILE_OPEN;
        //change the player position to the new position
        map[nextRow][nextCol] = TILE_PLAYER;
        
        //update for next change
        player.row = nextRow;
        player.col = nextCol;

        return STATUS_AMULET;
    }
    // cout<<"AMULET"<<endl;
    
    
    // DOOR
    if(map[nextRow][nextCol] == TILE_DOOR){
        //original player position changed to '-'
        map[player.row][player.col] = TILE_OPEN;
        //change the player position to the new position
        map[nextRow][nextCol] = TILE_PLAYER;
        
        //update for next change
        player.row = nextRow;
        player.col = nextCol;

        return STATUS_LEAVE;
        
    }

    // cout<<"DOOR"<<endl;



    // 4f) doPlayerMove - exit (0.0/1.0)
    if(map[nextRow][nextCol] == TILE_EXIT){
        //to be eable to exit the player most have at least one treasure
        if(player.treasure >= 1){
        //original player position changed to '-'
        map[player.row][player.col] = TILE_OPEN;
        //change the player position to the new position
        map[nextRow][nextCol] = TILE_PLAYER; 
        }else{
           nextRow = player.row;
            nextCol = player.col;
            return STATUS_STAY;
        }

        //update for next change
        player.row = nextRow;
        player.col = nextCol;

        return STATUS_ESCAPE;
    }

    // cout<<"Exit"<<endl;
    
    
    //original player position changed to '-'
    map[player.row][player.col] = TILE_OPEN;
    //change the player position to the new position
    map[nextRow][nextCol] = TILE_PLAYER; 
    
    //update for next change
    player.row = nextRow;
    player.col = nextCol;

    return STATUS_MOVE;
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    //bool function
    bool player_is_dead = false;
    //5a) doMonsterAttack - monster moves (0.0/1.0)
    
    // moves up
    for(int i = player.row-1; i >= 0; i--){

        //cannot see or move if it there is a pillar blocking it
        if(map[i][player.col] == TILE_PILLAR){
            break;
        }
         // moves closer to the player
         //moves in rows for up
        if(map[i][player.col] == TILE_MONSTER){
            if(map[i+1][player.col] == TILE_PLAYER){
                map[i][player.col] = TILE_OPEN;
                map[i+1][player.col] = TILE_MONSTER;
                player_is_dead = true;
            }
            //update the map
            map[i][player.col] = TILE_OPEN;
            map[i+1][player.col] = TILE_MONSTER;
        }
    }

    // moves down
    for(int i = player.row+1; i < maxRow; i++){
        //cannot see or move if it there is a pillar blocking it
        if(map[i][player.col] == TILE_PILLAR){
            break;
        }
         // moves closer to the player
         //moves in rows for down
        if(map[i][player.col] == TILE_MONSTER){
            if(map[i-1][player.col] == TILE_PLAYER){
                map[i][player.col] = TILE_OPEN;
                map[i-1][player.col] = TILE_MONSTER;
                player_is_dead = true;
            }
            //update the map
            map[i][player.col] = TILE_OPEN;
            map[i-1][player.col] = TILE_MONSTER;
        }
    }

    // moves left
    //cannot see or move if it there is a pillar blocking it
    for(int i = player.col-1; i >= 0; i--){
        if(map[player.row][i] == TILE_PILLAR){
            break;
        }
        // moves closer to the player
         //moves in col for left
        if(map[player.row][i] == TILE_MONSTER){
            if(map[player.row][i+1] == TILE_PLAYER){
                map[player.row][i] = TILE_OPEN;
                map[player.row][i+1] = TILE_MONSTER;
                player_is_dead = true;
            }
            //update map
            map[player.row][i] = TILE_OPEN;
            map[player.row][i+1] = TILE_MONSTER;
        }
    }

    //moves right
    //cannot see or move if it there is a pillar blocking it
    for(int i = player.col+1; i < maxCol; i++){
        if(map[player.row][i] == TILE_PILLAR){
            break;
        }
        // moves closer to the player
         //moves in col for left
        if(map[player.row][i] == TILE_MONSTER){
            if(map[player.row][i-1] == TILE_PLAYER){
                map[player.row][i] = TILE_OPEN;
                map[player.row][i-1] = TILE_MONSTER;
                player_is_dead = true;
            }
            //update map
            map[player.row][i] = TILE_OPEN;
            map[player.row][i-1] = TILE_MONSTER;
        }
    }


    // 5b) doMonsterAttack - monster attacks player (0.0/1.0)
    // 5d) doMonsterAttack - multiple monsters move (0.0/1.0)
    // 5e) doMonsterAttack - multiple monsters attack (0.0/1.0)
   return player_is_dead;
}
