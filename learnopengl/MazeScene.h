#ifndef MAZESCENE_H
#define MAZESCENE_H

//code made by: Olin Guerrero (15 years old) 
//
//how to run this code:
//on line  ~358~  is the maze object created
//you can enter 1 parameter,
//the width and height of the maze
//you can play around with that value
//by default it is set to (9)
//but you can change it how ever you like
//
//if you have trouble viewing the maze:
//on line 177 is a comment, if you
//uncomment that AND comment the line
//above you may be able to vieuw
//the maze better
//
//i hope you like it, greeting olin
//
//made on: 30/08/2019


#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class MazeGenerator
{
public:
    MazeGenerator(int width);
    void info();
    void generate();
    void printMaze(); //prints the maze
    vector <vector<string>> grid;

private:
    void startGeneration(); //starts the maze generation
    void makeGrid(); //sets the grid
    void setWalkable(); //sets at begining of program, the walls to not walkable
    void randomIndex(); //picks a random direction
    void checkDirections(int h, int w); //checks possible walk directions
    void savePosition(int x, int y); //saves position in a vector to later backtrack (move back)
    void backTrack(int& x, int& y); //moves back a spot and removes the position to complete the maze
    bool checkCompleted();


    int width;
    int height;
    int walkDir;
    bool walkBack;
    vector <vector<bool>> walkable;
    vector <int> direction;
    vector <int> oldPositions;
};

MazeGenerator::MazeGenerator(int width) {
    this->width = width;
    this->height = width;
}

void MazeGenerator::info() {
    cout << "Width of maze: " << width << endl;
    cout << "Height of maze: " << height << endl;
}

void MazeGenerator::generate() {
    //setup
    makeGrid();
    setWalkable();

    //begin
    startGeneration();
}

//PRIVATE METHODES------------------------

void MazeGenerator::startGeneration() {
    int posX = 1;
    int posY = 1;
    walkBack = false;

    while (true) {

        if (walkBack == false) {
            savePosition(posX, posY);
        }
        walkBack = false;


        //REMOVE LATER() {
        //printMaze();
        //system("PAUSE");
        //system("CLS");
        //}



        checkDirections(posY, posX);
        randomIndex();

        walkable[posY][posX] = false; // can cause error while backtracking

        if (walkDir == 1) {
            grid[posY - 1][posX] = " ";
            posY = posY - 2;
        }
        if (walkDir == 2) {
            grid[posY][posX + 1] = " ";
            posX = posX + 2;
        }
        if (walkDir == 3) {
            grid[posY + 1][posX] = " ";
            posY = posY + 2;
        }
        if (walkDir == 4) {
            grid[posY][posX - 1] = " ";
            posX = posX - 2;
        }
        if (walkDir == 0) {
            backTrack(posX, posY);
        }

        //check if completed
        if (checkCompleted() == true) {
            return;
        }
    }
}

void MazeGenerator::makeGrid() {
    for (int i = 0; i < height * 2 + 1; i++) {
        vector <string> temp;
        for (int j = 0; j < width * 2 + 1; j++) {
            temp.push_back("X");
        }
        grid.push_back(temp);
    }

    //create the holes
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (j % 2 == 0 || i % 2 == 0) {
                grid[i][j] = "#";
            }
            else {
                grid[i][j] = " ";
            }

            if (j == 0 || j == grid[i].size() - 1) {
                grid[i][j] = "#";
            }
            if (i == 0 || i == grid.size() - 1) {
                grid[i][j] = "#";
            }

            //created entrace and exit
            if (j == 0 && i == 1) {
                grid[i][j] = " ";
            }
            if (j == grid[i].size() - 1 && i == grid.size() - 2) {
                grid[i][j] = " ";
            }
        }
    }

}

void MazeGenerator::printMaze() {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            cout << grid[i][j] << " ";
            //cout << grid[i][j] << "";
        }
        cout << endl;
    }
}

void MazeGenerator::setWalkable() {
    for (int i = 0; i < grid.size(); i++) {
        vector <bool> temp;
        for (int j = 0; j < grid[i].size(); j++) {
            temp.push_back(true);
        }
        walkable.push_back(temp);
    }

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (j % 2 == 0 || i % 2 == 0) {
                walkable[i][j] = false;
            }
            else {
                walkable[i][j] = true;
            }

            if (j == 0 || j == grid[i].size() - 1) {
                walkable[i][j] = false;
            }
            if (i == 0 || i == grid.size() - 1) {
                walkable[i][j] = false;
            }
        }
    }
}

void MazeGenerator::randomIndex() {
    //before this methode run "checkDirections" to make a array of directions
    int i = rand() % direction.size();
    walkDir = direction[i];
}

void MazeGenerator::checkDirections(int h, int w) {
    if (direction.size() > 0) {
        direction.erase(direction.begin(), direction.end());
    }


    //checks the corners
    if (h == 1 && w == 1) {
        if (walkable[h][w + 2] == 1) {
            direction.push_back(2); //east
        }
        if (walkable[h + 2][w] == 1) {
            direction.push_back(3); //south
        }
    }
    else if (h == 1 && w == walkable[h].size() - 2) {
        if (walkable[h + 2][w] == 1) {
            direction.push_back(3); //south
        }
        if (walkable[h][w - 2] == 1) {
            direction.push_back(4); //west
        }
    }
    else if (h == walkable.size() - 2 && w == 1) {
        if (walkable[h - 2][w] == 1) {
            direction.push_back(1); //north
        }
        if (walkable[h][w + 2] == 1) {
            direction.push_back(2); //east
        }
    }
    else if (h == walkable.size() - 2 && w == walkable[h].size() - 2) {
        if (walkable[h - 2][w] == 1) {
            direction.push_back(1); //north
        }
        if (walkable[h][w - 2] == 1) {
            direction.push_back(4); //west
        }
    }

    //checks the sides
    else if (h == 1 && (w > 2 && w < walkable[h].size() - 3)) {
        if (walkable[h][w + 2] == 1) {
            direction.push_back(2); //east
        }
        if (walkable[h + 2][w] == 1) {
            direction.push_back(3); //south
        }
        if (walkable[h][w - 2] == 1) {
            direction.push_back(4); //west
        }
    }
    else if (h == walkable.size() - 2 && (w > 2 && w < walkable[h].size() - 3)) {
        if (walkable[h - 2][w] == 1) {
            direction.push_back(1); //north
        }
        if (walkable[h][w + 2] == 1) {
            direction.push_back(2); //east
        }
        if (walkable[h][w - 2] == 1) {
            direction.push_back(4); //west
        }
    }
    else if ((h > 2 && h < walkable.size() - 3) && w == 1) {
        if (walkable[h - 2][w] == 1) {
            direction.push_back(1); //north
        }
        if (walkable[h][w + 2] == 1) {
            direction.push_back(2); //east
        }
        if (walkable[h + 2][w] == 1) {
            direction.push_back(3); //south
        }
    }
    else if ((h > 2 && h < walkable.size() - 3) && w == walkable.size() - 2) {
        if (walkable[h - 2][w] == 1) {
            direction.push_back(1); //north
        }
        if (walkable[h + 2][w] == 1) {
            direction.push_back(3); //south
        }
        if (walkable[h][w - 2] == 1) {
            direction.push_back(4); //west
        }
    }
    else {
        if (walkable[h - 2][w] == 1) {
            direction.push_back(1); //north
        }
        if (walkable[h][w + 2] == 1) {
            direction.push_back(2); //east
        }
        if (walkable[h + 2][w] == 1) {
            direction.push_back(3); //south
        }
        if (walkable[h][w - 2] == 1) {
            direction.push_back(4); //west
        }
    }

    if (direction.size() == 0) {
        direction.push_back(0); //nothing
    }

    //cout << direction.size() << endl;
}

void MazeGenerator::savePosition(int x, int y) {
    oldPositions.push_back(x);
    oldPositions.push_back(y);
}

void MazeGenerator::backTrack(int& x, int& y) {
    oldPositions.pop_back();
    oldPositions.pop_back();

    x = oldPositions[oldPositions.size() - 2];
    y = oldPositions[oldPositions.size() - 1];
    walkBack = true;
}

bool MazeGenerator::checkCompleted() {
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (walkable[i][j] == 1) {
                return false;
            }
        }
    }
    return true;
}

class MazeScene : public Scene {
private:
	std::unique_ptr<GridFloor> gridFloor;
	std::vector<std::shared_ptr<SceneObject>> walls;	
	std::vector<std::shared_ptr<SceneObject>> cubes;
    int mazeGenVal = 5;
    int mazeSize = mazeGenVal * 2 + 1;
	float wallLength = 5.0f;
	float wallHeight = 5.0f;
public:
	MazeScene(std::shared_ptr<Shader> lampShader) {
		gridFloor = std::make_unique<GridFloor>(lampShader, 80);
		this->addObjectVec(gridFloor->getFloorLines());
		this->light = std::make_shared<DirectionalLight>();
		createGeometry(lampShader);
		this->clearColor = glm::vec4(0.0f);
	}

	virtual void update(Camera camera) {
		glClearColor(this->clearColor.x, this->clearColor.y, this->clearColor.z, this->clearColor[3]);
		this->renderScene(camera);
		gridFloor->updateFloor(camera);
	}

	void createGeometry(std::shared_ptr<Shader> lampShader)
	{
        srand(time(0));
        MazeGenerator maze(mazeGenVal);
        maze.generate();

		std::shared_ptr<GeometricObject> cube = std::make_shared<Cube>(glm::vec4(1.0f, 0.0f, 0.0f, 0.3f));
        glm::mat4 model = glm::mat4(1.0f);
        std::shared_ptr<SceneObject> list;
		GLuint cubeVAO = Scene::createVAO(cube->vertexData);

		// If none are rendering, check the for loop
		for (int x = 0; x < mazeSize; x++) {
			for (int y = 0; y < mazeSize; y++) {
                if (maze.grid[y][x] == "#") {
                    model = glm::mat4(1.0f);
                    model = glm::translate(model, glm::vec3(wallLength * x, 5.0f, wallLength * y));
                    model = glm::scale(model, glm::vec3(wallLength));
                    list = std::make_shared<SceneObject>();
                    *list = { cube, cubeVAO, model, lampShader, GL_TRIANGLES };
                    cubes.push_back(list);
                }

                //createSquare(x, y, cube, cubeVAO, lampShader);
			}
		}
		this->addObjectVec(cubes);
	}

    //not used. makes a grid with walls that don't count as a space
	void createSquare(int x, int y, std::shared_ptr<GeometricObject> cube, GLuint cubeVAO, std::shared_ptr<Shader> lampShader) {
		glm::mat4 model = glm::mat4(1.0f);
		std::shared_ptr<SceneObject> list;

		//left wall
		model = glm::translate(model, glm::vec3(wallLength * x, 5.0f, wallLength * y));
		model = glm::scale(model, glm::vec3(.5f, wallHeight, wallLength));
		list = std::make_shared<SceneObject>();
		*list = { cube, cubeVAO, model, lampShader, GL_TRIANGLES };
		cubes.push_back(list);

		//right wall
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(wallLength * x + wallLength, 5.0f, wallLength * y));
		model = glm::scale(model, glm::vec3(.5f, wallHeight, wallLength));
		list = std::make_shared<SceneObject>();
		*list = { cube, cubeVAO, model, lampShader, GL_TRIANGLES };
		cubes.push_back(list);

		//top wall
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(wallLength * x + wallLength / 2.0f, 5.0f, wallLength * y - wallLength / 2.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(.5f, wallHeight, wallLength));
		list = std::make_shared<SceneObject>();
		*list = { cube, cubeVAO, model, lampShader, GL_TRIANGLES };
		cubes.push_back(list);

		//bottom wall
		if (y == mazeSize - 1) {
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(wallLength * x + wallLength / 2.0f, 5.0f, wallLength * y + wallLength / 2.0f));
			model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(.5f, wallHeight, wallLength));
			list = std::make_shared<SceneObject>();
			*list = { cube, cubeVAO, model, lampShader, GL_TRIANGLES };
			cubes.push_back(list);
		}
	}
};



#endif