use std::io::Write;

use ray_tracer::{
    color::{ColorRGB, write_color},
    ray::ray::Ray,
    vector::vector::Vec3,
};

fn main() -> Result<(), Box<dyn std::error::Error>> {
    // image
    const ASPECT_RATIO: f64 = 16. / 9.;
    let image_width = 400;

    // calculate the image height
    let image_height = (image_width as f64 / ASPECT_RATIO) as i32;
    let image_height = if image_height < 1 { 1 } else { image_height };

    // camera
    let focal_length = 1.;
    let viewport_height = 2.;
    let viewport_width = viewport_height * (image_width / image_height) as f64;
    let camera_center = Vec3::new(0., 0., 0.);

    // calculate the vectors across the horizontal and down the vertical viewport edges.
    let (viewport_u, viewport_v) = (
        Vec3::new(viewport_width, 0., 0.),
        Vec3::new(0., -viewport_height, 0.),
    );

    // calculate the horizontal and vertical delta vectors from pixel to pixel.
    let (pixel_delta_u, pixel_delta_v) = (
        viewport_u / image_width as f64,
        viewport_v / image_height as f64,
    );

    // calculate the location of the upper left pixel.
    let viewport_upper_left =
        camera_center - Vec3::new(0., 0., focal_length) - viewport_u / 2. - viewport_v / 2.;
    let pixel100_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    write!(
        std::io::stdout(),  // P3 means colors are in ASCII
        "P3\n{} {}\n255\n", // then coumns and rows,
        image_width,        // then 255 for max color,
        image_height        // then RGB triplets
    )?;

    for i in 0..image_height {
        for j in 0..image_width {
            let pixel_center =
                pixel100_loc + (pixel_delta_u * i as f64) + (pixel_delta_v * j as f64);
            let ray_direction = pixel_center - camera_center;
            let ray = Ray::new(camera_center, ray_direction);

            let pixel_color = ray_color(&ray);

            // writing scaled color into Writer (stdout)
            write_color(&mut std::io::stdout(), &pixel_color)?;
        }
    }

    Ok(())
}

fn ray_color(ray: &Ray) -> ColorRGB {
    let unit_direction = ray.direction().try_unit().unwrap_or(Vec3::ZERO);
    let a = 0.5 * (unit_direction.y() + 1.);
    (1.0 - a) * ColorRGB::ONE + a * ColorRGB::new(0.5, 0.7, 1.)
}
