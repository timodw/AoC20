use std::fs::File;
use std::io::prelude::*;
use std::path::Path;

const INPUT_NAME: &str = "input_3.txt";
const MOVEMENT_VECTORS: [(usize, usize); 5] = [
    (1, 1),
    (1, 3),
    (1, 5),
    (1, 7),
    (2, 1),
];

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

    file_contents.pop(); // Remove trailing newline

    return file_contents;
}


fn main() {
    let file_contents: String = read_input_file();
    let input_seq: Vec<&str> = file_contents.split('\n').collect();

    let vertical_dim = input_seq.len();
    let horizontal_dim = input_seq[0].len();
    let mut top_map: Vec<u8> = Vec::new();

    // Populate topographical map
    for line in input_seq {
        for c in line.bytes() {
            top_map.push(c);
        }
    }

    let mut tree_product: i64 = 1;
    for movement_vec in &MOVEMENT_VECTORS {
        let mut tree_count: i64 = 0;
        let mut position: [usize; 2] = [0, 0];
        while position[0] < vertical_dim {
            if top_map[position[0] * horizontal_dim + (position[1] % horizontal_dim)] == b'#' {
                tree_count += 1;
            }

            position[0] += movement_vec.0;
            position[1] += movement_vec.1;
        }
        tree_product *= tree_count;
    }

    println!("{}", tree_product);
}