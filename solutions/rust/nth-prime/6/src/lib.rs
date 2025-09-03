fn is_prime(n: u32, primes: &[u32]) -> bool {
    primes
        .iter()
        .take_while(|&&prime| prime * prime <= n)
        .all(|prime| (n % prime) != 0)
}

pub fn nth(max: u32) -> u32 {
    if max == 0 {
        return 2;
    }

    let primes = (1..max)
        .fold((vec![2, 3], 3), |(mut primes, last), _| {
            let next = (last + 2..)
                .into_iter()
                .step_by(2)
                .find(|&candidate| is_prime(candidate, &primes))
                .unwrap();
            primes.push(next);
            (primes, next)
        });
    primes.1
}
