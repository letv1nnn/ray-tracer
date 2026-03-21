pub mod vector {
    use std::{
        fmt::Display,
        ops::{Add, AddAssign, Div, DivAssign, Mul, MulAssign, Neg, Sub, SubAssign},
    };

    #[derive(Debug, Copy, Clone)]
    pub struct Vec3(f64, f64, f64);

    impl Vec3 {
        pub fn new(x: f64, y: f64, z: f64) -> Self {
            Self(x, y, z)
        }

        // length of the vector
        pub fn length(&self) -> f64 {
            self.length_squared().sqrt()
        }
        pub fn length_squared(&self) -> f64 {
            self.0 * self.0 + self.1 * self.1 + self.2 * self.2
        }

        // unit vector from original
        pub fn unit(&self) -> Self {
            let len = self.length();
            if len == 0. {
                *self
            } else {
                Self(self.0 / len, self.1 / len, self.2 / len)
            }
        }

        // dot product
        pub fn dot(&self, rhs: Self) -> f64 {
            self.0 * rhs.0 + self.1 * rhs.1 + self.2 * rhs.2
        }
        // cross product
        pub fn cross(&self, rhs: Self) -> Self {
            Self::new(
                self.1 * rhs.2 - self.2 * rhs.1,
                self.2 * rhs.0 - self.0 * rhs.2,
                self.0 * rhs.1 - self.1 * rhs.0,
            )
        }

        // getters
        pub fn x(&self) -> f64 {
            self.0
        }
        pub fn y(&self) -> f64 {
            self.1
        }
        pub fn z(&self) -> f64 {
            self.2
        }
    }

    // comparison operation, Partial, becuase of the floats' behaviour
    impl PartialEq for Vec3 {
        fn eq(&self, other: &Self) -> bool {
            (self.0 - other.0).abs() < 1e-8
                && (self.1 - other.1).abs() < 1e-8
                && (self.2 - other.2).abs() < 1e-8
        }
    }

    // addition, both + and +=
    impl Add for Vec3 {
        type Output = Self;

        fn add(self, rhs: Self) -> Self::Output {
            Self::new(self.0 + rhs.0, self.1 + rhs.1, self.2 + rhs.2)
        }
    }
    impl AddAssign for Vec3 {
        fn add_assign(&mut self, rhs: Self) {
            self.0 += rhs.0;
            self.1 += rhs.1;
            self.2 += rhs.2;
        }
    }

    // subtraction, both - and -=
    impl Sub for Vec3 {
        type Output = Self;

        fn sub(self, rhs: Self) -> Self::Output {
            Self::new(self.0 - rhs.0, self.1 - rhs.1, self.2 - rhs.2)
        }
    }
    impl SubAssign for Vec3 {
        fn sub_assign(&mut self, rhs: Self) {
            self.0 -= rhs.0;
            self.1 -= rhs.1;
            self.2 -= rhs.2;
        }
    }

    // negation operator
    impl Neg for Vec3 {
        type Output = Self;

        fn neg(self) -> Self::Output {
            Self::new(-self.0, -self.1, -self.2)
        }
    }

    // vector scaling, *, *=, / and /=
    impl Mul<Vec3> for f64 {
        type Output = Vec3;

        fn mul(self, rhs: Vec3) -> Self::Output {
            Vec3::new(self * rhs.0, self * rhs.1, self * rhs.2)
        }
    }
    impl Mul<f64> for Vec3 {
        type Output = Self;

        fn mul(self, rhs: f64) -> Self::Output {
            Self::new(self.0 * rhs, self.1 * rhs, self.2 * rhs)
        }
    }
    impl MulAssign<f64> for Vec3 {
        fn mul_assign(&mut self, rhs: f64) {
            self.0 *= rhs;
            self.1 *= rhs;
            self.2 *= rhs;
        }
    }
    impl Div<f64> for Vec3 {
        type Output = Self;

        fn div(self, rhs: f64) -> Self::Output {
            Self::new(self.0 / rhs, self.1 / rhs, self.2 / rhs)
        }
    }
    impl DivAssign<f64> for Vec3 {
        fn div_assign(&mut self, rhs: f64) {
            self.0 /= rhs;
            self.1 /= rhs;
            self.2 /= rhs;
        }
    }

    // display for proper io operations
    impl Display for Vec3 {
        fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
            write!(f, "vec3<{}, {}, {}>", self.0, self.1, self.2)
        }
    }

    // from and into traits for suitable convertions
    impl From<[f64; 3]> for Vec3 {
        fn from(value: [f64; 3]) -> Self {
            Self::new(value[0], value[1], value[2])
        }
    }
}
