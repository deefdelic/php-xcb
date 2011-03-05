<?php
$xcb = xcb_init();
echo "Initializing:".$xcb ."\n";
echo "Root Width: ".xcb_root_width_in_pixels($xcb)."\n";

$tmp = xcb_list_extensions($xcb);
var_export($tmp);


foreach($tmp as $name){
	//$info = xcb_query_extension($xcb, $name);
	//echo $name .":".$info['first_event']."\n";
	//var_export(xcb_query_extension($name));
}

//exit();

$newid = xcb_generate_id($xcb);
xcb_create_window($xcb, $newid, xcb_root_id($xcb), 200, 200, 10, 10, 6);
xcb_configure_window_events($xcb, $newid, array(1048576,  524288));
xcb_map_window($xcb, $newid);
xcb_flush($xcb);
sleep(1);
echo "Setting up Events:\n";
/**
 * Events:
 *  XCB_EVENT_MASK_NO_EVENT = 0,
    XCB_EVENT_MASK_KEY_PRESS = 1,
    XCB_EVENT_MASK_KEY_RELEASE = 2,
    XCB_EVENT_MASK_BUTTON_PRESS = 4,
    XCB_EVENT_MASK_BUTTON_RELEASE = 8,
    XCB_EVENT_MASK_ENTER_WINDOW = 16,
    XCB_EVENT_MASK_LEAVE_WINDOW = 32,
    XCB_EVENT_MASK_POINTER_MOTION = 64,
    XCB_EVENT_MASK_POINTER_MOTION_HINT = 128,
    XCB_EVENT_MASK_BUTTON_1_MOTION = 256,
    XCB_EVENT_MASK_BUTTON_2_MOTION = 512,
    XCB_EVENT_MASK_BUTTON_3_MOTION = 1024,
    XCB_EVENT_MASK_BUTTON_4_MOTION = 2048,
    XCB_EVENT_MASK_BUTTON_5_MOTION = 4096,
    XCB_EVENT_MASK_BUTTON_MOTION = 8192,
    XCB_EVENT_MASK_KEYMAP_STATE = 16384,
    XCB_EVENT_MASK_EXPOSURE = 32768,
    XCB_EVENT_MASK_VISIBILITY_CHANGE = 65536,
    XCB_EVENT_MASK_STRUCTURE_NOTIFY = 131072,
    XCB_EVENT_MASK_RESIZE_REDIRECT = 262144,
    XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY = 524288,
    XCB_EVENT_MASK_SUBSTRUCTURE_REDIRECT = 1048576,
    XCB_EVENT_MASK_FOCUS_CHANGE = 2097152,
    XCB_EVENT_MASK_PROPERTY_CHANGE = 4194304,
    XCB_EVENT_MASK_COLOR_MAP_CHANGE = 8388608,
    XCB_EVENT_MASK_OWNER_GRAB_BUTTON = 16777216
 */

//xcb_configure_window_events($newid, array(1048576, 131072, 524288));
//xcb_configure_window_events_root($newid);
xcb_flush($xcb);
echo "Lowering\n";
//xcb_configure_window_lower($newid);
//xcb_flush();
//sleep(1);
//echo "Raising\n";
//xcb_configure_window_raise($newid);
//xcb_flush();
//xcb_configure_window_size($newid, 300, 300);
//xcb_flush();
//sleep(1);
//var_export(xcb_get_geometry($newid));
echo "Test Configure: \n";
//typedef enum xcb_config_window_t {
//    XCB_CONFIG_WINDOW_X = 1,
//    XCB_CONFIG_WINDOW_Y = 2,
//    XCB_CONFIG_WINDOW_WIDTH = 4,
//    XCB_CONFIG_WINDOW_HEIGHT = 8,
//    XCB_CONFIG_WINDOW_BORDER_WIDTH = 16,
//    XCB_CONFIG_WINDOW_SIBLING = 32,
//    XCB_CONFIG_WINDOW_STACK_MODE = 64
//} xcb_config_window_t;
xcb_configure_window($xcb, $newid, array(1, 2, 4, 8), array(150, 150, 300, 300));
xcb_flush($xcb);
sleep(1);
var_export(xcb_get_geometry($xcb, $newid));

sleep(1);
//echo "testing by name\n";
//xcb_configure_window($newid, array("XCB_CONFIG_WINDOW_X", "XCB_CONFIG_WINDOW_Y", "XCB_CONFIG_WINDOW_Z"), array(300, 400));
//xcb_flush();
//sleep(4);

echo "Graphics Test:\n";

$intColorMap = xcb_get_default_colormap($xcb);
//xcb_create_colormap($intColorMap, $newid);
echo "Colormap: {$intColorMap}\n";
//$red = xcb_alloc_color($intColorMap, "red", 255, 0, 0);
$red = xcb_alloc_named_color($xcb, $intColorMap, "Red");
echo "Red: {$red}\n";

$gcid = xcb_generate_id($xcb);
echo "GC ID: {$gcid}\n";
xcb_create_gc($xcb, $newid, $gcid, array(4, 8), array($red, $red));

xcb_poly_fill_rectangle($xcb, $newid, $gcid, 10, 10, 20, 20);
xcb_flush($xcb);


echo "End Test\n";
while ($e = xcb_wait_for_event($xcb)){
	var_export($e);
}
?>
