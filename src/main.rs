use std::io::Write;

use ray_tracer::color::{ColorRGB, write_color};

const IMAGE_HEIGHT: i32 = 256;
const IMAGE_WIDTH: i32 = 256;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    write!(
        std::io::stdout(),
        "P3\n{} {}\n255\n",
        IMAGE_WIDTH,
        IMAGE_HEIGHT
    )?;

    for i in 0..IMAGE_HEIGHT {
        for j in 0..IMAGE_WIDTH {
            let pixel_color = ColorRGB::new(
                i as f64 / (IMAGE_WIDTH - 1) as f64,
                j as f64 / (IMAGE_HEIGHT - 1) as f64,
                0.,
            );

            write_color(&mut std::io::stdout(), pixel_color)?;
        }
    }

    Ok(())
}
