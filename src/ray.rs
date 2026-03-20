// ray representation: P(t) = A + tb
// P is a 3D position along a line in 3D.
// A is the ray origin and b is the ray direction.
// t is a scalar to move P(t) along the ray.

pub mod ray {
    use crate::vector::vector::Vec3;

    pub struct Ray {
        origin: Vec3,
        direction: Vec3,
    }

    impl Ray {
        pub fn new(origin: Vec3, direction: Vec3) -> Self {
            Self { origin, direction }
        }

        pub fn origin(&self) -> Vec3 {
            self.origin
        }
        pub fn direction(&self) -> Vec3 {
            self.direction
        }

        // method to represent the function P(t)
        pub fn at(&self, t: f64) -> Vec3 {
            self.origin + t * self.direction
        }
    }
}
