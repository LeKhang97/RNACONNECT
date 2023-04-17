<html>
<head>
<title>PHP Test</title>
</head>
<body>

<?php
  $code = $_POST["exampleFormControlTextarea1"];
  $delimiters = array(",", ";", "\n");
  $array = preg_split('/[' . preg_quote(implode('', $delimiters), '/') . ']/', $code);
  $str_array = implode(",", $array);
  echo "Successful command</br>";
  print_r($str_array);
  exec("make get_input_php");

  $result = exec("./get_input_php " . escapeshellarg($str_array));

  echo $result;
?>

</body>
</html>
