use time::PrimitiveDateTime as DateTime;

pub fn after(start: DateTime) -> DateTime {
    start + time::Duration::seconds(10_i64.pow(9))
}
