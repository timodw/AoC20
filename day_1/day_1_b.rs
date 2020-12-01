use std::fs::File;
use std::io::prelude::*;
use std::path::Path;

const INPUT_NAME: &str = "input_1.txt";

fn read_input_file() -> String {
    let path = Path::new(INPUT_NAME);
    let display = path.display();

    let mut file = match File::open(&path) {
        Err(why) => panic!("Couldn't open {}: {}", display, why),
        Ok(file) => file,
    };

    let mut file_contents = String::new();
    match file.read_to_string(&mut file_contents) {
        Err(why) => panic!("Couldn't read {}: {}", display, why),
        Ok(_) => (),
    };

    return file_contents;
}

fn main() {
    let file_contents: String = read_input_file();
    let input_seq:Vec<i64> = file_contents.split('\n').map(|x| x.parse::<i64>().unwrap()).collect();

    for i in 0..input_seq.len() {
        for j in 0..input_seq.len() {
            for k in 0..input_seq.len() {
                if i != j && j != k && i != k && input_seq[i] + input_seq[j] + input_seq[k] == 2020 {
                    println!("Result: {}", input_seq[i] * input_seq[j] * input_seq[k]);
                }
            }
        } 
    }
}