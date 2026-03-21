use std::io::Write;

use crate::vector::vector::Vec3;

pub type ColorRGB = Vec3;

pub fn write_color(out: &mut impl Write, pixel_color: &ColorRGB) -> std::io::Result<()> {
    let (r, g, b) = (pixel_color.x(), pixel_color.y(), pixel_color.z());

    // translating the [0, 1] component values to the byte range [0, 255].
    let rbyte = (255.999 * r) as i32;
    let gbyte = (255.999 * g) as i32;
    let bbyte = (255.999 * b) as i32;

    write!(out, "{} {} {}\n", rbyte, gbyte, bbyte)
}
