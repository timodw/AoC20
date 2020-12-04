use std::fs::File;
use std::io::prelude::*;
use std::path::Path;
use std::collections::HashSet;

const INPUT_NAME: &str = "input_4.txt";

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

fn check_number_range(number_str: &str, min: u64, max: u64) -> bool {
    let number = number_str.parse::<u64>().unwrap();
    number >= min && number <= max
}

fn main() {
    let file_contents: String = read_input_file();
    let input_seq = file_contents.split("\n\n");

    let mut required_fields = HashSet::new();
    required_fields.insert("byr");
    required_fields.insert("iyr");
    required_fields.insert("eyr");
    required_fields.insert("hgt");
    required_fields.insert("hcl");
    required_fields.insert("ecl");
    required_fields.insert("pid");

    let mut valid_passports: u64 = 0;
    
    for passport in input_seq {
        let passport_data = passport.split_whitespace();
        let mut passport_fields = HashSet::new();
        for field in passport_data {
            let field_parsed: Vec<&str> = field.split(':').collect();
            let field_id = field_parsed[0];
            let field_data = field_parsed[1];
            match field_id {
                "byr" => {
                    if check_number_range(field_data, 1920, 2020) {
                        passport_fields.insert(field_id);
                    }
                },
                "iyr" => {
                    if check_number_range(field_data, 2010, 2020) {
                        passport_fields.insert(field_id);
                    }
                },
                "eyr" => {
                    if check_number_range(field_data, 2020, 2030) {
                        passport_fields.insert(field_id);
                    }
                },
                "hgt" => {
                    if field_data.len() >= 4 {
                        let unit = &field_data[field_data.len() - 2..];
                        let number = &field_data[..field_data.len() - 2];
                        if unit == "cm" {
                            if check_number_range(number, 150, 193) {
                                passport_fields.insert(field_id);
                            }
                        } else if unit == "in" {
                            if check_number_range(number, 59, 76) {
                                passport_fields.insert(field_id);
                            }
                        }
                    }
                },
                "hcl" => {
                    if field_data.as_bytes()[0] == b'#' && field_data.len() == 7 {
                        let mut valid: bool = true;
                        let valid_chars = "0123456789abcdef".as_bytes(); 
                        for c in (&field_data[1..]).bytes() {
                            if !valid_chars.contains(&c) {
                                valid = false;
                                break;
                            }
                        }
                        if valid {
                            passport_fields.insert(field_id);
                        }
                    }
                },
                "ecl" => {
                    //amb blu brn gry grn hzl oth
                    let mut valid_eye_colors: HashSet<&str> = HashSet::new();
                    valid_eye_colors.insert("amb");
                    valid_eye_colors.insert("blu");
                    valid_eye_colors.insert("brn");
                    valid_eye_colors.insert("gry");
                    valid_eye_colors.insert("grn");
                    valid_eye_colors.insert("hzl");
                    valid_eye_colors.insert("oth");
                    
                    if valid_eye_colors.contains(field_data) {
                        passport_fields.insert(field_id);
                    }
                },
                "pid" => {
                    if field_data.len() == 9 && field_data.chars().all(char::is_numeric) {
                        passport_fields.insert(field_id);
                    }
                }
                _ => (),
            };
        } 

        if passport_fields == required_fields {
            valid_passports += 1;
        }
    }

    println!("{}", valid_passports);
}
