// #include <Wire.h>
// #include <Keypad.h>
// #include <LiquidCrystal.h>

// const byte rows = 4; // four rows
// const byte cols = 4; // three columns
// char keys[rows][cols] = {
//     {'7', '8', '9', '/'},
//     {'4', '5', '6', 'x'},
//     {'1', '2', '3', '-'},
//     {'#', '0', '=', '+'}};
// byte rowPins[rows] = {7, 6, 5, 4}; // connect to the row pinouts of the keypad
// byte colPins[cols] = {3, 2, 1, 0}; // connect to the column pinouts of the keypad
// Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

// LiquidCrystal lcd(50, 51, 45, 46, 47, 48);

// int led_pins[4] = {16, 17, 18, 19};

// uint8_t modes_time[4] = {3, 6, 6, 6};

// int current_mode = 0;
// bool is_washing = false;
// unsigned long start_time;
// unsigned long last_mode_time = 0;

// const uint8_t device_address = 80;
// // #define device_address 0b1010000
// const uint8_t memory_address = 0;

// void restore_modes(void);
// void write_to_mem(uint8_t data_size, uint8_t mem_addr, char *data);
// void read_from_mem(uint8_t data_size, uint8_t mem_addr, char *data);
// void update_lcd(int mode);
// void update_lcd_timer(unsigned long passed_time);
// void update_LEDs(int mode);

// void setup()
// {
//   for (int i = 0; i < 4; i++)
//   {
//     pinMode(led_pins[i], OUTPUT);
//   }

//   Serial3.begin(9600);
//   Wire.begin();
//   lcd.begin(16, 2);

//   restore_modes();
// }

// char pressed_key;
// int last_mode = -1;

// unsigned long elapsed_time = 0;
// bool process_stopped = false;
// bool mode_changed = false;
// void loop()
// {
//   while (true)
//   {
//     char key = keypad.getKey();

//     if (key != NO_KEY)
//     {
//       if (key == '/' && current_mode == 4)
//       {
//         is_washing = false;
//         last_mode = -1;
//         current_mode = 0;
//         update_LEDs(current_mode);
//         update_lcd(current_mode);
//         continue;
//       }

//       if (key >= '0' && key <= '9')
//       {
//         Serial3.println("yes");
//         pressed_key = key;
//         continue;
//       }

//       if (key == '#' && !is_washing)
//       {
//         if (pressed_key >= '0' && pressed_key <= '4')
//         {
//           mode_changed=true;
//           current_mode = (int)pressed_key - 48;

//           char data_to_store[1] = {pressed_key};
//           write_to_mem(1, memory_address, data_to_store);

//           update_LEDs(current_mode);
//           update_lcd(current_mode);
//         }
//       }
//       else if (key == 'x')
//       {
//         Serial3.println("try to change time of mode  " + String(current_mode));

//         modes_time[current_mode] = (int)pressed_key - 48;

//         char data_to_save[1] = {pressed_key};
//         uint8_t mem_addr = memory_address + current_mode + 1;

//         write_to_mem(1, mem_addr, data_to_save);
//       }
//       else if (key == '+')
//       {
//         is_washing = true;
//         last_mode = -1;
//       }
//       else if (key == '-' && is_washing)
//       {
//         // stop washing
//         is_washing = false;
//         last_mode = -1;

//         process_stopped = true;
//         // stopped = true;
//       }
//     }

//     if (is_washing && current_mode != 4)
//     {

//       if (last_mode != current_mode)
//       {
//         // each time that mode is changed
//         last_mode = current_mode;

//         start_time = millis();
//         Serial3.println("yessssir");

//         if (process_stopped && !mode_changed)
//         { // means process was stopped and now wants to start
//           process_stopped = false;
//           Serial3.println("--------------->");
//           Serial3.println("elapsed: "+String(elapsed_time)+" --- last_mode: "+String(last_mode_time));
//           last_mode_time = last_mode_time - elapsed_time*1000;
          
//           elapsed_time=0;
//         }
//         else
//         {
//           mode_changed=false;
//           Serial3.println("--------------->>>");
//           last_mode_time = modes_time[current_mode] * 1000;
//         }
//       }
//       else
//       {
//         unsigned long mills = millis();
//         unsigned long elapsed_time_mills = (mills - start_time) % 1000;
//         if (!(elapsed_time_mills >= 20 && elapsed_time_mills <= 980)) // update remaining time in the edges
//         {
//           // Serial3.println("----------------------->");
//           // Serial3.println("last mode is " + String(last_mode) + " --- curr mode  " + String(current_mode) + " --- mode time " + String(last_mode_time));
//           // Serial3.println("millis " + String(mills) + " ---  start_time" + String(start_time));
//           elapsed_time = (mills - start_time) / 1000;

//           update_lcd_timer(elapsed_time);
//         }

//         if (last_mode_time / 1000 - ((mills - start_time) / 1000) <= 0)
//         {
//           current_mode = (current_mode + 1) % 5;

//           char mode_char = current_mode + 48;

//           Serial3.println("mode char: ");
//           Serial3.println(mode_char);
//           Serial3.println("---------");
//           char data_to_store[1] = {mode_char};
//           write_to_mem(1, memory_address, data_to_store);

//           update_lcd(current_mode);
//           update_LEDs(current_mode);

//           if (current_mode == 4)
//           {
//             is_washing = false;
//           }
//         }
//       }
//     }
//   }
// }

// void restore_modes(void)
// {
//   char restored_modes[5];
//   read_from_mem(5, memory_address, restored_modes);
//   Serial3.println("restoring");
//   Serial3.println(restored_modes[0]);

//   if (restored_modes[0] >= '0' && restored_modes[0] <= '4')
//   {
//     current_mode = restored_modes[0] - 48;
//   }

//   for (int i = 0; i <= 3; i++)
//   {

//     if (restored_modes[i + 1] > '0' && restored_modes[i + 1] <= '9')
//     {
//       modes_time[i] = (uint8_t)restored_modes[i + 1] - 48;
//     }
//   }

//   update_lcd(current_mode);
//   update_LEDs(current_mode);
// }

// void write_to_mem(uint8_t data_size, uint8_t mem_addr, char *data)
// {
//   Wire.beginTransmission(device_address);
//   Wire.write((uint8_t)((mem_addr & 0xFF00) >> 8));
//   Wire.write((uint8_t)((mem_addr & 0x00FF) >> 0));

//   for (int i = 0; i < data_size; i++)
//   {
//     Serial3.println("writing...: ");
//     Serial3.println(data[i]);

//     Serial3.println("-----==-----");
//     uint8_t d = (uint8_t)data[i] - 48;
//     Serial3.println("------------");
//     Serial3.println(d);
//     Wire.write(d);
//     delay(50);
//   }

//   Wire.endTransmission();
//   delay(50);
// }
// void read_from_mem(uint8_t data_size, uint8_t mem_addr, char *data)
// {
//   Wire.beginTransmission(device_address);
//   Wire.write((uint8_t)((mem_addr & 0xFF00) >> 8));
//   Wire.write((uint8_t)((mem_addr & 0x00FF) >> 0));
//   Wire.endTransmission();

//   Wire.requestFrom(device_address, data_size);
//   for (int i = 0; i < data_size; i++)
//   {
//     data[i] = Wire.read() + 48;
//     Serial3.println("reading...: ");
//     Serial3.println(data[i]);
//     Serial3.println("--------------");
//   }
// }

// void update_LEDs(int mode)
// {
//   if (mode == 4)
//   {
//     for (int i = 0; i < 4; i++)
//     {
//       digitalWrite(led_pins[i], HIGH);
//     }
//   }
//   else
//   {
//     // turn off all leds except current mode
//     for (int i = 0; i < 4; i++)
//     {
//       digitalWrite(led_pins[i], LOW);
//     }
//     digitalWrite(led_pins[mode], HIGH);
//   }
// }

// void update_lcd(int mode)
// {

//   lcd.clear();
//   switch (mode)
//   {
//   case 0:
//     lcd.print("pre_wash");
//     break;
//   case 1:
//     lcd.print("detergent wash");
//     break;
//   case 2:
//     lcd.print("wash with water");
//     break;
//   case 3:
//     lcd.print("drying");
//     break;
//   case 4:
//     lcd.print("finished");
//     break;
//   }
// }

// void update_lcd_timer(unsigned long passed_time)
// {
//   update_lcd(current_mode);

//   lcd.setCursor(0, 2);
//   String time_to_show = String(last_mode_time / 1000 - passed_time);
//   lcd.print("remaining:" + time_to_show + " s");
// }
























