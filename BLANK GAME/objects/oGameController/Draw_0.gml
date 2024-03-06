//var readString = arduino_read_line()
////show_debug_message(readString)
////draw_self()
////draw_text(100,100, string_digits(readString))

	




//if (global.arduinoIndex != -1)
//{
   
//	var receiveData = arduino_read(global.arduinoIndex,30)
//		if (!is_undefined(receiveData))
//		{
//			show_debug_message(receiveData)
//		}
//}

var times = 0
if (times == 0)
{
global.NFC1 = ""
global.NFC2 = ""
}
if (global.arduinoIndex != -1)
{
    var receiveData = "";
    while (global.NFC1 = "" && global.NFC2 = "")
    {
        // Read a line from the serial port
        var line = arduino_read(global.arduinoIndex, 8);
        
        // Exit the loop if no more data is available
        if (is_undefined(line) || string_length(line) == 0)
            break;
        
        // Append the non-empty line to the received data
        receiveData += line;
    }
        // Check if there's non-empty data before processing
    if (string_length(receiveData) > 0)
    {
        // Split the received data into separate lines
        var lines = string_split(receiveData,"\n")
        
        // Ensure there are at least two lines
        if (array_length_1d(lines) >= 2)
        {
            // Assign the values to separate variables
			global.NFC1 = lines[0];
            global.NFC2 = lines[1];
            
            // Display or use the values as needed
            show_debug_message("NFC1: " + global.NFC1);
            show_debug_message("NFC2: " + global.NFC2);
			//if (global.NFC1 != "" && global.NFC2 != "")
			//{
			//	arduino_destroy()
			//}
		}

	}
}
else
{
    show_debug_message("Failed to connect to COM3 at 115200 baud. Error code: " + string(global.arduinoIndex));
}

times++

 //show_debug_message("Connected to COM3 at 115200 baud");
// testit mikä toimii,,
	//arduino_read_line(global.arduinoIndex)
//	arduino_read_text(global.arduinoIndex, 100)
	//arduino_read_line_new(global.arduinoIndex)
// mikä näistä toimii
    
    // Close the connection
	//if(arduino_connected())
	//{
	//	var recievedData = arduino_read_line_new(arduinoIndex)
	//	show_debug_message("Received: " + recievedData)
	//}
    //		if(arduino_connected(global.arduinoIndex))
	//{
	//	show_debug_message("jee")
		
	//}
	
	//else
	//{ 
	//	show_debug_message("pöö")
		
	//}