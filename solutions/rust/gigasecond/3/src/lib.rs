use time::PrimitiveDateTime as DateTime;
use time::ext::NumericalDuration;

const GIGA : f64 = 1e9;

pub fn after(start: DateTime) -> DateTime {
    start + GIGA.seconds()
}
