cmake_minimum_required(VERSION 3.10)
set (CMAKE_CXX_STANDARD 17)
# set the project name
project(RayTracer)

set(SDL2_LIBRARIES "/usr/include/SDL2")

find_package(SDL2 REQUIRED)
find_package(Boost REQUIRED)

set(SOURCES main.cpp 
            CApp.cpp
            RayTrace/image.cpp
            RayTrace/camera.cpp
            RayTrace/gtfm.cpp
            RayTrace/ray.cpp
            RayTrace/scene.cpp
            RayTrace/qbLights/lightbase.cpp
            RayTrace/qbLights/pointlight.cpp
            RayTrace/qbMaterials/materialbase.cpp
            RayTrace/qbMaterials/simplematerial.cpp
            RayTrace/qbMaterials/simplerefractive.cpp
            RayTrace/qbPrimatives/cone.cpp
            RayTrace/qbPrimatives/cylinder.cpp
            RayTrace/qbPrimatives/objectbase.cpp
            RayTrace/qbPrimatives/objplane.cpp
            RayTrace/qbPrimatives/objsphere.cpp
            RayTrace/qbTextures/checker.cpp
            RayTrace/qbTextures/flat.cpp
            RayTrace/qbTextures/image.cpp
            RayTrace/qbTextures/texturebase.cpp
            )

add_executable(RayTracer ${SOURCES}) 

target_link_libraries(RayTracer ${SDL2_LIBRARIES})
