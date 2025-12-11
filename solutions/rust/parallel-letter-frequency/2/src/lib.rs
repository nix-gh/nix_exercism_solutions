use rayon::{
    iter::{IntoParallelIterator, IntoParallelRefIterator, ParallelIterator},
    slice::ParallelSlice,
};
use std::collections::HashMap;

fn merge_maps(mut a: HashMap<char, usize>, b: HashMap<char, usize>) -> HashMap<char, usize> {
    b.into_iter()
        .for_each(|(letter, count)| *a.entry(letter).or_insert(0) += count);
    a
}

fn total_len(texts: &[&str]) -> usize {
    texts.iter().cloned().map(str::len).sum()
}

fn install<OP, R>(worker_count: usize, runnable: OP) -> R
where
    OP: FnOnce() -> R + Send,
    R: Send + Default,
{
    rayon::ThreadPoolBuilder::new()
        .num_threads(worker_count)
        .build()
        .map(|pool| pool.install(runnable))
        .unwrap_or_default()
}

fn frequency_seq_it<ITC>(it: ITC) -> HashMap<char, usize>
where
    ITC: Iterator<Item = char>,
{
    it.map(|c| c.to_ascii_lowercase())
        .filter(|c| c.is_alphabetic())
        .fold(HashMap::new(), |mut letter_map, letter| {
            *letter_map.entry(letter).or_insert(0) += 1;
            letter_map
        })
}

pub fn frequency_by_chunks(texts: &[&str], worker_count: usize) -> HashMap<char, usize> {
    let chunk_len = (total_len(texts) + worker_count) / worker_count;
    install(worker_count, || {
    texts
        .iter()
        .flat_map(|s| s.chars())
        .collect::<Vec<char>>()
        .par_chunks(chunk_len)
        .map(|chunk| frequency_seq_it(chunk.iter().cloned()))
        .reduce_with(merge_maps)
        .unwrap_or_default()
    })
}

pub fn frequency_by_step(texts: &[&str], worker_count: usize) -> HashMap<char, usize> {
    install(worker_count, || {
    (0..worker_count)
        .into_par_iter()
        .map(|worker_id| {
            frequency_seq_it(
                texts
                    .iter()
                    .flat_map(|s| s.chars())
                    .skip(worker_id)
                    .step_by(worker_count),
            )
        })
        .reduce_with(merge_maps)
        .unwrap_or_default()
    })
}

pub fn frequency_by_text(texts: &[&str], worker_count: usize) -> HashMap<char, usize> {
    install(worker_count, || {
    texts
        .par_iter()
        .map(|s| frequency_seq_it(s.chars()))
        .reduce_with(merge_maps)
        .unwrap_or_default()
    })
}

pub fn frequency_by_text_chunk(texts: &[&str], worker_count: usize) -> HashMap<char, usize> {
    install(worker_count, || {
        texts
            .par_chunks((texts.len() + worker_count) / worker_count)
            .map(frequency_seq)
            .reduce_with(merge_maps)
            .unwrap_or_default()
    })
}

pub fn frequency_strategy(texts: &[&str], worker_count: usize) -> HashMap<char, usize> {
    const MINIMUM_CHUNK_LEN: usize = 1000;
    if total_len(texts) < worker_count * MINIMUM_CHUNK_LEN {
        frequency_seq(texts)
    } else {
        frequency_by_text_chunk(texts, worker_count)
    }
}

pub fn frequency_seq(texts: &[&str]) -> HashMap<char, usize> {
    frequency_seq_it(texts.iter().flat_map(|s| s.chars()))
}

pub fn frequency(texts: &[&str], worker_count: usize) -> HashMap<char, usize> {
    let reference_solution = frequency_seq(texts);
    [
        frequency_strategy(texts, worker_count),
        frequency_by_text_chunk(texts, worker_count),
        frequency_by_chunks(texts, worker_count),
        frequency_by_step(texts, worker_count),
        frequency_by_text(texts, worker_count),
    ]
    .iter()
    .all(|sol| *sol == reference_solution)
    .then_some(reference_solution)
    .expect("All factor fn does not give the same result!")
}
