# Ray Tracer

A small ray tracer implemented in C++.

## build & run

```sh
cmake -S . -B build
cmake --build build
./build/ray-tracer > output.ppm
```

```sh
rm -rf build/ # remove generated directory
```

## examples and explanation

![how ppm works](./assets/image.jpg)

![set the background](./assets/background.jpg)

![viewport and camera explanation](./assets/viewport_and_camera_explanation.jpg)

here, we is the overview of how our viewport(some plane in the space) and camera looks like. Camera is set to the default coordinates, and the viewport's distance is 1 from the camera(origin). Since the center of the viewport is (0, 0, -1), and we want our viewport origin to be the top-left corner, we need to set pixel(0, 0) and find a way to iterate through the plane. 
Hence, we define two vectors Vu and Vv along the horizontal and vertical lines of the viewport respectively. Then, we are calculating the delta Vu and Vv to now the iterating steps and the center of each viewport square.

![sphere](./assets/sphere.jpg)

using the sphere definition to define whether the ray intersects with the sphere or not.

![sphere](./assets/sphere_explanation.jpg)

