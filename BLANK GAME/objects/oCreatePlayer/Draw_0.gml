/// @description Insert description here
// You can write your code in this editor

object_set_visible(oCreatePlayer,true)
draw_self();
if (global.playersMade == true)
{
	object_set_visible(oCreatePlayer, false)
	instance_destroy(oCreatePlayer)

}






