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
            let field_id = field.split(':').collect::<Vec<&str>>()[0];
            if field_id != "cid" {
                passport_fields.insert(field_id);
            }
        } 

        if passport_fields == required_fields {
            valid_passports += 1;
        }
    }

    println!("{}", valid_passports);
}
