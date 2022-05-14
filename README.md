# OLAS (Our Lords And Saviors)
Another example repository for cmake based cpp development based on

* glfw
* glew
* glu
* gl

Reference : [Code Tech and Tutorials](https://www.youtube.com/watch?v=nlKcXPUJGwA&list=PLalVdRk2RC6o5GHu618ARWh0VO0bFlif4&index=1)
## Preparing

```
    # install dependencies 
    sudo apt-get update
    sudo apt-get install -y libglew-dev  
    sudo apt-get install -y libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev
    sudo apt-get install -y freeglut3-dev

    # Clone repository
    git clone git@github.com:eheperson/olas.git

    # Change ownership of executable
    chmod +x bake.sh

    # run baker executable
    ./bake

```