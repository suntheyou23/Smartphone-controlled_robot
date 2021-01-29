<?php
$data = $_GET['data'];
if($data=='a'){
    $fp = fopen("data.txt", "r");
    $contents = fread($fp, filesize($filename));
    print($contents);
    fclose($fp);
}
else
{
    $fp = fopen("data.txt", 'w');
    fwrite($fp,  $data);
    fclose($fp);
}
?>
