use criterion::{Criterion, criterion_group, criterion_main};
use prime_factors::*;

pub fn criterion_benchmark(c: &mut Criterion) {
    let n = 1_172_822_137_245;
    c.bench_function("factors_successors", |b| b.iter(|| factors_successors(n)));
    c.bench_function("factors_rec", |b| b.iter(|| factors_rec(n)));
    c.bench_function("factors_rec_no_vec", |b| b.iter(|| factors_rec_no_vec(n)));
    c.bench_function("factors_while", |b| b.iter(|| factors_while(n)));
    c.bench_function("factors_scan", |b| b.iter(|| factors_scan(n)));
}

criterion_group!(benches, criterion_benchmark);
criterion_main!(benches);
