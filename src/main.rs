use std::io::Write;

use ray_tracer::color::{ColorRGB, write_color};

const IMAGE_HEIGHT: i16 = 256;
const IMAGE_WIDTH: i16 = 256;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    write!(
        std::io::stdout(),  // P3 means colors are in ASCII
        "P3\n{} {}\n255\n", // then coumns and rows,
        IMAGE_WIDTH,        // then 255 for max color,
        IMAGE_HEIGHT        // then RGB triplets
    )?;

    let (width, height) = ((IMAGE_WIDTH - 1) as f64, (IMAGE_HEIGHT - 1) as f64);

    for i in 0..IMAGE_HEIGHT {
        for j in 0..IMAGE_WIDTH {
            // by convention, each of the r/g/b components are represented
            // internally be real-valued variables that fange from 0.0 to 1.0.
            // scaling 0-255 to 0-1:
            let pixel_color = ColorRGB::new(i as f64 / width, j as f64 / height, 0.6);
            // writing scaled color into Writer (stdout)
            write_color(&mut std::io::stdout(), &pixel_color)?;
        }
    }

    Ok(())
}
