fn sbu_to_euro(sbus: f32) -> f32 {
    sbus * 0.017
}



fn main() {
    let res = sbu_to_euro(1000.0);
    println!("{res}")
}
