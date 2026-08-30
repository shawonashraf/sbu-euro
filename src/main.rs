use std::env;
use std::io::{self, BufRead, Write};

const RATE: f32 = 0.017;

fn sbu_to_euro(sbus: f32) -> f32 {
    sbus * RATE
}

const BANNER: &str = r#"
  .   ____  ____  _   _  ____    _   _ ___  ____  ___ _____
 /|\ / ___)(  _ \( \_/ )(  _ \  ( \_/ ) __)(  _ \/ __|_   _)
(===)\___ \ ) __/ ) _ (  ) __/  ) _ ( ) _)  )   /\__ \ | |
 \|/ (___/ (_)   (_) (_)(_)    (_) (_)(___)(_)\_)(___/ |_|
 :: SBU to Euro Converter ::              (v0.1.0)
"#;

fn print_banner() {
    println!("\x1b[32m{BANNER}\x1b[0m");
}

fn print_conversion(sbus: f32) {
    println!("  {:>12.2} SBU  =  \x1b[33m€{:>10.2}\x1b[0m", sbus, sbu_to_euro(sbus));
}

fn usage() {
    println!("usage: sbu-euro [sbus]");
    println!("  sbu-euro 1000       convert 1000 SBU");
    println!("  sbu-euro            interactive mode");
}

fn parse_sbu(raw: &str) -> Option<f32> {
    raw.trim().parse::<f32>().ok().filter(|v| v.is_finite() && *v >= 0.0)
}

fn main() {
    print_banner();

    match env::args().nth(1) {
        Some(arg) => match parse_sbu(&arg) {
            Some(sbus) => print_conversion(sbus),
            None => {
                eprintln!("error: '{arg}' is not a non-negative number");
                usage();
                std::process::exit(1);
            }
        },
        None => {
            println!("Interactive mode — enter SBU amounts, 'q' to quit.");
            let stdin = io::stdin();
            loop {
                print!("sbu> ");
                io::stdout().flush().unwrap();
                let mut line = String::new();
                if stdin.lock().read_line(&mut line).unwrap_or(0) == 0 {
                    break;
                }
                let input = line.trim();
                if input.is_empty() {
                    continue;
                }
                if input == "q" || input == "quit" || input == "exit" {
                    break;
                }
                match parse_sbu(input) {
                    Some(sbus) => print_conversion(sbus),
                    None => println!("  invalid input: '{input}' (enter a number >= 0)"),
                }
            }
            println!("bye.");
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn converts_at_rate() {
        assert_eq!(sbu_to_euro(1000.0), 17.0);
        assert_eq!(sbu_to_euro(0.0), 0.0);
        assert!((sbu_to_euro(100.0) - 1.7).abs() < f32::EPSILON);
    }

    #[test]
    fn rejects_bad_input() {
        assert_eq!(parse_sbu("1000"), Some(1000.0));
        assert_eq!(parse_sbu("  42.5 "), Some(42.5));
        assert_eq!(parse_sbu("-1"), None);
        assert_eq!(parse_sbu("abc"), None);
        assert_eq!(parse_sbu("nan"), None);
        assert_eq!(parse_sbu("inf"), None);
    }
}
