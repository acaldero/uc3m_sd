<?php
header('Content-Type: text/event-stream');
header('Cache-Control: no-cache');

while (1) {
   echo "data: {'time': " . date('r') . "}\n\n";
   ob_flush(); flush();
   sleep(1);
}
?>
