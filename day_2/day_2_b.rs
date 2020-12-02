use std::fs::File;
use std::io::prelude::*;
use std::path::Path;

const INPUT_NAME: &str = "input_2.txt";

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

fn parse_password_info(password_info: &str) -> (usize, usize, char, &str) {
    let password_vec: Vec<&str> = password_info.split(": ").collect();
    let policy_vec: Vec<&str> = password_vec[0].split(' ').collect();
    let password: &str = password_vec[1];
    let location_vec: Vec<usize> = policy_vec[0].split('-').map(|x| x.parse::<usize>().unwrap()).collect();
    let policy_char: char = policy_vec[1].parse::<char>().unwrap();
    return (
        location_vec[0],
        location_vec[1],
        policy_char,
        password,
    );
}

fn check_password(loc0: usize, loc1: usize, policy_char: char, password: &str) -> bool {
    let password_chars: Vec<char> = password.chars().collect();
    if (password_chars.len() >= loc0 && password_chars[loc0 - 1] == policy_char) ^ (password_chars.len() >= loc1 && password_chars[loc1 - 1] == policy_char) {
        true
    } else {
        false
    }
}

fn main() {
    let file_contents: String = read_input_file();
    let input_seq = file_contents.split('\n');

    let mut correct_passwords: u64 = 0;
    for password_info in input_seq {
        let (loc0, loc1, policy_char, password) = parse_password_info(password_info);
        if check_password(loc0, loc1, policy_char, password) {
            correct_passwords += 1;
        }
    }
    println!("{}", correct_passwords);
}