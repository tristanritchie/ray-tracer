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
            RayTrace/rtLights/lightbase.cpp
            RayTrace/rtLights/pointlight.cpp
            RayTrace/rtMaterials/materialbase.cpp
            RayTrace/rtMaterials/simplematerial.cpp
            RayTrace/rtMaterials/simplerefractive.cpp
            RayTrace/rtPrimatives/cone.cpp
            RayTrace/rtPrimatives/cylinder.cpp
            RayTrace/rtPrimatives/objectbase.cpp
            RayTrace/rtPrimatives/objplane.cpp
            RayTrace/rtPrimatives/objsphere.cpp
            RayTrace/rtTextures/checker.cpp
            RayTrace/rtTextures/flat.cpp
            RayTrace/rtTextures/image.cpp
            RayTrace/rtTextures/texturebase.cpp
            )

add_executable(RayTracer ${SOURCES}) 

target_link_libraries(RayTracer ${SDL2_LIBRARIES})

set(CMAKE_CXX_FLAGS "-O3")
