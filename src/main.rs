use std::io::Write;

use ray_tracer::{
    color::{ColorRGB, write_color},
    ray::ray::Ray,
    rendered_image::rendered_image_setup::{RenderedImage, Viewport},
    vector::vector::Vec3,
};

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let rendered_image = RenderedImage::new(400, 2.0, Vec3::new(0.0, 0.0, 0.0));

    // calculate the location of the upper left pixel.
    // we are moving to the center of the viewport, then diagonlly to the top-left corner
    let viewport_upper_left = rendered_image.camera_center()
        - Vec3::new(0., 0., Viewport::FOCAL_LENGTH)
        - rendered_image.viewport_u() / 2.0
        - rendered_image.viewport_v() / 2.0;
    // defining the center of the first pixel
    // moving slightly by the half of deltas
    let pixel00_loc = viewport_upper_left
        + 0.5 * (rendered_image.viewport_delta_u() + rendered_image.viewport_delta_v());

    let mut out = std::io::stdout();
    write!(
        out,                           // P3 means colors are in ASCII
        "P3\n{} {}\n255\n",            // then coumns and rows,
        rendered_image.image_width(),  // then 255 for max color,
        rendered_image.image_height()  // then RGB triplets
    )?;

    for y in 0..rendered_image.image_height() {
        for x in 0..rendered_image.image_width() {
            // moving the pixel center by delta_u * x and delta_v * y
            let pixel_center = pixel00_loc
                + (rendered_image.viewport_delta_u() * x as f64)
                + (rendered_image.viewport_delta_v() * y as f64);
            let ray_direction = pixel_center - rendered_image.camera_center();
            let ray = Ray::new(rendered_image.camera_center(), ray_direction);

            let pixel_color = ray_color(&ray);

            // writing scaled color into Writer (stdout)
            write_color(&mut out, &pixel_color)?;
        }
    }

    Ok(())
}

fn hit_sphere(center: Vec3, radius: f64, ray: &Ray) -> f64 {
    let oc = center - ray.origin();
    let a = ray.direction().dot(&ray.direction());
    let b = -2.0 * ray.direction().dot(&oc);
    let c = oc.dot(&oc) - radius * radius;
    let discriminant = b * b - 4.0 * a * c;

    if discriminant < 0.0 {
        -1.0
    } else {
        (-b - discriminant.sqrt()) / (2.0 * a)
    }
}

fn ray_color(ray: &Ray) -> ColorRGB {
    let t = hit_sphere(Vec3::new(0.0, 0.0, -1.0), 0.5, &ray);
    if t > 0.0 {
        let n = (ray.at(t) - Vec3::new(0.0, 0.0, -1.0))
            .try_unit()
            .unwrap_or(Vec3::ZERO);
        return 0.5 * ColorRGB::new(n.x() + 1.0, n.y() + 1.0, n.z() + 1.0);
    }

    let unit_direction = ray.direction().try_unit().unwrap_or(Vec3::ZERO);
    let a = 0.5 * (unit_direction.y() + 1.);
    (1.0 - a) * ColorRGB::ONE + a * ColorRGB::new(0.5, 0.7, 1.)
}
