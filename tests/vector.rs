use ray_tracer::vector::vector::Vec3;

#[test]
fn creation_and_getters_of_a_vector() {
    let v = Vec3::new(1.0, 2.0, 3.0);
    assert!((v.x() - 1.0).abs() < 1e-8);
    assert!((v.y() - 2.0).abs() < 1e-8);
    assert!((v.z() - 3.0).abs() < 1e-8);

    assert!((v.red() - 1.0).abs() < 1e-8);
    assert!((v.green() - 2.0).abs() < 1e-8);
    assert!((v.blue() - 3.0).abs() < 1e-8);
}

#[test]
fn vectors_equality() {
    let a = Vec3::new(1.000000001, 2.0, 3.0);
    let b = Vec3::new(1.0, 2.0, 3.0);
    assert_eq!(a, b);
}

#[test]
fn adding_and_subtracting_vectors() {
    let a = Vec3::new(1.0, 2.0, 3.0);
    let b = Vec3::new(4.0, 5.0, 6.0);
    assert_eq!(a + b, Vec3::new(5.0, 7.0, 9.0));

    let mut c = a;
    c += b;
    assert_eq!(c, Vec3::new(5.0, 7.0, 9.0));

    assert_eq!(c - b, a);

    let mut d = c;
    d -= b;
    assert_eq!(d, a);
}

#[test]
fn vector_scaling() {
    let v = Vec3::new(1.0, -2.0, 3.0);
    assert_eq!(v * 2.0, Vec3::new(2.0, -4.0, 6.0));
    assert_eq!(2.0 * v, Vec3::new(2.0, -4.0, 6.0));

    let mut w = v;
    w *= 3.0;
    assert_eq!(w, Vec3::new(3.0, -6.0, 9.0));

    assert_eq!(w / 3.0, Vec3::new(1.0, -2.0, 3.0));

    let mut u = w;
    u /= 3.0;
    assert_eq!(u, v);
}

#[test]
fn vectors_length_and_unit() {
    let v = Vec3::new(3.0, 4.0, 0.0);
    assert!((v.length() - 5.0).abs() < 1e-8);
    assert!((v.length_squared() - 25.0).abs() < 1e-8);

    let unit = v.unit();
    assert!((unit.length() - 1.0).abs() < 1e-8);
    assert!((unit.x() - 0.6).abs() < 1e-8);
    assert!((unit.y() - 0.8).abs() < 1e-8);
    assert!((unit.z() - 0.0).abs() < 1e-8);

    let zero = Vec3::new(0.0, 0.0, 0.0);
    assert_eq!(zero.unit(), zero);
}

#[test]
fn dot_cross_products_of_vectors() {
    let a = Vec3::new(1.0, 0.0, 0.0);
    let b = Vec3::new(0.0, 1.0, 0.0);
    assert!((a.dot(b) - 0.0).abs() < 1e-8);

    let c = a.cross(b);
    assert_eq!(c, Vec3::new(0.0, 0.0, 1.0));
}

#[test]
fn displaying_vector() {
    let v = Vec3::new(1.0, 2.0, 3.0);
    let s = format!("{}", v);
    assert_eq!(s, "vec3<1, 2, 3>");
}

#[test]
fn from_into_vector_convertions() {
    let point = [1., 2., 3.];
    let vec: Vec3 = point.into();

    assert_eq!(vec, Vec3::new(1., 2., 3.));
    assert_eq!(vec, Vec3::from([1., 2., 3.]));
}
