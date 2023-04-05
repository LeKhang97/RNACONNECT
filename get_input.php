<html>
<head>
<title>PHP Test</title>
</head>
<body>

<?php
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
  $code = $_POST['code'];
  // do something with $code, such as write it to a file
} ?>

</body>
</html>