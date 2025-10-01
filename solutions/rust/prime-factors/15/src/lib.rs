use std::{
    collections::HashSet,
    iter::{self, successors},
};

fn is_divisible_by(n: u64, f: u64) -> bool {
    n % f == 0
}

fn times_divisible_by(n: u64, f: u64) -> u32 {
    (1..)
        .take_while(|x| {
            f.checked_pow(*x)
                .map(|x_pow| is_divisible_by(n, x_pow))
                .unwrap_or(false)
        })
        .last()
        .unwrap_or(0)
}

fn lazy_prime_generator(from: u64, to: u64) -> impl Iterator<Item = u64> {
    iter::once(from)
        .chain((from + 1..).step_by(2))
        .take_while(move |x| x * x <= to)
        .chain(iter::once(to))
}

pub fn factors_successors(n: u64) -> Vec<u64> {
    successors(Some((n, 1, 0)), |(remainder, last_factor, _exponent)| {
        if *remainder < 2 {
            None
        } else {
            lazy_prime_generator(last_factor + 1, *remainder)
                .find(|f| is_divisible_by(*remainder, *f))
                .map(|f| {
                    let exp = times_divisible_by(*remainder, f);
                    (remainder / f.pow(exp), f, exp)
                })
        }
    })
    .flat_map(|(_, f, exp)| iter::repeat_n(f, exp as usize))
    .collect()
}

fn factors_from(n: u64, from: u64) -> Vec<u64> {
    if n < from {
        return vec![];
    }
    lazy_prime_generator(from, n)
        .find(|f| is_divisible_by(n, *f))
        .iter()
        .flat_map(|f| {
            let exp = times_divisible_by(n, *f);
            iter::repeat_n(*f, exp as usize).chain(factors_from(n / f.pow(exp), f + 1))
        })
        .collect()
}

pub fn factors_rec_from(n: u64) -> Vec<u64> {
    factors_from(n, 2)
}

pub fn factors_while(n: u64) -> Vec<u64> {
    let mut divider = 2;
    let mut remainder = n;
    let mut list = Vec::new();
    while remainder != 1 && divider * divider <= remainder {
        while is_divisible_by(remainder, divider) {
            list.push(divider);
            remainder /= divider;
        }
        divider = if divider == 2 { 3 } else { divider + 2 };
    }
    if remainder != 1 {
        list.push(remainder);
    }
    list
}

//not adapted for an optimized solution in this exercise but interesting 
pub fn factors_scan(n: u64) -> Vec<u64> {
    iter::once(2)
        .chain((3..).step_by(2))
        .scan(n, |remainder, f| {
            (*remainder > 1).then(|| {
                (is_divisible_by(*remainder, f)).then(|| {
                    let exp = times_divisible_by(*remainder, f);
                    *remainder /= f.pow(exp);
                    (f, exp)
                })
            })
        })
        .flatten()
        .flat_map(|(f, exp)| iter::repeat_n(f, exp as usize))
        .collect()
}

pub fn all_factors(n: u64) -> Vec<u64> {
    let solutions = [
        factors_rec_from(n),
        factors_while(n),
        factors_successors(n),
        factors_scan(n),
    ]
    .into_iter()
    .collect::<HashSet<_>>();

    if solutions.len() != 1 {
        panic!("All factor fn does not give the same result!")
    }
    solutions.iter().next().cloned().unwrap()
}

//launch benchmark: uncomment lines in Cargo.toml then `cargo bench`
pub fn factors(n: u64) -> Vec<u64> {
    all_factors(n)
}

#[cfg(test)]
mod tests {
    use crate::factors;

    #[test]
    fn bench_test() {
        let factors = factors(9_052_954_875);
        let expected = [3, 3, 3, 3, 5, 5, 5, 894_119];
        assert_eq!(factors, expected);
    }

    #[test]
    fn huge_bench_test() {
        let factors = factors(1_172_822_137_245);
        let expected = [3, 3, 3, 3, 5, 11, 17, 15_485_867];
        assert_eq!(factors, expected);
    }

    #[test]
    fn prime_10e6() {
        let output = factors(15_485_867);
        let expected = [15_485_867];
        assert_eq!(output, expected);
    }
}
