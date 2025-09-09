#[derive(Debug, PartialEq, Eq)]
pub enum Error {
    InvalidInputBase,
    InvalidOutputBase,
    InvalidDigit(u32),
}

pub fn convert(digits: &[u32], from_base: u32, to_base: u32) -> Result<Vec<u32>, Error> {
    check_inputs(digits, from_base, to_base)
        .and_then(|_| Ok(from_value(from_digits(digits, from_base), to_base)))
}

fn check_inputs(digits: &[u32], from_base: u32, to_base: u32) -> Result<(), Error> {
    digits
        .iter()
        .find(|&&d| d >= from_base)
        .map(|d| Err(Error::InvalidDigit(*d)))
        .or((from_base < 2).then(|| Err(Error::InvalidInputBase)))
        .or((to_base < 2).then(|| Err(Error::InvalidOutputBase)))
        .unwrap_or(Ok(()))
}

fn from_digits(digits: &[u32], base: u32) -> u32 {
    digits
        .iter()
        .rev()
        .enumerate()
        .map(|(index, digit)| digit * base.pow(index as u32))
        .sum()
}

fn from_value(value: u32, base: u32) -> Vec<u32> {
    (value == 0).then_some(vec![0]).unwrap_or_else(|| {
        (0..=value.ilog(base))
            .rev()
            .map(|exp| (value / base.pow(exp)) % base)
            .collect()
    })
}
