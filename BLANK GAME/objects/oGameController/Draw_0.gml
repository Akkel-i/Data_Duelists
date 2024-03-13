//global.NFC1 = 49230523
//global.NFC2 = 34389293
//Perusluku homma


	//show_debug_message("Aaaaaaaaaaaaaaaaaaa")
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

		if (array_length_1d(lines) >= 2)
{
    // Assign the values to separate variables
    global.NFC1 = lines[0];
    global.NFC2 = lines[1];

    // Trim or truncate NFC1 to 8 characters
    if (string_length(string_trim(global.NFC1)) != 8)
    {
        global.NFC1 = "43262363";
    }


    // Trim or truncate NFC2 to 8 characters
    if (string_length(string_trim(global.NFC2)) != 8)
    {
        global.NFC2 = "54302154";
    }
   

    // Display or use the values as needed
    show_debug_message("NFC1: " + global.NFC1);
    show_debug_message("NFC2: " + global.NFC2);
}

	}
}
else
{
    show_debug_message("Failed to connect to COM3 at 115200 baud. Error code: " + string(global.arduinoIndex));
}


if (array_length(global.NFC1array) == 0 && global.NFC1 != "")
{
// Iterate through the string in steps of 2
for (var i = 0; i < 4; i++) {
    // Extract two characters from the string and convert them to numbers
    var num1 = real(string_char_at(global.NFC1, i * 2 + 1));
    var num2 = real(string_char_at(global.NFC1, i * 2 + 2));

    // Calculate the sum of the pair and store it in the array
    global.NFC1array[i] = num1 + num2;
}
for (var i = 0; i < 4; i++) {
    // Extract two characters from the string and convert them to numbers
    var num3 = real(string_char_at(global.NFC2, i * 2 + 1));
    var num4 = real(string_char_at(global.NFC2, i * 2 + 2));

    // Calculate the sum of the pair and store it in the array
    global.NFC2array[i] = num3 + num4;
}


// Display the contents of the array for testing purposes
//for (var i = 0; i < 4; i++) {
//    show_debug_message("Sum " + string(i+1) + ": " + string(global.NFC1array[i]));
//}
//for (var i = 0; i < 4; i++) {
//    show_debug_message("Sum " + string(i+1) + ": " + string(global.NFC2array[i]));
//}
}

//createPlayer = function (statsArray)
//{
//		if (global.creation = 1)
//		{
//			object_set_sprite(oPlayerObject,playerSprite1)
//			 global.posWid = 100 
//			 global.posHei = 100
//		}
		
//		else
//		{
//		 object_set_sprite(oPlayerObject, playerSprite2)
//		  global.posWid = 200
//		  global.posHei = 100
//		}
//		object_set_sprite(oPlayerObject, playerSprite2)
//        // Create a new player instance or use an existing player object
//        var player = instance_create_layer(global.posWid, global.posHei,"Instances", oPlayerObject);

//        // Assign stats to the player
//        player.hp = statsArray[0] + 50;
//        player.atk = statsArray[1];
//        player.def = statsArray[2];
//        player.agi = statsArray[3];
		
		
		
//        // Additional initialization or handling if needed
//        // ...
		
//		global.creation ++;
//        // Return the created player instance
//        return player;

//}
populatePlayer = function (statsArray)
{
		var player
        // Create a new player instance or use an existing player object
if global.creation = 1
{
 player = randomObject
}
else
{
 player = randomObject2	
}
        // Assign stats to the player
        player.hp = statsArray[0] + 50;
        player.str = statsArray[1];
        player.def = statsArray[2];
        player.agi = statsArray[3];

        // Additional initialization or handling if needed
        // ...
		
		player.atk = player.str - player.def;
		
		if (player.atk < 1 )
		{
			player.atk = 1;
		}
        // Return the created player instance
        global.creation ++;
		return player;

}
// Example usage for creating players with NFC data
if (array_length(global.NFC1array) == 4 && array_length(global.NFC2array) == 4 && global.playersMade == false)
{
	var player1 = randomObject
	var player2 = randomObject2
     player1 = populatePlayer(global.NFC1array);
     player2 = populatePlayer(global.NFC2array);
	
	//show_debug_message(player1.hp)
	//show_debug_message(player2.def)
	
	global.playersMade = true

    //if (player2.str != "")
    //{
    //    player2.direction = 180;  // Set the direction for movement
    //    player2.speed = 2;       // Set the speed for movement
    //}

    // Additional logic or handling if needed
    // ...
}
battleTimer = function()
{
 var timer = 0;
 while (timer <= 1600000)
 {
	 timer ++;
	 //show_debug_message( timer);
 }
}
if (global.playersMade == true && global.gameVisib == false)
{
	layer_set_visible("Instances_1", false)
	layer_set_visible("Instances", true)
	global.gameVisib = true;
	battleTimer();
}

if (global.playersMade == true && global.gameOver == false && global.gameVisib == true)
{
    while (global.gameOver == false) {
        var hit1 = random(6) + 1;
        var hit2 = random(6) + 1;
		
      
        if (random(21) <= randomObject.agi) {  // Check if randomObject's agility allows for a critical hit
            randomObject2.hp = randomObject2.hp - ((hit1 + randomObject.atk) * 1.5);
            show_debug_message("Player 1 critical hit! " + string((hit1 + randomObject.atk) * 1.5) + " damage");
        } else  {   
            randomObject2.hp = randomObject2.hp - (hit1 + randomObject.atk);
            show_debug_message("Player 1 normal attack! " + string(randomObject.atk + hit1) + " damage");
        }

        if (random(21) <= randomObject2.agi) { // Check if randomObject2's agility allows for a critical hit
            randomObject.hp = randomObject.hp - ((hit2 + randomObject2.atk) * 1.5);
            show_debug_message("Player 2 critical hit! " + string((hit2 + randomObject2.atk) * 1.5) + " damage");
        } else {
            randomObject.hp = randomObject.hp - (hit2 + randomObject2.atk);
            show_debug_message("Player 2 normal attack! " + string(hit2 + randomObject2.atk) + " damage");
        }  

    show_debug_message("pelaajan 1 hp on: " + string(randomObject.hp));
    show_debug_message("pelaajan 2 hp on: " + string(randomObject2.hp));



    if (randomObject.hp <= 0) {
    show_debug_message("player2 win");
	layer_set_visible("Winner2", true);
     global.gameOver = true;
	 
	 //object_set_visible(randomObject,false)

    }
    else if  (randomObject2.hp <= 0) {
    show_debug_message("player1 win");
    
	layer_set_visible("Winner1", true);
	global.gameOver = true;
	//object_set_visible(randomObject2,false)
	
    };
	
//battleTimer();
  };
}

