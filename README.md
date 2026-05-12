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

### basic ppm gradient

![how ppm works](./assets/image.jpg)

### camera, background and viewport setup

![set the background](./assets/background.jpg)

![viewport and camera explanation](./assets/viewport_and_camera_explanation.jpg)

Here is an overview of how our viewport (a virtual plane in 3D space) and camera are set up.

The camera is positioned at the default coordinates, the origin `(0, 0, 0)`. The viewport is placed at a distance of `1` unit in front of the camera along the negative z-axis. Therefore, the center of the viewport is located at `(0, 0, -1)`.

Since we want the viewport origin to correspond to the top-left corner of the image, we first determine the location of pixel `(0, 0)` and then define a way to iterate across the viewport.

To achieve this, we define two vectors:

- `Vu`, which spans the horizontal edge of the viewport
- `Vv`, which spans the vertical edge of the viewport

Using these vectors, we compute the per-pixel delta vectors along both axes. These delta vectors represent the step size between neighboring pixels and allow us to calculate the center position of each pixel on the viewport plane.

### sphere

![sphere](./assets/sphere.jpg)

using the sphere definition to define whether the ray intersects with the sphere or not.

![sphere](./assets/sphere_explanation.jpg)

