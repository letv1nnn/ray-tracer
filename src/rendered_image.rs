pub mod rendered_image_setup {
    use crate::vector::vector::Vec3;

    #[derive(Debug, Clone)]
    pub struct RenderedImage {
        image: Image,
        viewport: Viewport,
        camera_center: Vec3,
    }

    #[derive(Debug, Clone, Copy)]
    pub struct Image {
        width: u32,
        height: u32,
    }

    #[derive(Debug, Clone)]
    pub struct Viewport {
        width: f64,
        height: f64,
        viewport_u: Vec3,    // horizontal viewport vector
        viewport_v: Vec3,    // vertical viewport vector
        pixel_delta_u: Vec3, // horizontal delta vector
        pixel_delta_v: Vec3, // vertical delta vector
    }

    impl Image {
        pub fn new(width: u32) -> Self {
            let height = (width as f64 / RenderedImage::ASPECT_RATIO)
                .round()
                .max(1.0) as u32;
            Self { width, height }
        }
    }

    impl Viewport {
        pub const FOCAL_LENGTH: f64 = 1.0;

        pub fn new(height: f64, image: &Image) -> Self {
            // ASPECT_RATIO is ideal ratio, our w and h are i32, so it's not gonna be ideal
            let width = height * (image.width as f64 / image.height as f64);

            // vectors across the horizontal and down the vertical viewport edges
            let (viewport_u, viewport_v) =
                (Vec3::new(width, 0.0, 0.0), Vec3::new(0.0, -height, 0.0));

            // horizontal and vertical delta vectors from pixel to pixel
            let (pixel_delta_u, pixel_delta_v) = (
                viewport_u / image.width as f64,
                viewport_v / image.height as f64,
            );

            Self {
                width,
                height,
                viewport_u,
                viewport_v,
                pixel_delta_u,
                pixel_delta_v,
            }
        }
    }

    impl RenderedImage {
        // ideal aspect ration
        pub const ASPECT_RATIO: f64 = 16.0 / 9.0;

        pub fn new(image_width: u32, viewport_height: f64, camera_center: Vec3) -> Self {
            let image = Image::new(image_width);
            let viewport = Viewport::new(viewport_height, &image);
            Self {
                image,
                viewport,
                camera_center,
            }
        }

        pub fn image_width(&self) -> u32 {
            self.image.width
        }
        pub fn image_height(&self) -> u32 {
            self.image.height
        }

        pub fn viewport_width(&self) -> f64 {
            self.viewport.width
        }
        pub fn viewport_height(&self) -> f64 {
            self.viewport.height
        }

        pub fn viewport_u(&self) -> Vec3 {
            self.viewport.viewport_u
        }
        pub fn viewport_v(&self) -> Vec3 {
            self.viewport.viewport_v
        }

        pub fn viewport_delta_u(&self) -> Vec3 {
            self.viewport.pixel_delta_u
        }
        pub fn viewport_delta_v(&self) -> Vec3 {
            self.viewport.pixel_delta_v
        }

        pub fn camera_center(&self) -> Vec3 {
            self.camera_center
        }
    }
}
