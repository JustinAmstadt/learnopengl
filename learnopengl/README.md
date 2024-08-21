# Introduction

This is a simple game engine written with OpenGL that uses the learnopengl tutorial as a foundation.

All abstractions and optimizations were made by me.

# How to Change Scenes

Any class that inherits the Scene class can be used as a brand new scene as long as you call.

```
scene->makeCurrent();
```

and 

```
scene->update(camera);
```

in the proper places in the loop() function in main.

# Scenes Available

Dragonfly Scene: A simple flight simulator that shows arrows for gravity, lift/thrust, and drag that is controllable by the user.

Maze Scene: Generates a procedural maze of n size and renders it as cubes.

Ocean Scene: Creates a rainy ocean scene with fog and a moving ocean.

Tessellation Plane Scene: It compiles, but looks very wrong.

Sandbox Scene: A testing scene to try new ideas out. When an idea formulates I usually copy this scene and rename it and then empty the sandbox scene out again.

# Other Classes

There are other classes that aren't currently being used by a scene such as lighting and specific geometry that are available under the include directory