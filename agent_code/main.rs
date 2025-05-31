use minreq;
use std::env;
use std::{thread, time};
use std::process::Command;

fn main(){
    let current_dir = env::current_dir().unwrap();
    let dir = current_dir.to_str().unwrap();
    let filename = "\\temp.ps1";
    
    //Concatenate file name to curent dir
    let script_file = dir.to_owned() + filename;

    let x  = 10;
    let y = 10;

    while x == y {
        let value = Command::new("powershell")
        .arg(format!("{}", script_file))
        .output()
        .expect("Failed to execute script");
    
        let output = String::from_utf8(value.stdout).unwrap();
        let mut lines = output.lines();
    
        let temp = lines.nth(2).expect("Couldn't conver").parse::<i32>().unwrap();

         println!("{}c", temp);


        if temp >= 50 {
            pwm_5();
         }

        if temp >= 60 {
            pwm_140();}

        if temp >= 70 {
            pwm_245();}

         let ten_millis = time::Duration::from_millis(2000);
         thread::sleep(ten_millis);
    }
}


fn pwm_5() -> Result<(), minreq::Error> {
   let o = minreq::get("http://192.168.4.1/5").send()?;
   Ok(()) 
}

fn pwm_140() -> Result<(), minreq::Error> {
   let o = minreq::get("http://192.168.4.1/140").send()?;
   Ok(()) 
}

fn pwm_245() -> Result<(), minreq::Error> {
   let o = minreq::get("http://192.168.4.1/245").send()?;
   Ok(()) 
}

