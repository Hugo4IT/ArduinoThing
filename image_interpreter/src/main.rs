use std::{io, time::Duration};

use minifb::{Key, KeyRepeat, Menu, Window, WindowOptions, MENU_KEY_ALT};

const SCALE: usize = 1;
const WIDTH: usize = 160;
const HEIGHT: usize = 120;

const MENU_FB_RESET: usize = 1;

// fn rgb565_to_rgb888(r5g3: u8, g3b5: u8) -> (u8, u8, u8) {
//     (
//         r5g3 & 0b11111000,
//         ((r5g3 & 0b00000111) << 5) | ((g3b5 & 0b11100000) >> 3),
//         (g3b5 & 0b00011111) << 3,
//     )
// }

// Why is this camera such a bitch
// fn yuv_to_rgb(y: u8, u: u8, v: u8) -> (u8, u8, u8) {
//     /*
//         R = max(0, min(255, 1.164(Y - 16) + 1.596(Cr - 128)));
//         G = max(0, min(255, 1.164(Y - 16) - 0.813(Cr - 128) - 0.391(Cb - 128)));
//         B = max(0, min(255, 1.164(Y - 16) + 2.018(Cr - 128)));
//     */
//     let conv_y = 1.164 * (y as f64 - 16.0);
//     let r = conv_y + (1.596 * (u as f64 - 128.0));
//     let g = conv_y - (0.813 * (u as f64 - 128.0) - (0.391 * (v as f64 - 128.0)));
//     let b = conv_y + (2.018 * (u as f64 - 128.0));

//     (
//         r.clamp(0.0, 255.0) as u8,
//         g.clamp(0.0, 255.0) as u8,
//         b.clamp(0.0, 255.0) as u8,
//     )
// }

fn main() {
    let ports = serialport::available_ports().expect("No ports found!");
    for (i, port) in ports.iter().enumerate() {
        println!("{}: {}", i, port.port_name);
    }

    println!("Select a port (only the number):");

    let mut input = String::new();
    let stdin = io::stdin();
    stdin.read_line(&mut input).unwrap();

    let selection = usize::from_str_radix(input.trim(), 10).expect("Please only use numbers!");
    let mut port = serialport::new(&ports.get(selection).unwrap().port_name, 500000)
        .open()
        .expect("Failed to open port!");

    let mut framebuffer = vec![0; WIDTH * HEIGHT];
    let mut window = Window::new(
        "Camera output",
        WIDTH * SCALE,
        HEIGHT * SCALE,
        WindowOptions::default(),
    )
    .unwrap();
    window.limit_update_rate(Some(Duration::from_secs_f64(0.0166667)));
    window.update_with_buffer(&framebuffer, WIDTH, HEIGHT).unwrap();

    let mut fb_menu = Menu::new("FrameBuffer").unwrap();
    fb_menu
        .add_item("Reset position.", MENU_FB_RESET)
        .shortcut(Key::R, MENU_KEY_ALT)
        .enabled(true)
        .build();
    window.add_menu(&fb_menu);

    let mut pos = 0;

    let mut serial_buffer: Vec<u8> = vec![0; WIDTH * HEIGHT];
    while window.is_open() && !window.is_key_pressed(Key::Escape, KeyRepeat::No) {
        match port.read(&mut serial_buffer[..]) {
            Ok(n) => {
                for byte in serial_buffer.get(0..n).unwrap().iter() {
                    if (byte & 0x01) == 0x01 {
                        match byte >> 1 {
                            1 => pos = 0,
                            _ => ()
                        }
                    } else {
                        framebuffer[pos] = u32::from_be_bytes([0, *byte, *byte, *byte]);
                        pos += 1;
                        if pos == WIDTH * HEIGHT {
                            port.write(b"F").unwrap();
                            pos = 0
                        }
                    }
                }
            }
            Err(e) => match e.kind() {
                io::ErrorKind::TimedOut => (),
                _ => panic!("Error: {:?}", e),
            },
        }

        if let Some(id) = window.is_menu_pressed() {
            match id {
                MENU_FB_RESET => {
                    pos = 0;
                    framebuffer = vec![0; WIDTH * HEIGHT];
                }
                _ => (),
            }
        }

        window
            .update_with_buffer(&framebuffer, WIDTH, HEIGHT)
            .unwrap();
    }
}
