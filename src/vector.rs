pub mod vector {
    use std::{
        fmt::Display,
        ops::{
            Add, AddAssign, Div, DivAssign, Index, IndexMut, Mul, MulAssign, Neg, Sub, SubAssign,
        },
    };

    #[repr(C)]
    #[derive(Debug, Copy, Clone)]
    pub struct Vec3(f64, f64, f64);

    impl Vec3 {
        pub fn new(x: f64, y: f64, z: f64) -> Self {
            Self(x, y, z)
        }

        // consts
        pub const ZERO: Self = Self(0., 0., 0.);
        pub const ONE: Self = Self(1., 1., 1.);
        pub const EPS: f64 = 1e-8;

        // cannot impl PartialEq in this way,
        // because it violates the transitivity rule
        #[inline]
        pub fn eq_approx(&self, other: &Vec3) -> bool {
            (self.0 - other.0).abs() < Self::EPS
                && (self.1 - other.1).abs() < Self::EPS
                && (self.2 - other.2).abs() < Self::EPS
        }

        // length of the vector
        #[inline]
        pub fn length(&self) -> f64 {
            self.length_squared().sqrt()
        }
        #[inline]
        pub fn length_squared(&self) -> f64 {
            self.0 * self.0 + self.1 * self.1 + self.2 * self.2
        }

        // unit vector from original
        #[inline]
        pub fn try_unit(&self) -> Option<Self> {
            let len = self.length();
            if len < f64::EPSILON {
                None
            } else {
                Some(*self / len)
            }
        }

        // dot product
        #[inline]
        pub fn dot(&self, rhs: &Self) -> f64 {
            self.0 * rhs.0 + self.1 * rhs.1 + self.2 * rhs.2
        }
        // cross product
        #[inline]
        pub fn cross(&self, rhs: &Self) -> Self {
            Self::new(
                self.1 * rhs.2 - self.2 * rhs.1,
                self.2 * rhs.0 - self.0 * rhs.2,
                self.0 * rhs.1 - self.1 * rhs.0,
            )
        }

        // getters
        #[inline]
        pub fn x(&self) -> f64 {
            self.0
        }
        #[inline]
        pub fn y(&self) -> f64 {
            self.1
        }
        #[inline]
        pub fn z(&self) -> f64 {
            self.2
        }
    }

    impl Add for Vec3 {
        type Output = Self;

        #[inline]
        fn add(self, rhs: Self) -> Self::Output {
            Self::new(self.0 + rhs.0, self.1 + rhs.1, self.2 + rhs.2)
        }
    }
    impl AddAssign for Vec3 {
        #[inline]
        fn add_assign(&mut self, rhs: Self) {
            self.0 += rhs.0;
            self.1 += rhs.1;
            self.2 += rhs.2;
        }
    }

    // subtraction, both - and -=
    impl Sub for Vec3 {
        type Output = Self;

        #[inline]
        fn sub(self, rhs: Self) -> Self::Output {
            Self::new(self.0 - rhs.0, self.1 - rhs.1, self.2 - rhs.2)
        }
    }
    impl SubAssign for Vec3 {
        #[inline]
        fn sub_assign(&mut self, rhs: Self) {
            self.0 -= rhs.0;
            self.1 -= rhs.1;
            self.2 -= rhs.2;
        }
    }

    // negation operator
    impl Neg for Vec3 {
        type Output = Self;

        #[inline]
        fn neg(self) -> Self::Output {
            Self::new(-self.0, -self.1, -self.2)
        }
    }

    // vector scaling, *, *=, / and /=
    impl Mul<Vec3> for f64 {
        type Output = Vec3;

        #[inline]
        fn mul(self, rhs: Vec3) -> Self::Output {
            Vec3::new(self * rhs.0, self * rhs.1, self * rhs.2)
        }
    }
    impl Mul<f64> for Vec3 {
        type Output = Self;

        #[inline]
        fn mul(self, rhs: f64) -> Self::Output {
            Self::new(self.0 * rhs, self.1 * rhs, self.2 * rhs)
        }
    }
    impl MulAssign<f64> for Vec3 {
        #[inline]
        fn mul_assign(&mut self, rhs: f64) {
            self.0 *= rhs;
            self.1 *= rhs;
            self.2 *= rhs;
        }
    }
    impl Div<f64> for Vec3 {
        type Output = Self;

        #[inline]
        fn div(self, rhs: f64) -> Self::Output {
            Self::new(self.0 / rhs, self.1 / rhs, self.2 / rhs)
        }
    }
    impl DivAssign<f64> for Vec3 {
        #[inline]
        fn div_assign(&mut self, rhs: f64) {
            self.0 /= rhs;
            self.1 /= rhs;
            self.2 /= rhs;
        }
    }

    impl Index<usize> for Vec3 {
        type Output = f64;

        #[inline]
        fn index(&self, index: usize) -> &Self::Output {
            match index {
                0 => &self.0,
                1 => &self.1,
                2 => &self.2,
                _ => panic!("index out of range"),
            }
        }
    }

    impl IndexMut<usize> for Vec3 {
        #[inline]
        fn index_mut(&mut self, index: usize) -> &mut Self::Output {
            match index {
                0 => &mut self.0,
                1 => &mut self.1,
                2 => &mut self.2,
                _ => panic!("index out of range"),
            }
        }
    }

    impl Default for Vec3 {
        fn default() -> Self {
            Vec3::ZERO
        }
    }

    // display for proper io operations
    impl Display for Vec3 {
        fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
            write!(f, "vec3<{}, {}, {}>", self.0, self.1, self.2)
        }
    }

    // from and into traits for suitable conversions
    impl From<[f64; 3]> for Vec3 {
        fn from(value: [f64; 3]) -> Self {
            Self::new(value[0], value[1], value[2])
        }
    }
}
