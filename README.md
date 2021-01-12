# 3DEngine
A custom 3D rendering engine, written in C++ with OpenGL. This is the second version of the engine,
which is being reimplemented to incorporate an ECS system and clean up many of the programming
decisions made in the previous version.

# Example screenshot


# Cloning the repo
There are several third-party libraries that are used in this project. They are stored in the
ThirdParty repo, which is a submodule of this repository. Simply cloning the 3DEngine-v2 repo isn't
enough as the ThirdParty submodule is not automatically cloned with it.

To clone the ThirdParty submodule as well, the following set of commands can be run:

```
git clone https://github.com/PranavBahuguna/3DEngine-v2
git submodule init
git submodule update
```

Or to clone the repo and submodules in one go:

```
git clone --recurse-submodules https://github.com/PranavBahuguna/3DEngine-v2
```

# Features


# Controls
