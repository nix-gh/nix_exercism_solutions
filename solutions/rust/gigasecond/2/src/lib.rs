use time::PrimitiveDateTime as DateTime;
use time::ext::NumericalDuration;

pub fn after(start: DateTime) -> DateTime {
    start + 1e9.seconds()
}
