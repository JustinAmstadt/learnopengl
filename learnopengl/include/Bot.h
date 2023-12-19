#ifndef BOT_H
#define BOT_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include "Scene.h"

class Bot{
  private:
    glm::vec3 position = glm::vec3(0.0f);
    int coordX = 0;
    int coordZ = 1;
    std::shared_ptr<SceneObject> cube;

    void move (glm::vec3 direction){
      position.x += direction.x;
      position.y += direction.y;
      position.z += direction.z;

      glm::mat4 model = glm::mat4(1.0f);
      model = glm::translate(model, position);
      model = glm::scale(model, glm::vec3(5.0f / 2.0f));
      cube->model = glm::mat4(1.0f);
      cube->model = model * cube->model;
    }

    bool move (int x, int z, float length, std::vector<std::vector<std::string>>& mazeGrid){
      int newCoordX = coordX + x;
      int newCoordZ = coordZ + z;
      if(newCoordX > 0 && newCoordX < static_cast<int>(mazeGrid[0].size()) && newCoordZ > 0 && newCoordZ < static_cast<int>(mazeGrid.size())
          && !isWall(newCoordX, newCoordZ, mazeGrid)){
        move(glm::vec3(length * x, 0, length * z)); // 11 / 2 is one space over in the maze
        coordX = newCoordX;
        coordZ = newCoordZ;
        return true;
      }
      else{
        return false;
      }
    }

    bool isWall(int x, int z, std::vector<std::vector<std::string>>& mazeGrid){
      return (mazeGrid[z][x] == "#") ? true : false;
    }

  public:
    Bot(std::shared_ptr<SceneObject> cube, glm::vec3& pos){
      this->cube = cube;
      move(pos);
      printPos();
    }

    bool moveRight(std::vector<std::vector<std::string>>& mazeGrid){
      return move(1, 0, 5.0f, mazeGrid);
    }

    bool moveLeft(std::vector<std::vector<std::string>>& mazeGrid){
      return move(-1, 0, 5.0f, mazeGrid);
    }

    bool moveUp(std::vector<std::vector<std::string>>& mazeGrid){
      return move(0, -1, 5.0f, mazeGrid);
    }

    bool moveDown(std::vector<std::vector<std::string>>& mazeGrid){
      return move(0, 1, 5.0f, mazeGrid);
    }

    void printPos(){
      std::cout << "Bot: X: " << position.x << ", Y: " << position.y << ", Z: " << position.z << std::endl;
    }

};

#endif
